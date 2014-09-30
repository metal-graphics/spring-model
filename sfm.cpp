#include <vector>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;


#define rep(i,n) for(i=0;i<n;i++)
#define pb push_back
#define mp make_pair
#define INF 10000000
#define L0 200
#define K 20
#define E 50


class SFM{
public:
int n;
vector< pair<int, int> > p; // vertices Pair
long double  d[100][100], l[100][100], k[100][100], L;
long double dE_dx[100], dE_dy[100], d2E_dx2[100], d2E_dy2[100], d2E_dxdy[100];



void compute_d(){ // n: number of vertices
  int i, j, k;
  // Make sure you initialise d before running this function

  rep(k, n)
    rep(i, n)
      rep(j, n)
        if (d[i][k] + d[k][j] < d[i][j])
          d[i][j] = d[i][k] + d[k][j];

}

long double getL() {

  int i, j, max;
  max = -1;

  for (j = 0; j<n; j++)
    for (i = 0; i<j; i++)
      if (d[i][j] != INF && d[i][j] > max)
        max = d[i][j];

cout<<"d max======"<<max<<endl;
  return L0 / max;
}


void compute_l(){
  int i, j;

  rep(i, n)
    rep(j, n)
    l[i][j] = L * d[i][j];


}


void compute_k(){
  int i, j;

  rep(i, n)
    rep(j, n)
    k[i][j] = K / (d[i][j] * d[i][j]);

}


void compute_derivatives() {
  int i, j;
  long double t1, t2;

  cout << "Initialising all the required parameters" << endl;
  //

  rep(i, n)
    dE_dx[i] = 0;

  rep(i, n)
    rep(j, n){
      if (i == j)
        continue;
      t1 = p[i].first - p[j].first;
      t2 = p[i].second - p[j].second;
      dE_dx[i] += k[i][j] * (t1 - l[i][j] * t1 / sqrt(t1*t1 + t2*t2));
    }


  //

  rep(i, n)
    dE_dy[i] = 0;

  rep(i, n)
    rep(j, n){
      if (i == j)
        continue;
      t2 = p[i].first - p[j].first;
      t1 = p[i].second - p[j].second;
      dE_dy[i] += k[i][j] * (t1 - l[i][j] * t1 / sqrt(t1*t1 + t2*t2));
    }


  //

  rep(i, n)
    d2E_dx2[i] = 0;


  rep(i, n)
    rep(j, n){
      if (i == j)
        continue;
      t1 = p[i].first - p[j].first;
      t2 = p[i].second - p[j].second;
      d2E_dx2[i] += k[i][j] * (1 - l[i][j] * t2*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2)));

    }


  //

  rep(i, n)
    d2E_dy2[i] = 0;


  rep(i, n)
    rep(j, n){
      if (i == j)
        continue;
      t2 = p[i].first - p[j].first;
      t1 = p[i].second - p[j].second;
      d2E_dy2[i] += k[i][j] * (1 - l[i][j] * t2*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2)));
    }


  //

  rep(i, n)
    d2E_dxdy[i] = 0;

  rep(i, n)
    rep(j, n){
      if (i == j)
        continue;
      t1 = p[i].first - p[j].first;
      t2 = p[i].second - p[j].second;
      d2E_dxdy[i] += k[i][j] * l[i][j] * t1*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2));
    }

} //dp

int getVmax(){ // Vertex with maximum energy
  int i, j, vno; //vno: vertex number
  long double max;

  max = -1;

  rep(i, n)
  if (max < sqrt(dE_dy[i] * dE_dy[i] + dE_dx[i] * dE_dx[i]))
    max = sqrt(dE_dy[i] * dE_dy[i] + dE_dx[i] * dE_dx[i]),
    vno = i;

  return vno;
}

void update_parameters(int vno){
  int i;
  long double t1, t2;

  cout << "Updating parameters" << endl;
  //
  dE_dx[vno] = 0;
  for (i = 0; i < n; i++)
  {
    /*if (i == vno)
      continue;
    else*/
    if(i==vno)
      continue;
    {
      t1 = p[vno].first - p[i].first;
      t2 = p[vno].second - p[i].second;
      dE_dx[vno] += k[vno][i] * (t1 - l[vno][i] * t1 / sqrt(t1*t1 + t2*t2));
    }
  }
  //
  dE_dy[vno] = 0;
  for (i = 0; i < n; i++)
  {
    /*if (i == vno)
      continue;
    else*/
    if(i==vno)
      continue;
    {
      t2 = p[vno].first - p[i].first;
      t1 = p[vno].second - p[i].second;
      dE_dy[vno] += k[vno][i] * (t1 - l[vno][i] * t1 / sqrt(t1*t1 + t2*t2));
    }
  }
  //

  d2E_dx2[vno] = 0;
  for (i = 0; i < n; i++)
  {
    if (i == vno)
      continue;
    else
    {
      t1 = p[vno].first - p[i].first;
      t2 = p[vno].second - p[i].second;
      d2E_dx2[vno] += k[vno][i] * (1 - l[vno][i] * t2*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2)));;
    }
  }
  //

  d2E_dy2[vno] = 0;
  for (i = 0; i < n; i++)
  if (i == vno)
    continue;
  else{
    t2 = p[vno].first - p[i].first;
    t1 = p[vno].second - p[i].second;
    d2E_dy2[vno] += k[vno][i] * (1 - l[vno][i] * t2*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2)));;
  }
  //
  d2E_dxdy[vno] = 0;

  for (i = 0; i < n; i++)
  if (i == vno)
    continue;
  else{
    t1 = p[vno].first - p[i].first;
    t2 = p[vno].second - p[i].second;
    d2E_dxdy[vno] += k[vno][i] * l[vno][i] * t1*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2));
  }
}// update_parameters


