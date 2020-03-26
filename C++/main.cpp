#include "main.h"
#include "IDGenerator.h"
#include "College.h"
#include "Date.h"
#include "Employee.h"
#include "Lecturer.h"
#include "Student.h"
#include <iostream>

using namespace std;

int IDGenerator::idCounter[(int)eIDType::NUM_OF_TYPES];

int main()
{
	College* c = College::getInstance();
	if (c)
		mainMenu(*c);
}


// Menus
static void collegeMenu(College& c)
{
	cout << "Please choose one of the options bellow:" << endl
		<< "1. Add student" << endl
		<< "2. Add worker" << endl
		<< "3. Add course" << endl
		<< "4. Delete student" << endl
		<< "5. Delete worker" << endl
		<< "6. Delete course" << endl
		<< "7. Print college" << endl
		<< "0. To Exit" << endl
		<< "Your option: ";
	int  option;
	cin >> option;
	cout << "-----\n";
	getchar();
	switch (option)
	{
		case 0:
			break;
		case 1:
			initStudent(c);
			break;
		case 2:
			initWorker(c);
			break;
		case  3:
			initCourse(c);
			break;			
		case 4:
			deleteStudent(c);
			break;
		case 5:
			deleteWorker(c);
			break;
		case 6:
			deleteCourse(c);
			break;
		case 7:
			cout << c;
			break;
		default:
			cout << "Invalid Input!";
			break;
	}
}

static void studentMenu(College& c) 
{
	cout << "Please choose one of the options bellow:" << endl
		<< "1. Print student by ID" << endl
		<< "2. Add course" << endl
		<< "3. Add FinalProject" << endl
		<< "4. delete Course" << endl
		<< "5. get Avarage Of Student" << endl
	    << "0. To Exit" << endl
		<< "Your option: ";
	int  option;
	cin >> option;
	getchar();
	cout << "-----\n";
	switch (option) 
	{
		case 0:
			return;
		case 1:
			printStudent(c);
			break;
		case 2:
			addCourseToStudent(c);
			break;
		case 3:
			addFinalProjectToStudent(c);
			break;
		case 4:
			deleteCourseFromStudent(c);
			break;
		case 5:
			getAvarageStudent(c);
			break;
		default:
			
			cout << "Invalid Input!" << endl;
			break;
	}
}

static void employeeMenu(College& c) 
{
	cout << "Please choose one of the options bellow:" << endl
		<< "1. Print Employee by ID" << endl
		<< "2. Add Course To Lecturer" << endl
		<< "3. Delete Course To Lecturer" << endl
		<< "4. Change grade for student" << endl
		<< "0. To Exit" << endl
		<< "Your option: ";
	int  option;
	cin >> option;
	getchar();
	cout << "-----\n";
	switch (option)
	{
		case 0:
			break;
		case 1:
			printEmployee(c);
			break;
		case 2:
			addCourseToLecturer(c);
			break;
		case 3:
			deleteCourseFromLecturer(c);
			break;
		case 4:
			changeGradeForStudent(c);
			break;
		default:
			cout << "Invalid input!" << endl;
			break;
	}
}

