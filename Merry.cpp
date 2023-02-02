/*
 * Merry.cpp: A class for drawing a Merry-go-round hierarchical animated model.
 *
 */

#include "Merry.h"
#include "libtarga.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

// Destructor
Merry::~Merry(void)
{
    if (initialized)
    {
        glDeleteLists(display_list[0], 1);
        glDeleteLists(display_list[1], 1);
        gluDeleteQuadric(qobj[0]);
        gluDeleteQuadric(qobj[1]);
    }
}

// Initializer. Returns false if something went wrong, like not being able to
// load the texture.
bool
Merry::Initialize(void)
{
    for (int i = 0; i < 2; i++)
    {
        qobj[i] = gluNewQuadric();
        gluQuadricNormals(qobj[i], GLU_SMOOTH);
    }

    display_list[0] = glGenLists(1);
    glNewList(display_list[0], GL_COMPILE);
    glColor3f(1.000, 0.078, 0.576);
    gluCylinder(qobj[0], 5, 5, 2, 20, 16);
    glTranslatef(0.0, 0.0, 2);
    gluDisk(qobj[1], 2, 5, 20, 20);

    glColor3f(0.686, 0.933, 0.933);
    glTranslatef(0.0, 4.5f, 0);
    gluCylinder(qobj[0], 0.5f, 0.5f, 5, 10, 16);

    glTranslatef(0.0, -9.0f, 0);
    gluCylinder(qobj[0], 0.5f, 0.5f, 5, 10, 16);

    glTranslatef(0.0, 4.5f, 0);
    glTranslatef(4.5, 0.0f, 0);
    gluCylinder(qobj[0], 0.5f, 0.5f, 5, 10, 16);

    glTranslatef(-9.0, 0.0f, 0);
    gluCylinder(qobj[0], 0.5f, 0.5f, 5, 10, 16);

    glColor3f(1.000, 0.0, 0.0);
    glTranslatef(4.5f, 0.0f, 5);
    gluDisk(qobj[0], 0, 5, 20, 20);

    gluCylinder(qobj[0], 5, 5, 2, 20, 16);

    glTranslatef(0.0f, 0.0f, 2.0f);
    gluCylinder(qobj[0], 5, 0, 2, 20, 16);
    glEndList();

    ubyte* image_data;
    int	    image_height, image_width;

    // Load the image for the texture. The texture file has to be in
    // a place where it will be found.
    if (!(image_data = (ubyte*)tga_load("merry_cube.tga", &image_width,
        &image_height, TGA_TRUECOLOR_24)))
    {
        fprintf(stderr, "Ground::Initialize: Couldn't load roller_texture.tga\n");
        return false;
    }
    // This creates a texture object and binds it, so the next few operations
    // apply to this texture.
    glGenTextures(1, &texture_obj);
    glBindTexture(GL_TEXTURE_2D, texture_obj);

    // This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // This sets up the texture with high quality filtering. First it builds
    // mipmaps from the image data, then it sets the filtering parameters
    // and the wrapping parameters. We want the grass to be repeated over the
    // ground.
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image_width, image_height,
        GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_NEAREST_MIPMAP_LINEAR);

    // This says what to do with the texture. Modulate will multiply the
    // texture by the underlying color.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    display_list[1] = glGenLists(1);
    glNewList(display_list[1], GL_COMPILE);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_obj);
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glTexCoord2f(0.0, 0.0); // new
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0, 1.0); // new
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0, 1.0); // new
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0, 0.0); // new
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    glTexCoord2f(0.0, 0.0); // new
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0, 1.0); // new
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0, 1.0); // new
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0, 0.0); // new
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Front face  (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glTexCoord2f(0.0, 0.0); // new
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0, 1.0); // new
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0, 1.0); // new
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0, 0.0); // new
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Back face (z = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glTexCoord2f(0.0, 0.0); // new
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0, 1.0); // new
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0, 1.0); // new
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0, 0.0); // new
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Left face (x = -1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glTexCoord2f(0.0, 0.0); // new
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0, 1.0); // new
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0, 1.0); // new
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0, 0.0); // new
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    glTexCoord2f(0.0, 0.0); // new
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0, 1.0); // new
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0, 1.0); // new
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0, 0.0); // new
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube

    glEndList();

    display_list[2] = glGenLists(1);
    glNewList(display_list[2], GL_COMPILE);
    glColor3f(0, 1, 0);
    gluSphere(qobj[0], 1, 100, 20);
    glEndList();

    // We only do all this stuff once, when the GL context is first set up.
    initialized = true;

    return true;
}


// Draw just calls the display list we set up earlier.
void
Merry::Draw(void)
{
    glDisable(GL_CULL_FACE);
    glPushMatrix();
    // Translate the merry-go-round to the point
    glTranslatef(posn[0], posn[1], posn[2]);
    // Rotate the merry-go-round
    glRotatef(tpAngle * 30, 0, 0, 1);
    glCallList(display_list[0]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 4.5f);
    glRotatef(tpAngle * 30, 0, 0, 1);
    glCallList(display_list[1]);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20.0f, 20.0f, 0.0f);
    glCallList(display_list[2]);
    glPopMatrix();
    glEnable(GL_CULL_FACE);
}

void
Merry::Update(float angle)
{
    tpAngle += angle * 2.0f;
}