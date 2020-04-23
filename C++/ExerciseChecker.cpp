#include "ExerciseChecker.h"

double ExerciseChecker::getExerciseGradeByStudentId(int studentId) const 
{
	Grade* grade = course->getGradeForStudent(studentId);
	return (grade ? grade->exercisesGrade : -1);
}
bool ExerciseChecker::addExerciseGrade(int studentId, int courseID, int grade) 
{
	Grade* fGrade = course->getGradeForStudent(studentId);
	if (fGrade)
	{
		fGrade->exercisesGrade = grade;
		return true;
	}
	return false;
}