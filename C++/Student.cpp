#include "Student.h"

 Course* Student::getCourseById(int id) 
{
	 Course* c = nullptr;
	 vector<Course*>::iterator itr = courses.begin();
	 vector<Course*>::iterator itrEnd = courses.end();
	 for (; itr != itrEnd; ++itr)
	 {
		 if ((*itr)->getCourseID() == id)
    		 return *itr;
	 }
	 return c;
 }
 void Student::calculateAverage()
 {
	 if (courses.empty())
	 	return;
	 int sum = 0;
	 vector<Course*>::iterator itr = courses.begin();
	 vector<Course*>::iterator itrEnd = courses.end();
	 for (; itr != itrEnd; ++itr)
	 {
		 sum += (*itr)->calculateGradeOfCourse(getPersonID());
		 if (sum == -1)
			 return;
	 }
	 average = sum / courses.size();
 }
bool  Student::addCourse( Course* course)
{
	if (!getCourseById(course->getCourseID()))
	{
		*this += course;
		return true;
	}
	return false;
}

bool Student::deleteCourse( Course* course)
{
	if (getCourseById(course->getCourseID()))
	{
		*this -= course;
			return true;
	}

	return false;
}
const Student& Student::operator +=(Course* course) 
{
	courses.push_back(course);
	return *this;
}
const Student&  Student::operator-=(Course* course)
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
