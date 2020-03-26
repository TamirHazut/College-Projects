#include <string.h>
#include "Lecturer.h"
#include "Node.h"

Course& Lecturer::getCourseById(int id) 
{
	Course* c = nullptr;
	Node<Course> *node = courses.getHead();
	for (int i = 0; i < courses.size(); i++)
	{
		if (node->data.getCourseID() == id)
			return node->data;
	}
	return *c;
}

bool Lecturer::changeGradeToStudent(int studentID, int courseID, double grade)
{
	Course* course = &getCourseById(courseID);
    if (!course)
        return false;
	return course->changeStudentTestGrade(studentID, grade);
}
