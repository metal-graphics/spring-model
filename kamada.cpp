#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<utility>
#include<GL\glu.h>
#include<GL\glut.h>
#define x first ;
#define y second ;
#define for(i,n) for(i=0;i<n;i++)
#define pb push_back;
#define mp make_pair;
#define INF 10000000;
#define L0 400
#define K 500
#define E .01


int g[100][100];

vector< pair<int, int> > p; // vertices Pair
long double  d[100][100], l[100][100], k[100][100], L;
long double dE_dx[100], dE_dy[100], d2E_dx2[100], d2E_dy2[100], d2E_dxdy[100];




void compute_d(int n){ // n: number of vertices
	int i, j, k;

	for (k, n)
		for (i, n)
			for (j, n)
			if (d[i][k] + d[k][j] < d[i][j])
				d[i][j] = d[i][k] + d[k][j];

}

float getL() {

	int i, j, max;
	max = -1;

	for (j = 0; j<n; j++)
		for (i = 0; i<j; i++)
		if (d[i][j] != INF && d[i][j] > max)
			max = d[i][j];


	return L0 / max;
}


void compute_l(){
	int i, j;

	for (i, n)
	for (j, n)
		l[i][j] = L * d[i][j];

}


void compute_k(){
	int i, j;

	for (i, n)
	for (j, n)
		k[i][j] = K / (d[i][j] * d[i][j]);

}


void dp() {
	int i, j;
	long double t1, t2;

	//

	for (i, n)
		dE_dx[i] = 0;
	
	for (i, n)
		for (j, n){
			if (i == j)
				continue;
			t1 = p[i].x - p[j].x,
			t2 = p[i].y - p[j].y,
			dE_dx[i] += k[i][j] * (t1 - l[i][j] * t1 / sqrt(t1*t1 + t2*t2));
	}


	//
		
		for (i, n)
			dE_dy[i] = 0;

		for (i, n)
			for (j, n){
				if (i == j)
					continue;
					t2 = p[i].x - p[j].x,
					t1 = p[i].y - p[j].y,
					dE_dy[i] += k[i][j] * (t1 - l[i][j] * t1 / sqrt(t1*t1 + t2*t2));
		}


	//

	for (i, n)
		d2E_dx2[i] = 0;


	for (i, n)
		for (j, n){
			if (i == j)
				continue;
			t1 = p[i].x - p[j].x,
			t2 = p[i].y - p[j].y,
			d2E_dx2[i] +=  k[i][j] * (1 - l[i][j] * t2*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2)));
	
	}


	//

		for (i, n)
			d2E_dy2[i] = 0;


		for (i, n)
		for (j, n){
			if (i == j)
				continue;
				t2 = p[i].x - p[j].x,
				t1 = p[i].y - p[j].y,
				d2E_dy2[i] += k[i][j] * (1 - l[i][j] * t2*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2)));
		}
	
				
	//

	for (i, n)
		sd2E_dxdy[i] = 0; 

	for (i, n)
		for (j, n){
			if (i == j)
				continue;
			t1 = p[i].x - p[j].x,
			t2 = p[i].y - p[j].y,
			d2E_dxdy[i] +=  k[i][j] * l[i][j] * t1*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2));
	}

} //dp

int getVmax(){ // Vertex with maximum energy
	int i, j, vno; //vno: vertex number
	long double max;

	max = -1;

	for (i, n)
	if (max < sqrt(dE_dy[i] * dE_dy[i] + dE_dx[i] * dE_dx[i]))
		max = sqrt(dE_dy[i] * dE_dy[i] + dE_dx[i] * dE_dx[i]),
		vno = i;

	return vno;
}

void update_parameters(int vno){
	int i; 
	long double t1, t2;

//
	dE_dx[vno] = 0;
	for (i = 0; i < n ;i++)
		if (i == vno)
			continue;
		else{
			t1 = p[vno].x - p[i].x;
			t2 = p[vno].y - p[i].y;
			dE_dx[vno] += k[vno][i] * (t1 - l[vno][i] * t1 / sqrt(t1*t1 + t2*t2));
		}

//
		dE_dy[vno] = 0;
		for (i = 0; i < n; i++)
		if (i == vno)
			continue;
		else{
			t2 = p[vno].x - p[i].x;
			t1 = p[vno].y - p[i].y;
			dE_dy[vno] += k[vno][i] * (t1 - l[vno][i] * t1 / sqrt(t1*t1 + t2*t2));
		}
//

		d2E_dx2[vno] = 0;
		for (i = 0; i < n; i++)
		if (i == vno)
			continue;
		else{
			t1 = p[vno].x - p[i].x;
			t2 = p[vno].y - p[i].y;
			d2E_dx2[vno] += k[vno][i] * (1 - l[vno][i] * t2*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2)));;
		}
//

		d2E_dy2[vno] = 0;
		for (i = 0; i < n; i++)
		if (i == vno)
			continue;
		else{
			t2 = p[vno].x - p[i].x;
			t1 = p[vno].y - p[i].y;
			d2E_dy2[vno] += k[vno][i] * (1 - l[vno][i] * t2*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2)));;
		}
//
		d2E_dxdy[vno] = 0; 

		for (i = 0; i < n; i++)
		if (i == vno)
			continue;
		else{
			t1 = p[vno].x - p[i].x;
			t2 = p[vno].y - p[i].y;
			d2E_dxdy[vno] += k[vno][i] * l[vno][i] * t1*t2 / (sqrt(t1*t1 + t2*t2) * (t1*t1 + t2*t2));
		}
}// update_parameters


void minimiseEnergy( ){
	
	while (sqrt(dE_dx[getVmax()] * dE_dx[getVmax()] + dE_dy[getVmax()] * dE_dy[getVmax()]) > E) {
		int vno = getVmax();
		long double dx, dy, deltaM;
		deltaM = sqrt(dE_dx[vno] * dE_dx[vno] + dE_dy[vno] * dE_dy[vno]);
		
		while (deltaM > E){
			//solve for dx,dy
			dx = (d2E_dxdy * (-dE_dy) - (d2E_dy2)*(-dE_dx)) / (d2E_dxdy*d2E_dxdy - (d2E_dy2)*(d2E_dx2));
			dy = (d2E_dxdy * (-dE_dx) - (d2E_dx2)*(-dE_dy)) / (d2E_dxdy*d2E_dxdy - (d2E_dy2)*(d2E_dx2));
			p[vno].x += dx;
			p[vno].y += dy;
			//update  all the parameters for this point :: update_parameters(vno);
			update_parameters(vno);
			deltaM = sqrt(dE_dx[vno] * dE_dx[vno] + dE_dy[vno] * dE_dy[vno]);
		}
	}
} //minimiseEnergy



/*
-> use Floyd Warshall to calculate dij. O(n^3)
*/