

#include <crtdbg.h>
#include <stdlib.h>
#include "Application.h"

int main( void )
{
	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
	
}