#include "CppUnitTest.h"

#include "../Lab2/src/base/Date.h"
#include "../Lab2/src/base/Address.h"
#include "../Lab2/src/clients/Client.h"
#include "../Lab2/src/clients/PrivateClient.h"
#include "../Lab2/src/base/Person.h"

#include "../Lab2/src/repairs/WorkType.h"
#include "../Lab2/src/repairs/DesignWork.h"
#include "../Lab2/src/repairs/MasonryWork.h"
#include "../Lab2/src/repairs/FinishingWork.h"
#include "../Lab2/src/repairs/RepairObject.h"
#include "../Lab2/src/repairs/ProjectStage.h"
#include "../Lab2/src/repairs/Task.h"
#include "../Lab2/src/repairs/RepairProject.h"

#include "../Lab2/src/staff/RepairSpecialist.h"
#include "../Lab2/src/staff/Designer.h"
#include "../Lab2/src/staff/Electrician.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RepairFirmTests
{
    TEST_CLASS(WorkTypesTests)
    {
    public:
        TEST_METHOD(DesignWork_Cost_DependsOnComplexityAnd3D)
        {
            DesignWork w(1, 50.0, 3, true);
            double cost = w.calculateCost(10.0);

            Assert::IsTrue(cost > 0.0);
            Assert::IsTrue(cost > 50.0 * 10.0);
        }

        TEST_METHOD(MasonryWork_Cost_WithThicknessAndScaffolding)
        {
            MasonryWork w(2, 30.0, 0.3, true);
            double cost = w.calculateCost(20.0);

            Assert::IsTrue(cost > 30.0 * 20.0);
        }

        TEST_METHOD(FinishingWork_Cost_WithLayersAndPremium)
        {
            FinishingWork w(3, 15.0, 2, true);
            double cost = w.calculateCost(40.0);

            Assert::IsTrue(cost >= 15.0 * 40.0 * 2);
        }
    };

    TEST_CLASS(RepairObjectAndStageTests)
    {
    public:
        TEST_METHOD(RepairObject_Basic_AndOldBuilding)
        {
            Address addr("Apartment st.", "Minsk", "220000", "Belarus");
            Person p(1, "Ivan", "Ivanov", Date(10, 5, 1990), "+37529", "ivan@example.com", "AB1234567");
            PrivateClient client(1, &p, &addr, Date(1, 3, 2025), "+37529", "ivan@example.com");

                RepairObject obj(1, &addr, &client, "apartment", 75.5, 1980);

            Assert::AreEqual(std::string("apartment"), obj.getObjectType());
            Assert::IsTrue(obj.isOldBuilding());

            obj.setBuildYear(2015);
            Assert::IsFalse(obj.isOldBuilding());
        }

        TEST_METHOD(ProjectStage_Progress_AndCompletion)
        {
            ProjectStage stage(1, "Design", Date(1, 3, 2025), Date(31, 3, 2025));

            Assert::AreEqual(0, stage.getProgress());
            Assert::IsFalse(stage.isCompleted());

            stage.setProgress(50);
            Assert::AreEqual(50, stage.getProgress());
            Assert::IsFalse(stage.isCompleted());

            stage.setProgress(120);
            Assert::AreEqual(100, stage.getProgress());
            Assert::IsTrue(stage.isCompleted());
        }
    };

    TEST_CLASS(RepairProjectAndTaskTests)
    {
    public:
        TEST_METHOD(Task_Lifecycle_StatusAndDates)
        {
            Address addr("House st.", "Minsk", "220000", "Belarus");
            Person p(1, "Ivan", "Ivanov", Date(10, 5, 1990), "+37529", "ivan@example.com", "AB1234567");
            PrivateClient client(1, &p, &addr, Date(1, 3, 2025), "+37529", "ivan@example.com");

                RepairObject obj(1, &addr, &client, "house", 120.0, 2005);
            RepairProject project(1, &client, &obj, Date(1, 4, 2025), 20000.0);

            Designer designer(10, &p, Date(1, 1, 2020), 1000.0, "modern");
            DesignWork designWork(1, 50.0, 2, false);

            Task task(100,
                &project,
                &designer,
                &designWork,
                "Design living room",
                3,
                Date(5, 4, 2025));

            Assert::AreEqual(std::string("planned"), task.getStatus());
            Assert::AreEqual(3, task.getPriority());

            task.start();
            Assert::AreEqual(std::string("in_progress"), task.getStatus());

            Date finish(10, 4, 2025);
            task.complete(finish);
            Assert::AreEqual(std::string("done"), task.getStatus());
            Assert::IsTrue(task.isCompleted());
            Assert::AreEqual(finish.getDay(), task.getCompletedDate().getDay());
        }

        TEST_METHOD(RepairProject_Stages_Tasks_Progress)
        {
            Address addr("Office st.", "Minsk", "220000", "Belarus");
            Person p(1, "Ivan", "Ivanov", Date(10, 5, 1990), "+37529", "ivan@example.com", "AB1234567");
            PrivateClient client(1, &p, &addr, Date(1, 3, 2025), "+37529", "ivan@example.com");

                RepairObject obj(1, &addr, &client, "office", 300.0, 2010);
            RepairProject project(2, &client, &obj, Date(1, 5, 2025), 50000.0);

            ProjectStage s1(1, "Design", Date(1, 5, 2025), Date(15, 5, 2025));
            ProjectStage s2(2, "Construction", Date(16, 5, 2025), Date(30, 6, 2025));

            s1.setProgress(100);
            s2.setProgress(50);

            project.addStage(&s1);
            project.addStage(&s2);

            double progress = project.calculateProgress();
            Assert::AreEqual(75.0, progress);

            Electrician e(20, &p, Date(1, 1, 2019), 900.0, true);
            MasonryWork mw(2, 30.0, 0.25, false);

            Task t1(201, &project, &e, &mw, "Install wiring", 2, Date(10, 5, 2025));
            Task t2(202, &project, &e, &mw, "Install sockets", 2, Date(12, 5, 2025));

            project.addTask(&t1);
            project.addTask(&t2);

            Assert::AreEqual(2, project.countOpenTasks());

            t1.start();
            t1.complete(Date(20, 5, 2025));

            Assert::AreEqual(1, project.countOpenTasks());

            project.start();
            Assert::AreEqual(std::string("in_progress"), project.getStatus());

            project.complete();
            Assert::AreEqual(std::string("completed"), project.getStatus());
        }
    };
    TEST_CLASS(FinishingWorkTests)
    {
    public:
        TEST_METHOD(DefaultConstructor_InitializesFields)
        {
            FinishingWork w;
            Assert::AreEqual(1, w.getLayersCount());
            Assert::IsFalse(w.getPremiumMaterials());
            Assert::AreEqual(std::string("Finishing work"), w.getName());
        }

        TEST_METHOD(Setters_NormalValues)
        {
            FinishingWork w;
            w.setLayersCount(3);
            w.setPremiumMaterials(true);

            Assert::AreEqual(3, w.getLayersCount());
            Assert::IsTrue(w.getPremiumMaterials());
        }

        TEST_METHOD(SetLayersCount_TooSmall_ClampedToOne)
        {
            FinishingWork w;
            w.setLayersCount(0);
            Assert::AreEqual(1, w.getLayersCount());

            w.setLayersCount(-5);
            Assert::AreEqual(1, w.getLayersCount());
        }
    };
}
