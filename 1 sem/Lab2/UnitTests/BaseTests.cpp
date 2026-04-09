#include "CppUnitTest.h"

#include "../Lab2/src/base/Date.h"
#include "../Lab2/src/base/Address.h"
#include "../Lab2/src/base/Person.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RepairFirmTests
{
    TEST_CLASS(DateTests)
    {
    public:

        TEST_METHOD(Constructor_Default_IsValid)
        {
            Date d;
            Assert::AreEqual(1, d.getDay());
            Assert::AreEqual(1, d.getMonth());
            Assert::AreEqual(2000, d.getYear());
            Assert::IsTrue(d.isValid());
        }

        TEST_METHOD(Constructor_Custom_AndToString)
        {
            Date d(1, 3, 2025);
            Assert::AreEqual(1, d.getDay());
            Assert::AreEqual(3, d.getMonth());
            Assert::AreEqual(2025, d.getYear());
            Assert::AreEqual(std::string("01.03.2025"), d.toString());
        }

        TEST_METHOD(SetDate_Invalid_RollsBack)
        {
            Date d;
            d.setDate(31, 2, 2023);
            Assert::AreEqual(1, d.getDay());
            Assert::AreEqual(1, d.getMonth());
            Assert::AreEqual(2000, d.getYear());
        }

        TEST_METHOD(AddDays_LeapYear)
        {
            Date d(28, 2, 2024);
            d.addDays(2);
            Assert::AreEqual(1, d.getDay());
            Assert::AreEqual(3, d.getMonth());
            Assert::IsTrue(d.isValid());
        }

        TEST_METHOD(Compare_And_DaysUntil)
        {
            Date d1(1, 1, 2024);
            Date d2(5, 1, 2024);
            Assert::IsTrue(d1 < d2);
            Assert::IsTrue(d2 > d1);
            Assert::IsFalse(d1 == d2);
            Assert::AreEqual(4, d1.daysUntil(d2));
            Assert::AreEqual(-4, d2.daysUntil(d1));
        }
    };

    TEST_CLASS(AddressTests)
    {
    public:

        TEST_METHOD(FullAddress_AndValidation)
        {
            Address a("Lenina 1", "Minsk", "220000", "Belarus", "10", "15");
            Assert::IsTrue(a.isValid());
            Assert::IsTrue(a.validatePostalCode());

            std::string full = a.getFullAddress();
            Assert::IsTrue(full.find("Lenina 1") != std::string::npos);
            Assert::IsTrue(full.find("Minsk") != std::string::npos);
            Assert::IsTrue(full.find("Belarus") != std::string::npos);
        }

        TEST_METHOD(Setters_UpdateFields)
        {
            Address a;
            a.setStreet("Nezavisimosti 5");
            a.setCity("Minsk");
            a.setPostalCode("220001");
            a.setCountry("Belarus");
            a.setBuilding("5");
            a.setApartment("7");

            Assert::AreEqual(std::string("Nezavisimosti 5"), a.getStreet());
            Assert::AreEqual(std::string("Minsk"), a.getCity());
            Assert::AreEqual(std::string("220001"), a.getPostalCode());
            Assert::AreEqual(std::string("Belarus"), a.getCountry());
            Assert::AreEqual(std::string("5"), a.getBuilding());
            Assert::AreEqual(std::string("7"), a.getApartment());
        }

        TEST_METHOD(Address_Invalid_WhenEmpty)
        {
            Address a;
            Assert::IsFalse(a.isValid());
            Assert::IsFalse(a.validatePostalCode());
        }
    };

    TEST_CLASS(PersonTests)
    {
    public:

        TEST_METHOD(FullName_AndGetters)
        {
            Date birth(10, 5, 1990);
            Person p(1,
                "Ivan",
                "Ivanov",
                birth,
                "+375291234567",
                "ivan@example.com",
                "AB1234567",
                "BY");

            Assert::AreEqual(1, p.getId());
            Assert::AreEqual(std::string("Ivan"), p.getFirstName());
            Assert::AreEqual(std::string("Ivanov"), p.getLastName());
            Assert::AreEqual(std::string("Ivan Ivanov"), p.getFullName());
            Assert::AreEqual(std::string("AB1234567"), p.getPassportNumber());
        }

        TEST_METHOD(Age_Calculation)
        {
            Date birth(10, 5, 1990);
            Date today(1, 3, 2025);
            Person p(1, "Ivan", "Ivanov", birth, "+37529", "ivan@example.com", "AB1234567");

            int age = p.getAge(today);
            Assert::AreEqual(34, age);
        }

        TEST_METHOD(Email_Validation_AndUpdateContact)
        {
            Date birth(10, 5, 1990);
            Person p(1, "Ivan", "Ivanov", birth, "+37529", "wrong", "AB1234567");

            Assert::IsFalse(p.validateEmail());

            p.updateContact("+375291112233", "ivan@example.com");
            Assert::AreEqual(std::string("+375291112233"), p.getPhone());
            Assert::AreEqual(std::string("ivan@example.com"), p.getEmail());
            Assert::IsTrue(p.validateEmail());
        }

        TEST_METHOD(DefaultConstructor_InitializesFields)
        {
            Person p;
            Assert::AreEqual(0, p.getId());
            Assert::AreEqual(std::string(""), p.getFirstName());
            Assert::AreEqual(std::string(""), p.getLastName());
            Assert::AreEqual(std::string(""), p.getPhone());
            Assert::AreEqual(std::string(""), p.getEmail());
            Assert::AreEqual(std::string(""), p.getPassportNumber());
            Assert::AreEqual(std::string(""), p.getNationality());
        }

        TEST_METHOD(Setters_UpdateFields)
        {
            Person p;
            Date birth(2, 3, 1990);

            p.setFirstName("Ivan");
            p.setLastName("Petrov");
            p.setBirthDate(birth);
            p.setPhone("+37529");
            p.setEmail("ivan@example.com");
            p.setPassportNumber("AB1234567");
            p.setNationality("BY");

            Assert::AreEqual(std::string("Ivan"), p.getFirstName());
            Assert::AreEqual(std::string("Petrov"), p.getLastName());
            Assert::AreEqual(2, p.getBirthDate().getDay());
            Assert::AreEqual(std::string("+37529"), p.getPhone());
            Assert::AreEqual(std::string("ivan@example.com"), p.getEmail());
            Assert::AreEqual(std::string("AB1234567"), p.getPassportNumber());
            Assert::AreEqual(std::string("BY"), p.getNationality());
        }
    };
}
