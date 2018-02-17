///////////////////////////////////////////////////////////
//  TcpStateMachine.cpp
//  Declaration of the class TcpStateMachine
//  Created on:      17-Feb-2018 13:38:51
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "TcpStateMachine.h"
#include "MyTcpServer.h"
#include "Debug.h"

TcpStateMachine::TcpStateMachine(MyTcpServer* server)
 : server(server)
{
  ;
}


void TcpStateMachine::Start()
{
  state = CONNECTING;
}


void TcpStateMachine::Run()
{
  switch(state)
  {
    case IDLE:
    {
      rtos::Thread::wait(5000);
      break;
    }
    case CONNECTING: { Connecting(); break; }
    case OPENING:    { Opening();    break; }
    case BINDING:    { Binding();    break; }
    case LISTENING:  { Listening();  break; }
    case ACCEPTING:  { Accepting();  break; }
    case RUNNING:    { Running();    break; }
    case ERROR:      { Error();      break; }
    default:
    {
      Debug::Print("Default case reached!");
    }
  }
}


void TcpStateMachine::Connecting()
{
  nsapi_error_t ret = server->eth.Connect();
  if(NSAPI_ERROR_OK == ret)
  {
    state = OPENING;
  }
}


void TcpStateMachine::Opening()
{
  Debug::Print("Trying to open server");
  nsapi_error_t ret = server->TCPServer::open(&(server->eth));
  if(NSAPI_ERROR_OK == ret)
  {
     Debug::Print("Server opened successfully");
     state = BINDING;
  }
  else
  {
    Debug::Print("Error during server opening: ", ret);
    state = ERROR;
  }
}


void TcpStateMachine::Binding()
{
  Debug::Print("Trying to bind port ", server->port);
  nsapi_error_t ret = server->TCPServer::bind(
    server->eth.get_ip_address(), server->port);
  if(NSAPI_ERROR_OK == ret)
  {
    Debug::Print("Port bound to ", server->eth.get_ip_address());
    state = LISTENING;
  }
  else
  {
    Debug::Print("Error during server binding: ", ret);
    state = ERROR;
  }
}


void TcpStateMachine::Listening()
{
  Debug::Print("Start listening");
  nsapi_error_t ret = server->TCPServer::listen(server->simultanConnections);
  if(NSAPI_ERROR_OK == ret)
  {
    Debug::Print("Listening succsessful");
    state = ACCEPTING;
  }
  else
  {
    Debug::Print("Error during listening ", ret);
    state = ERROR;
  }
}


void TcpStateMachine::Accepting()
{
  Debug::Print("Accepting connection");
  nsapi_error_t ret = server->TCPServer::accept(
    &(server->clientSock), &(server->clientAddr));
  if(NSAPI_ERROR_OK == ret)
  {
    Debug::Print("Accepted: ", server->clientAddr.get_ip_address());
    Debug::Print("Communication port: ", server->clientAddr.get_port());

    state = RUNNING;
  }
  else
  {
    Debug::Print("Error during accepting ", ret);
    state = ERROR;
  }
}


void TcpStateMachine::Running()
{
  char message[] = "Hello World!\n\r";
  
  Debug::Print("Start sending");
  nsapi_error_t ret = server->clientSock.send(message, sizeof(message));
  if(NSAPI_ERROR_OK <= ret)
  {
    Debug::Print("Sending succsessful");
  }
  else
  {
    Debug::Print("Error during sending ", ret);
    state = ERROR;
  }

  rtos::Thread::wait(100);
}


void TcpStateMachine::Error()
{
  rtos::Thread::wait(5000);
}
