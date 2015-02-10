#include <math.h>
#include "gl_interface.hpp"
#include <iostream>

int win_width;
int win_height;
bool pause_motion = false,cam_follow = false,skeleton = true;
int count = 0;

//! Initialize GL State
void initGL(void)
{
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
}

//!GLFW Error Callback
void error_callback(int error, const char* description)
{
    std::cerr<<description<<std::endl;
}

//!GLFW framebuffer resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if  ( height == 0 ) height = 1;
	glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,50.0f);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,1,-10);
    win_width = width;
    win_height = height;
}

//!GLFW keyboard callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//!Close the window if the ESC key was presses
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_ESCAPE)	glfwSetWindowShouldClose(window, GL_TRUE);
		else if (key == GLFW_KEY_SPACE)
		{
			pause_motion = !(pause_motion);
		}
		else if (key == GLFW_KEY_RIGHT)
		{
			if(pause_motion) count++;
		}
		else if (key == GLFW_KEY_LEFT)
		{
			if(pause_motion) count--;
		}
		else if (key == GLFW_KEY_TAB)
		{
			cam_follow = !cam_follow;
		}
		else if (key == GLFW_KEY_ENTER)
		{
			skeleton = !skeleton;
		}
	}
}



