///////////////////////////////////////////////////////////
//  Communication.h
//  Declaration of the class Communication
//  Created on:      10-Feb-2018 17:17:35
//  Original author: Vitalij
///////////////////////////////////////////////////////////

#include "EthernetInterface.h"

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

class Communication
{
public:
  void Connect(void);

  ~Communication(void);

private:
  EthernetInterface net;
  void PrintNetworkInfo(EthernetInterface& interface);

};


#endif // COMMUNICATION_H
