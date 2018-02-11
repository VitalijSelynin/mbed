// main() runs in its own thread in the OS
#include "Blinky.h"
#include "Application.h"

int main() 
{
  Blinky blinky(LED1);
  Application app;
  
  app.Run();

  for(;;) 
  {
    blinky.HeartBeat();
  }
}
