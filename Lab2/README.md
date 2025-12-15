# RepairFirm System — Система управления фирмой по ремонту
---
## 📦 КЛАССЫ И ИХ ОПИСАНИЕ

### =============== BASE (Базовые типы) ===============

#### **Date** (Date.h/cpp)
**Назначение**: Представление и работа с датами

**Поля**:
- `int day` — день месяца (1-31)
- `int month` — месяц (1-12)
- `int year` — год (≥1)

**Методы**:
- `Date()` — конструктор по умолчанию (01.01.2000)
- `Date(int d, int m, int y)` — конструктор с параметрами
- `getDay() const`, `getMonth() const`, `getYear() const` — геттеры
- `setDate(int d, int m, int y)` — установка даты
- `isValid() const` — проверка валидности
- `isLeap(int y) const` — проверка високосного года
- `daysInMonth(int m, int y) const` — дни в месяце
- `addDays(int days)` — прибавить дни
- `daysUntil(const Date& other) const` — расстояние между датами
- `toString() const` — вывод в формате DD.MM.YYYY
- **Операторы**: `<`, `>`, `==` для сравнения

**Исключения**: `InvalidDateException`

---

#### **Address** (Address.h/cpp)
**Назначение**: Представление адреса объекта или клиента

**Поля**:
- `string street` — улица
- `string city` — город
- `string postalCode` — почтовый индекс
- `string country` — страна
- `string building` — номер дома
- `string apartment` — номер квартиры

**Методы**:
- `Address()` — конструктор по умолчанию
- `Address(const string& street, ...)` — полный конструктор
- Геттеры и сеттеры для всех полей
- `getFullAddress() const` — полный адрес в одну строку
- `isValid() const` — проверка (улица, город, индекс, страна обязательны)
- `validatePostalCode() const` — проверка индекса (4-10 символов)

**Исключения**: `InvalidAddressException`

---

#### **Person** (Person.h/cpp)
**Назначение**: Личные данные человека

**Поля**:
- `int id` — идентификатор
- `string firstName` — имя
- `string lastName` — фамилия
- `Date birthDate` — дата рождения
- `string phone` — телефон
- `string email` — email
- `string passportNumber` — номер паспорта
- `string nationality` — гражданство

**Методы**:
- `Person()`, `Person(...)`
- Геттеры и сеттеры
- `getFullName() const` — "Имя Фамилия"
- `getAge(const Date& today) const` — возраст в годах
- `validateEmail() const` — простая проверка email
- `updateContact(const string& newPhone, const string& newEmail)` — обновление контактов

**Ассоциации**: используется в Employee, PrivateClient

**Исключения**: `InvalidPersonDataException`

---

### =============== CLIENTS (Клиенты) ===============

#### **Client** (Client.h/cpp) — *базовый класс*
**Назначение**: Общая информация о клиенте

**Поля** (защищённые):
- `int id` — идентификатор
- `string name` — название/имя
- `Address* address` — адрес (указатель)
- `Date registrationDate` — дата регистрации
- `string phone` — телефон
- `string email` — email
- `string status` — статус клиента
- `double totalSpent` — общая сумма расходов

**Методы**:
- `Client()`, `Client(...)`
- Все геттеры и сеттеры
- **Виртуальные**: `registerClient()`, `deactivate()`, `block()`, `updateContacts()`
- `addSpent(double amount)` — добавить расходы
- **Виртуальный деструктор**

**Исключения**: `InvalidClientException`

---

#### **PrivateClient** (PrivateClient.h/cpp)
**Назначение**: Клиент — физическое лицо

**Наследование**: `Client`

**Дополнительные поля**:
- `Person* person` — данные о человеке (указатель)
- `string maritalStatus` — семейное положение
- `int dependents` — иждивенцы

**Методы**:
- Конструкторы
- `getPerson() const`, `getMaritalStatus() const`, `getDependents() const`
- `setPerson()`, `setMaritalStatus()`, `setDependents()`
- `hasValidPassport() const` — проверка паспорта
- `getAge(const Date& today) const` — возраст из Person

**Ассоциации**: 
- Композиция с `Person`
- Наследование от `Client`

---

#### **LegalEntityClient** (LegalEntityClient.h/cpp)
**Назначение**: Клиент — юридическое лицо (компания)

**Наследование**: `Client`

