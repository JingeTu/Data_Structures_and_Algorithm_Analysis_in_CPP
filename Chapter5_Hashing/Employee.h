//
// Created by 涂金戈 on 09/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_EMPLOYEE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_EMPLOYEE_H

#include <string>

class Employee {
public:
    Employee() {}

    Employee(std::string name, double salary = 0, int seniority = 0) : name{name} {}

    const std::string &getName() const { return name; }

    bool operator==(const Employee &rhs) const { return getName() == rhs.getName(); }

    bool operator!=(const Employee &rhs) const { return !(*this == rhs); }

private:
    std::string name;
    double salary;
    int seniority;
};

template<>
class hash<Employee> {
public:
    size_t operator()(const Employee &item) {
        static hash<std::string> hf;
        return hf(item.getName());
    }
};

template<>
class hash2<Employee> {
public:
    int operator()(const Employee &item) {
        static hash2<std::string> hf;
        return hf(item.getName());
    }
};
#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_EMPLOYEE_H
