// Demo.cpp : Defines the entry point for the console application.
//

#include "Kernel.h"


int main()
{
	Kernel* kernel = new Kernel();
	kernel->Initialize();
	kernel->Run();


	return 0;
}

