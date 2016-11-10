//
// Created by 涂金戈 on 09/11/2016.
//

#include <iostream>
#include "LinearProbingHashTable.h"
#include "Employee.h"

int main() {
    Employee e1("Adam");
    Employee e2("Bob");
    Employee e3("Cathy");
    Employee e4("Donne");

    LinearProbingHashTable<Employee> lph;
    lph.insert(e1);
    lph.insert(e2);

    if (!lph.contains(e3))
        std::cout << e3.getName() << " is not here.\n";
    else
        std::cout << e3.getName() << " is here.\n";

    lph.insert(e3);

    if (!lph.contains(e3))
        std::cout << e3.getName() << " is not here.\n";
    else
        std::cout << e3.getName() << " is here.\n";

    if (!lph.contains(Employee("Cauchy")))
        std::cout << "Cauchy is not here.\n";
    else
        std::cout << "Cauchy is here.\n";

    lph.insert(e4);

    lph.makeEmpty();

    if (!lph.contains(e3))
        std::cout << e3.getName() << " is not here.\n";
    else
        std::cout << e3.getName() << " is here.\n";

    return 0;
}