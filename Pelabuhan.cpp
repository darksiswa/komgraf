#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

#define ANGLE 0.2
#define SCALE 0.9
#define RAND 0.01

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include "imageloader.h"
#include "vec3f.h"
//#include "reader.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>



#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
 
#define KEY_ESCAPE 27
 
using namespace std;
#endif


GLfloat theta[] = {0.0,0.0,0.0};
int r=-50;
static GLfloat spin, spin2 = 0.0;
float angle = 0;
using namespace std;

float lastx, lasty;
GLint stencilBits;
static int viewx = 50;
static int viewy = 24;
static int viewz = 80;

float rot = 0;

GLuint texture[2]; //array untuk texture
GLuint SkyboxTexture[6]; 

//Reader obj;

//float g_rotation;

struct Images {//tempat image
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
};
typedef struct Images Images;


void kapal()
{
	glBegin(GL_QUADS);           
	glColor3f(.54,.27,.07);
	glVertex3f(-.4*r,.2*r,-.2*r);     
	glVertex3f(.4*r,.2*r,-.2*r);
	glVertex3f(.4*r,0.1*r,-.15*r);
	glVertex3f(-.4*r,0.1*r,-.15*r);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.35,0.77,0.38);
	glVertex3f(-.4*r,0.1*r,.15*r);       
	glVertex3f(.4*r,0.1*r,.15*r);
	glVertex3f(.4*r,.2*r,.2*r);
	glVertex3f(-.4*r,.2*r,.2*r);
	glEnd();


        	glBegin(GL_QUADS);           
     	glColor3f(0.41,0.41,0.41);       
	 
	glVertex3f(-.4*r,.1*r,-.15*r);
	glVertex3f(.4*r,.1*r,-.15*r);
	glVertex3f(.4*r,-.2*r,0.0*r);
        	glVertex3f(-.4*r,-.2*r,0.0*r);
	glEnd();
	
	glBegin(GL_QUADS);
	glColor3f(0.61,0.61,0.61);
	glVertex3f(-.4*r,-.2*r,0.0*r);        
        	glVertex3f(.4*r,-.2*r,0.0*r);
        	glVertex3f(.4*r,.1*r,.15*r);
        	glVertex3f(-.4*r,.1*r,.15*r);
	glEnd();
	
        	glBegin(GL_QUADS);
	glColor3f(0.60,0.16,0.42);
	glVertex3f(-.6*r,.2*r,0.0*r);               
	glVertex3f(-.4*r,.2*r,-.2*r);
        glVertex3f(-.4*r,.1*r,-.15*r);           
		glVertex3f(-.555*r,.1*r,0.0);
	glEnd();

        	glBegin(GL_QUADS);
	glColor3f(0.80,0.26,0.12);
	glVertex3f(-.555*r,.1*r,0.0*r);              
        	glVertex3f(-.4*r,.1*r,.15*r);
        	glVertex3f(-.4*r,.2*r,.2*r);
        	glVertex3f(-.6*r,.2*r,0.0*r);
	glEnd();


        	glBegin(GL_QUADS);
	glColor3f(0.70,0.46,0.82);
        	glVertex3f(.555*r,.1*r,0.0*r);             
        	glVertex3f(.4*r,.1*r,-.15*r);
        	glVertex3f(.4*r,.2*r,-.2*r);               
	glVertex3f(.6*r,.2*r,0.0*r);
        	glEnd();
       
        
        
        	glBegin(GL_QUADS);
	glColor3f(0.30,0.96,0.42);
        	glVertex3f(.6*r,.2*r,0.0*r);                
			glVertex3f(.4*r,.2*r,.2*r);
        	glVertex3f(.4*r,.1*r,.15*r);
	glVertex3f(.555*r,.1*r,0.0*r);
        	glEnd();

	


        	glBegin(GL_TRIANGLES);                
	glColor3f(0.6f, 0.7f, 0.5f);
	glVertex3f(-.555*r,.1*r,-0*r);                 
	glVertex3f(-.4*r,.1*r,-.15*r);
	glVertex3f(-.4*r,-.2*r,-0.0*r);
	glEnd();

         	glBegin(GL_TRIANGLES);
	glColor3f(0.4f, 0.6f, 0.4f);
        	glVertex3f(-.4*r,-.2*r,0.0*r);        
	glVertex3f(-.4*r,.1*r,.15*r);
	glVertex3f(-.555*r,.1*r,0*r);
	glEnd();


        	glBegin(GL_TRIANGLES);               
        	glColor3f(0.7f, 0.7f, 0.3f);
        	glVertex3f(.4*r,-.2*r,-0.0*r);       
        	glVertex3f(.4*r,.1*r,-.15*r);
	glVertex3f(.555*r,.1*r,-0*r);
	glEnd();
	
	

        	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.7f, 0.2f);
        	glVertex3f(.555*r,.1*r,0*r);         
        	glVertex3f(.4*r,.1*r,.15*r);
        	glVertex3f(.4*r,-.2*r,0.0*r);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(.555*r,.1*r,0*r);
	glVertex3f(.4*r,.1*r,-0.15*r);
	glVertex3f(-0.4*r,.1*r,-0.15*r);
	glVertex3f(-.555*r,.1*r,0*r);
	glVertex3f(-0.4*r,.1*r,.15*r);
	glVertex3f(.4*r,.1*r,0.15*r);
	glEnd();

	glBegin(GL_QUADS);                       
	glColor3f(0.30,0.96,0.42);
	glVertex3f(-.2,.3,.1);                   
    	glVertex3f(-.2,.1,.1);               
		glVertex3f(-.1,.1,.1);
    	glVertex3f(-.1,.3,.1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.30,0.96,0.42);
	glVertex3f(-.2*r,.3*r,-.1*r);
    	glVertex3f(-.2*r,.1*r,-.1*r);                
    	glVertex3f(-.1*r,.1*r,-.1*r);
    	glVertex3f(-.1*r,.3*r,-.1*r);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.30,0.96,0.42);
	glVertex3f(-.2*r,.1*r,.1*r);
    	glVertex3f(-.2*r,.3*r,.1*r);                
    	glVertex3f(-.2*r,.3*r,-.1*r);
    	glVertex3f(-.2*r,.1*r,-.1*r);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.30,0.96,0.42);
	glVertex3f(-.1*r,.1*r,.1*r);
    	glVertex3f(-.1*r,.3*r,.1*r);                
    	glVertex3f(-.1*r,.3*r,-.1*r);
    	glVertex3f(-.1*r,.1*r,-.1*r);
	glEnd();
	

	glBegin(GL_QUADS);
	glColor3f(0.30,0.96,0.42);
	glVertex3f(-.2*r,.3*r,.1*r);
    	glVertex3f(-.1*r,.3*r,.1*r);                
    	glVertex3f(-.1*r,.3*r,-.1*r);
    	glVertex3f(-.2*r,.3*r,-.1*r);
	glEnd();
	

    	glBegin(GL_QUADS);                     
	glColor3f(0.30,0.36,0.42);
	glVertex3f(-.1*r,.3*r,.1*r);
    	glVertex3f(.3*r,.3*r,.1*r);                
    	glVertex3f(.3*r,0.1*r,.1*r);
    	glVertex3f(-.1*r,.1*r,.1*r);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.00,0.0,0.0);
	glVertex3f(-.1*r,.3*r,-.1*r);
    	glVertex3f(.3*r,.3*r,-.1*r);                
    	glVertex3f(.3*r,0.1*r,-.1*r);
    	glVertex3f(-.1*r,.1*r,-.1*r);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0,1.0,0.0);
	glVertex3f(.3*r,.3*r,.1*r);
    	glVertex3f(.3*r,.3*r,-.1*r);                
    	glVertex3f(.3*r,.1*r,-.1*r); 
    	glVertex3f(.3*r,.1*r,.1*r);
	glEnd();

    	glBegin(GL_QUADS);
	glColor3f(0.30,0.36,0.12);
	glVertex3f(-.1*r,.3*r,.1*r);
    	glVertex3f(-.1*r,.3*r,-.1*r);                
    	glVertex3f(.3*r,.3*r,-.1*r); 
    	glVertex3f(.3*r,.3*r,.1*r);
	glEnd();                         

	glBegin(GL_QUADS);             
	glColor3f(0.30,0.36,0.12);
	glVertex3f(-.08*r,.4*r,.07*r);
    glVertex3f(-.08*r,.4*r,-.07*r);                
    glVertex3f(-.08*r,.3*r,-.07*r); 
    glVertex3f(-.08*r,.3*r,.07*r);
	glEnd();

	glBegin(GL_QUADS);             
	glColor3f(0.30,0.36,0.12);
	glVertex3f(.27*r,.4*r,.07*r);
    glVertex3f(.27*r,.4*r,-.07*r);                
                   
    glVertex3f(.27*r,.3*r,-.07*r); 
    glVertex3f(.27*r,.3*r,.07*r);
	glEnd();


    glBegin(GL_QUADS);
	glColor3f(1.00,0.56,0.12);
	glVertex3f(-.08*r,.4*r,.07*r);
    glVertex3f(.27*r,.4*r,.07*r);                
    glVertex3f(.27*r,.3*r,.07*r); 
    glVertex3f(-.08*r,.3*r,.07*r);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.30,0.36,0.12);
	glVertex3f(-.08*r,.4*r,-.07*r);
    glVertex3f(.27*r,.4*r,-.07*r);                
    glVertex3f(.27*r,.3*r,-.07*r); 
    glVertex3f(-.08*r,.3*r,-.07*r);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(5.0,0.0,0.0);
	glVertex3f(-0.08*r,.4*r,.07*r);
	glVertex3f(-0.08*r,.4*r,-.07*r);
    glVertex3f(.27*r,.4*r,-.07*r);                
    glVertex3f(.27*r,.4*r,.07*r); 
   	glEnd();

	                                
}