**Дополнительные поля**:
- `string companyName` — название компании
- `string taxId` — УНП/ИНН
- `string registrationNumber` — регистрационный номер
- `Person* director` — директор (указатель)
- `string bankAccount` — банковский счёт
- `bool isVatPayer` — плательщик НДС

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `validateTaxId() const` — проверка УНП (9-12 символов)
- `getSummaryInfo() const` — краткая информация

**Ассоциации**:
- Ассоциация с `Person` (директор)
- Наследование от `Client`

---

### =============== STAFF (Сотрудники) ===============

#### **Employee** (Employee.h/cpp) — *базовый класс*
**Назначение**: Общая информация о сотруднике

**Поля** (защищённые):
- `int id` — идентификатор
- `Person* person` — личные данные (указатель)
- `Date hireDate` — дата приема
- `double baseSalary` — базовый оклад
- `string position` — должность
- `string status` — статус

**Методы**:
- `Employee()`, `Employee(...)`
- Геттеры и сеттеры
- `hire()`, `dismiss()`, `sendToLeave()` — управление статусом
- `getExperienceYears(const Date& today) const` — стаж в годах
- **Виртуальный**: `calculateMonthlySalary() const` — зарплата с надбавками
- **Чисто виртуальный**: `getRole() const = 0` — роль сотрудника
- **Виртуальный деструктор**

**Ассоциации**:
- Композиция с `Person`
- Композиция с `Date`

**Исключения**: `InvalidEmployeeException`

---

#### **Manager** (Manager.h/cpp)
**Назначение**: Руководитель подразделения

**Наследование**: `Employee`

**Дополнительные поля**:
- `string department` — отдел
- `int teamSize` — размер команды
- `double performanceRating` — рейтинг эффективности

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `assignTask(int taskId)` — назначить задачу
- `conductMeeting()` — провести собрание
- `addTeamMember()` — добавить члена команды
- `calculateMonthlySalary() const override` — расчёт с бонусом за команду
- `getRole() const override` — возвращает "Manager"

---

#### **HRSpecialist** (HRSpecialist.h/cpp)
**Назначение**: Специалист по кадрам

**Наследование**: `Employee`

**Дополнительные поля**:
- `int hiredEmployees` — принятых сотрудников
- `int interviewsCount` — проведено собеседований

**Методы**:
- Конструкторы
- Геттеры
- `registerInterview()` — регистрация собеседования
- `hireNewEmployee()` — прием сотрудника
- `calculateMonthlySalary() const override` — зарплата + премия
- `getRole() const override` — "HRSpecialist"

---

#### **Accountant** (Accountant.h/cpp)
**Назначение**: Бухгалтер

**Наследование**: `Employee`

**Дополнительные поля**:
- `string qualificationLevel` — уровень квалификации
- `int closedReports` — закрытых отчётов

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `createInvoice(double amount)` — создание счёта
- `closeMonthlyReport()` — закрытие отчёта
- `calculateMonthlySalary() const override`
- `getRole() const override` — "Accountant"

---

#### **RepairSpecialist** (RepairSpecialist.h/cpp) — *базовый класс*
**Назначение**: Базовый класс для ремонтных специалистов

**Наследование**: `Employee`

**Дополнительные поля**:
- `string specialization` — специализация
- `int completedTasks` — выполненные задачи
- `int skillLevel` — уровень навыков

**Методы**:
- Конструкторы
- Геттеры
- `increaseSkill()` — повысить уровень
- `registerCompletedTask()` — регистрация задачи
- `calculateMonthlySalary() const override` — зарплата зависит от уровня
- **Чисто виртуальный**: `getRole() const override = 0`

---

#### **Designer** (Designer.h/cpp)
**Назначение**: Дизайнер

**Наследование**: `RepairSpecialist`

**Дополнительные поля**:
- `string mainStyle` — основной стиль
- `int createdDesigns` — созданных проектов

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `createDesign()` — создание дизайна
- `getRole() const override` — "Designer"

---

#### **Electrician** (Electrician.h/cpp)
**Назначение**: Электрик

**Наследование**: `RepairSpecialist`

**Дополнительные поля**:
- `bool hasHighVoltagePermit` — допуск к высокому напряжению
- `int safetyChecksDone` — техосмотров проведено

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `performRepair()` — выполнить ремонт
- `performSafetyCheck()` — провести техосмотр
- `getRole() const override` — "Electrician"

---

#### **Foreman** (Foreman.h/cpp)
**Назначение**: Прораб/бригадир

**Наследование**: `RepairSpecialist`

