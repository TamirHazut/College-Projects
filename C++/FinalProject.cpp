#include <string.h>
#include <iostream>

using namespace std;
#include "FinalProject.h"
 FinalProject::FinalProject(const FinalProject& OtherfinalProject) {
	 *this = OtherfinalProject;
}

void   FinalProject::setProjectName(const string& projectName) {
	this->projectName = projectName;
}
void FinalProject::setDesc(const string& desc) {
	
	this->description = desc;
}

const FinalProject& FinalProject::operator=(const FinalProject& other) {
	if (this != &other) {
		projectId = other.projectId;
		projectName = other.projectName;
		this->description =other.description;
	}
	return *this;
}


 ostream& operator<<(ostream& os, const FinalProject& fp) {
	 os << "Project id:" << fp.projectId << "\n" << "Project name:" << fp.projectName << "\n" << "project description: " << fp.description<<endl;
	 return os;
}
