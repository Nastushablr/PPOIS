#include "exceptions/RepairFirmExceptions.h"

InvalidPersonDataException::InvalidPersonDataException(const string& msg)
    : runtime_error(msg) {
}

InvalidAddressException::InvalidAddressException(const string& msg)
    : runtime_error(msg) {
}

InvalidDateException::InvalidDateException(const string& msg)
    : runtime_error(msg) {
}

InvalidClientException::InvalidClientException(const string& msg)
    : runtime_error(msg) {
}

InvalidEmployeeException::InvalidEmployeeException(const string& msg)
    : runtime_error(msg) {
}

InvalidProjectException::InvalidProjectException(const string& msg)
    : runtime_error(msg) {
}

InsufficientMaterialException::InsufficientMaterialException(const string& msg)
    : runtime_error(msg) {
}

InvalidPaymentException::InvalidPaymentException(const string& msg)
    : runtime_error(msg) {
}

InsufficientFundsException::InsufficientFundsException(const string& msg)
    : runtime_error(msg) {
}

ScheduleConflictException::ScheduleConflictException(const string& msg)
    : runtime_error(msg) {
}

ContractViolationException::ContractViolationException(const string& msg)
    : runtime_error(msg) {
}

OperationNotAllowedException::OperationNotAllowedException(const string& msg)
    : runtime_error(msg) {
}