//train 2D
//class untuk terain 2D
class Terrain {
private:
	int w; //Width
	int l; //Length
	float** hs; //Heights
	Vec3f** normals;
	bool computedNormals; //Whether normals is up-to-date
public:
	Terrain(int w2, int l2) {
		w = w2;
		l = l2;

		hs = new float*[l];
		for (int i = 0; i < l; i++) {
			hs[i] = new float[w];
		}

		normals = new Vec3f*[l];
		for (int i = 0; i < l; i++) {
			normals[i] = new Vec3f[w];
		}

		computedNormals = false;
	}

	~Terrain() {
		for (int i = 0; i < l; i++) {
			delete[] hs[i];
		}
		delete[] hs;

		for (int i = 0; i < l; i++) {
			delete[] normals[i];
		}
		delete[] normals;
	}

	int width() {
		return w;
	}

	int length() {
		return l;
	}

	//Sets the height at (x, z) to y
	void setHeight(int x, int z, float y) {
		hs[z][x] = y;
		computedNormals = false;
	}

	//Returns the height at (x, z)
	float getHeight(int x, int z) {
		return hs[z][x];
	}

	//Computes the normals, if they haven't been computed yet
	void computeNormals() {
		if (computedNormals) {
			return;
		}

		//Compute the rough version of the normals
		Vec3f** normals2 = new Vec3f*[l];
		for (int i = 0; i < l; i++) {
			normals2[i] = new Vec3f[w];
		}

		for (int z = 0; z < l; z++) {
			for (int x = 0; x < w; x++) {
				Vec3f sum(0.0f, 0.0f, 0.0f);

				Vec3f out;
				if (z > 0) {
					out = Vec3f(0.0f, hs[z - 1][x] - hs[z][x], -1.0f);
				}
				Vec3f in;
				if (z < l - 1) {
					in = Vec3f(0.0f, hs[z + 1][x] - hs[z][x], 1.0f);
				}
				Vec3f left;
				if (x > 0) {
					left = Vec3f(-1.0f, hs[z][x - 1] - hs[z][x], 0.0f);
				}
				Vec3f right;
				if (x < w - 1) {
					right = Vec3f(1.0f, hs[z][x + 1] - hs[z][x], 0.0f);
				}

				if (x > 0 && z > 0) {
					sum += out.cross(left).normalize();
				}
				if (x > 0 && z < l - 1) {
					sum += left.cross(in).normalize();
				}
				if (x < w - 1 && z < l - 1) {
					sum += in.cross(right).normalize();
				}
				if (x < w - 1 && z > 0) {
					sum += right.cross(out).normalize();
				}

				normals2[z][x] = sum;
			}
		}

		//Smooth out the normals
		const float FALLOUT_RATIO = 0.5f;
		for (int z = 0; z < l; z++) {
			for (int x = 0; x < w; x++) {
				Vec3f sum = normals2[z][x];

				if (x > 0) {
					sum += normals2[z][x - 1] * FALLOUT_RATIO;
				}
				if (x < w - 1) {
					sum += normals2[z][x + 1] * FALLOUT_RATIO;
				}
				if (z > 0) {
					sum += normals2[z - 1][x] * FALLOUT_RATIO;
				}
				if (z < l - 1) {
					sum += normals2[z + 1][x] * FALLOUT_RATIO;
				}

				if (sum.magnitude() == 0) {
					sum = Vec3f(0.0f, 1.0f, 0.0f);
				}
				normals[z][x] = sum;
			}
		}

		for (int i = 0; i < l; i++) {
			delete[] normals2[i];
		}
		delete[] normals2;

		computedNormals = true;
	}

