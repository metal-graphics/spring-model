#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <time.h>
#include <utility>
#include "DrawLine.h"

using namespace std;

typedef pair<int, int> pii;

pii temp;
int x, y, dx, dy;

void DrawLine::plotPixel( pii var )
{
  glBegin(GL_POINTS);

  glPointSize(10.0);

  glVertex2i( var.first, var.second );

  glEnd();

  glFlush();
}


//constructor
DrawLine::DrawLine( pii a, pii b )
{
  one = a;
  two = b;

  calculateSlope();
}


void DrawLine::calculateSlope()
{
  float m = (float)(two.second-one.second)/(two.first-one.first);

  plotPixel(one);
  plotPixel(two);

  if( m>0 && m<=1 )
  {
    bresenham1();
  }
  else if( m<0 && m>=-1 )
  {
    bresenham2();
  }
  else if( m>1 )
  {
    bresenham3();
  }
  else if( m<-1 )
  {
    bresenham4();
  }
}


void DrawLine::bresenham1()
{
  if(one.first>two.first)
  {
    temp = one;
    one = two;
    two = temp;
  }

  x = one.first, y = one.second;
  dx = two.first - one.first;
  dy = two.second - one.second;
  int d = 2*dy - dx;
  int incrE = 2*(dy);
  int incrNE = 2*(dy-dx);

  while( x< two.first )
  {
    if( d<=0 )
    {
      d+=incrE;
    }
    else
    {
      d+=incrNE;

      y++;
    }

    x++;

    temp = make_pair(x,y);
    plotPixel(temp);
  }
}


void DrawLine::bresenham2()
{
  if(one.first>two.first)
  {
    temp = one;
    one = two;
    two = temp;
  }

  x = one.first, y = one.second;
  dx = two.first - one.first;
  dy = two.second - one.second;
  int d = -(2*dy + dx);
  int incrE = 2*(dy);
  int incrSE = 2*(dy+dx);

  while( x < two.first )
  {
    if( d<=0 )
    {
      d-=incrE;
    }
    else
    {
      d-=incrSE;

      y--;
    }

    x++;

    temp = make_pair(x,y);
    plotPixel(temp);
  }
}


void DrawLine::bresenham3()
{
  if(one.second>two.second)
  {
    temp = one;
    one = two;
    two = temp;
  }

  x = one.first, y = one.second;
  dx = two.first - one.first;
  dy = two.second - one.second;
  int d = 2*dx - dy;
  int incrN = 2*(dx);
  int incrNE = 2*(dx-dy);

  while( y<two.second )
  {
    if( d<0 )
    {
      d+=incrN;
    }
    else
    {
      d+=incrNE;

      x++;
    }
    y++;

    temp = make_pair(x,y);
    plotPixel(temp);
  }
}


void DrawLine::bresenham4()
{
  if(one.second>two.second)
  {
    temp = one;
    one = two;
    two = temp;
  }

  x = one.first, y = one.second;
  dx = two.first - one.first;
  dy = two.second - one.second;
  int d = -(2*dy + dx);
  int incrS = 2*(dx);
  int incrSE = 2*(dy+dx);

  while( y<two.second )
  {
    if( d<0 )
    {
      d-=incrS;
    }
    else
    {
      d-=incrSE;

      x--;
    }

    y++;

    temp = make_pair(x,y);
    plotPixel(temp);
  }
}
