from __future__ import annotations

from typing import Callable, Dict, List

from army.exceptions import ArmyError
from army.models import Rank, Specialization
from army.world import World


class CommandProcessor:
    def __init__(self) -> None:
        self.world = World()
        self._running = True
        self.world.create_army("Army 1")

        self._handlers: Dict[str, Callable[[List[str]], None]] = {
            "help": self.handle_help,
            "menu": self.handle_help,
            "create_army": self.handle_create_army,
            "list_armies": self.handle_list_armies,
            "create_base": self.handle_create_base,
            "list_bases": self.handle_list_bases,
            "hire_soldier": self.handle_hire_soldier,
            "buy_vehicle": self.handle_buy_vehicle,
            "set_commander": self.handle_set_commander,
            "report_army": self.handle_report_army,
            "mobilize": self.handle_mobilize,
            "train": self.handle_train,
            "supply": self.handle_supply,
            "attack": self.handle_attack,
            "defend": self.handle_defend,
            "secure": self.handle_secure,
            "exit": self.handle_exit,
            "quit": self.handle_exit,
        }

    def run(self) -> None:
        self._print_banner()
        self.handle_help([])
        while self._running:
            try:
                raw = input("ArmyCLI> ").strip()
            except (EOFError, KeyboardInterrupt):
                print()
                break
            if not raw:
                continue

            parts = raw.split()
            cmd, *args = parts
            handler = self._handlers.get(cmd)
            if handler is None:
                print(f"Неизвестная команда: {cmd}. Введите 'help' для справки.")
                continue

            try:
                handler(args)
            except ArmyError as exc:
                print(f"[ОШИБКА] {exc}")
            except ValueError as exc:
                print(f"[ОШИБКА ВВОДА] {exc}")

    def _choose_army(self, prompt: str = "Выберите армию") -> str:
        armies = self.world.list_armies()
        if not armies:
            raise ArmyError("Армии не созданы. Сначала создайте армию.")
        print(f"{prompt}:")
        for idx, army in enumerate(armies, start=1):
            print(f"  {idx}) {army.name}")
        choice = input("Номер армии: ").strip()
        idx = int(choice)
        if idx < 1 or idx > len(armies):
            raise ValueError("Некорректный номер армии")
        return armies[idx - 1].name

    def _choose_base_from_army(
        self,
        army_name: str,
        prompt: str = "Выберите базу",
    ) -> str:
        army = self.world.get_army(army_name)
        if not army.bases:
            raise ArmyError(
                f"У армии '{army.name}' нет баз. "
                "Сначала создайте базу и привяжите её к армии.",
            )
        print(f"{prompt} армии '{army.name}':")
        for idx, base in enumerate(army.bases, start=1):
            print(f"  {idx}) {base.name} ({base.location})")
        choice = input("Номер базы: ").strip()
        idx = int(choice)
        if idx < 1 or idx > len(army.bases):
            raise ValueError("Некорректный номер базы")
        return army.bases[idx - 1].name

    @staticmethod
    def _print_banner() -> None:
        print("=" * 50)
        print("        ARMY SIMULATOR")
        print("=" * 50)

    def handle_help(self, _: List[str]) -> None:
        print("""
Главное меню команд:
--------------------------------------------------
  Общие команды ヾ(•ω•`)o:
    🆘 help / menu        - показать это меню
    🚪 exit / quit        - выход из программы

  Армии и базы (⌐■_■):
    create_army        - создать армию
    list_armies        - список армий
    create_base        - создать базу и привязать к армии
    list_bases         - список всех баз
    set_commander      - назначить командующего армией

  Личный состав и техника 🪖:
    hire_soldier       - нанять одного солдата
    mobilize           - мобилизовать список солдат
    buy_vehicle        - купить единицу техники

  Операции 🔫:
    report_army        - отчёт по армии
    train              - операция обучения армии
    supply             - операция логистики армии
    secure             - усилить безопасность баз армии
    attack             - атака армии на армию
    defend             - защита (то же, что attack, но с упором на защитника)
--------------------------------------------------
""")

    def handle_create_army(self, _: List[str]) -> None:
        name = input("Название армии (по умолчанию 'Army N'): ").strip()
        if not name:
            existing = self.world.list_armies()
            next_num = len(existing) + 1
            name = f"Army {next_num}"
        army = self.world.create_army(name)
        print(f"Создана армия '{army.name}'")

    def handle_list_armies(self, _: List[str]) -> None:
        armies = self.world.list_armies()
        if not armies:
            print("Армии не созданы.")
            return
        print("Список армий:")
        for army in armies:
            print(
                f"  - {army.name}: баз={len(army.bases)}, "
                f"солдат={army.total_soldiers()}, "
                f"техники={army.total_vehicles()}",
            )

    def handle_create_base(self, _: List[str]) -> None:
        name = input("Название базы: ").strip()
        location = input("Местоположение базы: ").strip()
        base = self.world.create_base(name, location)
        army_name = self._choose_army("К какой армии привязать базу")
        self.world.add_base_to_army(army_name, base.name)
        print(
            f"Создана база '{base.name}' в локации '{base.location}' "
            f"и привязана к армии '{army_name}'",
        )

    def handle_list_bases(self, _: List[str]) -> None:
        if not self.world.bases:
            print("Баз пока нет.")
            return
        print("Список всех баз:")
        for base in self.world.bases.values():
            print(
                f"  - {base.name} ({base.location}), "
                f"солдат: {len(base.soldiers)}, "
                f"техники: {len(base.vehicles)}, "
                f"запасы: {base.supplies}, "
                f"безопасность: {base.security_level}",
            )

    def handle_hire_soldier(self, _: List[str]) -> None:
        army_name = self._choose_army("Выберите армию для солдата")
        base_name = self._choose_base_from_army(
            army_name,
            "Выберите базу, на которую добавить солдата",
        )

        last_name = input("Фамилия: ").strip()
        first_name = input("Имя: ").strip()
        patronymic = input("Отчество (можно оставить пустым): ").strip()

        print("Доступные звания:")
        for rank in Rank:
            print(f"  - {rank.value}")
        rank_str = input("Звание (например, private): ").strip()
        try:
            rank = Rank(rank_str)
        except ValueError as exc:
            raise ValueError("Некорректное звание") from exc

        print("Доступные специализации:")
        for spec in Specialization:
            print(f"  - {spec.value}")
        spec_str = input("Специализация (например, infantry): ").strip()
        try:
            specialization = Specialization(spec_str)
        except ValueError as exc:
            raise ValueError("Некорректная специализация") from exc

        soldier = self.world.hire_soldier(
            base_name=base_name,
            last_name=last_name,
            first_name=first_name,
            patronymic=patronymic,
            rank=rank,
            specialization=specialization,
        )
        print(
            "Нанят солдат "
            f"id={soldier.id}, {soldier.full_name}, "
            f"звание={soldier.rank.value}, "
            f"специализация={soldier.specialization.value}",
        )

    def handle_mobilize(self, _: List[str]) -> None:
        army_name = self._choose_army("Выберите армию для мобилизации")
        base_name = self._choose_base_from_army(
            army_name,
            "Выберите базу, на которую отправить мобилизованных",
        )

        count_str = input("Сколько солдат мобилизовать: ").strip()
        count = int(count_str)
        fio_list: List[tuple[str, str, str]] = []
        print("Вводите ФИО каждого мобилизуемого:")
        for i in range(1, count + 1):
            print(f"Солдат {i}:")
            last_name = input("  Фамилия: ").strip()
            first_name = input("  Имя: ").strip()
            patronymic = input("  Отчество (можно пусто): ").strip()
            fio_list.append((last_name, first_name, patronymic))

        print("Операция 'Мобилизация' начата.")
        created = self.world.mobilize(base_name, fio_list)

        print(f"Создано мобилизованных солдат: {len(created)} на базу '{base_name}'.")
        print(f"  {'ФИО':<30} {'Ранг':<10} {'Специализация'}")
        print(f"  {'-'*30} {'-'*10} {'-'*15}")
        for soldier in created:
            print(
                f"  {soldier.full_name:<30} "
                f"{soldier.rank.value:<10} "
                f"{soldier.specialization.value}",
            )
        print("Операция завершена.")

    def handle_buy_vehicle(self, _: List[str]) -> None:
        army_name = self._choose_army("Выберите армию для техники")
        base_name = self._choose_base_from_army(
            army_name,
            "Выберите базу, на которую добавить технику",
        )

        name = input("Название техники (например, T-90): ").strip()
        type_ = input("Тип техники (танк, самолёт и т.п.): ").strip()
        vehicle = self.world.buy_vehicle(base_name, name, type_)
        print(
            "Закуплена техника "
            f"id={vehicle.id}, {vehicle.name}, тип={vehicle.type} "
            f"на базу '{base_name}'",
        )

    def handle_set_commander(self, _: List[str]) -> None:
        army_name = self._choose_army("Выберите армию для назначения командира")
        army = self.world.get_army(army_name)
        soldiers = army.all_soldiers()
        if not soldiers:
            raise ArmyError(
                "В армии нет солдат, невозможно назначить командира.",
            )
        print(f"Солдаты армии '{army.name}':")
        for s in soldiers:
            print(
                f"  id={s.id}: {s.full_name}, звание={s.rank.value}, "
                f"опыт={s.experience}",
            )
        soldier_id_str = input("Введите id солдата, которого назначить командиром: ")
        soldier_id = int(soldier_id_str)
        soldier = self.world.find_soldier(soldier_id)
        army.commander = soldier
        print(
            f"Командующим армии '{army.name}' назначен "
            f"{soldier.full_name} (id={soldier.id})",
        )

    def handle_report_army(self, _: List[str]) -> None:
        army_name = self._choose_army("Для какой армии вывести отчёт")
        army = self.world.get_army(army_name)

        print("=" * 100)
        print(f"ОТЧЁТ ПО АРМИИ: {army.name}")
        print("=" * 100)
        print(f"Количество баз: {len(army.bases)}")
        print(f"Количество живых солдат: {army.total_soldiers()}")
        print(f"Количество техники: {army.total_vehicles()}")
        if army.commander:
            print(f"Командующий: {army.commander.full_name}")
        print()

        print("Базы армии:")
        for base in army.bases:
            alive_count = len([s for s in base.soldiers if s.alive])
            print(
                f"  - {base.name} ({base.location}) | "
                f"живых солдат: {alive_count} | "
                f"техники: {len(base.vehicles)} | "
                f"запасы: {base.supplies} | "
                f"безопасность: {base.security_level}"
            )

        print()
        print("Список живых солдат:")
        soldiers = army.all_soldiers()

        if not soldiers:
            print("  Нет живых солдат.")
        else:
            header = (
                f"{'ID':<4} {'ФИО':<30} {'Ранг':<12} "
                f"{'Специализация':<15} {'Опыт':<8} {'База':<15}"
            )
            print(header)
            print("-" * len(header))

            for base in army.bases:
                for soldier in base.soldiers:
                    if not soldier.alive:
                        continue

                    row = (
                        f"{soldier.id:<4} "
                        f"{soldier.full_name:<30} "
                        f"{soldier.rank.value:<12} "
                        f"{soldier.specialization.value:<15} "
                        f"{soldier.experience:<8} "
                        f"{base.name:<15}"
                    )
                    print(row)

        print()
        print("Список техники:")
        vehicles_found = False

        vehicle_header = (
            f"{'ID':<4} {'Название':<20} {'Тип':<15} "
            f"{'Состояние':<12} {'Боеготова':<12} {'База':<15}"
        )
        print(vehicle_header)
        print("-" * len(vehicle_header))

        for base in army.bases:
            for vehicle in base.vehicles:
                vehicles_found = True
                row = (
                    f"{vehicle.id:<4} "
                    f"{vehicle.name:<20} "
                    f"{vehicle.type:<15} "
                    f"{vehicle.condition:<12} "
                    f"{str(vehicle.operational):<12} "
                    f"{base.name:<15}"
                )
                print(row)

        if not vehicles_found:
            print("Нет техники.")

        print("=" * 100)

    def handle_train(self, _: List[str]) -> None:
        army_name = self._choose_army("Какую армию обучать")
        print("Операция 'Обучение и подготовка' начата.")
        trained = self.world.train(army_name)
        print(f"Обучено солдат: {trained}")
        print("Операция завершена.")

    def handle_supply(self, _: List[str]) -> None:
        army_name = self._choose_army("Для какой армии запустить логистику")
        print("Операция 'Обеспечение логистики' начата.")
        result = self.world.supply(army_name)
        print(
            f"Армия '{result['army']}' получила {result['supplies_added']} ед. запасов. "
            f"Отремонтировано техники: {result['vehicles_repaired']}."
        )

    print("Операция завершена.")

    def handle_attack(self, _: List[str]) -> None:
        print("Настройка операции 'attack'.")
        attacker_name = self._choose_army("Выберите атакующую армию")
        defender_name = self._choose_army("Выберите защищающуюся армию")
        if attacker_name == defender_name:
            raise ValueError("Атакующая и защищающаяся армия должны быть разными.")
        print("Операция 'Участие в боевых действиях' начата.")
        result = self.world.battle(attacker_name, defender_name)
        self._print_battle_result(result)

    def handle_defend(self, _: List[str]) -> None:
        print("Настройка операции 'defend'.")
        defender_name = self._choose_army("Выберите армию, которая обороняется")
        attacker_name = self._choose_army("Выберите армию, которая атакует")
        if attacker_name == defender_name:
            raise ValueError("Атакующая и защищающаяся армия должны быть разными.")
        print("Операция 'Оборона и безопасность' начата.")
        result = self.world.battle(attacker_name, defender_name)
        self._print_battle_result(result)

    def handle_secure(self, _: List[str]) -> None:
        army_name = self._choose_army("Для какой армии усилить безопасность")
        print("Операция 'Безопасность и оборона' начата.")
        result = self.world.secure(army_name)
        print(
            f"Для армии '{result['army']}' усилено баз: " f"{result['upgraded_bases']}."
        )
        print("Операция завершена.")

    def handle_exit(self, _: List[str]) -> None:
        self._running = False
        print("Выход из программы. До свидания!")

    @staticmethod
    def _print_battle_result(result: dict) -> None:
        print(
            f"Результат: {result['outcome']}. "
            f"Потери атакующего: {result['attacker_losses']} солдат, "
            f"потери защитника: {result['defender_losses']} солдат, "
            f"уничтожено техники: {result['destroyed_vehicles']}.",
        )
        print("Операция завершена.")
