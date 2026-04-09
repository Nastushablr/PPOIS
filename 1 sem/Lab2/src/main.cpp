#include <iostream>
#include "base/Date.h"
#include "base/Address.h"
#include "base/Person.h"
#include "clients/PrivateClient.h"

using namespace std;

int main() {
    Date reg(1, 3, 2025);
    Date birth(10, 5, 1990);
    Address addr("Lenina 1", "Minsk", "220000", "Belarus");
    Person p(1, "Ivan", "Ivanov", birth, "+375291234567", "ivan@test.com", "AB1234567");
    PrivateClient client(101, &p, &addr, reg, "+375291234567", "ivan@test.com");

    cout << "Client: " << client.getName() << endl;
    cout << "Age: " << p.getAge(reg) << endl;

    return 0;
}
