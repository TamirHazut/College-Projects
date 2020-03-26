#include <string.h>
#include <iostream>

using namespace std;
#include "Course.h"
#include "Student.h"

void Course::setName(const string& name)
{
	this->name = name;
}
Grade* Course::getGradeForStudent(int studentID) 
{
	vector<Grade*>::iterator itr = grades.begin();
	vector<Grade*>::iterator itrEnd = grades.end();
	for (; itr != itrEnd; ++itr)
	{
		Student* s = (*itr)->studentID;
		if (s->getPersonID() == studentID)
		{
			return *itr;
		}
	}
	return nullptr;
}

bool Course::addStudent(Student* student)
{
	if (getGradeForStudent(student->getPersonID()))
		return false;
     
	*this += student;
	 return true;
}
bool Course::deleteStudent(int studentId)
{
	if (!getGradeForStudent(studentId))
		return false;
        
	 *this -= studentId;
	  return true;
}

bool Course::changeStudentTestGrade(int studentID, int grade)
{
	Grade* g = getGradeForStudent(studentID);
	if (!g)
	 return false;
	g->testGrade = grade;
	return true;
	
}
bool Course::changeStudentExercisesGrade(int studentID, int grade)
{
	Grade* g = getGradeForStudent(studentID);
	if (!g)
		return false;
	g->exercisesGrade = grade;
	return true;
}

/* Operators */

const Course& Course::operator=(const Course& c) 
{
	if (this != &c) {
		courseID = c.courseID;
		exerxcisesPercent = c.exerxcisesPercent;
		testPercent = c.testPercent;
		this->name = c.name;
	}
	return *this;
}

bool Course::operator==(const Course& c) const {
	return courseID == c.courseID;
}

const Course& Course::operator+=(Student* student)
{
	Grade* newGrade = new Grade { student ,0 , 0 };
	grades.push_back(newGrade);
	return *this;
}

ostream& operator<<(ostream& os, const Course& c)
{ 
	os << "CourseID: " << c.courseID <<  ", Course Name: " << c.name << endl
		<< "Test percent  Of This Course: " << c.testPercent << "%" << endl
		<< "Exerxcises Percent of this course " << c.exerxcisesPercent << "%"<<"\n" <<	endl;
	return os;
}

const Course& Course::operator-=(int studentID)
{
	vector <Grade*> newGrades;
	vector<Grade*>::iterator itr = grades.begin();
	vector<Grade*>::iterator itrEnd = grades.end();
	for (; itr != itrEnd; ++itr)
	{
		Student* s = (*itr)->studentID;
		if (s->getPersonID() != studentID)
		{
			newGrades.push_back(*itr);
		}
	}
	grades = newGrades;
	numberOfStudent--;
	return *this;
}

int Course::calculateGradeOfCourse(int id)  {
	Grade* g = getGradeForStudent(id);
    int sum = (g->exercisesGrade*exerxcisesPercent/100)+(g->testGrade*testPercent/100);
    return sum;
}


