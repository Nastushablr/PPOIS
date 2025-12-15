Person 8 6(14) -> Ассоциации: Date

Address 6 4(12) -> Ассоциации: (нет)

Date 3 7(12) -> Ассоциации: (нет)

Client 8 7(18) -> Ассоциации: Address, Date

PrivateClient 3 3(8) -> Ассоциации: Person, Client

LegalEntityClient 6 3(10) -> Ассоциации: Person, Client

Employee 6 7(18) -> Ассоциации: Person, Date

Manager 3 4(10) -> Ассоциации: Employee

HRSpecialist 2 3(8) -> Ассоциации: Employee

Accountant 2 3(8) -> Ассоциации: Employee

RepairSpecialist 3 4(10) -> Ассоциации: Employee

Designer 2 3(8) -> Ассоциации: RepairSpecialist

Electrician 2 3(8) -> Ассоциации: RepairSpecialist

Foreman 2 3(8) -> Ассоциации: RepairSpecialist

RepairObject 6 1(9) -> Ассоциации: Address, Client

ProjectStage 5 1(7) -> Ассоциации: Date

Task 9 5(17) -> Ассоциации: RepairProject, RepairSpecialist, WorkType, Date

WorkType 5 1(7) -> Ассоциации: (нет)

DesignWork 2 1(5) -> Ассоциации: WorkType

FinishingWork 2 1(5) -> Ассоциации: WorkType

MasonryWork 2 1(5) -> Ассоциации: WorkType

RepairProject 8 7(19) -> Ассоциации: Client, RepairObject, ProjectStage, Task, Date

Material 6 4(14) -> Ассоциации: (нет)

BuildingMaterial 3 1(5) -> Ассоциации: Material

FinishingMaterial 3 2(6) -> Ассоциации: Material

Tool 6 4(14) -> Ассоциации: Date

Warehouse 5 6(16) -> Ассоциации: Address, Material, Tool

Delivery 6 4(12) -> Ассоциации: Warehouse, Material, Date

Document 5 5(13) -> Ассоциации: Date, Employee

Contract 6 5(15) -> Ассоциации: Document, Client, RepairProject, Date

Estimate 5 6(16) -> Ассоциации: Document, RepairProject, Material, Date

Invoice 6 6(16) -> Ассоциации: Document, Client, Date

Payment 6 7(17) -> Ассоциации: Document, Invoice, Date

ActOfCompletion 4 4(12) -> Ассоциации: Document, RepairProject, Date

FinancialReport 6 6(16) -> Ассоциации: Document, Invoice, Payment, Date

Vehicle 7 4(14) -> Ассоциации: Employee, Date

Schedule 1 5(9) -> Ассоциации: Task

PriceList 3 5(11) -> Ассоциации: WorkType