	//Returns the normal at (x, z)
	Vec3f getNormal(int x, int z) {
		if (!computedNormals) {
			computeNormals();
		}
		return normals[z][x];
	}
};
//end class

float myrand(float R)
{
   return (2 * R * rand()) / RAND_MAX - R;
}

//---------------------------------------
// Recursive function to create trees
//---------------------------------------
void tree(float x1, float y1, float length1, float angle1, int depth)
{
   if (depth > 0)
   {
      // Draw line segment
      float x2 = x1 + length1 * cos(angle1);
      float y2 = y1 + length1 * sin(angle1);
      glVertex2f(x1, y1);
      glVertex2f(x2, y2);

      // Make two recursive calls
      float length2 = length1 * (SCALE + myrand(RAND));
      float angle2 = angle1 + ANGLE + myrand(RAND);
      tree(x2, y2, length2, angle2, depth-1);
      length2 = length1 * (SCALE + myrand(RAND));
      angle2 = angle1 - ANGLE + myrand(RAND);
      tree(x2, y2, length2, angle2, depth-1);
   }
}

void pohon(void){
//batang
GLUquadricObj *pObj;
pObj =gluNewQuadric();
gluQuadricNormals(pObj, GLU_SMOOTH);    

glPushMatrix();
glColor3ub(104,70,14);
//glEnable(GL_TEXTURE_2D);
//glEnable(GL_TEXTURE_2D);
//glBindTexture(GL_TEXTURE_2D, texture[0]);
glRotatef(270,1,0,0);
gluCylinder(pObj, 4, 0.7, 30, 25, 25);

glPopMatrix();
}