static void mainMenu(College& c)
{
	bool exit = false;
	do
	{
		int option;
		cout << "----------\nPlease choose 1 of the following :" << endl
			<< "1. Menu of College" << endl
			<< "2. Menu Of Studnet" << endl
			<< "3. Menu Of Employee" << endl
			<< "0. To Exit" << endl
			<< "Your option: ";
		cin >> option;
		getchar();
		cout << "----------\n";
		switch (option)
		{
		case 0:
			exit = true;
			break;
		case 1:
			collegeMenu(c);
			break;
		case 2:
			studentMenu(c);
			break;
		case 3:
			employeeMenu(c);
			break;
		default:
			cout << "Invalid Input!";
			break;
		}
		cout << "----------\n";
	} while (!exit);
	
}
static Date initDate()
{
	int year, month, day;
	cout << "Enter \"dd mm yyyy\":" << endl;
	cin >> day >> month >> year;
	return Date(day, month, year);
}
static Employee& initEmployee(College& c, const string& name, Date birthdate, int salary, int department)
{
	Employee* e = nullptr;
	switch (department)
	{
		case 0:
			return c.createLecturer(name, birthdate, salary);
		case 1:
			return c.createGuider(name, birthdate, salary);
		case 2:
			Course*  course = nullptr;
			Student* student = nullptr;
			int studentID;
			cout << "Enter student ID: ";
			cin >> studentID;
		    student = c.getStudentById(studentID);
			if (!student)
				return *e;

			if (strcmp(student->getName().c_str(), name.c_str())!=0)
				return *e;

			int courseID;
			cout << "Enter course ID: ";
			cin >> courseID;
			course = c.getCourseById(courseID);
			if (!course)
				return *e;

		case 3:
			return c.createClerk(name, birthdate, salary);
		case 4:
			return c.createMaintenance(name, birthdate, salary);
	}
}
void initWorker(College &c)
{
	int salary, department;
	Employee::eDepartment dep;
	char name[100];
	cout << "Enter employee's name: " << endl;
	cin.getline(name, 100);
	cout << "--Birthday--" << endl;
	Date birthDate = initDate();
	cout << "Enter employee's salary: " << endl;
	cin >> salary;
	cout << "Enter department:\n"
		<< "0. Lecturer\n"
		<< "1. Guider\n"
		<< "2. Exercise Checker\n"
		<< "3. Administration\n"
		<< "4. Maintenance\n"
		<< "Your option: ";
	cin >> department;
	if (c.addEmployee(&(initEmployee(c, name, birthDate, salary, department))))
		cout << "Added Succesfully.\n";
	else
		cout << "Adding Failed.\n";
}
static void initCourse(College &c)
{
	char name[100];
	int testPercent = -1;
	cout << "Enter course's name:" << endl;
	cin.getline(name, 100);
	do
	{
		cout << "Enter course's test percent (0-100):" << endl;
		cin >> testPercent;
	} while (testPercent < 0 || testPercent > 100);
	if (c.addCourse(new Course(name, testPercent)))
		cout << "Added Succesfully.\n";
	else
		cout << "Adding Failed.\n";
}
static void initStudent(College &c)
{
	char name[100];
	int currentYear, currentSemester;
	cout << "Enter student's name:" << endl;
	cin.getline(name, 100);
	cout << "--Birthday--" << endl;
	Date birthDate = initDate();
	cout << "Enter student's current year:" << endl;
	cin >> currentYear;
	cout << "Enter student's current semester:" << endl;
	cin >> currentSemester;
	cout << "--College start date--" << endl;
	Date startDate = initDate();
	if (c.addStudent((new Student(name, birthDate, currentYear, currentSemester, startDate))))
		cout << "Added Succesfully.\n";
	else
		cout << "Adding Failed.\n";
}

static void deleteWorker(College &c)
{
	int id;
	cout << "Enter worker ID: ";
	cin >> id;
	Employee* employee = c.getWorkerByWorkId(id);
	if (!(c.removeEmployee(employee)))
		cout << "Worker ID \"" << id << "\" was not found." << endl;
	else
		cout << "Worker ID \"" << id << "\" deleted." << endl;
}
static void deleteCourse(College &c)
{
	int id;
	cout << "---Enter course id";
	cin >> id;
	 Course* course = c.getCourseById(id);
	if (course && c.removeCourse(course))
		cout << "Course ID \"" << id << "\" deleted." << endl;
	else
		cout << "Course ID \"" << id << " \" was not found or deleted." << endl;

}
static void deleteStudent(College &c)
{
	int id;
	cout << "---Enter student ID----: " << endl;
	cin >> id;
	Student* student =c.getStudentById(id);
	if (student && c.removeStudent(student))
		cout << "Student ID \"" << id << "\" deleted." << endl;
	else
		cout << "Student ID \"" << id << "\" was not found or deleted." << endl;
}

