#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <time.h>
#include "DrawLine.h"
#include "DrawCircle.h"
#include "sfm.cpp"
#include <utility>
#include <cmath>
#include <vector>

#define INF 10000000;

using namespace std;

typedef pair<int, int> pii;

int clicks = 0, temp2, numPo=0;
pii a, b;

vector< pair<int,int> > points, newpo;
long double d[100][100];

void computeEnergy();
void drawGraph();


void mouseFunction( int button, int state, int x, int y )
{
  int i=0;
  if( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
  {
    if( y<= 100 )
    {
      computeEnergy();
    }
    else if( points.empty() )
    {
      numPo = 1;
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
            temp2 = i;
            clicks = 1;
          }
          else if(clicks==1)
          {
            b = points[i];
            clicks = 0;
            d[i][temp2] = 1;
            d[temp2][i] = 1;
            DrawLine dl = DrawLine(a, b);
          }
          break;
        }
      }
      if( i==sz )
      {
        numPo++;
        points.push_back( make_pair(x, 850-y) );
        DrawCircle dc = DrawCircle(make_pair(x, 850-y));
        clicks = 0;
      }
    }
  }
}


void computeEnergy()
{
  cout<<"numPo= "<<numPo;

  SFM s ;
  for(int i=0; i<numPo; i++)
  {
    for (int j = 0; j < numPo; j++)
    {
      if(d[i][j]!=1)
      {
        d[i][j] = INF;
      }
      s.d[i][j] = d[i][j];
    }
  }

  s.run_spring_force_model( points );

  newpo = s.p;

  drawGraph();
}


void drawGraph()
{
  for( int i=0; i<numPo; i++ )
  {
    DrawCircle dc1 = DrawCircle(newpo[i]);
  }
  for (int i = 0; i < numPo; i++)
  {
    for (int j = 0; j < numPo; j++)
    {
      if(d[i][j]==1)
      {
        DrawLine dl1 = DrawLine( newpo[i], newpo[j] );
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