//ranting  
void ranting(void){
GLUquadricObj *pObj;
pObj =gluNewQuadric();
gluQuadricNormals(pObj, GLU_SMOOTH); 
glPushMatrix();
glColor3ub(104,70,14);
glTranslatef(0,27,0);
glRotatef(330,1,0,0);
gluCylinder(pObj, 0.6, 0.1, 15, 25, 25);
glPopMatrix();

//daun
glPushMatrix();
glColor3ub(18,118,13);
glScaled(5, 5, 5);
glTranslatef(0,7,3);
glutSolidIcosahedron();
glPopMatrix();
}
void box(void){
     //glBindTexture(GL_TEXTURE_2D, texture[0]);
     
     glBegin(GL_QUADS);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
     
     
}
void awan(void){
glPushMatrix(); 
glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
glTranslatef(75, -10, 120);
glScalef(0.5, 0.5, 0.5);  
glColor3ub(153, 223, 255);
glutSolidSphere(10, 50, 50);
glPopMatrix(); 
   
glPushMatrix(); 
glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
glTranslatef(60, -11, 120);
glScalef(0.3, 0.3, 0.3);  
glColor3ub(153, 223, 255);
glutSolidSphere(10, 50, 50);
glPopMatrix(); 

glPushMatrix(); 
glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
glTranslatef(50, -11, 120);
glScalef(0.3, 0.3, 0.3);  
glColor3ub(153, 223, 255);
glutSolidSphere(10, 50, 50);
glPopMatrix(); 

glPushMatrix(); 
glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
glTranslatef(40, -11, 120);
glScalef(0.3, 0.3, 0.3);  
glColor3ub(153, 223, 255);
glutSolidSphere(10, 50, 50);
glPopMatrix(); 

glPushMatrix(); 
glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
glTranslatef(30, -11, 120);
glScalef(0.3, 0.3, 0.3);  
glColor3ub(153, 223, 255);
glutSolidSphere(10, 50, 50);
glPopMatrix();  

glPushMatrix(); 
glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
glTranslatef(20, -11, 120);
glScalef(0.3, 0.3, 0.3);  
glColor3ub(153, 223, 255);
glutSolidSphere(10, 50, 50);
glPopMatrix();      

}     

