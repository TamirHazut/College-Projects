#ifndef _MAINTENANCE__H
#define _MAINTENANCE__H
#include <iostream>
#include "Person.h"
#include "Employee.h"

using namespace std;

class Maintenance : public Employee
{
private:
	Employee::eDepartment department;
public:

	Maintenance(const string& name, const Date& birthDate, int salary) 
	: Person(name, birthDate), Employee(name, birthDate, salary, Employee::eDepartment::MAINTENANCE) {}
	Maintenance(const Maintenance& maintenance) = delete;
	virtual ~Maintenance();

	Employee::eDepartment getDepartment() const { return this->department; }

};

#endif // !_MAINTENANCE__H
