#include "College.h"
#include "Lecturer.h"
#include "Clerk.h"
#include "Guider.h"
#include "ExerciseChecker.h"
#include "Maintenance.h"

College* College::college = nullptr;

College* College::getInstance()
{
	if (!College::college)
		College::college = new College();
	return College::college;
}

// Getters
Employee* College::getWorkerByWorkId(int id) 
{
	Employee* e = nullptr;
	vector<Employee*>::iterator itr = workers.begin();
	vector<Employee*>::iterator itrEnd = workers.end();
	for (; itr != itrEnd; ++itr)
	{
		if (id == (*itr)->getWorkId())
			return *itr;
	}
	return e;
	
}
 Student *College::getStudentById(int id) 
{
	Student* s = nullptr;
	vector<Student*>::iterator itr = students.begin();
	vector<Student*>::iterator itrEnd = students.end();
	for (; itr != itrEnd; ++itr)
	{
		if (id == (*itr)->getPersonID())
		return *itr;
	}
	return s;

	
}
 Course* College::getCourseById(int id) 
{
	Course *c= nullptr;
	vector<Course*>::iterator itr = courses.begin();
	vector<Course*>::iterator itrEnd = courses.end();
	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getCourseID() == id)
		  return *itr;
	}
	return c;
}

// Add/Remove functions
bool College::addEmployee( Employee* worker) 
{
	if (!worker)
		return false;
		
	if (getWorkerByWorkId(worker->getWorkId()))
		return false;
	
	    *this += worker;
		 return true;
}
bool College::addStudent( Student* student)
{
	if (getStudentById(student->getPersonID()))
		return false;

	*this += student;
	 return true;
}
bool College::addCourse( Course* course)
{
	if (getCourseById(course->getCourseID()))
		return false;

    *this += course;
	 return true;
}

bool College::removeStudent( Student * student)
{
	if (getStudentById(student->getPersonID()))
	{
	 *this -= student;
	 return true;
	}
	return false;
}
bool College::removeEmployee( Employee * employee)
{
	if (getWorkerByWorkId(employee->getWorkId()))
	{
		*this -= employee;
		return true;
	}
	return false;
}
bool College::removeCourse( Course *course)
{
	    if(getCourseById(course->getCourseID()))
		{
			vector<Student*>::iterator itr = students.begin();
			vector<Student*>::iterator itrEnd = students.end();
	         for (;itr!=itrEnd;++itr)
			 {
				 
				 (*itr)->deleteCourse(course);
		     }
			 vector<Employee*>::iterator EmployeeItr = workers.begin();
			 vector<Employee*>::iterator EmployeeitrEnd = workers.end();
			 for (; EmployeeItr != EmployeeitrEnd; ++EmployeeItr)
			 {
				 Employee* e = getWorkerByWorkId((*EmployeeItr)->getPersonID());
				 if ( Lecturer*  lecturer = dynamic_cast<Lecturer*>(e)) 
				 {
					 lecturer->deleteCourse(*course);
				 }

			 }
	    	*this -= course;
		    return true;
	}
		return false;
}

/* Operators */
const College& College::operator+=(Employee* employee)
{
	workers.push_back(employee);
	return *this;
 }
const College& College::operator+=( Student* student) 
{	
	students.push_back(student);
	return *this;
}
const College& College::operator+=( Course* course) 
{
	courses.push_back(course);
	return *this;
}
const College& College::operator-=( Employee* employee) 
{
	vector<Employee*> newEmployee;
	vector<Employee*>::iterator itr = workers.begin();
	vector<Employee*>::iterator itrEnd = workers.end();
	for (; itr != itrEnd; ++itr) 
	{
		if ((*itr)->getWorkId() != employee->getWorkId())
		{
			newEmployee.push_back(*itr);
		}
	}
	workers = newEmployee;
	return *this;
}
const College& College::operator-=( Student* student)
{
	vector <Student*> newStudent;
	vector<Student*>::iterator itr = students.begin();
	vector<Student*>::iterator itrEnd = students.end();
	for (; itr != itrEnd; ++itr) 
	{
		if ((*itr)->getPersonID() != student->getPersonID()) 
		{
			newStudent.push_back(*itr);
		}
	}
	students = newStudent;
	return *this;
}
const College& College::operator-=( Course* course)
{
	vector <Course*> newCourse;
	vector<Course*>::iterator itr = courses.begin();
	vector<Course*>::iterator itrEnd = courses.end();
	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getCourseID() != course->getCourseID())
		{
			newCourse.push_back(*itr);
		}
	}
	courses = newCourse;
	return *this;
}
 