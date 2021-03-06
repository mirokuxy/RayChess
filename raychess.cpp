/***********************************************************
 * CMPT 361, Summer 2012
 *
 *  raycast.cpp
 *      
 *  Render a simple scene using ray tracing
 * 
 *  NAME: Yu Xiao
 *  SFU ID: 301267080
 *
 *  Template code for drawing a scene using raycasting.
 *  Some portions of the code was originally written by 
 *  M. vandePanne - and then modified by R. Zhang & H. Li
***********************************************************/

//#include "include/Angel.h"

#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
//#  include <GL/glut.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__


// GLM lib for matrix calculation
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/glm/gtx/rotate_vector.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "shader.h"
#include "trace.h"
#include "global.h"
#include "object.h"
#include "image_util.h"
#include "scene.h"

//
// Global variables
//
// Here we avoid dynamic memory allocation as a convenience. You can
// change the resolution of your rendered image by changing the values
// of WIN_X_SIZE and WIN_Y_SIZE in "global.h", along with other
// global variables
//

int win_width = WIN_WIDTH;
int win_height = WIN_HEIGHT;

glm::vec3 frame[WIN_HEIGHT][WIN_WIDTH];   
// array for the final image 
// This gets displayed in glut window via texture mapping, 
// you can also save a copy as bitmap by pressing 's'

float image_width = IMAGE_WIDTH;
float image_height = (float(WIN_HEIGHT) / float(WIN_WIDTH)) * IMAGE_WIDTH;

// some colors
glm::vec3 background_clr; // background color
glm::vec3 null_clr = glm::vec3(0.0, 0.0, 0.0);   // NULL color

//
// these view parameters should be fixed
//
glm::vec3 eye_pos = glm::vec3(0.0, 0.0, 0.0);  // eye position
float image_plane = -1.5;           // image plane position

// list of spheres in the scene
Object *scene = NULL;

// light 1 position and color
glm::vec3 light1;
glm::vec3 light1_ambient;
glm::vec3 light1_diffuse;
glm::vec3 light1_specular;

// global ambient term
glm::vec3 global_ambient;

// light decay parameters
float decay_a;
float decay_b;
float decay_c;

// maximum level of recursions; you can use to control whether reflection
// is implemented and for how many levels
int step_max = 1;

// You can put your flags here
int shadow_on = 0; // a flag to indicate whether you want to have shadows
int reflect_on = 0; // a flag to indicate whether to have reflection
int chessboard_on = 0; // whether to set up chessboard
int refract_on = 0;	// whether have refraction effect
int difref_on = 0; // whether to have diffuse reflection
int antiAlias_on = 0; 	// whether to have anti alias
int triangle_on = 0;	// whether show triangle mesh

int objectCount = 0;	// number of objects

// OpenGL
const int NumPoints = 6;

