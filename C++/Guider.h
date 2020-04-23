#ifndef _GUIDER__H
#define _GUIDER__H

#include "Lecturer.h"
#include "FinalProject.h"
#include <iostream>

using namespace std;

class Guider : public Lecturer
{
private:
	FinalProject* finalProject;
	

public:

	Guider(const string& name, const Date& birthDate, int salary,
	FinalProject* finalProject = nullptr)
		: Person(name, birthDate), Lecturer(name, birthDate, salary), finalProject(finalProject) {}
	Guider(const Guider& guider) : Person(guider), Lecturer(guider), finalProject(nullptr) {}

	FinalProject* getFinalProject() const { return this->finalProject; }
	bool setFinalProject(FinalProject* finalProject);


	virtual void toOs(ostream& os) const override
	{
		Lecturer::toOs(os);
		if (getFinalProject() != nullptr)
    		os << "Final Project :" << *finalProject << endl;
	}
};

#endif // !_GUIDER__H
