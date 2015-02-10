#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "structures.hpp"
#include "gl_interface.hpp"
#include <cmath>

//! Constants
float bust_angle_y=0.0f;
float bust_angle_x=0.0f;
float height_z = 59.0f;
float armor_angle =158.0f;
float right_arm_angle=0.0f;
float left_arm_angle=0.0f;
float right_arm_angle_z=0.0f;
float left_arm_angle_z=0.0f;
float right_forearm_angle=0.0f;
float left_forearm_angle=0.0f;
float left_thigh_angle=0.0f;
float right_thigh_angle=0.0f;
float left_thigh_angle_y=0.0f;
float right_thigh_angle_y=0.0f;
float right_leg_angle=0.0f;
float left_leg_angle=0.0f;
float right_leg_angle_y=0.0f;
float left_leg_angle_y=0.0f;

float right_connect_angle=0.0f;
float right_tier_angle=0.0f;

float left_connect_angle=0.0f;
float left_tier_angle=0.0f;

unsigned int *tex= new unsigned int [10];

bool lLight=true, rLight=true, right_spot=false, left_spot=false;
bool recording=false;
bool playback=false;

unsigned int framenum=0;

int rotateside = 0;
//2.95;

double piover180 = 0.0174532925;
float camera1_x=0.0f;
float camera1_y=0.0f;
float camera1_z=0.0f;
float camera1_ay=0.0f;

float bot_x=0.0f,bot_z=0.0f,bot_ay=90.0f;
int cam=1;


// unsigned int texture[0];
//! Materials
GLfloat mat_specularWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_ambientWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_diffuseWHITE[] ={255.0,255.0,255.0,1.0};
GLfloat mat_shininessWHITE[] ={128.0 * 0.4};

