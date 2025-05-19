#include <algorithm>
#include <cmath>
#include <iostream>
#include <math.h>
#include <ostream>
#include <sweep_line_tool.h>

sweep_line_tool::sweep_line_tool(canvas_buffer &canvas) : tool_base(canvas) {
  // This tool has no shape and is not draggable
  shape = TS_NONE;
  is_draggable = false;
}

void sweep_line_tool::fill(int a, int b, int row) {
  for (int i = a; i <= b; i++) {
    canvas.set_pixel(i, row);
  }
}
void sweep_line_tool::draw(int x, int y) {
  int xp0 = 40;
  int yp0 = 15;
  canvas.set_pixel(xp0, yp0);

  int xp1 = 13;
  int yp1 = 60;
  canvas.set_pixel(xp1, yp1);

  int xp2 = 85;
  int yp2 = 80;
  canvas.set_pixel(xp2, yp2);

  // the inverse of the derivative
  double d01 = (double)(xp0 - xp1) / (double)(yp0 - yp1); // 27 / -45
  double d02 = (double)(xp0 - xp2) / (double)(yp0 - yp2); // 45 / 65
  double d12 = (double)(xp2 - xp1) / (double)(yp2 - yp1); // 72 / 20

  int cury = yp0;
  double x0 = xp0;
  double x1 = xp0;

  while (cury <= yp1) {
    fill(std::ceil(std::min(x0, x1)), std::floor(std::max(x0, x1)), cury);
    x0 += d01;
    x1 += d02;
    cury++;
  }
  while (cury <= yp2) {
    fill(std::ceil(std::min(x0, x1)), std::floor(std::max(x0, x1)), cury);
    x0 += d12;
    x1 += d02;
    cury++;
  }
}
// Put debug output into the stream "stream" to be displayed in the
// main window
void sweep_line_tool::set_text(std::stringstream &stream) {
  stream << "Tool Sweep Line, click on the canvas to raster a triangle";
}
