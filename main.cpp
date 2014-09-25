#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <time.h>
#include "DrawLine.h"
#include "DrawCircle.h"
#include <utility>
#include <cmath>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

int clicks = 0;
pii a, b;
vector< pair<int, int> > points;

void mouseFunction( int button, int state, int x, int y )
{
  int i=0;
  if( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
  {
    if( points.empty() )
    {
      points.push_back( make_pair(x, 850-y) );
      DrawCircle dc = DrawCircle(make_pair(x, 850-y));
    }
    else
    {
      int sz = points.size();
      for( i=0; i<sz; i++ )
      {
        float rad;
        int dx1 = points[i].first - x;
        int dy1 = points[i].second - (850-y);
        rad = sqrt( dx1*dx1 + dy1*dy1 );

        if( rad<=10 )
        {
          if( clicks==0 )
          {
            a = points[i];
            clicks = 1;
          }
          else if(clicks==1)
          {
            b = points[i];
            clicks = 0;
            DrawLine dl = DrawLine(a, b);
          }
          break;
        }
      }
      if( i==sz )
      {
        points.push_back( make_pair(x, 850-y) );
        DrawCircle dc = DrawCircle(make_pair(x, 850-y));
        clicks = 0;
      }
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
