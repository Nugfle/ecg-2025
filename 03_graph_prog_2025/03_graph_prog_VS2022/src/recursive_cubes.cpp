//
// This source code is property of the Computer Graphics and Visualization
// chair of the TU Dresden. Do not distribute in modified or unmodified form!
// Copyright (C) 2016 CGV TU Dresden - All Rights Reserved
//
#include "recursive_cubes.h"
#include <GL/gl.h>

// Initialize variables
recursive_cubes::recursive_cubes() {
  angle = 0;
  // Set maximum recursion depth
  depth = 4;
}

// Render the scene
void recursive_cubes::render() {
  // Enable depth testing
  glEnable(GL_DEPTH_TEST);

  // Set the light parameters, projection and view
  setup_light();
  setup_projection();

  // Clear the screen
  glClearColor(1, 1, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the recursive rendering
  render_recursive(depth, true);
}

void recursive_cubes::render_recursive(int r, bool render_all) {
  // Recursion end condition
  if (r <= 0)
    return;

  render_cube();

  if (render_all) {
    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    glTranslatef(4, 0, 0);
    glScalef(0.5, 0.5, 0.5);
    render_recursive(r - 1, false);
    glPopMatrix();
  }

  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glTranslatef(4, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  render_recursive(r - 1, false);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-90, 1, 0, 0);
  glTranslatef(4, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  render_recursive(r - 1, false);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  glTranslatef(4, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  render_recursive(r - 1, false);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-90, 0, 1, 0);
  glTranslatef(4, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  render_recursive(r - 1, false);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glTranslatef(4, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  render_recursive(r - 1, false);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-90, 0, 0, 1);
  glTranslatef(4, 0, 0);
  glScalef(0.5, 0.5, 0.5);
  render_recursive(r - 1, false);
  glPopMatrix();
}

// Render one single cube
void recursive_cubes::render_cube() {
  // Set color to yellow
  glColor3d(1, 1, 0);
  // Render a cube with side length 2
  glutSolidCube(2);
}

// Set the projection and the view
void recursive_cubes::setup_projection() {
  // For projection choose a perspective matrix with an aperture angle of
  // 45deg, an aspect ratio that corresponds to the width and height of the
  // window, z_near at 0.01 and z_far at 100.0
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45,
                 glutGet(GLUT_WINDOW_WIDTH) /
                     static_cast<double>(glutGet(GLUT_WINDOW_HEIGHT)),
                 0.01, 100.0);

  // For the modelview matrix choose a view from the position (7.0, 3.0, 7.0) to
  // the position (0, 0, 0) where the up-direction is (0, 1, 0).
  // Also rotate with the specified angle around the Y-axis
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(7.0, 3.0, 7.0, 0, 0, 0, 0, 1, 0);
  glRotated(angle, 0, 1, 0);
}

// Set the light parameters
void recursive_cubes::setup_light() {
  // Enable lighting
  glEnable(GL_LIGHTING);

  // Enable light source 0
  glEnable(GL_LIGHT0);

  // Set the modelview matrix to be the identity to avoid
  // having the light position moved with the terrain.
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // Set light parameters
  float position[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  float ambient_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  float diffuse_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  float specular_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_color);

  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);

  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  glPopMatrix();
}

// Advance one frame
void recursive_cubes::advance_frame() {
  // Increase angle and perform a modulo 360
  angle = (angle + 1) % 360;
}

// Set debug text
void recursive_cubes::set_text(std::stringstream &stream) {
  stream << "Recursive cubes with recursion depth " << depth;
}
