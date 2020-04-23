#ifndef _STUDENT__H
#define _STUDENT__H
#include <iostream>

#include "Person.h"
#include "FinalProject.h"
#include "Course.h"
#include "Date.h"


// class Course;
using namespace std;

class Student : virtual public Person
{
private:
	int currentYear;
	int currentSemester;
	double average;
	Date startDate;
	vector<Course*> courses;
	FinalProject* finalProject;

public:
	// Constructors / Destructor
	Student(const char* name, const Date& birthDate, int currentYear, int currentSemester,
		const Date& startDate, FinalProject* finalProject = nullptr) 
		: Person(name, birthDate), currentYear(currentYear), currentSemester(currentSemester), startDate(startDate), finalProject(finalProject), average(0) {}
	Student(const Student& s) : Person(s), startDate(s.startDate), finalProject(nullptr)
	{
		
		this->courses = courses;
		this->currentYear = s.currentYear;
		this->currentSemester = s.currentSemester;
		setFinalProject(s.getFinalProject());
	}
	// Getters / Setters
	int getCurrentYear() const { return this->currentYear; }
	int getCurrentSemester() const { return this->currentSemester; }
	int getNumberOfCourses() const { return this->courses.size(); }
	double getAverageOfStudent()const { return this->average; }
	FinalProject* getFinalProject() const { return this->finalProject; }
	const Date& getStartDate() const { return this->startDate; }
	Course* getCourseById(int id) ;

	void setCurrentYear(int currentYear) {
		this->currentYear = currentYear;
	}
	void setCurrentSemester(int currentSemester) {
		this->currentSemester = currentSemester;
	}
	void setFinalProject(FinalProject* finalProject) {
		this->finalProject = finalProject;
	}

	virtual void toOs(ostream& os) const override
	{
		int i = 0;
		os << "Year of study: " << currentYear << ", Current semester: " << currentSemester << ", Number of courses: " << courses.size() << ", Start date: " << startDate << endl;
		if (finalProject)
			os << "Final project:\n" << *finalProject << endl;
		if (courses.size() > 0)
		{
			os << "Courses:" << endl;
			vector<Course*>::const_iterator itr = courses.begin();
			vector<Course*>::const_iterator itrEnd = courses.end();
			for (; itr != itrEnd; ++itr)
			{
				Grade* g = (*itr)->getGradeForStudent(getPersonID());
				os << "[Course-" << (i + 1) << ":" << (*itr)->getName()
				<< ", Test Grade: " << g->testGrade*(*itr)->getTestPercent()/100
				<< ", Exercises Grade: " << g->exercisesGrade*(*itr)->getTestPercent()/100
				<< "]" << endl;
				i++;
			}
		}	
	}

	// Other Functions
	bool addCourse(Course* course);
	bool deleteCourse( Course *course);
	void calculateAverage();
	bool operator==(int id) const { return this->getPersonID() == id; }

private:
	bool operator==(const Student& s) const { return this->average == s.average; }
	bool operator>(const Student& s) const { return this->average > s.average; }
	bool operator<(const Student& s) const { return this->average < s.average; }
	const Student& operator +=( Course* course) ;
	const Student& operator -=( Course* course);

};

#endif 