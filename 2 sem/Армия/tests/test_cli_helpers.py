from __future__ import annotations

import unittest
from unittest.mock import patch

from army.exceptions import ArmyError
from army.models import Rank, Specialization
from cli import CommandProcessor


class CliHelpersTestCase(unittest.TestCase):
    def setUp(self) -> None:
        self.cli = CommandProcessor()

    def test_handle_help(self) -> None:
        with patch("builtins.print") as mock_print:
            self.cli.handle_help([])
        self.assertTrue(mock_print.called)

    def test_handle_list_armies(self) -> None:
        with patch("builtins.print") as mock_print:
            self.cli.handle_list_armies([])
        self.assertTrue(mock_print.called)

    def test_handle_list_bases_empty(self) -> None:
        with patch("builtins.print") as mock_print:
            self.cli.handle_list_bases([])
        mock_print.assert_called_with("Баз пока нет.")

    def test_choose_army_valid(self) -> None:
        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["1"]):
                result = self.cli._choose_army()
        self.assertEqual(result, "Army 1")

    def test_choose_army_invalid(self) -> None:
        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["9"]):
                with self.assertRaises(ValueError):
                    self.cli._choose_army()

    def test_handle_create_army_with_name(self) -> None:
        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["Test Army"]):
                self.cli.handle_create_army([])
        self.assertIn("Test Army", self.cli.world.armies)

    def test_handle_create_army_default_name(self) -> None:
        with patch("builtins.print"):
            with patch("builtins.input", side_effect=[""]):
                self.cli.handle_create_army([])
        self.assertIn("Army 2", self.cli.world.armies)

    def test_handle_create_base(self) -> None:
        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["Base1", "Minsk", "1"]):
                self.cli.handle_create_base([])
        self.assertIn("Base1", self.cli.world.bases)
        army = self.cli.world.get_army("Army 1")
        self.assertEqual(len(army.bases), 1)

    def test_choose_base_from_army_without_bases(self) -> None:
        with patch("builtins.print"):
            with self.assertRaises(ArmyError):
                self.cli._choose_base_from_army("Army 1")

    def test_choose_base_from_army_valid(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")

        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["1"]):
                result = self.cli._choose_base_from_army("Army 1")

        self.assertEqual(result, "Base1")

    def test_choose_base_from_army_invalid(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")

        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["2"]):
                with self.assertRaises(ValueError):
                    self.cli._choose_base_from_army("Army 1")

    def test_handle_hire_soldier(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")

        with patch("builtins.print"):
            with patch(
                "builtins.input",
                side_effect=[
                    "1",
                    "1",
                    "Иванов",
                    "Иван",
                    "Иванович",
                    "private",
                    "infantry",
                ],
            ):
                self.cli.handle_hire_soldier([])

        army = self.cli.world.get_army("Army 1")
        self.assertEqual(army.total_soldiers(), 1)

    def test_handle_hire_soldier_invalid_rank(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")

        with patch("builtins.print"):
            with patch(
                "builtins.input",
                side_effect=[
                    "1",
                    "1",
                    "Иванов",
                    "Иван",
                    "Иванович",
                    "wrong_rank",
                ],
            ):
                with self.assertRaises(ValueError):
                    self.cli.handle_hire_soldier([])

    def test_handle_hire_soldier_invalid_specialization(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")

        with patch("builtins.print"):
            with patch(
                "builtins.input",
                side_effect=[
                    "1",
                    "1",
                    "Иванов",
                    "Иван",
                    "Иванович",
                    "private",
                    "wrong_spec",
                ],
            ):
                with self.assertRaises(ValueError):
                    self.cli.handle_hire_soldier([])

    def test_handle_mobilize(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")

        with patch("builtins.print"):
            with patch(
                "builtins.input",
                side_effect=[
                    "1",
                    "1",
                    "2",
                    "Петров",
                    "Пётр",
                    "Петрович",
                    "Сидоров",
                    "Сидор",
                    "",
                ],
            ):
                self.cli.handle_mobilize([])

        army = self.cli.world.get_army("Army 1")
        self.assertEqual(army.total_soldiers(), 2)

    def test_handle_buy_vehicle(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")

        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["1", "1", "T-90", "tank"]):
                self.cli.handle_buy_vehicle([])

        army = self.cli.world.get_army("Army 1")
        self.assertEqual(army.total_vehicles(), 1)

    def test_handle_set_commander(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")

        self.cli.world.hire_soldier(
            base_name="Base1",
            last_name="Иванов",
            first_name="Иван",
            patronymic="Иванович",
            rank=Rank.CAPTAIN,
            specialization=Specialization.INFANTRY,
        )

        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["1", "1"]):
                self.cli.handle_set_commander([])

        army = self.cli.world.get_army("Army 1")
        self.assertIsNotNone(army.commander)
        self.assertEqual(army.commander.id, 1)

    def test_handle_report_army_empty(self) -> None:
        with patch("builtins.print") as mock_print:
            with patch("builtins.input", side_effect=["1"]):
                self.cli.handle_report_army([])
        self.assertTrue(mock_print.called)

    def test_handle_train(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")
        self.cli.world.hire_soldier(
            base_name="Base1",
            last_name="Иванов",
            first_name="Иван",
            patronymic="Иванович",
            rank=Rank.PRIVATE,
            specialization=Specialization.INFANTRY,
        )

        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["1"]):
                self.cli.handle_train([])

        soldier = self.cli.world.get_army("Army 1").all_soldiers()[0]
        self.assertGreater(soldier.experience, 0)

    def test_handle_supply(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")
        self.cli.world.buy_vehicle("Base1", "T-90", "tank")
        vehicle = self.cli.world.get_army("Army 1").all_vehicles()[0]
        vehicle.damage(40)

        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["1"]):
                self.cli.handle_supply([])

        self.assertGreaterEqual(vehicle.condition, 60)

    def test_handle_secure(self) -> None:
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.add_base_to_army("Army 1", "Base1")
        base = self.cli.world.get_army("Army 1").bases[0]
        old_security = base.security_level

        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["1"]):
                self.cli.handle_secure([])

        self.assertEqual(base.security_level, old_security + 1)

    def test_create_second_army(self) -> None:
        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["Red"]):
                self.cli.handle_create_army([])

        self.assertIn("Red", self.cli.world.armies)

    def test_handle_attack_same_army_raises(self) -> None:
        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["1", "1"]):
                with self.assertRaises(ValueError):
                    self.cli.handle_attack([])

    def test_handle_defend_same_army_raises(self) -> None:
        with patch("builtins.print"):
            with patch("builtins.input", side_effect=["1", "1"]):
                with self.assertRaises(ValueError):
                    self.cli.handle_defend([])

    def test_handle_attack_success(self) -> None:
        self.cli.world.create_army("Red")
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.create_base("Base2", "Grodno")
        self.cli.world.add_base_to_army("Army 1", "Base1")
        self.cli.world.add_base_to_army("Red", "Base2")

        self.cli.world.hire_soldier(
            "Base1",
            "Иванов",
            "Иван",
            "Иванович",
            Rank.PRIVATE,
            Specialization.INFANTRY,
        )
        self.cli.world.hire_soldier(
            "Base2",
            "Петров",
            "Пётр",
            "Петрович",
            Rank.PRIVATE,
            Specialization.ARTILLERY,
        )

        with patch("builtins.print") as mock_print:
            with patch("builtins.input", side_effect=["1", "2"]):
                self.cli.handle_attack([])

        self.assertTrue(mock_print.called)

    def test_handle_defend_success(self) -> None:
        self.cli.world.create_army("Red")
        self.cli.world.create_base("Base1", "Minsk")
        self.cli.world.create_base("Base2", "Grodno")
        self.cli.world.add_base_to_army("Army 1", "Base1")
        self.cli.world.add_base_to_army("Red", "Base2")

        self.cli.world.hire_soldier(
            "Base1",
            "Иванов",
            "Иван",
            "Иванович",
            Rank.PRIVATE,
            Specialization.INFANTRY,
        )
        self.cli.world.hire_soldier(
            "Base2",
            "Петров",
            "Пётр",
            "Петрович",
            Rank.PRIVATE,
            Specialization.ARTILLERY,
        )

        with patch("builtins.print") as mock_print:
            with patch("builtins.input", side_effect=["2", "1"]):
                self.cli.handle_defend([])

        self.assertTrue(mock_print.called)

    def test_handle_exit(self) -> None:
        with patch("builtins.print"):
            self.cli.handle_exit([])
        self.assertFalse(self.cli._running)


if __name__ == "__main__":
    unittest.main()