**Дополнительные поля**:
- `int teamSize` — размер бригады
- `int finishedProjects` — завершённых проектов

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `registerFinishedProject()` — завершить проект
- `planSchedule()` — планировать график
- `getRole() const override` — "Foreman"

---

### =============== REPAIRS (Ремонтные проекты) ===============

#### **RepairProject** (RepairProject.h/cpp)
**Назначение**: Основной класс ремонтного проекта

**Поля**:
- `int id` — идентификатор
- `Client* client` — клиент (указатель)
- `RepairObject* object` — объект ремонта (указатель)
- `Date startDate` — дата начала
- `Date plannedEndDate` — плановая дата окончания
- `double budget` — бюджет
- `string status` — статус ("planned", "active", "completed")
- `vector<ProjectStage*> stages` — этапы проекта
- `vector<Task*> tasks` — задачи проекта

**Методы**:
- `RepairProject()`, `RepairProject(...)`
- Геттеры и сеттеры
- `addStage(ProjectStage* stage)` — добавить этап
- `addTask(Task* task)` — добавить задачу
- `calculateProgress() const` — процент завершения
- `countOpenTasks() const` — незавершённые задачи
- `start()` — запуск проекта
- `complete()` — завершение проекта

**Ассоциации**:
- Ассоциация с `Client`
- Композиция с `RepairObject`
- Композиция с `ProjectStage` (вектор)
- Композиция с `Task` (вектор)

**Исключения**: `InvalidProjectException`

---

#### **RepairObject** (RepairObject.h/cpp)
**Назначение**: Объект ремонта (квартира, дом, офис и т.д.)

**Поля**:
- `int id` — идентификатор
- `Address* address` — адрес (указатель)
- `Client* owner` — владелец (указатель)
- `string objectType` — тип ("квартира", "дом", "офис")
- `double area` — площадь м²
- `int buildYear` — год постройки

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `isOldBuilding() const` — проверка: постройка < 2000 года

**Ассоциации**:
- Ассоциация с `Address`
- Ассоциация с `Client`

---

#### **ProjectStage** (ProjectStage.h/cpp)
**Назначение**: Этап проекта (подготовка, монтаж, отделка и т.д.)

**Поля**:
- `int id` — идентификатор
- `string name` — название этапа
- `Date startDate` — дата начала
- `Date endDate` — дата окончания
- `int progress` — прогресс 0-100%

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `isCompleted() const` — проверка завершённости (progress == 100)

---

#### **Task** (Task.h/cpp)
**Назначение**: Отдельная задача в проекте

**Поля**:
- `int id` — идентификатор
- `RepairProject* project` — связанный проект (указатель)
- `RepairSpecialist* specialist` — назначенный специалист (указатель)
- `WorkType* workType` — тип работ (указатель)
- `string description` — описание
- `string status` — статус ("planned", "in_progress", "completed")
- `int priority` — приоритет 1-5
- `Date plannedDate` — плановая дата
- `Date completedDate` — дата фактического завершения

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `start()` — запуск задачи
- `complete(const Date& date)` — завершение с датой
- `isCompleted() const` — проверка завершённости

**Ассоциации**:
- Ассоциация с `RepairProject`
- Ассоциация с `RepairSpecialist`
- Ассоциация с `WorkType`

---

#### **WorkType** (WorkType.h/cpp) — *абстрактный*
**Назначение**: Базовый класс типов работ

**Поля** (защищённые):
- `int id` — идентификатор
- `string name` — название
- `double baseRate` — базовая ставка
- `string unit` — единица измерения
- `string description` — описание

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- **Чисто виртуальный**: `calculateCost(double amount) const = 0` — расчёт стоимости

---

#### **DesignWork** (DesignWork.h/cpp)
**Назначение**: Дизайнерские работы

**Наследование**: `WorkType`

**Дополнительные поля**:
- `int complexityLevel` — сложность 1-5
- `bool includes3D` — 3D визуализация

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `calculateCost(double hours) const override` — расчёт по часам

---

#### **FinishingWork** (FinishingWork.h/cpp)
**Назначение**: Отделочные работы

**Наследование**: `WorkType`

**Дополнительные поля**:
- `int layersCount` — количество слоёв
- `bool premiumMaterials` — премиум материалы

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `calculateCost(double area) const override` — расчёт по площади

---

#### **MasonryWork** (MasonryWork.h/cpp)
**Назначение**: Каменные работы

**Наследование**: `WorkType`

**Дополнительные поля**:
- `double wallThickness` — толщина стен см
- `bool requiresScaffolding` — требуются леса

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `calculateCost(double area) const override` — расчёт по площади

