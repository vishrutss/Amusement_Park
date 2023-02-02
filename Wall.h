/*
 Wall.h : Header file for class that creates walls
 */


#ifndef _WALL_H_
#define _WALL_H_

#include <FL/gl.h>
#include <gl/glu.h>

class Wall {
private:
    GLubyte     display_list;   // The display list that does all the work.
    GLdouble    height;
    GLdouble    width;
    GLuint      texture_obj;    // the object for the wall texture.
    GLdouble    length;
    float       posn[3];
    GLUquadric* qobj;
    bool        initialized;    // Whether or not we have been initialised.

public:
    // Constructor. Can't do initialization here because it is
    // created before the OpenGL context is set up.
    Wall(void) { 
        display_list = 0; 
        initialized = false; 
        height = 20.0; 
        width = 20.0; 
        length = 20.0; 
        posn[0] = posn[1] = posn[2] = 0.0f; 
    };
    Wall(GLdouble my_height, GLdouble my_width, GLdouble my_length, float x, float y, float z) {
        display_list = 0; initialized = false;
        height = my_height;
        length = my_length;
        width = my_width;

        posn[0] = x;
        posn[1] = y;
        posn[2] = z;
    };

    // Destructor. Frees the display lists and texture object.
    ~Wall(void);

    // Initializer. Creates the display list.
    bool    Initialize(void);

    // Does the drawing.
    void    Draw(void);
};


#endif