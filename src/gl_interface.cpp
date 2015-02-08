#include <math.h>
#include "gl_interface.hpp"
#include <iostream>

int win_width;
int win_height;
bool pause_motion = false;
int count = 0;

//! Initialize GL State
void initGL(void)
{
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);

	//Lighting params
	/*glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	GLfloat lightvals[] ={0.3,0.3,0.3,1};
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightvals);
	glLightfv(GL_LIGHT1,GL_AMBIENT,lightvals);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightvals);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,lightvals);

	GLfloat lightvals2[] = {0.5,0.4,0.2,1};
	glLightfv(GL_LIGHT2,GL_DIFFUSE,lightvals2);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,lightvals2);
	glLightfv(GL_LIGHT3,GL_AMBIENT,lightvals2);
	glLightfv(GL_LIGHT3,GL_AMBIENT,lightvals2);


	glGenTextures(10,tex);

	//texture = loadTexture("../images/marble.bmp",98);
	//texture = loadTexture("../images/armor.bmp",97);	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT,GL_FILL);
	init_structures();
	init_room();
	*/
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
	//!Close the window if the ESC key was pressed
	//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      //glfwSetWindowShouldClose(window, GL_TRUE);
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
	}
	/*
		else if (key == GLFW_KEY_F12)
		{
			recording=!recording;
			cout<<"Recording mode is "<<recording<<endl;
		}
		else if(playback) ;

		else if (key == GLFW_KEY_LEFT) {
			bot_ay+=5;
			rotateside = 1;
		}
	    else if (key == GLFW_KEY_RIGHT) {
	    	bot_ay-=5;
	    	rotateside = -1;
	    }
		else if (key == GLFW_KEY_UP) {
			bot_x-=0.1*(float)(cos(bot_ay*piover180));
			bot_z+=0.1*(float)(sin(bot_ay*piover180));
		}
		else if (key == GLFW_KEY_DOWN) {
			bot_x+=0.1*(float)(cos(bot_ay*piover180));
			bot_z-=0.1*(float)(sin(bot_ay*piover180));
		}
		else if (key == '1'){
			right_arm_angle-=2.0f;
		}
		else if (key == 'Q'){
			right_arm_angle+=2.0f;
		}
		else if (key == 'D'){
			right_arm_angle_z-=2.0f;
			if (right_arm_angle_z<-50.0f) right_arm_angle_z=-50.0f; 
		}
		else if (key == 'F'){
			left_arm_angle_z-=2.0f;
			if (left_arm_angle_z<-10.0f) left_arm_angle_z=-10.0f;
		}
		
		else if (key == 'G'){
			right_arm_angle_z+=2.0f;
			if (right_arm_angle_z>10.0f) right_arm_angle_z=10.0f;
		}
		else if (key == 'H'){
			left_arm_angle_z+=2.0f;
			if (left_arm_angle_z>50.0f) left_arm_angle_z=50.0f;
		}
		
		else if (key == '2')
			{
				right_forearm_angle-=2.0f;
				if (right_forearm_angle<-130.0f) right_forearm_angle=-130.0f; 
			}
	    else if (key == 'W')
			{
				right_forearm_angle+=2.0f;
				if (right_forearm_angle>0.0f) right_forearm_angle=0.0f; 
			}
		else if (key == '3'){
			left_arm_angle-=2.0f;
		}
		else if (key == 'E'){
			left_arm_angle+=2.0f;
		}
		else if (key == '4')
			{
				left_forearm_angle-=2.0f;
				if (left_forearm_angle<-130.0f) left_forearm_angle=-130.0f; 
			}
		else if (key == 'R')
			{
				left_forearm_angle+=2.0f;
				if (left_forearm_angle>0.0f) left_forearm_angle=0.0f; 
			}
		else if (key == '5')
			{
				left_thigh_angle-=2.0f;
				if (left_thigh_angle<-100.0f) left_thigh_angle=-100.0f;

			}
		else if (key == 'T')
			{
				left_thigh_angle+=2.0f;
				if (left_thigh_angle>100.0f) left_thigh_angle=100.0f;

			}
		else if (key == '6')
			{
				left_leg_angle+=2.0f;
				if (left_leg_angle>150.0f) left_leg_angle=150.0f; 
			}
		else if (key == 'Y')
			{
				left_leg_angle-=2.0f;
				if (left_leg_angle<-100.0f) left_leg_angle=-100.0f;
			}
		else if (key == GLFW_KEY_F1)
			{
				left_leg_angle_y+=2.0f;
				//~ if (left_leg_angle<-100.0f) left_leg_angle=-100.0f;
			}
		else if (key == 'L')
			{
				left_leg_angle_y-=2.0f;
				//~ if (left_leg_angle<-100.0f) left_leg_angle=-100.0f;
			}
		else if (key == '7')
			{
				right_thigh_angle-=2.0f;
				if (right_thigh_angle<-100.0f) right_thigh_angle=-100.0f;
			}
		else if (key == 'U')
			{
				right_thigh_angle+=2.0f;
				if (right_thigh_angle>100.0f) right_thigh_angle=100.0f;
			}
		else if (key == '8')
			{
				right_leg_angle+=2.0f;
				if (right_leg_angle>150.0f) right_leg_angle=150.0f; 
			}
		else if (key == 'I')
			{
				right_leg_angle-=2.0f;
				if (right_leg_angle<-100.0f) right_leg_angle=-100.0f;
			}
		else if (key == 'K')
			{
				right_leg_angle_y-=2.0f;
				//~ if (right_leg_angle_y<-100.0f) right_leg_angle=-100.0f;
			}
		else if (key == GLFW_KEY_F4) right_spot=!right_spot;
		else if (key == GLFW_KEY_F5) left_spot=!left_spot;
		else if (key == GLFW_KEY_F2)
			{
				right_leg_angle_y+=2.0f;
				//~ if (right_leg_angle_y<-100.0f) right_leg_angle=-100.0f;
			}
		else if (key == '9')
			{
				left_thigh_angle_y-=2.0f;
				if (left_thigh_angle_y<-40.0f) left_thigh_angle_y=-40.0f;
			}
		else if (key == 'O')
			{
				left_thigh_angle_y+=2.0f;
				if (left_thigh_angle_y>40.0f) left_thigh_angle_y=40.0f;
			}
		else if (key == '0')
			{
				right_thigh_angle_y-=2.0f;
				if (right_thigh_angle_y<-40.0f) right_thigh_angle_y=-40.0f;
			}
		else if (key == 'P')
			{
				right_thigh_angle_y+=2.0f;
				if (right_thigh_angle_y>40.0f) right_thigh_angle_y=40.0f;
			}
		else if (key == '-')
			{
				right_connect_angle+=2.0f;
				if (right_connect_angle>200.0f) right_connect_angle=200.0f; 
			}
		else if (key == ';')
			{
				right_connect_angle-=2.0f;
				if (right_connect_angle<-100.0f) right_connect_angle=-100.0f;
			}
		else if (key == '=')
			{
				left_connect_angle+=2.0f;
				if (left_connect_angle>200.0f) left_connect_angle=200.0f; 
			}
		else if (key == ',')
			{
				left_connect_angle-=2.0f;
				if (left_connect_angle<-100.0f) left_connect_angle=-100.0f;
			}
			
		else if (key == '[')
			{
				right_tier_angle+=2.0f;
				if (right_tier_angle>200.0f) right_tier_angle=200.0f;
			}
		else if (key == '.')
			{
				right_tier_angle-=2.0f;
				if (right_tier_angle<-160.0f) right_tier_angle=-160.0f; 
			}
			
		else if (key == ']')
			{
				left_tier_angle+=2.0f;
				if (left_tier_angle>160.0f) left_tier_angle=160.0f; 
			}
		else if (key == '/')
			{
				left_tier_angle-=2.0f;
				if (left_tier_angle<-200.0f) left_tier_angle=-200.0f;
			}
		else if (key == 'Z')
			{
				armor_angle-=2.0f;
				//~ if (left_tier_angle<-200.0f) left_tier_angle=-200.0f;
			}
			
		else if (key == 'J')
			{
				armor_angle+=2.0f;
				//~ if (left_tier_angle<-200.0f) left_tier_angle=-200.0f;
			}
		
		else if (key=='A') lLight=!lLight;
			
		else if (key=='S') rLight=!rLight;

		else if (key=='N')
			{
				camera1_x-=(float)sin(camera1_ay*piover180) * 0.15f;
				camera1_z-=(float)cos(camera1_ay*piover180) * 0.15f;
			}
		else if (key=='M')
			{
				camera1_x+=(float)sin(camera1_ay*piover180) * 0.15f;
				camera1_z+=(float)cos(camera1_ay*piover180) * 0.15f;
				
			}
		else if (key=='V')
			{
				camera1_ay-= 1.0f;
				
			}
		else if (key=='B')
			{
				camera1_ay+=1.0f;
			}
		else if (key=='C')
			{
				camera1_y+=0.1;
			}
		else if (key=='X')
			{
				camera1_y-=0.1;
			}
		else if (key=='`') {
			if (cam!=3) cam++;
			else cam=1;
		}
		else if (key == GLFW_KEY_SPACE)
		{
			printframe();
		}
		else if (key == GLFW_KEY_F11)
		{
			playback=!playback;
			glfwSetTime(0);
			cout<<"Playback mode is "<<playback<<endl;
		}
		else if (key == GLFW_KEY_F12)
		{
			recording=!recording;
			cout<<"Recording mode is "<<recording<<endl;
		}
		else if (key == GLFW_KEY_ENTER)
		{
			if(count == 0){
			bool flag = true;
			while(flag){
				flag = false;
				if(height_z<-10){
					height_z+=1;
					flag = true;
				}

				if(height_z>-8){
					height_z-=1;
					flag = true;
				}
				
				if(bust_angle_x<87){
					bust_angle_x+=2;
					flag = true;
				}if(bust_angle_x>89){
					bust_angle_x-=2;
					flag = true;
				}

				if(armor_angle<-1){
					armor_angle+=2;
					flag = true;
				}if(armor_angle>1){
					armor_angle-=2;
					flag = true;
				}


				if(right_arm_angle<-1){
					right_arm_angle+=2;
					flag = true;
				}if(right_arm_angle>1){
					right_arm_angle-=2;
					flag = true;
				}


				if(left_arm_angle<-1){
					left_arm_angle+=2;
					flag = true;
				}if(left_arm_angle>1){
					left_arm_angle-=2;
					flag = true;
				}

				if(right_arm_angle_z<9){
					right_arm_angle_z+=2;
					flag = true;
				}if(right_arm_angle_z>11){
					right_arm_angle_z-=2;
					flag = true;
				}

				if(left_arm_angle_z<-11){
					left_arm_angle_z+=2;
					flag = true;
				}if(left_arm_angle_z>-9){
					left_arm_angle_z-=2;
					flag = true;
				}

				if(right_forearm_angle<-1){
					right_forearm_angle+=2;
					flag = true;
				}if(right_forearm_angle>1){
					right_forearm_angle-=2;
					flag = true;
				}

				if(left_forearm_angle<-1){
					left_forearm_angle+=2;
					flag = true;
				}if(left_forearm_angle>1){
					left_forearm_angle-=2;
					flag = true;
				}

				if(left_thigh_angle<-1){
					left_thigh_angle+=2;
					flag = true;
				}if(left_thigh_angle>1){
					left_thigh_angle-=2;
					flag = true;
				}
				
				if(right_thigh_angle<-1){
					right_thigh_angle+=2;
					flag = true;
				}if(right_thigh_angle>1){
					right_thigh_angle-=2;
					flag = true;
				}

				if(left_thigh_angle_y<-11){
					left_thigh_angle_y+=2;
					flag = true;
				}if(left_thigh_angle_y>-9){
					left_thigh_angle_y-=2;
					flag = true;
				}

				if(right_thigh_angle_y<9){
					right_thigh_angle_y+=2;
					flag = true;
				}if(right_thigh_angle_y>11){
					right_thigh_angle_y-=2;
					flag = true;
				}

				if(right_leg_angle<149){
					right_leg_angle+=2;
					flag = true;
				}if(right_leg_angle>151){
					right_leg_angle-=2;
					flag = true;
				}

				if(left_leg_angle<149){
					left_leg_angle+=2;
					flag = true;
				}if(left_leg_angle>151){
					left_leg_angle-=2;
					flag = true;
				}

				if(right_leg_angle_y<15){
					right_leg_angle_y+=2;
					flag = true;
				}if(right_leg_angle_y>17){
					right_leg_angle_y-=2;
					flag = true;
				}

				if(left_leg_angle_y<-11){
					left_leg_angle_y+=2;
					flag = true;
				}if(left_leg_angle_y>-9){
					left_leg_angle_y-=2;
					flag = true;
				}

				if(right_connect_angle<163){
					right_connect_angle+=2;
					flag = true;
				}if(right_connect_angle>165){
					right_connect_angle-=2;
					flag = true;
				}

				if(right_tier_angle<-165){
					right_tier_angle+=2;
					flag = true;
				}if(right_tier_angle>-163){
					right_tier_angle-=2;
					flag = true;
				}


				if(left_connect_angle<163){
					left_connect_angle+=2;
					flag = true;
				}if(left_connect_angle>165){
					left_connect_angle-=2;
					flag = true;
				}

				if(left_tier_angle<-165){
					left_tier_angle+=2;
					flag = true;
				}if(left_tier_angle>-163){
					left_tier_angle-=2;
					flag = true;
				}
				renderGL();
				glfwSwapBuffers(window);
			}
			}
			if(count == 1){
				bool flag = true;
				while(flag){
					flag = false;
					
					if(height_z<58){
						height_z+=2;
						flag = true;
					}

					if(height_z>60){
						height_z-=2;
						flag = true;
					}
					
					if(bust_angle_x<-1){
						bust_angle_x+=2;
						flag = true;
					}if(bust_angle_x>1){
						bust_angle_x-=2;
						flag = true;
					}

					if(armor_angle<157){
						armor_angle+=2;
						flag = true;
					}if(armor_angle>159){
						armor_angle-=2;
						flag = true;
					}


					if(right_arm_angle<-1){
						right_arm_angle+=2;
						flag = true;
					}if(right_arm_angle>1){
						right_arm_angle-=2;
						flag = true;
					}


					if(left_arm_angle<-1){
						left_arm_angle+=2;
						flag = true;
					}if(left_arm_angle>1){
						left_arm_angle-=2;
						flag = true;
					}

					if(right_arm_angle_z<-1){
						right_arm_angle_z+=2;
						flag = true;
					}if(right_arm_angle_z>1){
						right_arm_angle_z-=2;
						flag = true;
					}

					if(left_arm_angle_z<-1){
						left_arm_angle_z+=2;
						flag = true;
					}if(left_arm_angle_z>1){
						left_arm_angle_z-=2;
						flag = true;
					}

					if(right_forearm_angle<-1){
						right_forearm_angle+=2;
						flag = true;
					}if(right_forearm_angle>1){
						right_forearm_angle-=2;
						flag = true;
					}

					if(left_forearm_angle<-1){
						left_forearm_angle+=2;
						flag = true;
					}if(left_forearm_angle>1){
						left_forearm_angle-=2;
						flag = true;
					}

					if(left_thigh_angle<-1){
						left_thigh_angle+=2;
						flag = true;
					}if(left_thigh_angle>1){
						left_thigh_angle-=2;
						flag = true;
					}
					
					if(right_thigh_angle<-1){
						right_thigh_angle+=2;
						flag = true;
					}if(right_thigh_angle>1){
						right_thigh_angle-=2;
						flag = true;
					}

					if(left_thigh_angle_y<-1){
						left_thigh_angle_y+=2;
						flag = true;
					}if(left_thigh_angle_y>1){
						left_thigh_angle_y-=2;
						flag = true;
					}

					if(right_thigh_angle_y<-1){
						right_thigh_angle_y+=2;
						flag = true;
					}if(right_thigh_angle_y>1){
						right_thigh_angle_y-=2;
						flag = true;
					}

					if(right_leg_angle<-1){
						right_leg_angle+=2;
						flag = true;
					}if(right_leg_angle>1){
						right_leg_angle-=2;
						flag = true;
					}

					if(left_leg_angle<-1){
						left_leg_angle+=2;
						flag = true;
					}if(left_leg_angle>1){
						left_leg_angle-=2;
						flag = true;
					}

					if(right_leg_angle_y<-1){
						right_leg_angle_y+=2;
						flag = true;
					}if(right_leg_angle_y>1){
						right_leg_angle_y-=2;
						flag = true;
					}

					if(left_leg_angle_y<-1){
						left_leg_angle_y+=2;
						flag = true;
					}if(left_leg_angle_y>1){
						left_leg_angle_y-=2;
						flag = true;
					}

					if(right_connect_angle<-1){
						right_connect_angle+=2;
						flag = true;
					}if(right_connect_angle>1){
						right_connect_angle-=2;
						flag = true;
					}

					if(right_tier_angle<-1){
						right_tier_angle+=2;
						flag = true;
					}if(right_tier_angle>1){
						right_tier_angle-=2;
						flag = true;
					}


					if(left_connect_angle<-1){
						left_connect_angle+=2;
						flag = true;
					}if(left_connect_angle>1){
						left_connect_angle-=2;
						flag = true;
					}

					if(left_tier_angle<-1){
						left_tier_angle+=2;
						flag = true;
					}if(left_tier_angle>1){
						left_tier_angle-=2;
						flag = true;
					}
					if (recording) capture_frame(framenum++);
					renderGL();
					glfwSwapBuffers(window);
				}
			}
			count = 1 - count;	
		}
	}
	if (action == GLFW_RELEASE) {
		rotateside=0;
	}
	*/
}