void pohon_bind(){
     
     		   //pohon1
glPushMatrix();

glTranslatef(0.1,15,0);    
glScalef(0.5, 0.5, 0.5);
glRotatef(90,0,1,0);
pohon();
glPopMatrix();

//ranting1
glPushMatrix();
ranting();
glPopMatrix();

//ranting2
glPushMatrix();
glScalef(1.5, 1.5, 1.5);
glTranslatef(0,25,25);   
glRotatef(250,1,0,0);
ranting();
glPopMatrix();

//ranting3
glPushMatrix();
glScalef(1.8, 1.8, 1.8);
glTranslatef(0,-6,21.5);   
glRotatef(-55,1,0,0);
ranting();
glPopMatrix();

//-------------------//
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}

//Loads a terrain from a heightmap.  The heights of the terrain range from
//-height / 2 to height / 2.
//load terain di procedure inisialisasi
Terrain* loadTerrain(const char* filename, float height) {
	Image* image = loadBMP(filename);
	Terrain* t = new Terrain(image->width, image->height);
	for (int y = 0; y < image->height; y++) {
		for (int x = 0; x < image->width; x++) {
			unsigned char color = (unsigned char) image->pixels[3 * (y
					* image->width + x)];
			float h = height * ((color / 255.0f) - 0.5f);
			t->setHeight(x, y, h);
		}
	}

	delete image;
	t->computeNormals();
	return t;
}

float _angle = 60.0f;
//buat tipe data terain
Terrain* _terrain;
Terrain* _terrainTanah;
Terrain* _terrainAir;

const GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
const GLfloat light_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat light_ambient2[] = { 0.3f, 0.3f, 0.3f, 0.0f };
const GLfloat light_diffuse2[] = { 0.3f, 0.3f, 0.3f, 0.0f };

const GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void cleanup() {
	delete _terrain;
	//delete _terrainTanah;
}


//------------
//mengambil gambar BMP
int ImageLoad(char *filename, Images *image) {
	FILE *file;
	unsigned long size; // ukuran image dalam bytes
	unsigned long i; // standard counter.
	unsigned short int plane; // number of planes in image

	unsigned short int bpp; // jumlah bits per pixel
	char temp; // temporary color storage for var warna sementara untuk memastikan filenya ada


	if ((file = fopen(filename, "rb")) == NULL) {
		printf("File Not Found : %s\n", filename);
		return 0;
	}
	// mencari file header bmp
	fseek(file, 18, SEEK_CUR);
	// read the width
	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {//lebar beda
		printf("Error reading width from %s.\n", filename);
		return 0;
	}
	//printf("Width of %s: %lu\n", filename, image->sizeX);
	// membaca nilai height
	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {//tingginya beda
		printf("Error reading height from %s.\n", filename);
		return 0;
	}
	//printf("Height of %s: %lu\n", filename, image->sizeY);
	//menghitung ukuran image(asumsi 24 bits or 3 bytes per pixel).

	size = image->sizeX * image->sizeY * 3;
	// read the planes
	if ((fread(&plane, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);//bukan file bmp
		return 0;
	}
	if (plane != 1) {
		printf("Planes from %s is not 1: %u\n", filename, plane);//
		return 0;
	}
	// read the bitsperpixel
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);

		return 0;
	}
	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);//bukan 24 pixel
		return 0;
	}
	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);
	// read the data.
	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");//gagal ambil memory
		return 0;
	}
	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}
	for (i = 0; i < size; i += 3) { // membalikan semuan nilai warna (gbr - > rgb)
		temp = image->data[i];
		image->data[i] = image->data[i + 2];
		image->data[i + 2] = temp;
	}
	// we're done.
	return 1;
}

