///////////////////////////////////////////////////////////
//  MyTcpServer.h
//  Declaration of the class MyTcpServer
//  Created on:      16-Feb-2018 18:12:14
//  Original author: Vitalij
///////////////////////////////////////////////////////////


#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include "TCPServer.h"
#include "Communication.h"

class MyTcpServer : private TCPServer
{
public:
  MyTcpServer(void);
  void Start(void);
  void Run(void);

private:
  Communication eth;
  uint16_t port;

  enum State
  {
    IDLE,
    CONNECTING,
    OPENING,
    BINDING,
    RUNNING,
    ERROR
  };

  State state;

  void Connecting(void);
  void Opening(void);
  void Binding(void);
  void Running(void);
  void Error(void);
};


#endif // MYTCPSERVER_H
