from __future__ import annotations

import random
from dataclasses import dataclass, field
from typing import Dict, List, Tuple

from .exceptions import ArmyError
from .models import Army, Base, Rank, Soldier, Specialization, Vehicle


@dataclass
class World:

    bases: Dict[str, Base] = field(default_factory=dict)
    armies: Dict[str, Army] = field(default_factory=dict)
    _next_soldier_id: int = 1
    _next_vehicle_id: int = 1

    def create_army(self, name: str) -> Army:
        if name in self.armies:
            raise ArmyError(f"Армия '{name}' уже существует")
        army = Army(name=name)
        self.armies[name] = army
        return army

    def list_armies(self) -> List[Army]:
        return list(self.armies.values())

    def create_base(self, name: str, location: str) -> Base:
        if name in self.bases:
            raise ArmyError(f"База '{name}' уже существует")
        base = Base(name=name, location=location)
        self.bases[name] = base
        return base

    def get_army(self, name: str) -> Army:
        try:
            return self.armies[name]
        except KeyError as exc:
            raise ArmyError(f"Армия '{name}' не найдена") from exc

    def get_base(self, name: str) -> Base:
        try:
            return self.bases[name]
        except KeyError as exc:
            raise ArmyError(f"База '{name}' не найдена") from exc

    def add_base_to_army(self, army_name: str, base_name: str) -> None:
        army = self.get_army(army_name)
        base = self.get_base(base_name)
        army.add_base(base)

    def hire_soldier(
        self,
        base_name: str,
        last_name: str,
        first_name: str,
        patronymic: str,
        rank: Rank,
        specialization: Specialization,
    ) -> Soldier:
        base = self.get_base(base_name)
        soldier = Soldier(
            id=self._next_soldier_id,
            last_name=last_name,
            first_name=first_name,
            patronymic=patronymic,
            rank=rank,
            specialization=specialization,
        )
        self._next_soldier_id += 1
        base.add_soldier(soldier)
        return soldier

    def buy_vehicle(self, base_name: str, name: str, type_: str) -> Vehicle:
        base = self.get_base(base_name)
        vehicle = Vehicle(
            id=self._next_vehicle_id,
            name=name,
            type=type_,
        )
        self._next_vehicle_id += 1
        base.add_vehicle(vehicle)
        return vehicle

    def find_soldier(self, soldier_id: int) -> Soldier:
        for base in self.bases.values():
            for soldier in base.soldiers:
                if soldier.id == soldier_id:
                    return soldier
        raise ArmyError(f"Солдат с id={soldier_id} не найден")

    def mobilize(
        self,
        base_name: str,
        fio_list: List[Tuple[str, str, str]],
    ) -> List[Soldier]:
        created: List[Soldier] = []
        all_specializations = list(Specialization)

        for last_name, first_name, patronymic in fio_list:
            random_spec = random.choice(all_specializations)
            soldier = self.hire_soldier(
                base_name=base_name,
                last_name=last_name,
                first_name=first_name,
                patronymic=patronymic,
                rank=Rank.PRIVATE,  # самый низкий ранг
                specialization=random_spec,
            )
            created.append(soldier)
        return created

    def train(self, army_name: str, amount: int = 10) -> int:
        army = self.get_army(army_name)
        trained = 0
        for soldier in army.all_soldiers():
            soldier.train(amount)
            trained += 1
        return trained

    def supply(self, army_name: str) -> dict:
        army = self.get_army(army_name)

        total_added_supplies = 0
        total_repaired = 0

        for base in army.bases:
            added = 40
            base.supplies += added
            total_added_supplies += added

            for vehicle in base.vehicles:
                if base.supplies < 20:
                    break

                if vehicle.condition < 100:
                    vehicle.repair(25)
                    base.supplies -= 20
                    total_repaired += 1

        return {
            "army": army.name,
            "supplies_added": total_added_supplies,
            "vehicles_repaired": total_repaired,
        }

    def secure(self, army_name: str) -> dict:
        army = self.get_army(army_name)

        upgraded_bases = 0

        for base in army.bases:
            # Усиление охраны требует ресурсов
            if base.supplies >= 30:
                base.supplies -= 30
                base.security_level += 1
                upgraded_bases += 1

        return {
            "army": army.name,
            "upgraded_bases": upgraded_bases,
        }

    def battle(self, attacker_name: str, defender_name: str) -> dict:
        attacker = self.get_army(attacker_name)
        defender = self.get_army(defender_name)

        if not attacker.all_soldiers() or not defender.all_soldiers():
            raise ArmyError("Обе армии должны иметь солдат для боя")

        attack_power = (
            sum(1 + s.experience // 20 for s in attacker.all_soldiers())
            + len(attacker.all_vehicles()) * 2
        )
        defense_modifier = sum(b.security_level for b in defender.bases)
        defense_power = (
            sum(1 + s.experience // 20 for s in defender.all_soldiers())
            + len(defender.all_vehicles()) * 2
            + defense_modifier
        )

        attack_score = attack_power + random.randint(-5, 5)
        defense_score = defense_power + random.randint(-5, 5)

        result = {
            "attacker": attacker_name,
            "defender": defender_name,
            "outcome": "",
            "attacker_losses": 0,
            "defender_losses": 0,
            "destroyed_vehicles": 0,
        }

        if attack_score > defense_score:
            loser = defender
            result["outcome"] = "победа атакующего"
        else:
            loser = attacker
            result["outcome"] = "защита удержана"

        loser_soldiers = [s for s in loser.all_soldiers() if s.alive]
        loser_vehicles = [v for v in loser.all_vehicles() if v.operational]

        if loser_soldiers:
            soldiers_lost = random.randint(
                1,
                max(1, len(loser_soldiers) // 3),
            )
        else:
            soldiers_lost = 0

        if loser_vehicles:
            vehicles_lost = random.randint(
                0,
                max(0, len(loser_vehicles) // 3),
            )
        else:
            vehicles_lost = 0

        import random as _r

        for soldier in _r.sample(loser_soldiers, soldiers_lost):
            soldier.alive = False
        for vehicle in _r.sample(loser_vehicles, vehicles_lost):
            vehicle.damage(100)

        if loser is attacker:
            result["attacker_losses"] = soldiers_lost
        else:
            result["defender_losses"] = soldiers_lost

        result["destroyed_vehicles"] = vehicles_lost
        return result
