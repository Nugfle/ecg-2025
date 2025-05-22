//
// This source code is property of the Computer Graphics and Visualization
// chair of the TU Dresden. Do not distribute in modified or unmodified form!
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "rectangle_tool.h"
#include <algorithm>

// Initialize the tool and store a reference of a canvas_buffer
rectangle_tool::rectangle_tool(canvas_buffer &canvas) : tool_base(canvas) {
  shape = TS_BOX;
}

// Draw a box from (x0, y0) to (x1, y1)
void rectangle_tool::draw(int x0, int y0, int x1, int y1) {
  /************
  Additional task: Implement the rasterization of a rectangle that
                   ranges from (x0, y0) to (x1, y1).
Zusatzaufgabe:   Implementieren Sie die Rasterisierung eines
                   Rechtecks, das von (x0, y0) nach (x1, y1) geht.
  *************/
  if (x0 > x1)
    std::swap(x0, x1);
  if (y0 > y1)
    std::swap(y0, y1);

  // Draw the four lines of the rectangle

  // Top horizontal line
  for (int x = x0; x <= x1; x++)
    canvas.set_pixel(x, y0);

  // Bottom horizontal line
  for (int x = x0; x <= x1; x++)
    canvas.set_pixel(x, y1);

  // Left vertical line (skip corners as they're already drawn)
  for (int y = y0 + 1; y < y1; y++)
    canvas.set_pixel(x0, y);

  // Right vertical line (skip corners as they're already drawn)
  for (int y = y0 + 1; y < y1; y++)
    canvas.set_pixel(x1, y);
}

// Put debug output into the stream "stream" to be displayed in the
// main window
void rectangle_tool::set_text(std::stringstream &stream) {
  stream << "Tool: Rectangle (click and drag mouse to draw)";
}
