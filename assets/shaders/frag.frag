#version 460 core

out vec4 fragColor;

layout(location = 0) uniform sampler1D map; 
layout(location = 1) uniform dvec2 mouseCoord;
layout(location = 2) uniform double zoom;
layout(location = 3) uniform dvec2 mouse2Coord;
layout(location = 4) uniform ivec2 winSize;

void main()
{
	dvec2 dWinSize = winSize;
	dvec2 normCoord      = ((gl_FragCoord.xy) / dWinSize) * 2.0 - 1;
	dvec2 normMouseCoord = ((mouseCoord) / dWinSize) * 2.0 - 1;
	dvec2 norm2MouseCoord = ((mouse2Coord) / dWinSize) * 2.0 - 1;
	
	double zoomInv = 1 / zoom;

	dvec2 coord = (((normCoord - norm2MouseCoord) * zoomInv) + normMouseCoord);

	const int maxIter = 350;

	double x = 0.0;
	double y = 0.0;
	double xx = 0.0;
	double yy = 0.0;

	int iter = 0;

	while (xx + yy <= 4 && iter < maxIter) {
		double temp = xx - yy + coord.x;
		y = 2*x*y + coord.y;
		x = temp;
		xx = x * x;
		yy = y * y;
		iter++;
	}
	
	fragColor = vec4(iter == maxIter ? vec3(0.0) : texture(map, float(iter)/maxIter).xyz, 1.0);
}