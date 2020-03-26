#ifndef _EXERCISECHECKER__H
#define _EXERCISECHECKER__H

#include "Student.h"
#include "Employee.h"
#include "Course.h"

#include <iostream>

using namespace std;

class ExerciseChecker : public Student, public Employee
{
private:

	// Members
	 Course* course; // Pointer to a course to check

public:

	ExerciseChecker(const Employee& e, const Student& s,  Course* course)
					: Person(e.getName(), e.getBirthDate()),
					Employee(e),
					Student(s), course(course) {}
	ExerciseChecker(const ExerciseChecker& exerciseChecker) = delete;

	virtual void toOs(ostream& os) const override
	{
		Employee::toOs(os);
		os << "exercise in course:" << *course << endl;;
	}

	// Getters / Setters
	const Course* getCourse() const { return this->course; }
	double getExerciseGradeByStudentId(int studentId) const;

	// Other Functions
	bool addExerciseGrade(int studentId, int courseID, int grade);
	bool changeGradeToStudent(int studentID, int courseID, double grade) { return course->changeStudentExercisesGrade(studentID, grade); }
};

#endif // !_EXERCISECHECKER__H