//mengambil tekstur
Images * loadTexture() {
	Images *image1;
	// alokasi memmory untuk tekstur
	image1 = (Images *) malloc(sizeof(Images));
	if (image1 == NULL) {
		printf("Error allocating space for image");//memory tidak cukup
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("images.bmp", image1)) {
		exit(1);
	}
	return image1;
}
//--------------

//mengambil tekstur
Images * loadTextureSky1() {
	Images *imageSky1;
	// alokasi memmory untuk tekstur
	imageSky1 = (Images *) malloc(sizeof(Images));
	if (imageSky1 == NULL) {
		printf("Error allocating space for image");//memory tidak cukup
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("front.bmp", imageSky1)) {
		exit(1);
	}
	return imageSky1;
}
//--------------

//mengambil tekstur
Images * loadTextureSky2() {
	Images *imageSky2;
	// alokasi memmory untuk tekstur
	imageSky2 = (Images *) malloc(sizeof(Images));
	if (imageSky2 == NULL) {
		printf("Error allocating space for image");//memory tidak cukup
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("back.bmp", imageSky2)) {
		exit(1);
	}
	return imageSky2;
}
//--------------

//mengambil tekstur
Images * loadTextureSky3() {
	Images *imageSky3;
	// alokasi memmory untuk tekstur
	imageSky3 = (Images *) malloc(sizeof(Images));
	if (imageSky3 == NULL) {
		printf("Error allocating space for image");//memory tidak cukup
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("left.bmp", imageSky3)) {
		exit(1);
	}
	return imageSky3;
}
//--------------

//mengambil tekstur
Images * loadTextureSky4() {
	Images *imageSky4;
	// alokasi memmory untuk tekstur
	imageSky4 = (Images *) malloc(sizeof(Images));
	if (imageSky4 == NULL) {
		printf("Error allocating space for image");//memory tidak cukup
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("left.bmp", imageSky4)) {
		exit(1);
	}
	return imageSky4;
}
//--------------

//mengambil tekstur
Images * loadTextureSky5() {
	Images *imageSky5;
	// alokasi memmory untuk tekstur
	imageSky5 = (Images *) malloc(sizeof(Images));
	if (imageSky5 == NULL) {
		printf("Error allocating space for image");//memory tidak cukup
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("up.bmp", imageSky5)) {
		exit(1);
	}
	return imageSky5;
}
//--------------

//mengambil tekstur
Images * loadTextureSky6() {
	Images *imageSky6;
	// alokasi memmory untuk tekstur
	imageSky6 = (Images *) malloc(sizeof(Images));
	if (imageSky6 == NULL) {
		printf("Error allocating space for image");//memory tidak cukup
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("down.bmp", imageSky6)) {
		exit(1);
	}
	return imageSky6;
}
//--------------

//mengambil tekstur
Images * loadTexture2() {
	Images *image2;
	// alokasi memmory untuk tekstur
	image2 = (Images *) malloc(sizeof(Images));
	if (image2== NULL) {
		printf("Error allocating space for image");//memory tidak cukup
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("biru.bmp", image2)) {
		exit(1);
	}
	return image2;
}
//--------------

void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;


	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[0]);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[1]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[2]);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[3]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[4]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[5]);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();

}