void minimiseEnergy()
{
  long double prev;
  long double dx, dy, deltaM;
  prev = -1;

  while (sqrt(dE_dx[getVmax()] * dE_dx[getVmax()] + dE_dy[getVmax()] * dE_dy[getVmax()]) > E  )
  {
    int vno = getVmax();

    deltaM = sqrt(dE_dx[vno] * dE_dx[vno] + dE_dy[vno] * dE_dy[vno]);

    cout << "Minimising energy of vertex: " << vno << " with delta:" << deltaM << endl;

    while (deltaM > E)
    {
      //solve for dx,dy
      dx = (d2E_dxdy[vno] * (dE_dy[vno]) - (d2E_dy2[vno])*(dE_dx[vno])) / (-d2E_dxdy[vno] * d2E_dxdy[vno] + (d2E_dy2[vno])*(d2E_dx2[vno]));
      dy = (d2E_dxdy[vno] * (-dE_dx[vno]) + (d2E_dx2[vno])*(dE_dy[vno])) / (d2E_dxdy[vno] * d2E_dxdy[vno] - (d2E_dy2[vno])*(d2E_dx2[vno]));
      p[vno].first += dx;
      p[vno].second += dy;
      //update  all the parameters for this point :: update_parameters(vno);
      prev = deltaM;
      update_parameters(vno);
      deltaM = sqrt(dE_dx[vno] * dE_dx[vno] + dE_dy[vno] * dE_dy[vno]);
      cout << "Updated delta: " << deltaM <<" "<<prev<<" "<<deltaM - prev<<" "<<dx<<" "<<dy<<" "<<dE_dx[vno]<<" "<<dE_dy[vno]<< endl;
    long diff = (long)deltaM - prev;
    long one = 1;
      if(  diff < one  )
          break;
    }
    //Update the new value in the main graph accordingly
  }

} //minimiseEnergy

void print_values() { //For debugging purposes
  int i, j;

  cout << "d values" << endl;
  rep(i, n){
    rep(j, n)
      cout << d[i][j] << " "; cout << endl;
  }
  cout << "l values" << endl;
  rep(i, n){
    rep(j, n)
      cout << l[i][j] << " "; cout << endl;
  }

  cout << "k values" << endl;
  rep(i, n){
    rep(j, n)
      cout << k[i][j] << " "; cout << endl;
  }

  cout << "derivatives" << endl;
  rep(i, n)
    cout << dE_dx[i] << " " << dE_dy[i] << " " << d2E_dx2[i] << " " << d2E_dy2[i] << " " << d2E_dxdy[i] << endl;

}

 void run_spring_force_model( vector< pair<int,int> > p1 ) {

  int i, j;


  p = p1;
  n = p.size();


  for(i=0;i<n;i++){
    for(j=0;j<n;j++)
      cout<<d[i][j]<<" ";
    cout<<endl;

  }



  cout << "Computing d values" << endl;
  compute_d();

  L = getL();

  cout << "Computing l values" << endl;
  compute_l();

  cout << "Computing k values" << endl;
  compute_k();

  compute_derivatives();

  print_values(); /* For debugging purposes*/

  minimiseEnergy();

}

}; //end of class
/*   : For initial testing purposes
int main() {

  int i, j;
  n = 4;
  for (i = 0; i<n; i++)
  for (j = 0; j<n; j++)
    d[i][j] = rand()%100+5; //totally connected graph

  p.pb(mp(1, 2));
  p.push_back(mp(3, 5));
  p.push_back(mp(4,7));
  p.push_back(mp(8, 5));


  run_spring_force_model(p);

  for (i = 0; i < p.size(); i++)
    cout << p[i].first << " " << p[i].second << endl;
  return 0;
}
*/



/*
-> use Floyd Warshall to calculate dij. O(n^3)
*/



/*  Observations:
DeltaM value is not decreasing after every iteration, is there any pattern that it follows?
*/
