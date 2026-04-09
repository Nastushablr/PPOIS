from __future__ import annotations

from dataclasses import dataclass, field
from enum import Enum
from typing import List, Optional


class Rank(str, Enum):
    PRIVATE = "private"
    SERGEANT = "sergeant"
    LIEUTENANT = "lieutenant"
    CAPTAIN = "captain"
    MAJOR = "major"
    COLONEL = "colonel"
    GENERAL = "general"


class Specialization(str, Enum):
    INFANTRY = "infantry"
    ARTILLERY = "artillery"
    TANK_CREW = "tank_crew"
    PILOT = "pilot"
    ENGINEER = "engineer"
    MEDIC = "medic"
    SIGNAL = "signal"
    RESERVIST = "reservist"


@dataclass
class Soldier:
    id: int
    last_name: str
    first_name: str
    patronymic: str
    rank: Rank
    specialization: Specialization
    experience: int = 0
    alive: bool = True

    @property
    def full_name(self) -> str:
        return f"{self.last_name} {self.first_name} {self.patronymic}".strip()

    def train(self, amount: int = 10) -> None:
        if amount < 0:
            raise ValueError("amount должен быть неотрицательным")
        self.experience = min(100, self.experience + amount)


@dataclass
class Vehicle:
    id: int
    name: str
    type: str
    condition: int = 100
    operational: bool = True

    def damage(self, amount: int = 30) -> None:
        if amount < 0:
            raise ValueError("amount должен быть неотрицательным")
        self.condition = max(0, self.condition - amount)
        if self.condition == 0:
            self.operational = False

    def repair(self, amount: int = 20) -> None:
        if amount < 0:
            raise ValueError("amount должен быть неотрицательным")
        self.condition = min(100, self.condition + amount)
        if self.condition > 0:
            self.operational = True


@dataclass
class Base:
    name: str
    location: str
    soldiers: List[Soldier] = field(default_factory=list)
    vehicles: List[Vehicle] = field(default_factory=list)
    supplies: int = 100
    security_level: int = 1

    def add_soldier(self, soldier: Soldier) -> None:
        self.soldiers.append(soldier)

    def add_vehicle(self, vehicle: Vehicle) -> None:
        self.vehicles.append(vehicle)


@dataclass
class Army:
    name: str
    bases: List[Base] = field(default_factory=list)
    commander: Optional[Soldier] = None

    def add_base(self, base: Base) -> None:
        if base not in self.bases:
            self.bases.append(base)

    def total_soldiers(self) -> int:
        return sum(len([s for s in b.soldiers if s.alive]) for b in self.bases)

    def total_vehicles(self) -> int:
        return sum(len(b.vehicles) for b in self.bases)

    def all_soldiers(self, alive_only: bool = True) -> List[Soldier]:
        soldiers: List[Soldier] = []
        for base in self.bases:
            if alive_only:
                soldiers.extend([s for s in base.soldiers if s.alive])
            else:
                soldiers.extend(base.soldiers)
        return soldiers

    def all_vehicles(self) -> List[Vehicle]:
        vehicles: List[Vehicle] = []
        for base in self.bases:
            vehicles.extend(base.vehicles)
        return vehicles
