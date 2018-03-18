///////////////////////////////////////////////////////////
//  ConnectorClientStateMachine.cpp
//  Definition of the class ConnectorClientStateMachine
//  Created on:      18-Mar-2018 13:01:38
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "ConnectorClientStateMachine.h"
#include "DebugClass.h"
#include "Thread.h"
#include "nsapi_types.h"
#include "ConnectorClient.h"


// This is address to mbed Device Connector
#define MBED_SERVER_ADDRESS "coap://api.connector.mbed.com:5684"


ConnectorClientStateMachine::ConnectorClientStateMachine(ConnectorClient* connector)
: connector(connector),
  state(IDLE)
{
  ;
}


void ConnectorClientStateMachine::Start()
{
  state = CONNECTING;
}


void ConnectorClientStateMachine::Run()
{
  switch(state)
  {
    case IDLE:
    {
      rtos::Thread::wait(5000);
      break;
    }

    case CONNECTING:  { Connecting(); break; }
    case SETUP:       { Setup();      break; }
    case REGISTER:    { Register();   break; }
    case UPDATE:      { Update();     break; }
    case UNREGISTER:  { Unregister(); break; }
    case DETACH:      { Detach();     break; }
    case ERROR:       { Error();      break; }

    default:
    {
      DebugClass::Print("Default case reached!");
    }
  }
}

void ConnectorClientStateMachine::PrintNetworkInfo()
{
  DebugClass::Print("IP address: ", connector->eth.get_ip_address());
  DebugClass::Print("MAC address: ", connector->eth.get_mac_address());
  DebugClass::Print("Netmask: ", connector->eth.get_netmask());
  DebugClass::Print("Gateway: ", connector->eth.get_gateway());
}


void ConnectorClientStateMachine::Connecting()
{
  DebugClass::Print("Start connecting");
  nsapi_error_t ret = connector->eth.connect();

  if(NSAPI_ERROR_OK == ret)
  {
    DebugClass::Print("Connection successful");
    PrintNetworkInfo();

    state = SETUP;
  }
}


void ConnectorClientStateMachine::Setup()
{
  DebugClass::Print("Trying to setup");

  connector->mbedClient.create_interface(MBED_SERVER_ADDRESS,
    &connector->eth);

  M2MDevice* deviceObject = 
    connector->mbedClient.create_device_object();

  objectList.push_back(deviceObject);
  // TODO other objects

  state = REGISTER;
}


void ConnectorClientStateMachine::Register()
{
  DebugClass::Print("Register at mbed Device Connector");

  M2MSecurity* registerObject =  
    connector->mbedClient.create_register_object();

  // Set endpoint registration object
  connector->mbedClient.set_register_object(registerObject);

  connector->mbedClient.test_register(registerObject, objectList);

  state = UPDATE;
}


void ConnectorClientStateMachine::Update()
{
  DebugClass::Print("Start Updateing");
  connector->mbedClient.test_update_register();
  rtos::Thread::wait(25000);
}


void ConnectorClientStateMachine::Unregister()
{
  // DebugClass::Print("Accepting connection");
  // nsapi_error_t ret = server->TCPServer::accept(
  //   &(server->clientSock), &(server->clientAddr));
  // if(NSAPI_ERROR_OK == ret)
  // {
  //   DebugClass::Print("Accepted: ", server->clientAddr.get_ip_address());
  //   DebugClass::Print("Communication port: ", server->clientAddr.get_port());

  //   state = RUNNING;
  // }
  // else
  // {
  //   DebugClass::Print("Error during accepting ", ret);
  //   state = ERROR;
  // }
}


void ConnectorClientStateMachine::Detach()
{
  // char message[] = "Hello World!\n\r";
  
  // DebugClass::Print("Start sending");
  // nsapi_error_t ret = server->clientSock.send(message, sizeof(message));
  // if(NSAPI_ERROR_OK <= ret)
  // {
  //   DebugClass::Print("Sending succsessful");
  // }
  // else
  // {
  //   DebugClass::Print("Error during sending ", ret);
  //   state = ERROR;
  // }

  // rtos::Thread::wait(100);
}


void ConnectorClientStateMachine::Error()
{
  rtos::Thread::wait(5000);
}