---

### =============== MATERIALS (Материалы и склады) ===============

#### **Material** (Material.h/cpp) — *базовый класс*
**Назначение**: Базовый класс строительных материалов

**Поля** (защищённые):
- `int id` — идентификатор
- `string name` — название
- `string unit` — единица (м³, м², шт и т.д.)
- `int quantity` — количество на складе
- `double unitPrice` — цена за единицу
- `string supplier` — поставщик

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `getTotalCost() const` — общая стоимость (quantity × unitPrice)
- `increaseQuantity(int delta)` — добавить количество
- `reserve(int amount)` — зарезервировать материал
- **Виртуальный деструктор**

**Исключения**: `InsufficientMaterialException`

---

#### **BuildingMaterial** (BuildingMaterial.h/cpp)
**Назначение**: Строительные материалы

**Наследование**: `Material`

**Дополнительные поля**:
- `string strengthClass` — класс прочности (М400, М500 и т.д.)
- `bool forOutdoorUse` — для наружных работ
- `double density` — плотность кг/м³

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `getTotalCost() const override` — с учётом класса прочности

---

#### **FinishingMaterial** (FinishingMaterial.h/cpp)
**Назначение**: Отделочные материалы

**Наследование**: `Material`

**Дополнительные поля**:
- `string color` — цвет
- `string finishType` — тип отделки (матовая, глянцевая и т.д.)
- `double coverage` — расход м²/единица

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `getCoverableArea() const` — площадь покрытия (quantity × coverage)

---

#### **Tool** (Tool.h/cpp)
**Назначение**: Инструменты и оборудование

**Поля**:
- `int id` — идентификатор
- `string name` — название
- `string toolType` — тип (дрель, пила, уровень и т.д.)
- `int quantity` — количество
- `string condition` — состояние (новое, хорошее, требует ремонта)
- `Date lastService` — последнее обслуживание

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `checkout(int amount)` — выдача инструмента
- `returnBack(int amount)` — возврат инструмента
- `markServiced(const Date& date)` — отметить обслуживание

---

#### **Warehouse** (Warehouse.h/cpp)
**Назначение**: Склад материалов и инструментов

**Поля**:
- `int id` — идентификатор
- `Address* address` — адрес склада (указатель)
- `double maxValue` — максимальная стоимость запасов
- `vector<Material*> materials` — материалы
- `vector<Tool*> tools` — инструменты

**Методы**:
- Конструкторы
- Геттеры
- `addMaterial(Material* material)` — добавить материал
- `addTool(Tool* tool)` — добавить инструмент
- `findMaterialByName(const string& name) const` — поиск материала
- `findToolByName(const string& name) const` — поиск инструмента
- `calculateTotalValue() const` — общая стоимость запасов

**Ассоциации**:
- Ассоциация с `Address`
- Композиция с `Material` (вектор)
- Композиция с `Tool` (вектор)

---

#### **Delivery** (Delivery.h/cpp)
**Назначение**: Доставка материалов между складами

**Поля**:
- `int id` — идентификатор
- `Warehouse* fromWarehouse` — склад отправления (указатель)
- `Warehouse* toWarehouse` — склад назначения (указатель)
- `vector<Material*> materials` — перемещаемые материалы
- `Date plannedDate` — плановая дата доставки
- `string status` — статус ("planned", "in_transit", "completed")

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `addMaterial(Material* material)` — добавить материал в доставку
- `start()` — начало доставки
- `complete()` — завершение доставки

**Ассоциации**:
- Ассоциация с `Warehouse` (два)
- Композиция с `Material` (вектор)

---

### =============== DOCUMENTS (Документооборот) ===============

#### **Document** (Document.h/cpp) — *абстрактный*
**Назначение**: Базовый класс всех документов

**Поля** (защищённые):
- `int id` — идентификатор
- `Date createdDate` — дата создания
- `Employee* author` — автор (указатель)
- `string status` — статус
- `int version` — версия документа

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `save()` — сохранить документ
- `markArchived()` — архивировать
- `incrementVersion()` — увеличить версию
- **Чисто виртуальный**: `generateSummary() const = 0` — краткое содержание
- **Виртуальный деструктор**

---

#### **Contract** (Contract.h/cpp)
**Назначение**: Договор с клиентом на работы

**Наследование**: `Document`

