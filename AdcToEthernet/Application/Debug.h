///////////////////////////////////////////////////////////
//  Debug.h
//  Declaration of the class Debug
//  Created on:      11-Feb-2018 15:10:12
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#ifndef DEBUG_H
#define DEBUG_H

class Debug
{
public:
  static void Print(const char* cString);
  static void Print(const char* cString, float vlaue);
  static void Print(const char* cString, signed int vlaue);
  static void Print(const char* firstString, const char* secondString);
};


#endif //DEBUG_H