//untuk di display
void drawSceneTanah(Terrain *terrain, GLfloat r, GLfloat g, GLfloat b) {
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	 glTranslatef(0.0f, 0.0f, -10.0f);
	 glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	 glRotatef(-_angle, 0.0f, 1.0f, 0.0f);

	 GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	 glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	 GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	 GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
	 glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	 glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	 */
	 
	
	float scale = 500.0f / max(terrain->width() - 1, terrain->length() - 1);
	glScalef(scale, scale, scale);
	glTranslatef(-(float) (terrain->width() - 1) / 2, 0.0f,
			-(float) (terrain->length() - 1) / 2);

	glColor3f(r, g, b);
	 //glBindTexture(GL_TEXTURE_2D, texture[0]);
	for (int z = 0; z < terrain->length() - 1; z++) {
		//Makes OpenGL draw a triangle at every three consecutive vertices
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < terrain->width(); x++) {
            
			Vec3f normal = terrain->getNormal(x, z);
			glNormal3f(normal[0], normal[1], normal[2]);
			glVertex3f(x, terrain->getHeight(x, z), z);
			normal = terrain->getNormal(x, z + 1);
			glNormal3f(normal[0], normal[1], normal[2]);
			glVertex3f(x, terrain->getHeight(x, z + 1), z + 1);
		}
		glEnd();
	}

}

//unsigned int LoadTextureFromBmpFile(char *filename);
//----
/*Image * loadTexture() {
	Image *image1;
	// alokasi memmory untuk tekstur
	image1 = (Image *) malloc(sizeof(Image));
	if (image1 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("wood.bmp", image1)) {
		exit(1);
	}
	return image1;
}*/
//----


void display(void) {
	glClearStencil(0); //clear the stencil buffer
	glClearDepth(1.0f);
	glClearColor(0.0, 0.6, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //clear the buffers
	glLoadIdentity();
//	gluLookAt(viewx, viewy, viewz, 0.0, 0.0, 5.0, 0.0, 1.0, 0.0);
	gluLookAt(viewx, viewy, viewz, 500.0, -50.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt( 0,1,4, 0,0,0, 0,1,0);

	glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	drawSceneTanah(_terrain, 0.5f, 0.5f, 0.5f);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
    //glBindTexture(GL_TEXTURE_2D, SkyboxTexture[5]);
	glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glBindTexture(GL_TEXTURE_3D, texture[0]);
	//drawSceneTanah(_terrainTanah, 0.7f, 0.2f, 0.1f);
	//glPopMatrix();

	//glPushMatrix();

	//glBindTexture(GL_TEXTURE_3D, texture[0]);
	//glEnable(GL_TEXTURE_2D);
	drawSceneTanah(_terrainAir, 0.0f, 0.2f, 0.5f);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//glPushMatrix();

//		   glClear(GL_COLOR_BUFFER_BIT);
		   //glColor3f(0.0, 1.0, 0.0);
		   //glBegin(GL_LINES);
			//	tree(0, -80, 20, 1.5, 10);
		   //glEnd();
		   //glPopMatrix();
		   


//-------------------//
		   //pohon1
glPushMatrix();
glTranslatef(-70,-8,-100);    
glScalef(0.5, 0.5, 0.5);
//glRotatef(90,0,1,0);
pohon_bind();
glPopMatrix();

		   //pohon2
glPushMatrix();
glTranslatef(-40,-8,-100);    
glScalef(0.5, 0.5, 0.5);
//glRotatef(90,0,1,0);
pohon_bind();
glPopMatrix();




//batas
glPushMatrix();
glTranslatef(0, 0, 0);
awan();
glPopMatrix();

//batas2
glPushMatrix();
glTranslatef(0, 0, -80);
awan();
glPopMatrix();

//batas2
glPushMatrix();
glTranslatef(0, 0, -160);
awan();
glPopMatrix();

//batas2
glPushMatrix();
glTranslatef(0, 0, -240);
awan();
glPopMatrix();





//box1
glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]);

glScalef(7, 5, 5);
glTranslatef(-5,1,10);   
glRotatef(0,1,0,0);
box();
glDisable(GL_TEXTURE_2D);
glPopMatrix();

//box2
glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]);

glScalef(7, 5, 5);
glTranslatef(-5,1,15);   
glRotatef(0,1,0,0);
box();
glDisable(GL_TEXTURE_2D);
glPopMatrix();

//box2
glPushMatrix();
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, texture[0]);

glScalef(7, 5, 5);
glTranslatef(-5,1,20);   
glRotatef(0,1,0,0);
box();
glDisable(GL_TEXTURE_2D);
glPopMatrix();

