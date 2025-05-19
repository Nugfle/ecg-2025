//
// This source code is property of the Computer Graphics and Visualization
// chair of the TU Dresden. Do not distribute in modified or unmodified form!
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "bresenham_line_tool.h"
#include <algorithm>
#include <math.h>

// Initialize the tool and store a reference of a canvas_buffer
bresenham_line_tool::bresenham_line_tool(canvas_buffer &canvas)
    : tool_base(canvas) {
  // This tool draws lines!
  shape = TS_LINE;
}

// Draw a line from (x0, y0) to (x1, y1)
void bresenham_line_tool::draw(int x0, int y0, int x1, int y1) {
  double error, m;
  int y, y_step;
  bool swapped;

  swapped = false;

  // Bresenham works by first constructing the standard case
  // (i.e. a line with a positive slope smaller than 1 and
  // drawn from left to right). Then an error term is calculated
  // (which is basically the slope). In the drawing loop over
  // the x-coordinate the y-coordinate is increased whenever
  // the error reaches a certain boundary.

  // If the slope is bigger than 1 then exchange X and Y to
  // implicitly have the drawing loop over y where the slope will
  // be smaller than one then. Remember that there was a swap.
  if (abs(y1 - y0) > abs(x1 - x0)) {
    std::swap(x0, y0);
    std::swap(x1, y1);
    swapped = true;
  }

  // If the starting position is bigger than the stop position than
  // exchange the start and stop point.
  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  // Now with the almost-standard case the slope is calculated. Mind the
  // (double)-cast here which is neccessary to have a non-integer result and
  // that the absolute value is calculated.
  m = fabs((y1 - y0) / static_cast<double>(x1 - x0));

  // It might be that the real slope is negative. If this is the case
  // then move the y-position up instead of down when needed
  y_step = 1;
  if (y0 > y1)
    y_step = -1;

  error = 0;
  y = y0;

  for (int x = x0; x <= x1; x++) {

    // Draw a pixel at (x, y) or (y, x) if x and y were swapped
    if (swapped)
      canvas.set_pixel(y, x);
    else
      canvas.set_pixel(x, y);

    // Add the error introduced with this pixel
    error += m;
    // If the error reaches a certain boundary than change y and
    // decrease the error term
    if (error >= 0.5) {
      y += y_step;
      error -= 1;
    }
  }
}

// Put debug output into the stream "stream" to be displayed in the
// main window
void bresenham_line_tool::set_text(std::stringstream &stream) {
  stream << "Tool: Bresenham-Line (click and drag mouse to draw)";
}
