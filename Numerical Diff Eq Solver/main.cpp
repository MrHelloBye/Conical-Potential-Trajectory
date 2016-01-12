//
//  main.cpp
//  Numerical Diff Eq Solver
//
//  Created by Liam Clink on 11/28/15.
//  Copyright © 2015 Liam Clink. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <fstream> // To print to file

using namespace std;

int main() {

	double const pi = acos(-1);
	double alpha = pi/4;
	double x0, xdot0, ydot0;
	double tmax;
	
	cout << "Enter x0: ";
	cin >> x0;
	cout << "Enter xdot0: ";
	cin >> xdot0;
	cout << "Enter ydot0: ";
	cin >> ydot0;
	cout << "Enter tmax: ";
	cin >> tmax;
	
	int numOfSteps = 1000000;
	double delt = tmax/numOfSteps; // Defines shift in t
	double L=x0*ydot0;
	double A = (pow(ydot0, 2))*pow(x0, 2)*sin(alpha)*sin(alpha); // y component of v is perp
	double B = 9.81*sin(alpha)*cos(alpha);
	double rprime = xdot0;
	double ra, rb = x0, rc = pow(delt, 2)/2*(A/pow(rb, 3)-B)+rb+delt*rprime;
	double thetaprime = ydot0*x0/pow(rb, 2);
	double thetaa, thetab = 0, thetac = thetab + delt*thetaprime;
	
	ofstream Plot;
	Plot.open("Plot.txt");

	for (int n = 0; n <= numOfSteps; n++) {
		// Should maybe put this part after r
		thetaa = thetab;
		thetab = thetac;
		thetac = thetaa + 2*delt*thetaprime;
		thetaprime = ydot0*x0/pow(rb, 2); // (thetac-thetaa)/(2*delt); <- This didn't work...
		
		ra=rb;
		rb=rc;
		rc=pow(delt, 2)*(A/pow(rb, 3)-B)+2*rb-ra;
		rprime = (rc-ra)/(2*delt);
		double theta = fmod(thetaa, 2*pi);
		
		if (n%(numOfSteps/1000) == 0) {
			Plot << ra << '\t' << theta << endl; //for writing file
		}
		
		if (n%(numOfSteps/10) == 0) {
			printf("t=%g, theta=%g, r=%g\n", n*delt, theta/pi*180, rb);
			cout << "E=" << rprime*rprime+0.5*L*L/(rb*rb)+9.81*rb << endl; //Should be constant (E cons.)
		}
	}
	Plot.close();
	
	return 0;
}
