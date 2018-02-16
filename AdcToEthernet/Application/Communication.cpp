///////////////////////////////////////////////////////////
//  Communication.cpp
//  Definition of the class Communication
//  Created on:      11-Feb-2018 17:18:47
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "Communication.h"
#include "Debug.h"

nsapi_error_t Communication::Connect()
{
  Debug::Print("Bringing up the ethernet interface");
  nsapi_error_t error = EthernetInterface::connect();

  if(0 != error)
  {
    Debug::Print("Error during networt connection: ", error);
  }
  else
  {
    Debug::Print("Connection established");
    PrintNetworkInfo();
  }

  return error;
}

void Communication::PrintNetworkInfo()
{
  Debug::Print("IP address: ", EthernetInterface::get_ip_address());
  Debug::Print("MAC address: ", EthernetInterface::get_mac_address());
  Debug::Print("Netmask: ", EthernetInterface::get_netmask());
  Debug::Print("Gateway: ", EthernetInterface::get_gateway());
}
