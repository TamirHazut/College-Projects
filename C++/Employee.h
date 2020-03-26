#ifndef __EMPLOYEE_H_
#define __EMPLOYEE_H_
#include "Person.h"
#include <iostream>

using namespace std;

class Employee : virtual public Person
{
public:
	enum class eDepartment { TEACHING_FACULTY, FINAL_PROJECTS, EXERCISE_CHECKERS, ADMINISTRATION, MAINTENANCE, NUM_OF_DEPARTMENTS };
	const char* eDepartmentString[(int)eDepartment::NUM_OF_DEPARTMENTS] = { "Teaching Faculty", "Final Projects", "Exercise Checkers", "Administration", "Maintenance" };

private:
	// Members
	int workerID;
	int seniority;
	int salary;
	Employee::eDepartment department;

public:
	// Constructors / Destructor
	Employee(const string& name, const Date& birthDate, int salary, Employee::eDepartment department) :
	Person(name, birthDate), workerID(IDGenerator::generateID(IDGenerator::eIDType::EMPLOYEE)), salary(salary), seniority(0), department(department) {}
	Employee(const Employee& e) : Person(e)
	{
		this->workerID = e.workerID;
		this->seniority = e.seniority;
		this->salary = e.salary;
		this->department = e.department;
	}
	
	virtual void toOs(ostream& os) const override
	{ 
		os << "WorkerID: " << workerID << ", Department: " << eDepartmentString[(int)department] <<  ", Seniority: " << seniority << ", Salary: " << salary << "$ a month." << endl;
	}
	// Getters / Setters
	int getWorkId() const { return this->workerID; }
	int getSeniority() const { return this->seniority; }
	int getSalary() const { return this->salary; }
	Employee::eDepartment getDepartment() const { return this->department; }
	bool setSalary(int salary)
	{
		if (salary < 0)
        	return false;
    	this->salary = salary;
    	return true;
	}

	/* operator ++ for seniority */
	bool operator==(int id) { return this->getPersonID() == id; }
	const Employee& operator++()
	{
		seniority++;
		return *this;
	}
};
#endif
