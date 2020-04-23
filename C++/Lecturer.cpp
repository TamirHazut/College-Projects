#include <string.h>
#include "Lecturer.h"
#include "Node.h"

Course* Lecturer::getCourseById(int id) 
{
	Node<Course*> *node = courses.getHead();
	for (int i = 0; i < courses.size(); i++)
	{
		if (node->data->getCourseID() == id)
			return node->data;
	}
	return nullptr;
}

bool Lecturer::changeGradeToStudent(int studentID, int courseID, double grade)
{
	Course* course = getCourseById(courseID);
    if (!course)
        return false;
	return course->changeStudentTestGrade(studentID, grade);
}
