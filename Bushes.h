/*
 Tree.h: Header file for class that creates trees
 */


#ifndef _BUSHES_H_
#define _BUSHES_H_

#include <FL/gl.h>
#include <gl/GLU.h>

class Bushes {
private:
    GLubyte     display_list;   // The display list that does all the work.
    GLdouble    radius;
    float       posn[3];
    GLUquadric* qobj;
    bool        initialized;    // Whether or not we have been initialised.

public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Bushes(void) { 
        display_list = 0; 
        initialized = false; 
        radius = 3.0; 
        posn[0] = posn[1] = posn[2] = 0.0f; 
    };
    Bushes(GLdouble my_radius, float x, float y, float z) {
        display_list = 0; 
        initialized = false;
        radius = my_radius;
        posn[0] = x;
        posn[1] = y;
        posn[2] = z;
    };

    // Destructor. Frees the display lists and texture object.
    ~Bushes(void);

    // Initializer. Creates the display list.
    bool    Initialize(void);

    // Does the drawing.
    void    Draw(void);
};


#endif