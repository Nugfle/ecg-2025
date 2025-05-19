//
// This source code is property of the Computer Graphics and Visualization
// chair of the TU Dresden. Do not distribute in modified or unmodified form!
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "line_fill_tool.h"
#include <cmath>
#include <iostream>
#include <set>
#include <stack>

// Initialize the tool and store a reference of a canvas_buffer
line_fill_tool::line_fill_tool(canvas_buffer &canvas) : tool_base(canvas) {
  // This tool has no shape and is not draggable
  shape = TS_NONE;
  is_draggable = false;
}

bool line_fill_tool::is_on_border_top(int x, int y) {
  if (y < 1) {
    return true;
  }
  return canvas.get_pixel(x, y - 1);
}
bool line_fill_tool::is_on_border_bot(int x, int y) {
  if (y >= canvas.get_height() - 1) {
    return true;
  }
  return canvas.get_pixel(x, y + 1);
}
bool line_fill_tool::is_on_border_left(int x, int y) {
  if (x < 1) {
    return true;
  }
  return canvas.get_pixel(x - 1, y);
}
bool line_fill_tool::is_on_border_right(int x, int y) {
  if (x >= canvas.get_width() - 1) {
    return true;
  }
  return canvas.get_pixel(x + 1, y);
}
waiting_line line_fill_tool::find_right_border(int x, int y) {
  waiting_line line;
  line.y = y;
  int cx = x;
  while (!is_on_border_right(cx, y)) {
    cx++;
  }
  line.x = cx;
  return line;
}

// Fill the shape that contains the point (x, y)
void line_fill_tool::draw(int x, int y) {
  /************
  Additional task: Implement the line fill algorithm. You can declare
                   helper methods and properties in the header file if needed
and implement them here. Zusatzaufgabe:   Implementieren Sie den
Line-Fill-Algorithmus. Falls benoetigt koennen Sie sich Helfermethoden in der
dazugehoerigen Header-Datei deklarieren und in dieser Datei definieren.
  *************/
  std::stack<waiting_line> unvisited = std::stack<waiting_line>();
  std::set<waiting_line, Comp> lines = std::set<waiting_line, Comp>();
  waiting_line start = find_right_border(x, y);
  std::cout << "startx: " << start.x << "starty: " << start.y << std::endl;
  unvisited.push(start);

  while (!unvisited.empty()) {
    waiting_line current_line = unvisited.top();

    int cx = current_line.x;
    int cy = current_line.y;

    unvisited.pop();
    lines.clear();
    std::cout << "curx: " << cx << "cury: " << cy << std::endl;

    while (!is_on_border_left(cx, cy)) {
      canvas.set_pixel(cx, cy);
      // if we were on the top before, but now there is nothing
      if (!is_on_border_top(cx, cy)) {
        waiting_line l = find_right_border(cx, cy - 1);
        lines.insert(l);
      }
      // if we were on the bot before, but now there is nothing
      if (!is_on_border_bot(cx, cy)) {
        waiting_line l = find_right_border(cx, cy + 1);
        lines.insert(l);
      }
      cx--;
    }
    canvas.set_pixel(cx, cy);
    // we hit the left border
    if (!is_on_border_top(cx, cy)) {
      waiting_line l = find_right_border(cx, cy - 1);
      lines.insert(l);
    }
    if (!is_on_border_bot(cx, cy)) {
      waiting_line l = find_right_border(cx, cy + 1);
      lines.insert(l);
    }

    for (waiting_line line : lines) {
      unvisited.push(line);
    }
  }
}

// Put debug output into the stream "stream" to be displayed in the
// main window
void line_fill_tool::set_text(stringstream &stream) {
  stream << "Tool: Line Fill (click to fill)";
}
