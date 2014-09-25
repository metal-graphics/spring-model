#include <iostream>
#include <utility>

using namespace std;

typedef pair<int, int> pii;

class DrawLine
{
  public:
    void plotPixel( pii );
    DrawLine( pii , pii );

  private:
    pii one, two;
    void calculateSlope( void );
    void bresenham1( void );
    void bresenham2( void );
    void bresenham3( void );
    void bresenham4( void );
};
