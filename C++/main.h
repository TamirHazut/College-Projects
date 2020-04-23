#ifndef _MAIN__H
#define _MAIN__H

#include "College.h"

static College* instantiateCollege();
	
// Menus
static void collegeMenu(College& c);
static void studentMenu(College& c);
static void employeeMenu(College& c);
static void mainMenu(College& c);


//init fucntion
static Date initDate();
static Employee& createEmployee(College& c, const string& name, Date birthdate, int salary, int department);
static void initWorker(College&c);
static void initStudent(College &c);
static void initCourse(College &c);


// delete Student/Worker/Course
static void deleteWorker(College &c);
static void deleteStudent(College &c);
static void deleteCourse(College &c);


// print student/worker
static void printStudent(College& c);
static void printEmployee(College& c);

//student Menu Functions
static void addCourseToStudent(College& c);
static void deleteCourseFromStudent(College& c);
static void  addFinalProjectToStudent(College& c);
static void getAvarageStudent(College& c);

//Worker Menu Fucntions
static void addCourseToLecturer(College& c);
static void deleteCourseFromLecturer(College& c);
static void changeGradeForStudent(College& c);


#endif // !_MAIN__H
