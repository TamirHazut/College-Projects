#ifndef _CLERK__H
#define _CLERK__H

#include "College.h"
#include <iostream>

using namespace std;

class Clerk : public Employee 
{
private:
	Employee::eDepartment department;

public:
	Clerk(const string& name, const Date& birthDate, int salary)
	: Person(name, birthDate), Employee(name, birthDate, salary, Employee::eDepartment::ADMINISTRATION) {}
	Clerk(const Clerk& clerk) = delete;

	Employee::eDepartment getDepartment() const { return this->department; }
	void setDeprtment(Employee::eDepartment dep);

};

#endif // !_CLERK__H
