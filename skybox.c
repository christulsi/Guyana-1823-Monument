#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include "skybox.h"

GLuint LoadTexture(const char * filename,int wrap, int width, int height)
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    //Open the image file
    file = fopen(filename, "rb");
    //If it doesn't open just return 0
    if(file == NULL)
    {
        return 0;
    }

    //Allocate space for data and read
    data = (unsigned char *)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);

    //Close the file
    fclose(file);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP  );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP  );

    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
    free(data);

    return texture;
		glDeleteTextures( 1, &texture );
}

void load(){

	texture[0] = LoadTexture("txStormydays_back.bmp", 0, 1024, 1024);  //BACK
	texture[1] = LoadTexture("txStormydays_front.bmp", 0, 1024, 1024); //FRONT
	texture[2] = LoadTexture("txStormydays_left.bmp", 0, 1024, 1024);  //LEFT
	texture[3] = LoadTexture("txStormydays_right.bmp", 0, 1024, 1024); //RIGTH
	texture[4] = LoadTexture("txStormydays_down.bmp", 0, 1024, 1024);  //DOWN
	texture[5] = LoadTexture("txStormydays_up.bmp", 0, 1024, 1024);    //UP

}

void SkyFrameWork(){

	int width = 1024;
	int height = 1024;
	int length = 1024;

	//start in this coordinates
	int x = 0;
	int y = 0;
	int z = 0;

	//center the square
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	// Bind the BACK texture of the sky map to the BACK side of the cube
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	//FRONT
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z + length);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z + length);
	glEnd();

	//BOTTOM
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y,  z + length);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,  z + length);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
	glEnd();

	//TOP
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();

	//LEFT
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y,  z + length);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);

	glEnd();

	//RIGHT
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z + length);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopAttrib();
	glDisable( GL_TEXTURE_2D );
  //Reset and transform the matrix.
  glLoadIdentity();

}