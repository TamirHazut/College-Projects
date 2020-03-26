#pragma warning(disable: 4996)
#ifndef _FINALPROJECT__H
#define _FINALPROJECT__H

#include <iostream>
#include "IDGenerator.h"

using namespace std;



class FinalProject
{
private:
	int projectId;
	std::string projectName;
	std::string description; // description
	// Guider* guider; // pointer to project guider 
	// Student* student; // pointer to student
public:
	FinalProject(const string& projectName, const string& desc) : projectId(IDGenerator::generateID(IDGenerator::eIDType::FINAL_PROJECT)), projectName(projectName), description(desc) {}
	FinalProject(const FinalProject& OtherfinalProject);
	~FinalProject();

	const string& getProjectName() const { return this->projectName; }
	const string& getDescription() const { return this->description; }
	int getID() const { return this->projectId; }

	void setProjectName(const string& projectName);
	void setDesc(const string& desc);
	const FinalProject& operator=(const FinalProject& other);

	friend ostream& operator<<(ostream& os, const FinalProject& fp);
	operator const char* () { return this->description.c_str(); }
	// friend class College; // to allow it to use copy constructor 
};

#endif 