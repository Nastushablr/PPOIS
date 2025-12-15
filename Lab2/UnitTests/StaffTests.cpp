#include "CppUnitTest.h"

#include "../Lab2/src/base/Date.h"
#include "../Lab2/src/base/Person.h"
#include "../Lab2/src/staff/Employee.h"
#include "../Lab2/src/staff/Manager.h"
#include "../Lab2/src/staff/Accountant.h"
#include "../Lab2/src/staff/HRSpecialist.h"
#include "../Lab2/src/staff/RepairSpecialist.h"
#include "../Lab2/src/staff/Foreman.h"
#include "../Lab2/src/staff/Designer.h"
#include "../Lab2/src/staff/Electrician.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RepairFirmTests
{
    TEST_CLASS(StaffEmployeeTests)
    {
    public:
        TEST_METHOD(Employee_Hire_Dismiss_Leave_Experience)
        {
            Date birth(10, 5, 1990);
            Date hire(1, 3, 2020);
            Date today(1, 3, 2025);

            Person p(1, "Ivan", "Ivanov", birth, "+37529", "ivan@example.com", "AB1234567");

            Manager m(101, &p, hire, 1000.0, "Projects");

            Assert::AreEqual(std::string("active"), m.getStatus());
            Assert::AreEqual(5, m.getExperienceYears(today));

            m.sendToLeave();
            Assert::AreEqual(std::string("on_leave"), m.getStatus());

            m.dismiss();
            Assert::AreEqual(std::string("dismissed"), m.getStatus());

            m.hire();
            Assert::AreEqual(std::string("active"), m.getStatus());
        }
    };

    TEST_CLASS(AccountantTests)
    {
    public:

        TEST_METHOD(DefaultConstructor_SetsJuniorAndZeroReports)
        {
            Accountant acc;

            Assert::AreEqual(0, acc.getClosedReports());
        }

        TEST_METHOD(CloseMonthlyReport_IncrementsCounter)
        {
            Accountant acc;

            Assert::AreEqual(0, acc.getClosedReports());

            acc.closeMonthlyReport();
            Assert::AreEqual(1, acc.getClosedReports());

            acc.closeMonthlyReport();
            Assert::AreEqual(2, acc.getClosedReports());
        }

        TEST_METHOD(CreateInvoice_DoesNotThrow)
        {
            Accountant acc;

            acc.createInvoice(1000.0);
            acc.createInvoice(0.0);
            acc.createInvoice(-500.0);
        }
    };

    TEST_CLASS(ManagerAccountantHRTests)
    {
    public:
        TEST_METHOD(Manager_Salary_Department_Team)
        {
            Date birth(10, 5, 1990);
            Date hire(1, 1, 2020);
            Person p(1, "Ivan", "Ivanov", birth, "+37529", "ivan@example.com", "AB1234567");

            Manager m(201, &p, hire, 1200.0, "Construction");

            Assert::AreEqual(std::string("Manager"), m.getRole());
            Assert::AreEqual(std::string("Construction"), m.getDepartment());
            Assert::AreEqual(0, m.getTeamSize());

            m.addTeamMember();
            m.addTeamMember();
            m.setPerformanceRating(8.0);

            Assert::AreEqual(2, m.getTeamSize());
            Assert::AreEqual(8.0, m.getPerformanceRating());

            double salary = m.calculateMonthlySalary();
            Assert::IsTrue(salary > 1200.0);
        }
        TEST_METHOD(DefaultConstructor_InitializesFields)
        {
            Manager m;
            Assert::AreEqual(std::string(""), m.getDepartment());
            Assert::AreEqual(0, m.getTeamSize());
            Assert::AreEqual(0.0, m.getPerformanceRating(), 1e-6);

            HRSpecialist hr;
            Assert::AreEqual(0, hr.getHiredEmployees());
            Assert::AreEqual(0, hr.getInterviewsCount());
        }

        TEST_METHOD(AssignTask_AndConductMeeting_DoNotThrow)
        {
            Manager m;
            m.assignTask(42);
            m.conductMeeting();
        }

        TEST_METHOD(Accountant_Qualification_AndSalary)
        {
            Date birth(5, 7, 1988);
            Date hire(1, 2, 2021);
            Person p(2, "Anna", "Sidorova", birth, "+37529", "anna@example.com", "CD7654321");

            Accountant a(301, &p, hire, 900.0, "junior");

            Assert::AreEqual(std::string("Accountant"), a.getRole());
            Assert::AreEqual(std::string("junior"), a.getQualificationLevel());

            double baseSalary = a.calculateMonthlySalary();
            Assert::AreEqual(900.0, baseSalary);

            a.setQualificationLevel("middle");
            double midSalary = a.calculateMonthlySalary();
            Assert::IsTrue(midSalary > 900.0);

            a.setQualificationLevel("senior");
            double seniorSalary = a.calculateMonthlySalary();
            Assert::IsTrue(seniorSalary > midSalary);
        }

        TEST_METHOD(HRSpecialist_HiredEmployees_AndSalary)
        {
            Date birth(1, 1, 1995);
            Date hire(1, 6, 2022);
            Person p(3, "Olga", "Petrova", birth, "+37529", "olga@example.com", "EF1234567");

            HRSpecialist hr(401, &p, hire, 800.0);

            Assert::AreEqual(std::string("HR Specialist"), hr.getRole());
            Assert::AreEqual(0, hr.getHiredEmployees());
            Assert::AreEqual(0, hr.getInterviewsCount());

            hr.registerInterview();
            hr.registerInterview();
            hr.hireNewEmployee();
            hr.hireNewEmployee();

            Assert::AreEqual(2, hr.getHiredEmployees());
            Assert::AreEqual(2, hr.getInterviewsCount());

            double salary = hr.calculateMonthlySalary();
            Assert::IsTrue(salary > 800.0);
        }
    };

    TEST_CLASS(RepairSpecialistsTests)
    {
    public:
        TEST_METHOD(Foreman_TeamSize_Projects_AndSalary)
        {
            Date birth(10, 5, 1985);
            Date hire(1, 3, 2015);
            Person p(4, "Sergey", "Kuznetsov", birth, "+37529", "sergey@example.com", "GH1234567");

            Foreman f(501, &p, hire, 1100.0);

            Assert::AreEqual(std::string("Foreman"), f.getRole());
            Assert::AreEqual(std::string("foreman"), f.getSpecialization());

            f.setTeamSize(5);
            f.registerFinishedProject();
            f.registerFinishedProject();
            f.increaseSkill();
            f.registerCompletedTask();

            Assert::AreEqual(5, f.getTeamSize());
            Assert::AreEqual(2, f.getFinishedProjects());
            Assert::IsTrue(f.getSkillLevel() >= 2);
            Assert::IsTrue(f.getCompletedTasks() >= 1);

            double salary = f.calculateMonthlySalary();
            Assert::IsTrue(salary > 1100.0);
        }
        TEST_METHOD(DefaultConstructor_InitializesFields)
        {
            Foreman f;
            Assert::AreEqual(0, f.getTeamSize());
            Assert::AreEqual(0, f.getFinishedProjects());
            Assert::AreEqual(std::string("foreman"), f.getSpecialization());

            Electrician e;
            Assert::IsFalse(e.getHasHighVoltagePermit());
            Assert::AreEqual(0, e.getSafetyChecksDone());
            Assert::AreEqual(std::string("electrician"), e.getSpecialization());
        }

        TEST_METHOD(PlanSchedule_CanBeCalled)
        {
            Foreman f;
            f.planSchedule();
        }

        TEST_METHOD(Designer_Designs_AndSpecialization)
        {
            Date birth(15, 8, 1992);
            Date hire(1, 4, 2020);
            Person p(5, "Elena", "Designova", birth, "+37529", "elena@example.com", "IJ1234567");

            Designer d(601, &p, hire, 1000.0, "loft");

            Assert::AreEqual(std::string("Designer"), d.getRole());
            Assert::AreEqual(std::string("designer"), d.getSpecialization());
            Assert::AreEqual(std::string("loft"), d.getMainStyle());
            Assert::AreEqual(0, d.getCreatedDesigns());

            d.createDesign();
            d.createDesign();
            d.setMainStyle("minimalism");

            Assert::AreEqual(2, d.getCreatedDesigns());
            Assert::AreEqual(std::string("minimalism"), d.getMainStyle());

            double salary = d.calculateMonthlySalary();
            Assert::IsTrue(salary > 1000.0);
        }

        TEST_METHOD(Electrician_Permit_SafetyChecks_AndSalary)
        {
            Date birth(20, 9, 1987);
            Date hire(1, 5, 2018);
            Person p(6, "Pavel", "Tokarev", birth, "+37529", "pavel@example.com", "KL1234567");

            Electrician e(701, &p, hire, 950.0, true);

            Assert::AreEqual(std::string("Electrician"), e.getRole());
            Assert::AreEqual(std::string("electrician"), e.getSpecialization());
            Assert::IsTrue(e.getHasHighVoltagePermit());
            Assert::AreEqual(0, e.getSafetyChecksDone());

            e.performRepair();
            e.performSafetyCheck();
            e.performSafetyCheck();
            e.setHasHighVoltagePermit(false);

            Assert::IsFalse(e.getHasHighVoltagePermit());
            Assert::AreEqual(2, e.getSafetyChecksDone());
            Assert::IsTrue(e.getCompletedTasks() >= 1);

            double salary = e.calculateMonthlySalary();
            Assert::IsTrue(salary > 950.0);
        }
    };
}
