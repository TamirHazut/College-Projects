
#include <map>
#include <string>
#include <stack>

#include "symtab.h"

static	  
std::stack<std::map<std::string, myType>> symbolTables;
static
std::stack<std::map<std::string, myType>> tempStack;

// returns the type of the identifier
// returns UNKOWN when the identifier is not in the symbol table
myType getSymbol (const char *name)
{
    std::string theName = name;
    std::map<std::string, myType>::iterator it;
    myType symbolType;
    while (!symbolTables.empty()) {
        it = symbolTables.top().find (theName);
        if (it == symbolTables.top().end()) {
            tempStack.push(symbolTables.top());
            symbolTables.pop();
        } else {
            break;
        }
    }
    if (symbolTables.empty()) {
       symbolType = UNKNOWN;
   } else {
       symbolType = it->second;
   }
    while (!tempStack.empty()) {
        symbolTables.push(tempStack.top());
        tempStack.pop();
    }   
   return symbolType;	   
}

// return value: 0 if  name already exists in symboltable
//            otherwise returns 1 
int putSymbol (const char *name, myType type)
{
    if (symbolTables.empty())
        createSymbolTable();
    std::string theName = name;
    if (symbolTables.top().count (name))
       return 0;
    symbolTables.top() [theName] = type;
    return 1;
}

void createSymbolTable() {
    std::map<std::string, myType> symbolTable;
    // symbolTable = std::map<std::string, myType>;
    symbolTables.push(symbolTable);
}

void deleteSymbolTable() {
    symbolTables.pop();
}

