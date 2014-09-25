#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <time.h>
#include "DrawLine.h"
#include <utility>

using namespace std;

typedef pair<int, int> pii;

int clicks = 0;
pii a, b;

void mouseFunction( int button, int state, int x, int y )
{
  if( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
  {
    if( clicks==0 )
    {
      a = make_pair( x, 850-y );
      clicks = 1;
    }
    else if( clicks==1 )
    {
      b = make_pair( x, 850-y );
      clicks=0;
      DrawLine ld = DrawLine( a, b );
    }
  }
}


void myInit()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glColor3f (1.0, 1.0, 1.0);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  gluOrtho2D(0, 850.0, 0.0, 850.0);

  glMatrixMode(GL_MODELVIEW);

  glutMouseFunc( mouseFunction );

  glFlush();
}


int main(int argc, char** argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize(850,850);

  glutInitWindowPosition(750, 0);

  glutCreateWindow("midpoint algorithm");

  glutDisplayFunc(myInit);

  glutMainLoop();

  return 0;
}
