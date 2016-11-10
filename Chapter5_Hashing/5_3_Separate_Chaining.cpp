//
// Created by 涂金戈 on 09/11/2016.
//

#include "SeparateChainingHashTable.h"
#include "Employee.h"
#include <iostream>

int main() {
    Employee e1("Adam");
    Employee e2("Bob");
    Employee e3("Cathy");
    Employee e4("Donne");

    SeparateChainingHashTable<Employee> sch;
    sch.insert(e1);
    sch.insert(e2);

    if (!sch.contains(e3))
        std::cout << e3.getName() << " is not here.\n";
    else
        std::cout << e3.getName() << " is here.\n";

    sch.insert(e3);

    if (!sch.contains(e3))
        std::cout << e3.getName() << " is not here.\n";
    else
        std::cout << e3.getName() << " is here.\n";

    if (!sch.contains(Employee("Cauchy")))
        std::cout << "Cauchy is not here.\n";
    else
        std::cout << "Cauchy is here.\n";

    sch.insert(e4);

    sch.makeEmpty();

    if (!sch.contains(e3))
        std::cout << e3.getName() << " is not here.\n";
    else
        std::cout << e3.getName() << " is here.\n";

    return 0;
}
