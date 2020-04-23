#pragma warning(disable: 4996)
#ifndef _COURSE__H
#define _COURSE__H

#include <iostream>
#include <string.h>
#include "IDGenerator.h"
#include <vector>

using namespace std;

class Student;

typedef struct 
{
	Student* studentID;
	int testGrade;
	int exercisesGrade;
} Grade;

class Course
{
private:
	int courseID;
	double exerxcisesPercent; // Exercises weight on course grade
	double testPercent; // test weight on course grade
	std::string name;
	int numberOfStudent;
	vector<Grade*> grades;

public:
	// Constructors / Destructor
	Course(const std::string& name, double testPercent) 
	: courseID(IDGenerator::generateID(IDGenerator::eIDType::COURSE)), name(name), testPercent(testPercent), exerxcisesPercent((100-testPercent)), numberOfStudent(0) {}
	

	/* Getters/Setters */ 
	int getCourseID() const { return this->courseID; }
	double getExerxcisesPercent() const { return this->exerxcisesPercent; }
	double getTestPercent() const { return this->testPercent; }
	int getNumOfStudents() const { return this->numberOfStudent; }
	const string & getName() const { return this->name; }
	Grade* getGradeForStudent(int studentID);
	void setName(const string& name);
	/* Other Functions */

	bool addStudent(Student* student);
	bool deleteStudent(int id);
	bool changeStudentTestGrade(int studentID, int grade);
	bool changeStudentExercisesGrade(int studentID, int grade);
	int calculateGradeOfCourse(int id);

	/* Operators Overload */
	bool operator==(const Course& c) const;
	const Course& operator =(const Course& c);
	Course* operator*(const Course& c) { return this; }
	operator const char* ()  { return this->name.c_str(); }
	
	friend ostream& operator<<(ostream& os,  const Course& c); 
private:
	const Course& operator+=(Student* student);
	const Course& operator-=(int studentID);
};


#endif 