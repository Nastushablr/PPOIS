#include "CppUnitTest.h"

#include "../Lab2/src/base/Date.h"
#include "../Lab2/src/base/Person.h"
#include "../Lab2/src/base/Address.h"
#include "../Lab2/src/clients/Client.h"
#include "../Lab2/src/clients/PrivateClient.h"
#include "../Lab2/src/staff/Employee.h"
#include "../Lab2/src/staff/Manager.h"

#include "../Lab2/src/repairs/RepairProject.h"
#include "../Lab2/src/repairs/RepairObject.h"

#include "../Lab2/src/documents/Contract.h"
#include "../Lab2/src/documents/Invoice.h"
#include "../Lab2/src/documents/Payment.h"
#include "../Lab2/src/documents/FinancialReport.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RepairFirmTests
{
    static void createBasicContext(Client*& client,
        Employee*& author,
        RepairProject*& project)
    {
        static Address addr("Main st. 1", "Minsk", "220000", "Belarus");
        static Person person(1, "Ivan", "Ivanov",
            Date(10, 5, 1990),
            "+37529", "ivan@example.com", "AB1234567");
        static PrivateClient privateClient(1, &person, &addr,
            Date(1, 3, 2025),
            "+37529", "ivan@example.com");
        static Manager manager(10, &person, Date(1, 1, 2020), 1000.0, "Construction");
        static RepairObject object(1, &addr, &privateClient, "apartment", 60.0, 2000);
        static RepairProject proj(1, &privateClient, &object, Date(1, 4, 2025), 10000.0);

        client = &privateClient;
        author = &manager;
        project = &proj;
    }

    TEST_CLASS(DocumentsTests)
    {
    public:

        TEST_METHOD(Contract_Create_Sign_Terminate_AndIsActive)
        {
            Client* client = nullptr;
            Employee* author = nullptr;
            RepairProject* project = nullptr;
            createBasicContext(client, author, project);

            Contract c(100,
                Date(15, 3, 2025),
                author,
                client,
                Date(1, 4, 2025),
                Date(30, 4, 2025),
                12000.0);

            Assert::AreEqual(12000.0, c.getAmount(), 0.0001);
            Assert::AreEqual(Date(1, 4, 2025).getDay(), c.getStartDate().getDay());
            Assert::IsNull(c.getProject());

            c.setProject(project);
            Assert::IsNotNull(c.getProject());

            c.setTermsText("Standard terms");
            Assert::AreEqual(std::string("Standard terms"), c.getTermsText());

            c.sign();
            bool activeMid = c.isActiveOn(Date(15, 4, 2025));
            bool activeBefore = c.isActiveOn(Date(25, 3, 2025));

            Assert::IsTrue(activeMid);
            Assert::IsFalse(activeBefore);

            c.terminate();
            bool activeAfterTerminate = c.isActiveOn(Date(20, 4, 2025));
            Assert::IsFalse(activeAfterTerminate);

            std::string summary = c.generateSummary();
            Assert::IsTrue(summary.find("12000") != std::string::npos);
        }

        TEST_METHOD(Invoice_Create_AddItems_Tax_Overdue)
        {
            Client* client = nullptr;
            Employee* author = nullptr;
            RepairProject* project = nullptr;
            createBasicContext(client, author, project);

            Invoice inv(200,
                Date(20, 4, 2025),
                author,
                client,
                1000.0,
                0.2,
                Date(30, 4, 2025));

            Assert::AreEqual(1000.0, inv.getAmount(), 0.0001);
            Assert::AreEqual(0.2, inv.getTaxRate(), 0.0001);
            Assert::AreEqual(std::string("unpaid"), inv.getPaymentStatus());

            inv.addItem("Stage1 work");
            inv.addItem("Stage2 work");
            Assert::AreEqual<size_t>(2, inv.getItems().size());

            double totalWithTax = inv.getTotalWithTax();
            Assert::AreEqual(1200.0, totalWithTax, 0.0001);

            Assert::IsFalse(inv.isOverdue(Date(29, 4, 2025)));

            Assert::IsTrue(inv.isOverdue(Date(5, 5, 2025)));

            inv.markPaid();
            Assert::AreEqual(std::string("paid"), inv.getPaymentStatus());
            Assert::IsFalse(inv.isOverdue(Date(10, 5, 2025)));

            std::string summary = inv.generateSummary();
            Assert::IsTrue(summary.find("Invoice #") != std::string::npos);
        }

        TEST_METHOD(Payment_Process_AndRefund)
        {
            Client* client = nullptr;
            Employee* author = nullptr;
            RepairProject* project = nullptr;
            createBasicContext(client, author, project);

            Invoice inv(201,
                Date(21, 4, 2025),
                author,
                client,
                500.0,
                0.0,
                Date(1, 5, 2025));

            Payment pay(300,
                Date(25, 4, 2025),
                author,
                &inv,
                500.0,
                Date(25, 4, 2025),
                "card");

            Assert::AreEqual(500.0, pay.getAmount(), 0.0001);
            Assert::AreEqual(std::string("card"), pay.getMethod());
            Assert::IsFalse(pay.isRefunded());

            pay.setTransactionId("TX123");
            Assert::AreEqual(std::string("TX123"), pay.getTransactionId());

            pay.markProcessed();
            pay.markRefunded();
            Assert::IsTrue(pay.isRefunded());

            std::string summary = pay.generateSummary();

            Assert::IsTrue(summary.find("Payment") != std::string::npos);
            Assert::IsTrue(summary.find("500") != std::string::npos);
            Assert::IsTrue(summary.find("status") != std::string::npos);

        }

        TEST_METHOD(FinancialReport_AddAndRecalculate)
        {
            Client* client = nullptr;
            Employee* author = nullptr;
            RepairProject* project = nullptr;
            createBasicContext(client, author, project);

            FinancialReport report(400,
                Date(31, 5, 2025),
                author,
                "May 2025");

            Invoice inv1(210, Date(5, 5, 2025), author, client, 1000.0, 0.0, Date(20, 5, 2025));
            Invoice inv2(211, Date(10, 5, 2025), author, client, 1500.0, 0.0, Date(25, 5, 2025));

            Payment p1(310, Date(15, 5, 2025), author, &inv1, 1000.0, Date(15, 5, 2025), "bank");
            Payment p2(311, Date(25, 5, 2025), author, &inv2, 500.0, Date(25, 5, 2025), "cash");

            report.addInvoice(&inv1);
            report.addInvoice(&inv2);
            report.addPayment(&p1);
            report.addPayment(&p2);

            report.recalculateTotals();

            Assert::AreEqual(2500.0, report.getTotalInvoiced(), 0.0001);
            Assert::AreEqual(1500.0, report.getTotalPaid(), 0.0001);
            Assert::AreEqual(1000.0, report.getTotalOutstanding(), 0.0001);

            double paidPercent = report.getPaidPercent();
            Assert::AreEqual(60.0, paidPercent, 0.001);

            std::string summary = report.generateSummary();
            Assert::IsTrue(summary.find("2500") != std::string::npos);
        }
        TEST_METHOD(DefaultConstructor_InitializesFields)
        {
            Invoice inv;
            Assert::IsNull(inv.getClient());
            Assert::AreEqual(0.0, inv.getAmount(), 1e-6);
            Assert::AreEqual(0.0, inv.getTaxRate(), 1e-6);
            Assert::AreEqual(std::string("unpaid"), inv.getPaymentStatus());
            Assert::AreEqual<size_t>(0, inv.getItems().size());
        }

        TEST_METHOD(Setters_UpdateFields)
        {
            Invoice inv;
            Date due(15, 5, 2025);

            inv.setAmount(1000.0);
            inv.setTaxRate(20.0);
            inv.setDueDate(due);

            Assert::AreEqual(1000.0, inv.getAmount(), 1e-6);
            Assert::AreEqual(20.0, inv.getTaxRate(), 1e-6);
            Assert::AreEqual(15, inv.getDueDate().getDay());
        }
    };
    TEST_CLASS(PaymentTests)
    {
    public:
        TEST_METHOD(DefaultConstructor_InitializesFields)
        {
            Payment p;
            Assert::IsNull(p.getInvoice());
            Assert::AreEqual(0.0, p.getAmount(), 1e-6);
            Assert::AreEqual(std::string(""), p.getMethod());
            Assert::AreEqual(std::string(""), p.getTransactionId());
            Assert::IsFalse(p.isRefunded());
        }

        TEST_METHOD(Setters_AndMarkFailed)
        {
            Payment p;
            Date d(5, 4, 2025);

            p.setPaymentDate(d);
            p.setMethod("card");
            p.markFailed();

            Assert::AreEqual(5, p.getPaymentDate().getDay());
            Assert::AreEqual(std::string("card"), p.getMethod());
            Assert::AreEqual(std::string("failed"), p.getStatus());
        }
    };
}