GLfloat mat_specularGRAY[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientGRAY[] ={0.5,0.5,0.5,1.0};
GLfloat mat_diffuseGRAY[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessGRAY[] ={128.0 * 0.6};

GLfloat mat_specularBLUE[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientBLUE[] ={0,0,1,1.0};
GLfloat mat_diffuseBLUE[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessBLUE[] ={128.0 };

GLfloat mat_specularGREEN[] ={0.633, 0.727811, 0.633,1.0};
GLfloat mat_ambientGREEN[] ={0.0215, 0.1745, 0.0215,1.0};
GLfloat mat_diffuseGREEN[] ={0.07568, 0.61424, 0.07568,1.0};
GLfloat mat_shininessGREEN[] ={128.0};

GLfloat mat_specularYELLOW[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientYELLOW[] ={1,1,0,1.0};
GLfloat mat_diffuseYELLOW[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessYELLOW[] ={128.0};

GLfloat mat_specularRED[] ={0.75,0.75,0.75,1.0};
GLfloat mat_ambientRED[] ={1.0,0.0,0.0,1.0};
GLfloat mat_diffuseRED[] ={0.50,0.50,0.50,1.0};
GLfloat mat_shininessRED[] ={128.0};

GLfloat mat_specularORANGE[] ={0.393548, 0.271906, 0.166721, 1.0};
GLfloat mat_ambientORANGE[] ={0.2125,0.1275,0.054,1.0};
GLfloat mat_diffuseORANGE[] ={0.714, 0.4284, 0.18144, 1.0};
GLfloat mat_shininessORANGE[] ={128.0*0.2};

GLfloat mat_specularBLACK[] ={0.9,0.9,0.9,1.0};
GLfloat mat_ambientBLACK[] ={0.1,0.1,0.1,1.0};
GLfloat mat_diffuseBLACK[] ={0.1,0.1,0.1,1.0};
GLfloat mat_shininessBLACK[] ={128.0 * 0.6};

GLfloat mat_specularGRAYBLACK[] ={0.9,0.9,0.9,1.0};
GLfloat mat_ambientGRAYBLACK[] ={0.5,0.5,0.5,1.0};
GLfloat mat_diffuseGRAYBLACK[] ={0.5,0.5,0.5,1.0};
GLfloat mat_shininessGRAYBLACK[] ={128.0 * 0.6};

//! Utility Functions
void SetMaterial(GLfloat spec[], GLfloat amb[], GLfloat diff[], GLfloat shin[])
{

  glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  glMaterialfv(GL_FRONT, GL_SHININESS, shin);
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
}

void glFFrustrum(char axis,GLfloat radius1,GLfloat radius2,GLfloat height,GLint slices)
{
	glPushMatrix();
	  if (axis == 'x') glRotatef(90,0,1,0);
	  else if (axis == 'y') glRotatef(90,1,0,0);
	  GLUquadricObj* quadric = gluNewQuadric();
	  gluCylinder(quadric,radius1,radius2,height,slices,10);  
	  GLUquadricObj* quadric2 = gluNewQuadric();\
	  glPushMatrix();
	  gluDisk(quadric2,0,radius1,slices,10);
	  glPopMatrix();
	  glTranslatef(0,0,height);
	  GLUquadricObj* quadric3 = gluNewQuadric();
	  glRotatef(180,0,1,0);
	  gluDisk(quadric2,0,radius2,slices,20);
	glPopMatrix();
}

void drawdisk(float radius,int degree,int in){
	float PI=3.14159265358979324;
	int k;
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0,0,in);
	glVertex3f(0,0,0);
	for(k = 0; k <= degree; k++){
		glVertex3f((float) radius*cos((float) k*PI/180),(float) radius*sin((float) k*PI/180),0);
	}
	glEnd();
}

void drawcylinder(float radius, int longSlices, int latSlices,int p,int q,int in){

   int i,k;
   float PI=3.14159265358979324;
   for(k = 0; k < q; k++){
      glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= p; i++){
		 glTexCoord2f((float)i*1.0/p, (float)1.0/q);
		 glNormal3f( in * radius * cos( (float)1/latSlices * PI/2.0 ) * cos( 2.0 * ((float)i)/longSlices * PI ),
                     in * radius * sin( (float)1/latSlices * PI/2.0 ),
					 in * radius * cos( (float)1/latSlices * PI/2.0 ) * sin( 2.0 * ((float)i)/longSlices * PI ) );
         glVertex3f( radius * cos( (float)1/latSlices * PI/2.0 ) * cos( 2.0 * ((float)i)/longSlices * PI ),
                     radius * sin( (float)1/latSlices * PI/2.0 ),
					 radius * cos( (float)1/latSlices * PI/2.0 ) * sin( 2.0 * ((float)i)/longSlices * PI ) );
		 glTexCoord2f((float)i*1.0/p, 0);
		 glNormal3f( in * radius * cos( 2.0 * ((float)i)/longSlices * PI ),
                     0,
					 in * radius * sin( 2.0 * ((float)i)/longSlices * PI ) );
         glVertex3f( radius * cos( 2.0 * ((float)i)/longSlices * PI ),
                     0,
					 radius * sin( 2.0 * ((float)i)/longSlices * PI ) );
	  }
      glEnd();
   }
}

void glCube(GLfloat side)
{
	glPushMatrix();
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
		GLfloat a = side/2;
		glBegin(GL_QUADS);
		
		 glNormal3f(0,0,1);
		//glTexCoord2f(0.0,0.0); 
		glVertex3f(a,a,a);
		//glTexCoord2f(0.5,0.0); 
		glVertex3f(-a,a,a);
		//glTexCoord2f(0.5,0.5); 
		glVertex3f(-a,-a,a);
		//glTexCoord2f(0.0,0.5); 
		glVertex3f(a,-a,a);
		
		glNormal3f(0,0,-1);
		glVertex3f(a,a,-a);
		glVertex3f(-a,a,-a);
		glVertex3f(-a,-a,-a);
		glVertex3f(a,-a,-a);
		
		glNormal3f(1,0,0);
		glVertex3f(a,-a,a);
		glVertex3f(a,a,a);
		glVertex3f(a,a,-a);
		glVertex3f(a,-a,-a);
		
		glNormal3f(-1,0,0);
		glVertex3f(-a,a,a);
		glVertex3f(-a,a,-a);
		glVertex3f(-a,-a,-a);
		glVertex3f(-a,-a,a);
		
		glNormal3f(0,1,0);
		glVertex3f(a,a,a);
		glVertex3f(a,a,-a);
		glVertex3f(-a,a,-a);
		glVertex3f(-a,a,a);
		
		glNormal3f(0,-1,0);
		glVertex3f(a,-a,a);
		glVertex3f(a,-a,-a);
		glVertex3f(-a,-a,-a);
		glVertex3f(-a,-a,a);    
		
		glEnd();
		//glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void struct_bust(void)
{
	glNewList(bust,GL_COMPILE);
	glPushMatrix();
		glPushMatrix();
			SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
			glColor3f(1.0,1.0,1.0);
			glScalef(1.0,0.8,0.5);
			GLUquadricObj* quadric = gluNewQuadric();
			gluSphere(quadric,0.6,10,5);
			glTranslatef(0.0,-0.75,0.0);
			SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
			glColor3f(1.0,1.0,0.0);
			glCube(0.5);
			
			glTranslatef(0,0.3,0);
			SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
			glColor3ub(128,128,128);
			GLUquadricObj* quadric2 = gluNewQuadric();
			gluSphere(quadric2,0.5,5,5);
			
			glScalef(1.0,0.2,1.0);
		glPopMatrix();
		
		glPushMatrix();
			SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
			glColor3f(1,0,1);
			glScalef(1.7,2.8,0.1);
			glTranslatef(0.03,-0.1,-6);
			glCube(0.5);
			
		glPopMatrix();
		
		glPushMatrix();
			SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
			glRotatef(10,0,1,0);
			glColor3f(1,0,1);
			glScalef(0.1,2.8,0.9);
			glTranslatef(5.63,-0.1,-0.33);
			
			glCube(0.5);
			
		glPopMatrix();
		
		glPushMatrix();
			SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
			glRotatef(-10,0,1,0);
			glColor3f(1,0,1);
			glScalef(0.1,2.8,0.9);
			glTranslatef(-4.63,-0.1,-0.33);
			glCube(0.5);
			
		glPopMatrix();

		
		glPushMatrix();
			glTranslatef(0,0.25,0);
			glTranslatef(-0.8,0,0);
			glTranslatef(1.1,0,0);
			glTranslatef(0,-0.25,0);
			glTranslatef(-1.1,0.25,0.0);
			SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
			glColor3f(1.0,1.0,0.0);
			glScalef(0.5,0.5,0.5);
			glColor3ub(128,128,128);
			glTranslatef(0.0,0.05,0.0);
			glColor3ub(255,0,0);
			glFFrustrum('x',0.2,0.2,0.7,10);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0,0.25,0);
			glTranslatef(0.8,0,0);
			glTranslatef(-1.1,0,0);
			glTranslatef(0,-0.25,0);
			glScalef(-1,1,1);
			glTranslatef(-1.1,0.25,0.0);
			SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
			glColor3f(1.0,1.0,0.0);
			glScalef(0.5,0.5,0.5);
			glColor3ub(128,128,128);
			glTranslatef(0.0,0.05,0.0);
			glColor3ub(255,0,0);
			glFFrustrum('x',0.2,0.2,0.7,10);
		glPopMatrix();
	glPopMatrix();
	glEndList();
	
}
void struct_armor(void) {
	glNewList(armor,GL_COMPILE);
		glPushMatrix();
			SetMaterial(mat_specularGRAYBLACK, mat_ambientGRAYBLACK, mat_diffuseGRAYBLACK, mat_shininessGRAYBLACK);
			glColor3f(1.0,0.0,0.0);
			glPushMatrix();
				glScalef(0.3,0.7,0.4);
				GLUquadricObj* quadric = gluNewQuadric();
				glTranslatef(-2.0,0.4,0.0);
				glCube(0.5);
			glPopMatrix();
			float shear[] = { 1, 0, 0, 0, 
			0.5, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
			glPushMatrix();
				SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
				glScalef(0.3,0.7,0.4);
				glTranslatef(-2.0,0.4,0.0);
				glScalef(0.9,0.8,0.95);
				glTranslatef(0.1,0.5,0.0);
				glMultMatrixf(shear);
				glCube(0.5);
			glPopMatrix();
			glPushMatrix();
				glScalef(0.27,0.61,0.38);
				glTranslatef(-1.5,1.385,0.0);
				shear[4]=2;
				glMultMatrixf(shear);
				glCube(0.5);
			glPopMatrix();
			//Right Part of Armor
			SetMaterial(mat_specularGRAYBLACK, mat_ambientGRAYBLACK, mat_diffuseGRAYBLACK, mat_shininessGRAYBLACK);
			glPushMatrix();
				glScalef(0.3,0.7,0.4);
				glTranslatef(2.0,0.4,0.0);
				glCube(0.5);
			glPopMatrix();
			shear[4]=-0.5;
			glPushMatrix();
				SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
				glScalef(0.3,0.7,0.4);
				glTranslatef(2.0,0.4,0.0);
				glScalef(0.9,0.8,0.95);
				glTranslatef(-0.1,0.5,0.0);
				glMultMatrixf(shear);
				glCube(0.5);
			glPopMatrix();
			glPushMatrix();
				glScalef(0.27,0.61,0.38);
				glTranslatef(1.5,1.385,0.0);
				shear[4]=-2;
				glMultMatrixf(shear);
				glCube(0.5);
			glPopMatrix();
			glPushMatrix();
				glScalef(0.75,0.27,0.38);
				glTranslatef(0,3.9,0.0);
				glCube(0.5);
			glPopMatrix();
			SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
			glPushMatrix();
				glTranslatef(0,0.6,0.4);
				glRotatef(-35,1,0,0);	
				glScalef(1,0.17,0.9);
				glTranslatef(0,3.9,-0.4);
				glCube(0.5);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0.8,0.2);
				glRotatef(-75,1,0,0);	
				glScalef(1,0.17,0.9);
				glTranslatef(0,3.9,-0.4);
				glCube(0.5);
			glPopMatrix();
			SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
			glPushMatrix();
				glTranslatef(0.25,0.8,-0.5);
				glNormal3f(0,0.12,-0.4);
				glBegin(GL_TRIANGLE_STRIP);	
				glVertex3f( 0.0f, -0.4f, -0.12f );
				glVertex3f( 0.0f, 0.0f, 0.0f );
				glVertex3f( 0.22f, -0.4f, -0.12f );
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.25,0.8,-0.5);
				glNormal3f(0,0.12,-0.4);
				glBegin(GL_TRIANGLE_STRIP);	
				glVertex3f( 0.0f, -0.4f, -0.12f );
				glVertex3f( 0.0f, 0.0f, 0.0f );
				glVertex3f( -0.12f, -0.4f, -0.12f );
				glEnd();
			glPopMatrix();
			SetMaterial(mat_specularGRAYBLACK, mat_ambientGRAYBLACK, mat_diffuseGRAYBLACK, mat_shininessGRAYBLACK);
			glPushMatrix();
				glTranslatef(0.25,0.8,-0.5);
				glNormal3f(-0.132,-0.0924,-0.066);
				glBegin(GL_TRIANGLE_STRIP);	
				glVertex3f( 0.0f, 0.0f, 0.0f );
				glVertex3f( 0.22f, -0.4f, -0.12f );
				glVertex3f( 0.0f, 0.3f, 0.42f );
				glVertex3f( 0.3f, -0.4f, 0.42f );
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.25,0.8,-0.5);
				glNormal3f(0.132,-0.0924,-0.066);
				glBegin(GL_TRIANGLE_STRIP);	
				glVertex3f( 0.0f, 0.0f, 0.0f );
				glVertex3f( -0.12f, -0.4f, -0.12f );
				glVertex3f( 0.0f, 0.3f, 0.42f );
				glVertex3f( -0.2f, -0.4f, 0.42f );
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glScalef(0.15,0.15,1.9);
				glRotatef(90,0,0,1);
				glRotatef(90,1,0,0);
				glTranslatef(6.5,-0.05,1.24);
				drawcylinder(1,40,16,10,16,2);
				glPushMatrix();
					glNormal3f(1,0,0);
					glScalef(1,0.09,1);
					glTranslatef(1,0.1,0);
					gluSphere(quadric,0.3,10,10);
				glPopMatrix();
				glRotatef(90,1,0,0);
				drawdisk(1,90,1);
				glTranslatef(0,0,-0.095);
				drawdisk(1,90,-1);
			glPopMatrix();
			glPushMatrix();
				glScalef(0.15,0.15,1.9);
				glRotatef(90,0,0,1);
				glRotatef(270,1,0,0);
				glTranslatef(6.5,-0.05,1.24);
				drawcylinder(1,40,16,10,16,2);
				glPushMatrix();
					glNormal3f(1,0,0);
					glScalef(1,0.09,1);
					glTranslatef(1,1.0,0);
					gluSphere(quadric,0.3,10,10);
				glPopMatrix();
				glRotatef(90,1,0,0);
				drawdisk(1,90,1);
				glTranslatef(0,0,-0.095);
				drawdisk(1,90,-1);
			glPopMatrix();
			glScalef(1.0,0.2,1.0);
		glPopMatrix();
	glEndList();
}

void struct_pelvis(void)
{
	glNewList(pelvis,GL_COMPILE);
	glPushMatrix();
		SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
		glColor3f(1.0,1.0,0.0);
		glTranslatef(0.0,-0.75,0.0);
		glRotatef(90,1,0,0);
		GLUquadricObj* quadric = gluNewQuadric();
		gluCylinder(quadric,0.2,0.05,0.5,4,10);  
		gluDisk(quadric,0,0.2,4,10);
		glTranslatef(0,0,0.5);
		gluDisk(quadric,0,0.05,4,10);
		glTranslatef(-0.2,0,-0.1);
		glFFrustrum('x',0.05,0.05,0.4,4);
	glPopMatrix();	
	glEndList();
}

void struct_forearm(void)
{
	
	glNewList(forearm,GL_COMPILE);
	glPushMatrix();
		GLUquadricObj* quadric = gluNewQuadric();
		glTranslatef(-1.2,-0.65,0.0);
		//glTranslatef(-0.0,-0.7,0.0);
		//glScalef(,0.5,0.5);
		glPushMatrix();
			SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
			glScalef(1,1,0.7);
			glFFrustrum('y',0.1,0.05,0.7,20);
		glPopMatrix();
		
		SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
		glTranslatef(0.0,-0.77,0.0);
		
	glPopMatrix();
		
	glEndList();
}

void struct_hand(void)
{
	
	glNewList(hand,GL_COMPILE);
	glPushMatrix();	
		//glTranslatef(-1.2,-0.65,0.0);
		//glTranslatef(-0.0,-0.7,0.0);
		//glScalef(,0.5,0.5);
		
		SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
		//glTranslatef(0.0,-0.77,0.0);
		glPushMatrix();
			glScalef(0.1,0.15,0.03);
			glCube(1.0);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.0,-0.07,0.07);
			glScalef(0.1,0.03,0.15);
			glCube(1.0);
		glPopMatrix();
		
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glPushMatrix();
			glTranslatef(-0.1,0.0,-0.01);
			glScalef(0.1,0.1,0.1);
			glFFrustrum('x',0.3,0.3,0.6,30);
		glPopMatrix();
	glPopMatrix();
	glEndList();
}

void struct_connect(void)
{
	glNewList(connect,GL_COMPILE);
	glPushMatrix();	
		
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glPushMatrix();
			glRotatef(15,0,0,1);
			glTranslatef(-0.1,-0.03,-0.015);
			glScalef(0.03,-0.1,0.1);
			glFFrustrum('y',0.35,0.35,3.5,30);
		glPopMatrix();
	glPopMatrix();
	glEndList();
}
void struct_tire(void)
{
	glNewList(tire,GL_COMPILE);
	glPushMatrix();	
		glPushMatrix();
			glTranslatef(-0.2,-0.52,-0.01);
			glScalef(0.05,-0.1,0.1);
			glFFrustrum('y',1.5,0.5,9.5,30);
		glPopMatrix();
		
		glTranslatef(-0.13,-0.0,-0.01);
		glScalef(-0.5,0.5,0.5);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glFFrustrum('x',0.15,0.35,0.38,30);
		SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
		glTranslatef(0.3,0.0,0.0);
		glRotatef(90,0,1,0);
		glFFrustrum('z',0.5,0.5,0.2,30);
		
	glPopMatrix();
	glEndList();
}

void struct_frontwheel(void)
{
	glNewList(frontwheel,GL_COMPILE);
	glPushMatrix();
		glTranslatef(-1.1,0.25,0.0);
		SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
		glScalef(0.5,0.5,0.5);

		GLUquadricObj* quadric = gluNewQuadric();
		glTranslatef(0.0,0.05,0.0);
		glColor3ub(255,0,0);
		
		glTranslatef(-0.2,0.00,0.0);
		
		SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
		glTranslatef(0.0,-0.25,0.2);
		glScalef(-1,1,1);
		glFFrustrum('x',0.15,0.35,0.5,30);
		SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
		glTranslatef(0.3,0.0,0.0);
		glRotatef(90,0,1,0);
		glFFrustrum('z',0.5,0.5,0.2,30);
	glPopMatrix();
	glEndList();
}

void struct_arm(void)
{
	
	glNewList(arm,GL_COMPILE);
	glPushMatrix();
		glTranslatef(-1.1,0.25,0.0);
		SetMaterial(mat_specularRED, mat_ambientRED, mat_diffuseRED, mat_shininessRED);
		glColor3f(1.0,1.0,0.0);
		glScalef(0.5,0.5,0.5);
		glColor3ub(128,128,128);
		GLUquadricObj* quadric = gluNewQuadric();
		glTranslatef(0.0,0.05,0.0);
		glColor3ub(255,0,0);
		//glFFrustrum('x',0.2,0.2,0.7,10);
		glTranslatef(-0.2,0.00,0.0);
	
		glPushMatrix();
			glFFrustrum('y',0.3,0.28,0.75,30);
			glScalef(1,2,1);
			gluSphere(quadric,0.3,20,20);
		glPopMatrix();
		
		SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
		
		/*glPushMatrix();
			glTranslatef(0.0,-0.25,0.2);
			glScalef(-1,1,1);
			glFFrustrum('x',0.15,0.35,0.5,30);
			SetMaterial(mat_specularBLACK, mat_ambientBLACK, mat_diffuseBLACK, mat_shininessBLACK);
			glTranslatef(0.3,0.0,0.0);
			glRotatef(90,0,1,0);
			glFFrustrum('z',0.5,0.5,0.2,30);
		glPopMatrix();
		*/
		SetMaterial(mat_specularGRAYBLACK, mat_ambientGRAYBLACK, mat_diffuseGRAYBLACK, mat_shininessGRAYBLACK);
		glTranslatef(0.0,-0.75,0.0);
		glFFrustrum('y',0.25,0.22,0.75,30);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glTranslatef(-0.2,-0.90,0.0);
		glFFrustrum('x',0.2,0.2,0.4,30);

	glPopMatrix();		
	glEndList();
}

void struct_leg(void)
{
	
	glNewList(leg,GL_COMPILE);
	glPushMatrix();
		
		glTranslatef(0.4,-2.3,0.0);
		glScalef(2.0,1.3,2.0);
		glRotatef(3,0,0,1);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3ub(128,128,128);
		GLUquadricObj* quadric = gluNewQuadric();
		gluSphere(quadric,0.1,20,20);
		
		glTranslatef(0.0,-0.5,0.0);
		glScalef(0.4,2,0.4);
		SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
		glColor3ub(0,0,255);
		glCube(0.5);
	glPopMatrix();		
	glEndList();
	

}

void struct_foot(void)
{
	glNewList(foot,GL_COMPILE);
	glPushMatrix();
		
		glTranslatef(0.4,-2.3,0.0);
		glScalef(2.0,1.3,2.0);
		glRotatef(3,0,0,1);
		GLUquadricObj* quadric = gluNewQuadric();
		
		glTranslatef(0.0,-0.5,0.0);
		glScalef(0.4,2,0.4);
		SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
		
		glColor3ub(255,0,0);
		glTranslatef(0.0,-0.25,-0.2);
		glScalef(1.5,0.3,1);
		glFFrustrum('z',0.2,0.1,0.7,10);
		
		glTranslatef(0.0,0.0,0.65);
		gluSphere(quadric,0.1,20,20);
	glPopMatrix();		
	glEndList();
	

}

void struct_thigh(void)
{
	glNewList(thighs,GL_COMPILE);
	glPushMatrix();
		glTranslatef(-0.2,-1.15,0.0);
		glScalef(2.0,2.0,2.0);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3ub(128,128,128);
		GLUquadricObj* quadric = gluNewQuadric();
		gluSphere(quadric,0.05,20,20);

		glTranslatef(-0.03,0.01,0.0);
		SetMaterial(mat_specularWHITE, mat_ambientWHITE, mat_diffuseWHITE, mat_shininessWHITE);
		glColor3ub(255,255,255);
		glRotatef(-8,0,0,1);
		glFFrustrum('y',0.064,0.064,0.55,8);

	glPopMatrix();	
	glEndList();
}

void struct_head(void)
{
	
	glNewList(head,GL_COMPILE);
	glPushMatrix();
		//SetMaterial(mat_specularWHITE, mat_ambientWHITE, mat_diffuseWHITE, mat_shininessWHITE);
		SetMaterial(mat_specularYELLOW, mat_ambientYELLOW, mat_diffuseYELLOW, mat_shininessYELLOW);
		glColor3ub(255,255,255);
		glTranslatef(0,6.6,0);
		glScalef(0.25,2.0,0.3);
		GLUquadricObj* quadric = gluNewQuadric();
		gluSphere(quadric,0.5,10,10);
		glPushMatrix();
			glTranslatef(0,0,0);
			//glFFrustrum('y',0.25,0.25,0.8,10);
		glPopMatrix();
		SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
		glColor3ub(0,0,255);
		glTranslatef(0.0,0.2,0.2);
		glScalef(0.8,0.4,0.5);
		glCube(1.0);
		
	glPopMatrix();
	glEndList();
}

void struct_neck(void)
{
	
	glNewList(neck,GL_COMPILE);
	glPushMatrix();
		//SetMaterial(mat_specularWHITE, mat_ambientWHITE, mat_diffuseWHITE, mat_shininessWHITE);
		SetMaterial(mat_specularGRAY, mat_ambientGRAY, mat_diffuseGRAY, mat_shininessGRAY);
		glColor3ub(255,255,255);
		glTranslatef(0,5.3,0);
		glScalef(0.3,0.5,0.5);
		GLUquadricObj* quadric = gluNewQuadric();
		glPushMatrix();
			glFFrustrum('y',0.25,0.25,0.8,10);
		glPopMatrix();
		//gluSphere(quadric,0.6,10,5);
		glScalef(1,2,1);
		glTranslatef(0,0.4,0);
		SetMaterial(mat_specularBLUE, mat_ambientBLUE, mat_diffuseBLUE, mat_shininessBLUE);
		glBegin(GL_TRIANGLE_STRIP);	
			//glVertex3f( -0.35f, -0.1f, 0.0f );
			
			glVertex3f( -0.35f, -0.4f, 0.0f );
			glVertex3f( -0.35f, -0.7f, 0.0f );
			
			glVertex3f( -0.25f, -0.4f, 0.35f );
			glVertex3f( -0.25f, -0.75f, 0.35f ); //vertex 1
			 //vertex 2
			glVertex3f( 0.25f, -0.75f, 0.35f );
			glVertex3f( 0.25f, -0.4f, 0.35f );
			
			glVertex3f( 0.35f, -0.7f, 0.0f );
			glVertex3f( 0.35f, -0.4f, 0.0f );
			
			//glVertex3f( 0.35f, -0.1f, 0.0f );
			//vertex 3
			//glVertex3f( 1.5f, 1.0f, 0.0f ); //vertex 4
			
		glEnd();
	glPopMatrix();
	glEndList();
}

//! Initialize Display Lists
void init_structures(void)
{
	struct_head();
	struct_neck();
	struct_bust();
	struct_frontwheel();
	struct_armor();
	struct_pelvis();
	struct_thigh();
	struct_arm();
	struct_forearm();
	struct_leg();
	struct_foot();
	struct_hand();
	struct_tire();
	struct_connect();
}