static void printStudent(College &c)
{
	int id;
	cout << "Enter student ID: ";
	cin >> id;
	Student* student = c.getStudentById(id);
	if (student)
		cout << *student;
	else
		cout << "Student ID \"" << id << "\" was not found." << endl;
}
static void printEmployee(College &c)
{
	int id;
	cout << "Enter worker ID: ";
	cin >> id;
	Employee* employee = c.getWorkerByWorkId(id);
	if (employee)
		cout << employee;
	else
		cout << "Worker ID \"" << id << "\" was not found." << endl;
}
static void addCourseToStudent(College& c)
{
	int courseID;
	int studentID;
	cout << "Enter student's ID:" << endl;
	cin >> studentID;
	Student* student = c.getStudentById(studentID);
	if (!student)
	{
		cout << "Student ID: \"" << studentID << " \" was not found." << endl;
		return;
	}
	cout << "Enter course's ID:" << endl;
	cin >> courseID;
	Course* course = c.getCourseById(courseID);
	if (!course)
	{
		cout << "Course ID: \"" << courseID << " \" was not found" << endl;
		return;
	}
	if (student->addCourse(course) && course->addStudent(studentID))
		cout << "Added Succesfully" << endl;
	else
		cout << "Adding Faild" << endl;


}
static void  addFinalProjectToStudent(College &c)
{
	int GuiderId;
	int studentID;
	char ProjectName[100];
	char projectDes[100];
	cout << "Enter student's ID: " << endl;
	cin >> studentID;
	Student* student = c.getStudentById(studentID);
	if (!student)
	{
		cout << "Student ID: \"" << studentID << " \" was not found." << endl;
		return;
	}
	if (student->getFinalProject() != nullptr)
	{
		cout << "Student ID: \"" << studentID << " \" already has a final project " << endl;
		return;
	}
	getchar();
	cout << "Enter project Name" << endl;
	cin.getline(ProjectName, 100);
	cout << "Enter project Description" << endl;
	cin.getline(projectDes, 100);
	FinalProject* finalProject = new FinalProject(ProjectName, projectDes);
	cout << "Enter Guider ID" << endl;
	cin >> GuiderId;
	Employee* worker = c.getWorkerByWorkId(GuiderId);
	if (!worker)
	{
		cout << "Guider ID: \"" << GuiderId << " \" was not found." << endl;
		return;
	}
	Guider* guider = dynamic_cast<Guider*>(worker);
	if (!guider)
	{
		cout << "Employee ID: \"" << GuiderId << " \" is not a guider." << endl;
		return;
	}
	if (guider->getFinalProject() != nullptr)
	{
		cout << "this guider allready has final project to guide";
		return;
	}
	student->setFinalProject(finalProject);
	guider->setFinalProject(finalProject);
	cout << "---Add Succesfully---";

}


static void deleteCourseFromStudent(College& c)
{
	int courseID;
	int studentID;
	cout << "Enter student's ID:" << endl;
	cin >> studentID;
	Student* student = c.getStudentById(studentID);
	if (!student)
	{
		cout << "Student ID: \"" << studentID << " \" was not found." << endl;
		return;
	}
	cout << "Enter course's ID:" << endl;
	cin >> courseID;
	Course* course = c.getCourseById(courseID);
	if (!course)
	{
		cout << "Course ID: \"" << courseID << " \" was not found" << endl;
		return;
	}
	if (!student->deleteCourse(course))
		cout << "Course ID: \"" << courseID << " \" was not found for Student ID: \"" << studentID << " \"." << endl;
	else
		cout << "Course ID: \"" << courseID << "\" deleted for Student ID: \"" << studentID << " \"." << endl;
}

