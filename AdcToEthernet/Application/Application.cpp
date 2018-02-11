///////////////////////////////////////////////////////////
//  Application.cpp
//  Implementation of the class Application
//  Created on:      10-Feb-2018 22:49:23
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "Application.h"
#include "Debug.h"


void Application::Run()
{
  Debug::Print("Starting application");

  thread.Start();
}
