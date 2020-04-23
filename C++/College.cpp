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
	vector<Employee*>::iterator itr = workers.begin();
	vector<Employee*>::iterator itrEnd = workers.end();
	for (; itr != itrEnd; ++itr)
	{
		if (id == (*itr)->getWorkId())
			return *itr;
	}
	return nullptr;
	
}
 Student *College::getStudentById(int id) 
{
	vector<Student*>::iterator itr = students.begin();
	vector<Student*>::iterator itrEnd = students.end();
	for (; itr != itrEnd; ++itr)
	{
		if (id == (*itr)->getPersonID())
		return *itr;
	}
	return nullptr;

	
}
 Course* College::getCourseById(int id) 
{
	vector<Course*>::iterator itr = courses.begin();
	vector<Course*>::iterator itrEnd = courses.end();
	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getCourseID() == id)
		  return *itr;
	}
	return nullptr;
}

// Add/Remove functions
bool College::addEmployee( Employee& worker)
{
	if (!worker)
		return false;
		
	if (getWorkerByWorkId(worker.getWorkId()))
		return false;
	
	    *this += &worker;
		 return true;
}
bool College::addStudent( Student& student)
{
	if (getStudentById(student.getPersonID()))
		return false;

	*this += &student;
	 return true;
}
bool College::addCourse( Course& course)
{
	if (getCourseById(course.getCourseID()))
		return false;

    *this += &course;
	 return true;
}

bool College::removeStudent( Student& student)
{
	if (getStudentById(student.getPersonID()))
	{
	 *this -= &student;
	 return true;
	}
	return false;
}
bool College::removeEmployee( Employee& employee)
{
	if (getWorkerByWorkId(employee.getWorkId()))
	{
		*this -= &employee;
		return true;
	}
	return false;
}
bool College::removeCourse( Course& course)
{
	    if(getCourseById(course.getCourseID()))
		{
			vector<Student*>::iterator itr = students.begin();
			vector<Student*>::iterator itrEnd = students.end();
	         for (;itr!=itrEnd;++itr)
			 {
				 
				 (*itr)->deleteCourse(&course);
		     }
			 vector<Employee*>::iterator EmployeeItr = workers.begin();
			 vector<Employee*>::iterator EmployeeitrEnd = workers.end();
			 for (; EmployeeItr != EmployeeitrEnd; ++EmployeeItr)
			 {
				 Employee* e = getWorkerByWorkId((*EmployeeItr)->getPersonID());
				 if ( Lecturer*  lecturer = dynamic_cast<Lecturer*>(e)) 
				 {
					 lecturer->deleteCourse(course);
				 }

			 }
	    	*this -= &course;
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
	vector<Employee*>::iterator itr = workers.begin();
	vector<Employee*>::iterator itrEnd = workers.end();
	for (; itr != itrEnd; ++itr) 
	{
		if ((*itr)->getWorkId() != employee->getWorkId())
		{
			workers.erase(itr);
		}
	}
	return *this;
}
const College& College::operator-=( Student* student)
{
	vector<Student*>::iterator itr = students.begin();
	vector<Student*>::iterator itrEnd = students.end();
	for (; itr != itrEnd; ++itr) 
	{
		if ((*itr)->getPersonID() != student->getPersonID()) 
		{
			students.erase(itr);
		}
	}
	return *this;
}
const College& College::operator-=( Course* course)
{
	vector<Course*>::iterator itr = courses.begin();
	vector<Course*>::iterator itrEnd = courses.end();
	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getCourseID() != course->getCourseID())
		{
			courses.erase(itr);
		}
	}
	return *this;
}
 