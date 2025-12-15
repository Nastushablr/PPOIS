#include "CppUnitTest.h"

#include "../Lab2/src/base/Date.h"
#include "../Lab2/src/base/Address.h"
#include "../Lab2/src/base/Person.h"
#include "../Lab2/src/clients/Client.h"
#include "../Lab2/src/clients/PrivateClient.h"
#include "../Lab2/src/clients/LegalEntityClient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RepairFirmTests
{
    TEST_CLASS(ClientTests)
    {
    public:

        TEST_METHOD(Client_Register_Deactivate_Block_UpdateContacts)
        {
            Date reg(1, 3, 2025);
            Address addr("Lenina 1", "Minsk", "220000", "Belarus");
            Client c(101, "Test Client", &addr, reg, "+37529", "test@client.com");

            Assert::AreEqual(std::string("new"), c.getStatus());
            Assert::AreEqual(0.0, c.getTotalSpent());

            c.registerClient();
            Assert::AreEqual(std::string("active"), c.getStatus());

            c.updateContacts("+375291112233", "updated@client.com");
            Assert::AreEqual(std::string("+375291112233"), c.getPhone());
            Assert::AreEqual(std::string("updated@client.com"), c.getEmail());

            c.addSpent(500.0);
            c.addSpent(300.0);
            Assert::AreEqual(800.0, c.getTotalSpent());

            c.deactivate();
            Assert::AreEqual(std::string("inactive"), c.getStatus());

            c.block();
            Assert::AreEqual(std::string("blocked"), c.getStatus());
        }

        TEST_METHOD(PrivateClient_Passport_And_Age)
        {
            Date birth(10, 5, 1990);
            Date reg(1, 3, 2025);
            Address addr("Lenina 1", "Minsk", "220000", "Belarus");
            Person person(1,
                "Ivan",
                "Ivanov",
                birth,
                "+37529",
                "ivan@example.com",
                "AB1234567");

            PrivateClient pc(201, &person, &addr, reg, "+37529", "ivan@example.com");

            Assert::AreEqual(std::string("Ivan Ivanov"), pc.getName());

            Assert::IsTrue(pc.hasValidPassport());

            int age = pc.getAge(reg);
            Assert::AreEqual(34, age);

            pc.setMaritalStatus("married");
            pc.setDependents(2);
            Assert::AreEqual(std::string("married"), pc.getMaritalStatus());
            Assert::AreEqual(2, pc.getDependents());
        }

        TEST_METHOD(PrivateClient_SetPerson_SyncName)
        {
            Date birth(10, 5, 1990);
            Date reg(1, 3, 2025);
            Address addr("Lenina 1", "Minsk", "220000", "Belarus");

            Person p1(1, "Ivan", "Ivanov", birth, "+37529", "ivan@example.com", "AB1234567");
            Person p2(2, "Petr", "Petrov", birth, "+37529", "petr@example.com", "CD7654321");

            PrivateClient pc(202, &p1, &addr, reg, "+37529", "ivan@example.com");
            Assert::AreEqual(std::string("Ivan Ivanov"), pc.getName());

            pc.setPerson(&p2);
            Assert::AreEqual(std::string("Petr Petrov"), pc.getName());
            Assert::IsTrue(pc.hasValidPassport());
        }

        TEST_METHOD(LegalEntityClient_BasicFields_AndValidateTaxId)
        {
            Date reg(1, 3, 2025);
            Address addr("Nezavisimosti 5", "Minsk", "220001", "Belarus");
            Person director(1,
                "Anna",
                "Sidorova",
                Date(15, 2, 1985),
                "+37529",
                "anna@company.com",
                "MP1234567");

            LegalEntityClient lc(301,
                "BestBuild LLC",
                &addr,
                reg,
                "+375293334455",
                "info@bestbuild.com",
                "123456789",
                &director);

            Assert::AreEqual(std::string("BestBuild LLC"), lc.getCompanyName());
            Assert::AreEqual(std::string("BestBuild LLC"), lc.getName());

            Assert::AreEqual(std::string("123456789"), lc.getTaxId());
            Assert::IsTrue(lc.validateTaxId());

            Assert::IsNotNull(lc.getDirector());
            Assert::AreEqual(std::string("Anna Sidorova"), lc.getDirector()->getFullName());

            lc.setBankAccount("BY00TEST00000000000000000000");
            lc.setIsVatPayer(true);
            Assert::AreEqual(std::string("BY00TEST00000000000000000000"), lc.getBankAccount());
            Assert::IsTrue(lc.getIsVatPayer());

            std::string summary = lc.getSummaryInfo();
            Assert::IsTrue(summary.find("BestBuild LLC") != std::string::npos);
            Assert::IsTrue(summary.find("123456789") != std::string::npos);
        }

        TEST_METHOD(LegalEntityClient_ChangeCompanyName_SyncBaseName)
        {
            Date reg(1, 3, 2025);
            Address addr("Nezavisimosti 5", "Minsk", "220001", "Belarus");
            Person director(1,
                "Anna",
                "Sidorova",
                Date(15, 2, 1985),
                "+37529",
                "anna@company.com",
                "MP1234567");

            LegalEntityClient lc(302,
                "OldName LLC",
                &addr,
                reg,
                "+37529",
                "info@old.com",
                "987654321",
                &director);

            Assert::AreEqual(std::string("OldName LLC"), lc.getName());

            lc.setCompanyName("NewName LLC");
            Assert::AreEqual(std::string("NewName LLC"), lc.getCompanyName());
            Assert::AreEqual(std::string("NewName LLC"), lc.getName());
        }
        TEST_METHOD(DefaultConstructor_InitializesFields)
        {
            Client c;
            Assert::AreEqual(0, c.getId());
            Assert::AreEqual(std::string(""), c.getName());
            Assert::IsNull(c.getAddress());
            Assert::AreEqual(std::string(""), c.getPhone());
            Assert::AreEqual(std::string(""), c.getEmail());
            Assert::AreEqual(std::string("new"), c.getStatus());
            Assert::AreEqual(0.0, c.getTotalSpent(), 1e-6);

            LegalEntityClient lc;
            Assert::AreEqual(std::string(""), lc.getCompanyName());
            Assert::AreEqual(std::string(""), lc.getTaxId());
            Assert::AreEqual(std::string(""), lc.getRegistrationNumber());
            Assert::IsNull(lc.getDirector());
            Assert::AreEqual(std::string(""), lc.getBankAccount());
            Assert::IsFalse(lc.getIsVatPayer());
        }

        TEST_METHOD(Setters_UpdateFields)
        {
            Client c;
            Address addr("Main st", "Minsk", "220000", "Belarus");

            c.setName("Test Client");
            c.setAddress(&addr);
            c.setPhone("+37529");
            c.setEmail("test@example.com");
            c.setStatus("vip");

            Assert::AreEqual(std::string("Test Client"), c.getName());
            Assert::IsTrue(c.getAddress() == &addr);
            Assert::AreEqual(std::string("+37529"), c.getPhone());
            Assert::AreEqual(std::string("test@example.com"), c.getEmail());
            Assert::AreEqual(std::string("vip"), c.getStatus());
        }
    };

}
