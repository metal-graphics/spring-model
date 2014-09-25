#include<iostream>
#include<vector>
#include<map>
#include<utility>
//#include<GL\glu.h>
//#include<GL\glut.h>
#define x first ;
#define y second ;
#define for(i,n) for(i=0;i<n;i++)
#define pb push_back;
#define mp make_pair;
#define INF 10000000;
#define L0 400

int g[100][100];
vector< pair<int,int> > p; // vertices Pair
long double  d[100][100],l[100][100],k[100][100],L;

long double dE_dx[100] , dE_dy[100],d2E_dx2[100],d2E_dy2[100],d2E_dxdy[100];

long double sdE_dx,sdE_dy,sd2E_dx2,sd2E_dy2,sd2E_dxdy;



void compute_d(int n){ // n: number of vertices
  int i,j,k;

 for(k,n)
  for(i,n)
    for(j,n)
      if( d[i][k] + d[k][j] < d[i][j] )
        d[i][j] = d[i][k] + d[k][j];

}

float getL() {

int i,j,max;
max = -1;
for(j=0;j<n;j++)
  for(i=0;i<j;i++)
    if( d[i][j] != INF && d[i][j] > max)
      max = d[i][j];


return L0/max;
}


void compute_l(){
  int i,j;

  for(i,n)
    for(j,n)
      l[i][j] = L * d[i][j];

}


void compute_k(){
  int i,j;

  for(i,n)
    for(j,n)
      k[i][j] = K/(d[i][j]*d[i][j]);

}





int main() {


return 0;
 } //main


/*

-> use Floyd Warshall to calculate dij. O(n^3)
-> use Dynamic programming to store the values.
*/