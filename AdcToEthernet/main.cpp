// main() runs in its own thread in the OS
#include "Blinky.h"
#include "Application.h"

int main() 
{
  Blinky<LED1> blinky;
  Application app;
  
  app.Run();

  while (true) 
  {
    blinky.ToggleWait();
  }
}
