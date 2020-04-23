#ifndef _COLLEGE__H
#define _COLLEGE__H

#include <iostream>
#include <vector>

#include "Student.h"
#include "Employee.h"
#include "ExerciseChecker.h"
#include "Lecturer.h"
#include "Guider.h"
#include "Clerk.h"
#include "Maintenance.h"

using namespace std;

class College
{
private:
	// Members
	vector<Employee*> workers;
	vector<Student*> students;
	vector<Course*> courses;
	// Constructors
	College() {}
	College(const College& c);
	static College* college;

public:
	static College* getInstance();
	const College& operator=(const College& other);
	// Getters / Setters
	int getNumberOfStudents() const { return students.size(); }
	int getNumberOfWorkers() const { return workers.size(); }
	int getNumberOfCourses() const { return courses.size(); }
	Employee* getWorkerByWorkId(int id);
	Student* getStudentById(int id);
	Course* getCourseById(int id);

	// Add/Remove functions for college
	bool addEmployee(Employee& worker);
	bool addStudent(Student& student);
	bool addCourse( Course& course);
	bool removeEmployee(Employee& employee);
	bool removeStudent( Student& student);  
	bool removeCourse( Course& course);

	// Create/Delete functions (from menu)
	Lecturer& createLecturer(const string & name, Date birthdate, int salary) const { return *(new Lecturer(name, birthdate, salary)); }
	Guider& createGuider(const string & name, Date birthdate, int salary) const { return *(new Guider(name, birthdate, salary)); }
	ExerciseChecker& createExerciseChecker(const string & name, Date birthdate, int salary, const Student& s, Course* c) const 
	{
		return *(new ExerciseChecker(*(new Employee(name, birthdate, salary, Employee::eDepartment::EXERCISE_CHECKERS)), s, c));
	}
	Clerk& createClerk(const string& name, Date birthdate, int salary) const { return *(new Clerk(name, birthdate, salary)); }
	Maintenance& createMaintenance(const string & name, Date birthdate, int salary) const { return *(new Maintenance(name, birthdate, salary)); }
	
	void show(ostream& os) const  {
		vector<Course*>::const_iterator CourseItr = courses.begin();
		vector<Course*>::const_iterator CourseItrEnd = courses.end();
		vector<Student*>::const_iterator StudentItr = students.begin();
		vector<Student*>::const_iterator StudentItrEnd = students.end();
		vector<Employee*>::const_iterator EmployeeItr = workers.begin();
		vector<Employee*>::const_iterator EmployeeItrEnd = workers.end();
		os << "Number of workers: " << workers.size() << endl;
		if (workers.size()> 0)
		{
			os << "Workers:" << endl;
			for (; EmployeeItr != EmployeeItrEnd; ++EmployeeItr)
			{
				os << **EmployeeItr;
			}
		}
		os << "--\nNumber of student: " << students.size() << endl; 
		if (students.size()> 0)
		{
			for (; StudentItr != StudentItrEnd; ++StudentItr)
			{
				os << **StudentItr;
			}
		}
		os << "--\nNumber of courses: " << courses.size() << endl;
		if (courses.size() >0)
		{
			os << "Courses:" << endl;
			for (; CourseItr != CourseItrEnd; ++CourseItr)
			{
				os << **CourseItr;
			}
		}
	}

	friend ostream& operator<<(ostream& os, College& c)
	{
		c.show(os);
		return os;
	}

private:
	const College& operator+=(Employee* employee);
	const College& operator+=(Student* student);
	const College& operator+=(Course* course);
	const College& operator-=(Employee* employee);
	const College& operator-=(Student* student);
	const College& operator-=(Course* course);
};

#endif // !_COLLEGE__H