static void getAvarageStudent(College& c) 
{
	int studentID = 0;
	cout << "Enter Id Of Student:" << endl;
	cin >> studentID;
	Student *student = c.getStudentById(studentID);
	if (!student) 
	{
		cout << "Student ID: \"" << studentID << " \" was not found." << endl;
		return;
	}
	student->calculateAverage();
	cout << "Avarage of this Student is:" << student->getAverageOfStudent() << endl;
}

static void addCourseToLecturer(College&c)
{

	Lecturer* lecturer = nullptr;
	int lecturerID;
	int courseID;
	cout << "Enter lecturer's ID:" << endl;
	cin >> lecturerID;
	Employee* worker = c.getWorkerByWorkId(lecturerID);
	if (!worker)
	{
		cout << "Lecturer ID: \"" << lecturerID << " \" was not found." << endl;
		return;
	}
	 lecturer = dynamic_cast<Lecturer*>(worker);
	if (!lecturer)
	{
		cout << "Employee ID: \"" << lecturerID << " \" is not a lecturer." << endl;
		return;
	}
	cout << "Enter course's ID:" << endl;
	cin >> courseID;
	Course* course = c.getCourseById(courseID);
	if (!course)
	{
		cout << "Course ID: \"" << courseID << " \" was not found" << endl;
		return;
	}
	if (lecturer->addCourse(*course))
		cout << "Added Succesfully" << endl;
	else
		cout << "Adding Faild" << endl;
}
static void deleteCourseFromLecturer(College& c)
{
	int lecturerID;
	int courseID;
	cout << "Enter lecturer's ID:" << endl;
	cin >> lecturerID;
	Employee* worker = c.getWorkerByWorkId(lecturerID);
	if (!worker)
	{
		cout << "Lecturer ID: \"" << lecturerID << " \" was not found." << endl;
		return;
	}
	Lecturer* lecturer = dynamic_cast<Lecturer*>(worker);
	if (!lecturer)
	{
		cout << "Employee ID: \"" << lecturerID << " \" is not a lecturer." << endl;
		return;
	}
	cout << "Enter course's ID:" << endl;
	cin >> courseID;
	Course* course = c.getCourseById(courseID);
	if (!course)
	{
		cout << "Course ID: \"" << courseID << " \" was not found" << endl;
		return;
	}
	if (lecturer->deleteCourse(*course))
		cout << "Deleted Succesfully" << endl;
	else
		cout << "Deletion Faild" << endl;
}
static void changeGradeForStudent(College &c)
{

	int lecturerID;
	int courseID;
	int studentID;
	double grade = -1;
	cout << "Enter student's ID:" << endl;
	cin >> studentID;
	do
	{
		cout << "Enter student's grade:" << endl;
		cin >> grade;
	} while (grade < 0 || grade > 100);
	cout << "Enter course's ID:" << endl;
	cin >> courseID;
	cout << "Enter lecturer ID:" << endl;
	cin >> lecturerID;
	Employee* worker = c.getWorkerByWorkId(lecturerID);
	if (!worker)
	{
		cout << "Employee ID: \"" << lecturerID << "\" was not found." << endl;
		return;
	}
	if (Lecturer *lecturer = dynamic_cast<Lecturer*>(worker))
	{
		if (lecturer->changeGradeToStudent(studentID, courseID, grade))
			cout << "Student ID: \"" << studentID << "\" test grade for Course ID: \"" << courseID << "\" changed to: " << grade << endl;
		else
			cout << "Changing grade of Student ID: \"" << studentID << "\" test grade for Course ID: \"" << courseID << "\" failed!" << endl;
		return;
	}
	else if (ExerciseChecker* ec = dynamic_cast<ExerciseChecker*>(worker))
	{
		if (ec->changeGradeToStudent(studentID, courseID, grade))
			cout << "Student ID: \"" << studentID << "\" exercise grade for Course ID: \"" << courseID << "\" changed to: " << grade << endl;
		else
			cout << "Changing grade of Student ID: \"" << studentID << "\" test grade for Course ID: \"" << courseID << "\" failed!" << endl;
		return;
	}
	else
		cout << "Changing grade failed." << endl;

}



