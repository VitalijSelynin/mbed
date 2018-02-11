///////////////////////////////////////////////////////////
//  Debug.cpp
//  Definition of the class Debug
//  Created on:      11-Feb-2018 15:10:12
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "Debug.h"
#include <iostream>

void Debug::Print(const char* cString)
{
  std::cout << cString << std::endl;
}

void Debug::Print(const char* cString, float value)
{
  std::cout << cString << value << std::endl;
}

void Debug::Print(const char* cString, signed int value)
{
  std::cout << cString << value << std::endl;
}

void Debug::Print(const char* firstString, const char* secondString)
{
  std::cout << firstString << secondString << std::endl;
}
