#include <cstdlib>

#include "Application.h"

int main()
{
	Application app;
	app.run(1000, 1000, "Mandelbrot Set");

	return EXIT_SUCCESS;
}