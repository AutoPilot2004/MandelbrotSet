#pragma once

struct Application
{
	Application();
	~Application();

	void run(int width, int height, const char* title);
};