**Дополнительные поля**:
- `Client* client` — клиент (указатель)
- `RepairProject* project` — проект (указатель)
- `Date startDate` — дата начала работ
- `Date endDate` — дата окончания работ
- `double amount` — сумма контракта
- `string termsText` — условия договора

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `sign()` — подписание контракта
- `terminate()` — расторжение
- `isActiveOn(const Date& date) const` — проверка активности на дату
- `generateSummary() const override` — краткое содержание

**Ассоциации**:
- Наследование от `Document`
- Ассоциация с `Client`
- Ассоциация с `RepairProject`

**Исключения**: `ContractViolationException`

---

#### **Estimate** (Estimate.h/cpp)
**Назначение**: Смета на выполнение работ

**Наследование**: `Document`

**Дополнительные поля**:
- `RepairProject* project` — проект (указатель)
- `vector<Material*> materials` — список материалов
- `double laborCost` — стоимость работ
- `double totalAmount` — общая сумма
- `Date validUntil` — действительна до

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `addMaterial(Material* material)` — добавить материал
- `clearMaterials()` — очистить список
- `calculateTotal()` — пересчёт итога
- `isExpired(const Date& today) const` — проверка действительности
- `generateSummary() const override`

**Ассоциации**:
- Наследование от `Document`
- Ассоциация с `RepairProject`
- Композиция с `Material` (вектор)

---

#### **Invoice** (Invoice.h/cpp)
**Назначение**: Счёт-фактура клиенту

**Наследование**: `Document`

**Дополнительные поля**:
- `Client* client` — клиент (указатель)
- `double amount` — сумма без НДС
- `double taxRate` — ставка НДС (%)
- `Date dueDate` — дата оплаты
- `string paymentStatus` — статус оплаты
- `vector<string> items` — позиции счёта

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `addItem(const string& line)` — добавить позицию
- `getTotalWithTax() const` — сумма с НДС
- `markPaid()` — отметить как оплачено
- `isOverdue(const Date& today) const` — проверка просрочки
- `generateSummary() const override`

**Ассоциации**:
- Наследование от `Document`
- Ассоциация с `Client`

**Исключения**: `InvalidPaymentException`

---

#### **Payment** (Payment.h/cpp)
**Назначение**: Платёж от клиента

**Наследование**: `Document`

**Дополнительные поля**:
- `Invoice* invoice` — связанный счёт (указатель)
- `double amount` — сумма платежа
- `Date paymentDate` — дата платежа
- `string method` — метод оплаты (наличные, карта, перевод)
- `string transactionId` — ID транзакции
- `bool refunded` — возвращен ли платёж

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `markProcessed()` — отметить обработку
- `markFailed()` — отметить ошибку
- `markRefunded()` — отметить возврат
- `generateSummary() const override`

**Ассоциации**:
- Наследование от `Document`
- Ассоциация с `Invoice`

**Исключения**: `InvalidPaymentException`, `InsufficientFundsException`

---

#### **ActOfCompletion** (ActOfCompletion.h/cpp)
**Назначение**: Акт выполненных работ (подписывается клиентом)

**Наследование**: `Document`

**Дополнительные поля**:
- `RepairProject* project` — проект (указатель)
- `Date completionDate` — дата завершения
- `string customerComment` — комментарий клиента
- `int qualityScore` — оценка качества (1-5)

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `signByCustomer()` — подпись клиента
- `isSigned() const` — проверка подписи
- `generateSummary() const override`

**Ассоциации**:
- Наследование от `Document`
- Ассоциация с `RepairProject`

---

#### **FinancialReport** (FinancialReport.h/cpp)
**Назначение**: Финансовый отчёт за период

**Наследование**: `Document`

**Дополнительные поля**:
- `string periodLabel` — период отчёта (месяц/квартал/год)
- `vector<Invoice*> invoices` — счета
- `vector<Payment*> payments` — платежи
- `double totalInvoiced` — выставлено всего
- `double totalPaid` — оплачено всего
- `double totalOutstanding` — остаток задолженности

**Методы**:
- Конструкторы
- Геттеры
- `addInvoice(Invoice* invoice)` — добавить счёт
- `addPayment(Payment* payment)` — добавить платёж
- `clearData()` — очистить данные
- `recalculateTotals()` — пересчёт итогов
- `getPaidPercent() const` — процент оплаты
- `generateSummary() const override`

**Ассоциации**:
- Наследование от `Document`
- Композиция с `Invoice` (вектор)
- Композиция с `Payment` (вектор)

---

### =============== UTILITIES (Прочие классы) ===============

