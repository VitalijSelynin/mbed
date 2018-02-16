///////////////////////////////////////////////////////////
//  ApplicationThread.cpp
//  Definition of the class ApplicationThread
//  Created on:      11-Feb-2018 13:38:58
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include"ApplicationThread.h"
#include "Debug.h"
#include "VoltageReader.h"
#include "Thread.h"
#include "MyTcpServer.h"

void ApplicationThread::Start()
{
  thread.start(mbed::callback(ApplicationThread::Run));
}

void ApplicationThread::Run()
{
  Debug::Print("ApplicationThread started");
  VoltageReader voltage;
  MyTcpServer server;

  server.Start();

    float voltageArray[voltage.GetVoltageCount()];
    for(uint32_t i = 0; i < voltage.GetVoltageCount(); i++)
    {
      voltageArray[i] = voltage.GetRawValue(i);
    }

    Debug::Print("Voltage 0: ", voltageArray[0]);
    Debug::Print("Voltage 1: ", voltageArray[1]);
    Debug::Print("Voltage 2: ", voltageArray[2]);
    Debug::Print("Voltage 3: ", voltageArray[3]);
    rtos::Thread::wait(500);

  for(;;)
  {
    server.Run();
  }
}
