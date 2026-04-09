from __future__ import annotations

import unittest
from unittest.mock import patch

from army.exceptions import ArmyError
from army.models import Rank, Specialization
from army.world import World


class WorldTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self.world = World()

        self.world.create_army("Blue")
        self.world.create_army("Red")

        self.world.create_base("Alpha", "North")
        self.world.create_base("Bravo", "South")

        self.world.add_base_to_army("Blue", "Alpha")
        self.world.add_base_to_army("Red", "Bravo")

        self.world.hire_soldier(
            base_name="Alpha",
            last_name="Иванов",
            first_name="Иван",
            patronymic="Иванович",
            rank=Rank.PRIVATE,
            specialization=Specialization.INFANTRY,
        )
        self.world.hire_soldier(
            base_name="Bravo",
            last_name="Петров",
            first_name="Пётр",
            patronymic="Петрович",
            rank=Rank.PRIVATE,
            specialization=Specialization.ARTILLERY,
        )

    def test_create_army_success(self) -> None:
        army = self.world.create_army("Green")
        self.assertEqual(army.name, "Green")

    def test_create_army_duplicate_raises(self) -> None:
        with self.assertRaises(ArmyError):
            self.world.create_army("Blue")

    def test_create_base_success(self) -> None:
        base = self.world.create_base("Charlie", "West")
        self.assertEqual(base.name, "Charlie")
        self.assertEqual(base.location, "West")

    def test_create_base_duplicate_raises(self) -> None:
        with self.assertRaises(ArmyError):
            self.world.create_base("Alpha", "Elsewhere")

    def test_get_army_not_found(self) -> None:
        with self.assertRaises(ArmyError):
            self.world.get_army("Unknown")

    def test_get_base_not_found(self) -> None:
        with self.assertRaises(ArmyError):
            self.world.get_base("Unknown")

    def test_add_base_to_army(self) -> None:
        self.world.create_base("Charlie", "West")
        self.world.add_base_to_army("Blue", "Charlie")
        blue = self.world.get_army("Blue")
        self.assertEqual(len(blue.bases), 2)

    def test_hire_soldier(self) -> None:
        soldier = self.world.hire_soldier(
            base_name="Alpha",
            last_name="Сидоров",
            first_name="Сидор",
            patronymic="Сидорович",
            rank=Rank.SERGEANT,
            specialization=Specialization.ENGINEER,
        )
        self.assertEqual(soldier.rank, Rank.SERGEANT)
        self.assertEqual(soldier.specialization, Specialization.ENGINEER)

    def test_buy_vehicle(self) -> None:
        vehicle = self.world.buy_vehicle("Alpha", "T-90", "tank")
        self.assertEqual(vehicle.name, "T-90")
        self.assertEqual(vehicle.type, "tank")

    def test_find_soldier_success(self) -> None:
        soldier = self.world.find_soldier(1)
        self.assertEqual(soldier.id, 1)

    def test_find_soldier_not_found(self) -> None:
        with self.assertRaises(ArmyError):
            self.world.find_soldier(999)

    @patch("army.world.random.choice")
    def test_mobilize_creates_soldiers(self, mock_choice) -> None:
        mock_choice.return_value = Specialization.MEDIC
        created = self.world.mobilize(
            "Alpha",
            [
                ("Смирнов", "Алексей", "Игоревич"),
                ("Козлов", "Максим", "Олегович"),
            ],
        )
        self.assertEqual(len(created), 2)
        self.assertEqual(created[0].rank, Rank.PRIVATE)
        self.assertEqual(created[0].specialization, Specialization.MEDIC)

    def test_train_increases_experience(self) -> None:
        trained = self.world.train("Blue", amount=20)
        self.assertEqual(trained, 1)
        blue = self.world.get_army("Blue")
        self.assertEqual(blue.all_soldiers()[0].experience, 20)

    def test_supply_adds_resources_and_repairs(self) -> None:
        self.world.buy_vehicle("Alpha", "T-90", "tank")
        blue = self.world.get_army("Blue")
        vehicle = blue.all_vehicles()[0]
        vehicle.damage(50)

        result = self.world.supply("Blue")

        self.assertEqual(result["army"], "Blue")
        self.assertGreater(result["supplies_added"], 0)
        self.assertGreaterEqual(result["vehicles_repaired"], 1)
        self.assertGreater(vehicle.condition, 50)

    def test_secure_uses_supplies(self) -> None:
        blue = self.world.get_army("Blue")
        base = blue.bases[0]
        old_security = base.security_level
        old_supplies = base.supplies

        result = self.world.secure("Blue")

        self.assertEqual(result["army"], "Blue")
        self.assertEqual(result["upgraded_bases"], 1)
        self.assertEqual(base.security_level, old_security + 1)
        self.assertEqual(base.supplies, old_supplies - 30)

    def test_secure_without_supplies(self) -> None:
        blue = self.world.get_army("Blue")
        base = blue.bases[0]
        base.supplies = 0

        result = self.world.secure("Blue")

        self.assertEqual(result["upgraded_bases"], 0)
        self.assertEqual(base.security_level, 1)

    @patch("army.world.random.randint")
    @patch("army.world.random.sample")
    def test_battle_attacker_wins_and_defender_loses_soldier(
        self,
        mock_sample,
        mock_randint,
    ) -> None:
        defender = self.world.get_army("Red")
        defender_soldier = defender.all_soldiers()[0]

        mock_randint.side_effect = [5, -5, 1, 0]

        mock_sample.side_effect = [
            [defender_soldier],
            [],
        ]

        result = self.world.battle("Blue", "Red")

        self.assertEqual(result["outcome"], "победа атакующего")
        self.assertEqual(result["defender_losses"], 1)
        self.assertFalse(defender_soldier.alive)

    def test_battle_without_soldiers_raises(self) -> None:
        empty_world = World()
        empty_world.create_army("A")
        empty_world.create_army("B")
        empty_world.create_base("BaseA", "X")
        empty_world.create_base("BaseB", "Y")
        empty_world.add_base_to_army("A", "BaseA")
        empty_world.add_base_to_army("B", "BaseB")

        with self.assertRaises(ArmyError):
            empty_world.battle("A", "B")
