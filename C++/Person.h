#pragma warning(disable: 4996)
#ifndef _PERSON__H
#define _PERSON__H
#include <iostream>
#include <string.h>
#include "IDGenerator.h"
#include "Date.h"
#include <vector>

using namespace std;
class Person
{
private:
	int personID;
	std::string personName;
	Date birthDate;
	
public:
	// Constructors / Destructor
	
	Person(const string& name, const Date& birthDate) : personID(IDGenerator::generateID(IDGenerator::eIDType::PERSON)), personName(name), birthDate(birthDate) {};
	Person(const Person& p) : birthDate(p.birthDate)
	{
		setName(p.getName());
		this->personID = p.personID;
		this->birthDate = p.birthDate;
	}

	// Getters / Setters
	const string& getName() const { return this->personName; }
	const Date& getBirthDate() const { return this->birthDate; }
	int getPersonID() const { return this->personID; }
	void setName(const string& name) { this->personName = name; }

	virtual void toOs(ostream& os) const { }

	// Operators
	virtual bool operator==(const Person& other) const { return this->personID == other.getPersonID(); }
	friend ostream& operator<<(ostream& os, const Person& p)
	{ 
		os << "Name: " << p.personName << ", ID: " << p.personID << ", Birthdate: " << p.birthDate << endl;
		p.toOs(os);
		return os;
	}
	operator const char* () { return this->personName.c_str(); }
};


#endif // !_PERSON__H