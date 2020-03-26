#include "Guider.h"

bool Guider::setFinalProject(FinalProject* finalProject)
{ 
	if (finalProject != nullptr)
	{
	 	this->finalProject = finalProject; 
 	 	return true;
	}
	return false;
}