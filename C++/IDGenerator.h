#ifndef __IDGENERATOR_H_
#define __IDGENERATOR_H_
class IDGenerator
{
public:
    enum class eIDType { PERSON, EMPLOYEE, COURSE, FINAL_PROJECT, NUM_OF_TYPES };
private:
    static int idCounter[(int)eIDType::NUM_OF_TYPES];
public:
    static int generateID(IDGenerator::eIDType idType) { return ++idCounter[(int)idType]; }
};
#endif