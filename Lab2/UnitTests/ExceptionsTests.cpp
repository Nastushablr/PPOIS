#include "CppUnitTest.h"
#include "../Lab2/src/exceptions/RepairFirmExceptions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RepairFirmTests
{
    TEST_CLASS(ExceptionsTests)
    {
    public:

        TEST_METHOD(InvalidPersonDataException_IsRuntimeError)
        {
            try
            {
                throw InvalidPersonDataException("invalid person");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("invalid person") != string::npos);
                return;
            }
        }

        TEST_METHOD(InvalidAddressException_IsRuntimeError)
        {
            try
            {
                throw InvalidAddressException("invalid address");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("invalid address") != string::npos);
                return;
            }
        }

        TEST_METHOD(InvalidDateException_IsRuntimeError)
        {
            try
            {
                throw InvalidDateException("invalid date");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("invalid date") != string::npos);
                return;
            }
        }

        TEST_METHOD(InvalidClientException_IsRuntimeError)
        {
            try
            {
                throw InvalidClientException("invalid client");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("invalid client") != string::npos);
                return;
            }
        }

        TEST_METHOD(InvalidEmployeeException_IsRuntimeError)
        {
            try
            {
                throw InvalidEmployeeException("invalid employee");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("invalid employee") != string::npos);
                return;
            }
        }

        TEST_METHOD(InvalidProjectException_IsRuntimeError)
        {
            try
            {
                throw InvalidProjectException("invalid project");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("invalid project") != string::npos);
                return;
            }
        }

        TEST_METHOD(InsufficientMaterialException_IsRuntimeError)
        {
            try
            {
                throw InsufficientMaterialException("insufficient material");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("insufficient material") != string::npos);
                return;
            }
        }

        TEST_METHOD(InvalidPaymentException_IsRuntimeError)
        {
            try
            {
                throw InvalidPaymentException("invalid payment");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("invalid payment") != string::npos);
                return;
            }
        }

        TEST_METHOD(InsufficientFundsException_IsRuntimeError)
        {
            try
            {
                throw InsufficientFundsException("insufficient funds");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("insufficient funds") != string::npos);
                return;
            }
        }

        TEST_METHOD(ScheduleConflictException_IsRuntimeError)
        {
            try
            {
                throw ScheduleConflictException("schedule conflict");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("schedule conflict") != string::npos);
                return;
            }
        }

        TEST_METHOD(ContractViolationException_IsRuntimeError)
        {
            try
            {
                throw ContractViolationException("contract violation");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("contract violation") != string::npos);
                return;
            }
        }

        TEST_METHOD(OperationNotAllowedException_IsRuntimeError)
        {
            try
            {
                throw OperationNotAllowedException("operation not allowed");
            }
            catch (const runtime_error& e)
            {
                Assert::IsTrue(string(e.what()).find("operation not allowed") != string::npos);
                return;
            }
        }
    };
}