//obj.draw("data//1.obj");


//obj.Draw();



//skybox
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, SkyboxTexture[0]);
glBindTexture(GL_TEXTURE_2D, SkyboxTexture[1]);
glBindTexture(GL_TEXTURE_2D, SkyboxTexture[2]);
glBindTexture(GL_TEXTURE_2D, SkyboxTexture[3]);
glBindTexture(GL_TEXTURE_2D, SkyboxTexture[4]);
glBindTexture(GL_TEXTURE_2D, SkyboxTexture[5]);
glTranslatef(0,0,25); 
Draw_Skybox(0,10,0,300,500,400);	
glDisable(GL_TEXTURE_2D);


	glutSwapBuffers();
	glFlush();
	rot++;
	angle++;

}

void init(void) {
//    glEnable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE);

	_terrain = loadTerrain("heightmap.bmp", 20);
	//_terrainTanah = loadTerrain("heightmapTanah.bmp", 20);
	_terrainAir = loadTerrain("heightmapAir.bmp", 20);
	//freopen( "CON", "wt", stdout );
    //freopen( "CON", "wt", stderr );
	//obj.load("data//1.obj");
	
//	obj.Load("jjj.obj");

	//binding texture
	Images *image1 = loadTexture();
	Images *image2 = loadTexture2();
	
	Images *imageSky1 = loadTextureSky1();
	Images *imageSky2 = loadTextureSky2();
	Images *imageSky3 = loadTextureSky3();
	Images *imageSky4 = loadTextureSky4();
	Images *imageSky5 = loadTextureSky5();
	Images *imageSky6 = loadTextureSky6();
	
	
	if (image1 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
	//makeCheckImage();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate texture/ membuat texture
	glGenTextures(2, texture);
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB,GL_UNSIGNED_BYTE, image1->data);
	
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB,GL_UNSIGNED_BYTE, image2->data);
	
	glGenTextures(6, SkyboxTexture);
	//front
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[0]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageSky1->sizeX, imageSky1->sizeY, 0, GL_RGB,GL_UNSIGNED_BYTE, imageSky1->data);
	//back
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[1]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageSky2->sizeX, imageSky2->sizeY, 0, GL_RGB,GL_UNSIGNED_BYTE, imageSky2->data);
	//left
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[2]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageSky3->sizeX, imageSky3->sizeY, 0, GL_RGB,GL_UNSIGNED_BYTE, imageSky3->data);
	//right
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[3]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageSky4->sizeX, imageSky4->sizeY, 0, GL_RGB,GL_UNSIGNED_BYTE, imageSky4->data);
	//up
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[4]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageSky5->sizeX, imageSky5->sizeY, 0, GL_RGB,GL_UNSIGNED_BYTE, imageSky5->data);
	//down
	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[5]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageSky6->sizeX, imageSky6->sizeY, 0, GL_RGB,GL_UNSIGNED_BYTE, imageSky6->data);
}

static void kibor(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_HOME:
		viewy++;
		break;
	case GLUT_KEY_END:
		viewy--;
		break;
	case GLUT_KEY_UP:
		viewz--;
		break;
	case GLUT_KEY_DOWN:
		viewz++;
		break;

	case GLUT_KEY_RIGHT:
		viewx++;
		break;
	case GLUT_KEY_LEFT:
		viewx--;
		break;

	case GLUT_KEY_F1: {
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	}
		;
		break;
	case GLUT_KEY_F2: {
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient2);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse2);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	}
		;
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'd') {

		spin = spin - 1;
		if (spin > 360.0)
			spin = spin - 360.0;
	}
	if (key == 'a') {
		spin = spin + 1;
		if (spin > 360.0)
			spin = spin - 360.0;
	}
	if (key == 'q') {
		viewz++;
	}
	if (key == 'e') {
		viewz--;
	}
	if (key == 's') {
		viewy--;
	}
	if (key == 'w') {
		viewy++;
	}
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}




int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH); //add a stencil buffer to the window
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Pelabuhan");
	init();
	

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(kibor);

	glutKeyboardFunc(keyboard);

	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
    
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glutMainLoop();
	return 0;
}