//----------------------------------------------------------------------------
// define __NO_DISPLAY__ to turn off opengl 
#ifndef __NO_DISPLAY__
void init()
{
	// Vertices of a square
	float ext = 1.0;
	float points[NumPoints * 4] = {
		 -ext, -ext,  0, 1.0 , //v1
		  ext, -ext,  0, 1.0 , //v2
		 -ext,  ext,  0, 1.0 , //v3	
		 -ext,  ext,  0, 1.0 , //v3	
		  ext, -ext,  0, 1.0 , //v2
		  ext,  ext,  0, 1.0  //v4
	};

	// Texture coordinates
	float tex_coords[NumPoints * 2] = {
		0.0, 0.0,
		1.0, 0.0,
		0.0, 1.0,
		0.0, 1.0,
		1.0, 0.0,
		1.0, 1.0
	};

	// Initialize texture Objects
	float newFrame[WIN_HEIGHT][WIN_WIDTH][3];

	for(int i=0;i<WIN_HEIGHT;i++)
		for(int j=0;j<WIN_WIDTH;j++){
			newFrame[i][j][0] = frame[i][j].x;
			newFrame[i][j][1] = frame[i][j].y;
			newFrame[i][j][2] = frame[i][j].z;
		}


	GLuint texture;
	glGenTextures( 1, &texture );

	glBindTexture( GL_TEXTURE_2D, texture );


	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, WIN_WIDTH, WIN_HEIGHT, 0,
		GL_RGB, GL_FLOAT, newFrame );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glActiveTexture( GL_TEXTURE0 );

	// Create and initialize a buffer Object
	GLuint buffer;
	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(tex_coords), NULL, GL_STATIC_DRAW );
	GLintptr offset = 0;
	glBufferSubData( GL_ARRAY_BUFFER, offset, sizeof(points), points );
	offset += sizeof(points);
	glBufferSubData( GL_ARRAY_BUFFER, offset, sizeof(tex_coords), tex_coords );

	// Load shaders and use the resulting shader program
	Shader myShader( "vshader.glsl", "fshader.glsl" );
	myShader.Use();

	// set up vertex arrays
	offset = 0;
	GLuint vPosition = glGetAttribLocation( myShader.Program, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		(GLvoid*) (offset) );

	offset += sizeof(points);
	GLuint vTexCoord = glGetAttribLocation( myShader.Program, "vTexCoord" ); 
	glEnableVertexAttribArray( vTexCoord );
	glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
		(GLvoid*) (offset) );

	glUniform1i( glGetUniformLocation( myShader.Program, "texture"), 0 );

	glClearColor( 1.0, 1.0, 1.0, 1.0 );
}
#endif

/*********************************************************
 * This is the OpenGL display function. It is called by
 * the event handler to draw the scene after you have
 * rendered the image using ray tracing. Remember that
 * the pointer to the image memory is stored in 'frame'.
 *
 * There is no need to change this.
 **********************************************************/

void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	
	#ifndef __NO_DISPLAY__
	glDrawArrays( GL_TRIANGLES, 0, NumPoints );
	#endif

	glutPostRedisplay();

	glutSwapBuffers();
}

/*********************************************************
 * This function handles keypresses
 *
 *   s - save image
 *   q - quit
 *
 * DO NOT CHANGE
 *********************************************************/

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':case 'Q':
		//free(scene);
		freeObjects();
		exit(0);
		break;
	case 's':case 'S':
		save_image();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------

int main( int argc, char **argv )
{
	// Parse the arguments
	if (argc < 2) {
		printf("Missing arguments ... use:\n");
		printf("./raycast step_max <options>\n");
		return -1;
	}
	
	/*
	if (strcmp(argv[1], "-u") == 0) {  // user defined scene
		set_up_user_scene();
	} else { // default scene
		set_up_default_scene();
	}
	*/

	step_max = atoi(argv[1]); // maximum level of recursions

	// Optional arguments
	for(int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "+s") == 0)	shadow_on = 1;
		if (strcmp(argv[i], "+l") == 0) reflect_on = 1;
		//if (strcmp(argv[i], "+c") == 0) chessboard_on = 1;
		if (strcmp(argv[i], "+r") == 0) refract_on = 1;
		if (strcmp(argv[i], "+f") == 0) difref_on = 1;
		if (strcmp(argv[i], "+p") == 0) antiAlias_on = 1;
		if (strcmp(argv[i], "+t") == 0) triangle_on = 1;
	}

	set_up_global_variable();

	if(chessboard_on = 1)
		set_up_chessboard();

	if(triangle_on)
		set_up_triangles();


	//printf("object Count : %d\n",objectCount);

	set_up_chessPiece();



	//printObjects();

	// ray trace the scene now
	// we have used so many global variables and this function is
	// happy to carry no parameters	
	printf("Rendering scene using my fantastic ray tracer ...\n");
	ray_trace();
	printf("After ray trace\n");

	// we want to make sure that intensity values are normalized
	histogram_normalization();

	// Show the result in glut via texture mapping
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize( WIN_WIDTH, WIN_HEIGHT );
	glutCreateWindow( "Ray tracing" );
	glewInit();

	#ifndef __NO_DISPLAY__
	init();
	#endif
	printf("After init\n");

	glutDisplayFunc( display );
	glutKeyboardFunc( keyboard );
	glutMainLoop();

	return 0;
}
