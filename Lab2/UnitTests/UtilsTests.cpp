#include "CppUnitTest.h"

#include "../Lab2/src/base/Date.h"
#include "../Lab2/src/staff/Employee.h"
#include "../Lab2/src/staff/Manager.h"
#include "../Lab2/src/repairs/WorkType.h"
#include "../Lab2/src/repairs/DesignWork.h"
#include "../Lab2/src/repairs/Task.h"
#include "../Lab2/src/repairs/RepairProject.h"
#include "../Lab2/src/clients/PrivateClient.h"
#include "../Lab2/src/base/Person.h"
#include "../Lab2/src/base/Address.h"
#include "../Lab2/src/staff/RepairSpecialist.h"
#include "../Lab2/src/staff/Designer.h"

#include "../Lab2/src/utils/PriceList.h"
#include "../Lab2/src/utils/Schedule.h"
#include "../Lab2/src/utils/Vehicle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RepairFirmTests
{
    static void createContext(PrivateClient*& client,
        RepairProject*& project,
        RepairSpecialist*& specialist,
        WorkType*& workType)
    {
        static Address addr("Main st. 1", "Minsk", "220000", "Belarus");
        static Person person(1, "Ivan", "Ivanov",
            Date(10, 5, 1990),
            "+37529", "ivan@example.com", "AB1234567");
        static PrivateClient privateClient(1, &person, &addr,
            Date(1, 3, 2025),
            "+37529", "ivan@example.com");
        static RepairObject object(1, &addr, &privateClient, "apartment", 60.0, 2000);
        static RepairProject proj(1, &privateClient, &object,
            Date(1, 4, 2025),
            10000.0);
        static Designer designer(10, &person, Date(1, 1, 2020),
            1000.0, "modern");
        static DesignWork designWork(1, 50.0, 2, false);

        client = &privateClient;
        project = &proj;
        specialist = &designer;
        workType = &designWork;
    }

    TEST_CLASS(UtilsTests)
    {
    public:

        TEST_METHOD(PriceList_WorkRates_AndMaterialMarkup)
        {
            PriceList list("Spring 2025", 15.0);

            PrivateClient* client = nullptr;
            RepairProject* project = nullptr;
            RepairSpecialist* specialist = nullptr;
            WorkType* workType = nullptr;
            createContext(client, project, specialist, workType);

            double costDefault = list.calculateWorkCost(workType, 10.0);
            Assert::IsTrue(costDefault > 0.0);

            list.setWorkRate(workType->getId(), 80.0);
            Assert::IsTrue(list.hasWorkRate(workType->getId()));

            double costCustom = list.calculateWorkCost(workType, 10.0);
            Assert::AreEqual(800.0, costCustom, 0.0001);

            double materials = 1000.0;
            double withMarkup = list.applyMaterialMarkup(materials);
            Assert::AreEqual(1150.0, withMarkup, 0.0001);
        }

        TEST_METHOD(Schedule_Add_Remove_AndFilterByDate)
        {
            Schedule sched;

            PrivateClient* client = nullptr;
            RepairProject* project = nullptr;
            RepairSpecialist* specialist = nullptr;
            WorkType* workType = nullptr;
            createContext(client, project, specialist, workType);

            Task t1(1, project, specialist, workType,
                "Task 1", 1, Date(5, 4, 2025));
            Task t2(2, project, specialist, workType,
                "Task 2", 2, Date(6, 4, 2025));

            sched.addTask(&t1);
            sched.addTask(&t2);

            Assert::AreEqual<size_t>(2, sched.getTasks().size());

            auto day5 = sched.getTasksForDate(Date(5, 4, 2025));
            Assert::AreEqual<size_t>(1, day5.size());
            Assert::AreEqual(1, day5[0]->getId());

            Assert::AreEqual(2, sched.countTasksByStatus("planned"));
            t1.start();
            t1.complete(Date(7, 4, 2025));
            Assert::AreEqual(1, sched.countTasksByStatus("planned"));
            Assert::AreEqual(1, sched.countTasksByStatus("done"));

            sched.removeTask(&t1);
            Assert::AreEqual<size_t>(1, sched.getTasks().size());
        }

        TEST_METHOD(Vehicle_FuelAndMileage)
        {
            Person driverPerson(1, "Pavel", "Driver",
                Date(1, 1, 1985),
                "+37529", "driver@example.com", "DR1234567");
            Manager driverEmp(20, &driverPerson, Date(1, 1, 2020), 900.0, "Logistics");

            Vehicle v(1,
                "1234 AB-7",
                "Ford Transit",
                10.0,
                &driverEmp,
                Date(1, 3, 2025),
                100000.0);

            Assert::AreEqual(std::string("1234 AB-7"), v.getPlateNumber());
            Assert::AreEqual(10.0, v.getFuelConsumptionPer100km(), 0.0001);
            Assert::AreEqual(100000.0, v.getMileage(), 0.0001);

            double fuel = v.estimateFuelForDistance(250.0);
            Assert::AreEqual(25.0, fuel, 0.0001);

            v.addTrip(150.0);
            Assert::AreEqual(100150.0, v.getMileage(), 0.0001);

            v.setFuelConsumptionPer100km(12.0);
            fuel = v.estimateFuelForDistance(100.0);
            Assert::AreEqual(12.0, fuel, 0.0001);
        }
        TEST_METHOD(DefaultConstructor_InitializesFields)
        {
            Vehicle v;
            Assert::AreEqual(0, v.getId());
            Assert::AreEqual(std::string(""), v.getPlateNumber());
            Assert::AreEqual(std::string(""), v.getModel());
            Assert::AreEqual(0.0, v.getFuelConsumptionPer100km(), 1e-6);
            Assert::IsNull(v.getDriver());
            Assert::AreEqual(0.0, v.getMileage(), 1e-6);
        }
    };
}
