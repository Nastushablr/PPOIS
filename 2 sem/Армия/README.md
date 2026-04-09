```markdown
# 🪖 Army Simulator


**Консольный симулятор управления армией.**



## 📋 Основная функциональность

### 🏰 Управление армиями и базами
- `create_army` — создание армии
- `create_base` — создание базы и привязка к армии  
- `list_armies` — список армий
- `list_bases` — список всех баз
- `report_army` — детальный отчёт по армии

### 🪖 Личный состав
- `hire_soldier` — наём одного солдата (звание + специализация)
- `mobilize` — массовая мобилизация по списку ФИО
- `set_commander` — назначение командира армии
- `train` — обучение солдат (повышение опыта)

### 🚀 Техника и логистика
- `buy_vehicle` — закупка техники (T-90, самолёты и т.д.)
- `supply` — логистика: пополнение запасов + ремонт техники

### ⚔️ Операции
- `secure` — усиление безопасности баз
- `attack` / `defend` — боевые действия между армиями

## 🏗️ Архитектура проекта

```text
army-cli/
├── army/
│   ├── __init__.py
│   ├── cli.py
│   ├── models.py
│   ├── world.py
│   └── exceptions.py
├── tests/
│   ├── test_cli_helpers.py
│   ├── test_models.py
│   ├── test_world.py
├── main.py
└── README.md
```


**Интерактивный ввод:**
```bash
ArmyCLI> help          # Показать все команды
ArmyCLI> create_army   # Создать армию Red Army  
ArmyCLI> create_base   # Добавить базу в Минске
ArmyCLI> hiresoldier   # Нанять солдата
ArmyCLI> exit          # Выход
```

## 🧪 Тестирование и качество кода

### Запуск тестов
```bash
# Все 57 тестов
python -m unittest discover -v

# Результат:
# Ran 57 tests in 0.817s
# OK
```


**Результат покрытия:**
```
Name                        Stmts  Miss Cover
------------------------------------------------
army/__init__.py                0     0   100%
army/models.py                 93     0   100% 
army/world.py                 132     4    97%
tests/test_cli_helpers.py     192     1    99%
tests/test_models.py          171     0   100%
tests/test_world.py          115     0   100%
------------------------------------------------
TOTAL                         853    53    94%
```


## 📖 Полный список команд CLI

| Команда | Описание | Пример |
|---------|----------|--------|
| `help` | Показать меню | `help` |
| `create_army` | Создать армию | `create_army` |
| `list_armies` | Список армий | `list_armies` |
| `create_base` | Создать базу | `create_base` |
| `list_bases` | Список баз | `list_bases` |
| `hire_soldier` | Нанять солдата | `hire_soldier` |
| `mobilize` | Мобилизация | `mobilize` |
| `buy_vehicle` | Купить технику | `buy_vehicle` |
| `set_commander` | Назначить командира | `set_commander` |
| `report_army` | Отчёт армии | `report_army` |
| `train` | Обучение солдат | `train` |
| `supply` | Логистика | `supply` |
| `secure` | Безопасность баз | `secure` |
| `attack` | Атаковать | `attack` |
| `defend` | Защищаться | `defend` |
| `exit` | Выход | `exit` |

