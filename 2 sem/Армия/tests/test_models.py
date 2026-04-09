from __future__ import annotations

import unittest

from army.models import Army, Base, Rank, Soldier, Specialization, Vehicle


class SoldierModelTestCase(unittest.TestCase):
    def test_full_name(self) -> None:
        soldier = Soldier(
            id=1,
            last_name="Иванов",
            first_name="Иван",
            patronymic="Иванович",
            rank=Rank.PRIVATE,
            specialization=Specialization.INFANTRY,
        )
        self.assertEqual(soldier.full_name, "Иванов Иван Иванович")

    def test_train_increases_experience(self) -> None:
        soldier = Soldier(
            id=1,
            last_name="Петров",
            first_name="Пётр",
            patronymic="Петрович",
            rank=Rank.PRIVATE,
            specialization=Specialization.ARTILLERY,
        )
        soldier.train(15)
        self.assertEqual(soldier.experience, 15)

    def test_train_caps_at_100(self) -> None:
        soldier = Soldier(
            id=1,
            last_name="Сидоров",
            first_name="Сидор",
            patronymic="Сидорович",
            rank=Rank.PRIVATE,
            specialization=Specialization.MEDIC,
            experience=95,
        )
        soldier.train(20)
        self.assertEqual(soldier.experience, 100)

    def test_train_negative_raises(self) -> None:
        soldier = Soldier(
            id=1,
            last_name="Козлов",
            first_name="Андрей",
            patronymic="Игоревич",
            rank=Rank.PRIVATE,
            specialization=Specialization.ENGINEER,
        )
        with self.assertRaises(ValueError):
            soldier.train(-1)


class VehicleModelTestCase(unittest.TestCase):
    def test_damage_reduces_condition(self) -> None:
        vehicle = Vehicle(id=1, name="T-90", type="tank")
        vehicle.damage(30)
        self.assertEqual(vehicle.condition, 70)
        self.assertTrue(vehicle.operational)

    def test_damage_to_zero_disables_vehicle(self) -> None:
        vehicle = Vehicle(id=1, name="T-90", type="tank")
        vehicle.damage(100)
        self.assertEqual(vehicle.condition, 0)
        self.assertFalse(vehicle.operational)

    def test_damage_negative_raises(self) -> None:
        vehicle = Vehicle(id=1, name="T-90", type="tank")
        with self.assertRaises(ValueError):
            vehicle.damage(-5)

    def test_repair_increases_condition(self) -> None:
        vehicle = Vehicle(id=1, name="T-90", type="tank", condition=50)
        vehicle.repair(20)
        self.assertEqual(vehicle.condition, 70)
        self.assertTrue(vehicle.operational)

    def test_repair_caps_at_100(self) -> None:
        vehicle = Vehicle(id=1, name="T-90", type="tank", condition=90)
        vehicle.repair(30)
        self.assertEqual(vehicle.condition, 100)

    def test_repair_negative_raises(self) -> None:
        vehicle = Vehicle(id=1, name="T-90", type="tank")
        with self.assertRaises(ValueError):
            vehicle.repair(-10)


class ArmyModelTestCase(unittest.TestCase):
    def test_add_base_and_totals(self) -> None:
        army = Army(name="Army 1")
        base = Base(name="Alpha", location="North")
        soldier = Soldier(
            id=1,
            last_name="Иванов",
            first_name="Иван",
            patronymic="Иванович",
            rank=Rank.PRIVATE,
            specialization=Specialization.INFANTRY,
        )
        vehicle = Vehicle(id=1, name="T-90", type="tank")

        base.add_soldier(soldier)
        base.add_vehicle(vehicle)
        army.add_base(base)

        self.assertEqual(army.total_soldiers(), 1)
        self.assertEqual(army.total_vehicles(), 1)
        self.assertEqual(len(army.all_soldiers()), 1)
        self.assertEqual(len(army.all_vehicles()), 1)

    def test_total_soldiers_counts_only_alive(self) -> None:
        army = Army(name="Army 1")
        base = Base(name="Alpha", location="North")

        alive_soldier = Soldier(
            id=1,
            last_name="Иванов",
            first_name="Иван",
            patronymic="Иванович",
            rank=Rank.PRIVATE,
            specialization=Specialization.INFANTRY,
            alive=True,
        )
        dead_soldier = Soldier(
            id=2,
            last_name="Петров",
            first_name="Пётр",
            patronymic="Петрович",
            rank=Rank.PRIVATE,
            specialization=Specialization.ARTILLERY,
            alive=False,
        )

        base.add_soldier(alive_soldier)
        base.add_soldier(dead_soldier)
        army.add_base(base)

        self.assertEqual(army.total_soldiers(), 1)
        self.assertEqual(len(army.all_soldiers()), 1)
        self.assertEqual(len(army.all_soldiers(alive_only=False)), 2)
