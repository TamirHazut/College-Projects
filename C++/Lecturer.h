#ifndef _LECTURER__H
#define _LECTURER__H

#include <iostream>
using namespace std;

#include "Person.h"
#include "Employee.h"
#include "Course.h"
#include "LinkedList.h"
class Course;

class Lecturer : public Employee
{
private:
	LinkedList<Course*> courses;

public:
	Lecturer(const string& name, const Date& birthDate, int salary)
		: Person(name, birthDate), Employee(name, birthDate, salary, eDepartment::TEACHING_FACULTY) {};
	/* Constructors */ 
	Lecturer(const Lecturer& lec) : Person(lec), Employee(lec){}
	
	/* Getters/Setters */
	int getNumOfCourses() const { return courses.size(); }
	Course* getCourseById(int id);
	bool addCourse(Course& course) { return courses.add(&course); }
	bool deleteCourse(const Course & course) { return courses.remove(new Course(course)); }
	bool changeGradeToStudent(int studentID, int courseID, double grade);

	
	virtual void toOs(ostream& os) const override	{
		Employee::toOs(os);
		if (!courses.isEmpty())
		{
			os << "Lecturing Courses:" << endl;
			os << courses << endl;
		}
	}
};

#endif // !_LECTURER__H