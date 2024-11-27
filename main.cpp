#include <Mandelbrot_Set/Core.h>

#include "Application.h"

int main()
{
	auto res = Application::run(1000, 1000, "Mandelbrot Set");

	if (!res) Lib::fatal_error(res.error().msg, res.error().code);

	return *res;
}