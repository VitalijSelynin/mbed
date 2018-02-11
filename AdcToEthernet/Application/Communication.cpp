///////////////////////////////////////////////////////////
//  Communication.cpp
//  Definition of the class Communication
//  Created on:      11-Feb-2018 17:18:47
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "Communication.h"
#include "Debug.h"

void Communication::Connect(void)
{
  Debug::Print("Bringing up the ethernet interface");
  nsapi_error_t error = net.connect();

  if(0 != error)
  {
    Debug::Print("Error during networt connection: ", error);
  }
  else
  {
    Debug::Print("Connection established");
    PrintNetworkInfo(net);
  }


}

void Communication::PrintNetworkInfo(EthernetInterface& interface)
{
    Debug::Print("IP address: ", interface.get_ip_address());
    Debug::Print("MAC address: ", interface.get_mac_address());
    Debug::Print("Netmask: ", interface.get_netmask());
    Debug::Print("Gateway: ", interface.get_gateway());
}

Communication::~Communication()
{
  net.disconnect();
}
