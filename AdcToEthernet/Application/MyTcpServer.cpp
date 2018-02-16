///////////////////////////////////////////////////////////
//  MyTcpServer.cpp
//  Definition of the class MyTcpServer
//  Created on:      16-Feb-2018 18:26:23
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "MyTcpServer.h"
#include "Debug.h"

MyTcpServer::MyTcpServer()
: port(1337),
  state(IDLE)
{
  ;
}

void MyTcpServer::Start()
{
  state = CONNECTING;
}

void MyTcpServer::Run()
{
  switch(state)
  {
    case IDLE:
    {
      rtos::Thread::wait(5000);
      break;
    }
    case CONNECTING:
    {
      Connecting();
      break;
    }
    case OPENING:
    {
      Opening();
      break;
    }
    case BINDING:
    {
      Binding();
      break;
    }
    case RUNNING:
    {
      Running();
      break;
    }
    case ERROR:
    {
      Error();
      break;
    }
    default:
    {
      ;
    }
  }
}


void MyTcpServer::Connecting()
{
  nsapi_error_t error = eth.Connect();
  if(0 == error)
  {
    state = OPENING;
  }
}


void MyTcpServer::Opening()
{
  Debug::Print("Trying to open server");
  nsapi_error_t error = TCPServer::open(&eth);
  if(0 == error)
  {
     Debug::Print("Server opened successfully");
     state = BINDING;
  }
  else
  {
    Debug::Print("Error during server opening: ", error);
    state = ERROR;
  }
}


void MyTcpServer::Binding()
{
  Debug::Print("Trying to bind port ", port);
  nsapi_error_t error = TCPServer::bind(eth.get_ip_address(), port);
  if(0 == error)
  {
    Debug::Print("Port bound to ", eth.get_ip_address());
    state = RUNNING;
  }
  else
  {
    Debug::Print("Error during server binding: ", error);
    state = ERROR;
  }
}


void MyTcpServer::Running()
{
  Debug::Print("Server is running");
  rtos::Thread::wait(5000);
}


void MyTcpServer::Error()
{
  rtos::Thread::wait(5000);
}