#### **Vehicle** (Vehicle.h/cpp)
**Назначение**: Транспортное средство компании

**Поля**:
- `int id` — идентификатор
- `string plateNumber` — номерной знак
- `string model` — модель
- `double fuelConsumptionPer100km` — расход л/100км
- `Employee* driver` — водитель (указатель)
- `Date lastServiceDate` — дата ТО
- `double mileage` — пробег км

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `estimateFuelForDistance(double km) const` — расход топлива на расстояние
- `addTrip(double km)` — добавить поездку (увеличить пробег)

**Ассоциации**:
- Ассоциация с `Employee` (водитель)

---

#### **Schedule** (Schedule.h/cpp)
**Назначение**: Расписание задач

**Поля**:
- `vector<Task*> tasks` — список задач

**Методы**:
- `addTask(Task* task)` — добавить задачу
- `removeTask(Task* task)` — удалить задачу
- `getTasks() const` — получить все задачи
- `getTasksForDate(const Date& date) const` — задачи на дату
- `countTasksByStatus(const string& status) const` — подсчёт по статусу

**Ассоциации**:
- Композиция с `Task` (вектор)

---

#### **PriceList** (PriceList.h/cpp)
**Назначение**: Прайс-лист услуг

**Поля**:
- `string name` — название
- `map<int, double> workBaseRates` — ставки по ID типа работ
- `double materialMarkupPercent` — наценка на материалы %

**Методы**:
- Конструкторы
- Геттеры и сеттеры
- `setWorkRate(int workTypeId, double rate)` — установить ставку
- `hasWorkRate(int workTypeId) const` — проверка наличия
- `getWorkRate(int workTypeId) const` — получить ставку
- `calculateWorkCost(const WorkType* workType, double amount) const` — расчёт стоимости
- `applyMaterialMarkup(double materialCost) const` — применить наценку

---

### =============== EXCEPTIONS (Исключения) ===============

Все исключения наследуют от `std::runtime_error`.

**Исключения валидации данных**:
- `InvalidPersonDataException` — некорректные личные данные
- `InvalidAddressException` — неверный адрес
- `InvalidDateException` — неверная дата
- `InvalidClientException` — некорректные данные клиента
- `InvalidEmployeeException` — некорректные данные сотрудника
- `InvalidProjectException` — проблемы с проектом

**Исключения бизнес-логики**:
- `InsufficientMaterialException` — недостаточно материалов
- `InvalidPaymentException` — некорректный платёж
- `InsufficientFundsException` — недостаточно средств
- `ScheduleConflictException` — конфликт расписания
- `ContractViolationException` — нарушение условий договора
- `OperationNotAllowedException` — операция запрещена статусом

**Использование**: Выбрасываются при нарушении условий, ловятся в бизнес-логике.

---

## 📊 ДИАГРАММА НАСЛЕДОВАНИЯ

```
Employee                   WorkType              Material           Document
   ├─ Manager              ├─ DesignWork         ├─ BuildingMaterial   ├─ Contract
   ├─ HRSpecialist         ├─ FinishingWork      └─ FinishingMaterial  ├─ Estimate
   ├─ Accountant           └─ MasonryWork                              ├─ Invoice
   └─ RepairSpecialist                                                 ├─ Payment
      ├─ Designer                                                      ├─ ActOfCompletion
      ├─ Electrician                                                   └─ FinancialReport
      └─ Foreman

Client
   ├─ PrivateClient
   └─ LegalEntityClient
```

---

## 📋 ОСНОВНЫЕ АССОЦИАЦИИ

| Класс | Связь | С кем |
|-------|-------|-------|
| `RepairProject` | содержит | `ProjectStage[]`, `Task[]` |
| `RepairProject` | связан с | `Client`, `RepairObject` |
| `Task` | назначена | `RepairSpecialist` |
| `Task` | использует | `WorkType` |
| `Warehouse` | хранит | `Material[]`, `Tool[]` |
| `Delivery` | связывает | `Warehouse` (от/до) |
| `Delivery` | перевозит | `Material[]` |
| `Employee` | описан | `Person` |
| `PrivateClient` | связан с | `Person` |
| `LegalEntityClient` | руководит | `Person` (директор) |
| `Vehicle` | управляет | `Employee` (водитель) |
| `Contract` | регулирует | `Client`, `RepairProject` |
| `Invoice` | выставлена | `Client` |
| `Payment` | погашает | `Invoice` |
| `FinancialReport` | агрегирует | `Invoice[]`, `Payment[]` |

---
