//
// Created by 涂金戈 on 09/11/2016.
//

#include <iostream>
#include "DoubleHashingHashTable.h"
#include "Employee.h"

int main() {
    Employee e1("Adam");
    Employee e2("Bob");
    Employee e3("Cathy");
    Employee e4("Donne");

    DoubleHashingHashTable<Employee> dhh;
    dhh.insert(e1);
    dhh.insert(e2);

    if (!dhh.contains(e3))
        std::cout << e3.getName() << " is not here.\n";
    else
        std::cout << e3.getName() << " is here.\n";

    dhh.insert(e3);

    if (!dhh.contains(e3))
        std::cout << e3.getName() << " is not here.\n";
    else
        std::cout << e3.getName() << " is here.\n";

    if (!dhh.contains(Employee("Cauchy")))
        std::cout << "Cauchy is not here.\n";
    else
        std::cout << "Cauchy is here.\n";

    dhh.insert(e4);

    dhh.makeEmpty();

    if (!dhh.contains(e3))
        std::cout << e3.getName() << " is not here.\n";
    else
        std::cout << e3.getName() << " is here.\n";

    return 0;
}