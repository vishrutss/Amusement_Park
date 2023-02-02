#include "Bushes.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

Bushes::~Bushes(void)
{
    if (initialized)
    {
        glDeleteLists(display_list, 1);
        gluDeleteQuadric(qobj);
    }
}


bool Bushes::Initialize(void)
{
    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);

    display_list = glGenLists(1);
    glNewList(display_list, GL_COMPILE);
    glColor3f(0.133f, 0.545f, 0.133f);
    gluSphere(qobj, radius, 100, 20);
    glEndList();

    // We only do all this stuff once, when the GL context is first set up.
    initialized = true;

    return true;
}


// Draw just calls the display list we set up earlier.
void Bushes::Draw(void)
{
    glPushMatrix();

    // Translate the bush to the point
    glTranslatef(posn[0], posn[1], posn[2]);

    glCallList(display_list);
    glPopMatrix();
}
