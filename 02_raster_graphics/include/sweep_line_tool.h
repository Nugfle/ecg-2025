#pragma once
#include "tool_base.h"
class sweep_line_tool : public tool_base {
public:
  sweep_line_tool(canvas_buffer &canvas);
  void fill(int a, int b, int row);
  void draw(int x, int y);
  void set_text(std::stringstream &stream);
};
