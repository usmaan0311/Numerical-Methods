#ifndef BURGERHEADERDEF
#define BURGERHEADERDEF

#include<string>
#include<cmath>

class Burger{
double nu=0.07;
double L=2.0*M_PI;
double courant=0.1;
int nx;
int nt;
double dt;
double dx;
	public:
		Burger(int ,int );
		double Diff(double (Burger::*f)(double,double), double ,double, double);
		double* InitCond(double*,double*);
		double* XVector(double*);
		double Phi(double, double);
		double* FinDiff(double*);
		void WriteSol(double*,double*,std::string);

};


#endif
