// *****************************************************************************
// *** lattice.cpp                                                           ***
// *** lattice building and tight binding matrix building                    ***
// *****************************************************************************

#include <iostream>
#include <cmath>
#include <complex>
#include "armadillo"
#include "../include/const.h"
#include "../include/coordin.h"
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/spherical_harmonic.hpp>

using namespace std;
using namespace arma;
using jun::sphertocarde;
using jun::mod;
using jun::PI;
using jun::FACTORIAL;
extern double Hs0;
extern double Hs1;
extern double Hs2;
extern double Hs3;
extern double Hs4;
extern double Hs5;
extern double Rc;  //parameter for psudopotential
extern double Rv;  //range to calculate local potential
extern double Z;
extern double A;   //lattice constant
extern double radius;
extern vec a1;
extern vec a2;
extern vec a3;

//convergent parameters
extern double dr;
extern double dtheta;
extern double dphi;
extern double Rinte;

double LATTICE_psudo_pot(vec x){
    if(mod(x)<Rc)
        return 0;
    else
        return -Z/mod(x);
}

double LATTICE_pot(vec r){
    vec x;
    vec x0,xr;
    x=sphertocarde(r);
    x0(0)=int(x(0)/A)*A;
    x0(1)=int(x(1)/A)*A;
    x0(2)=int(x(2)/A)*A;
    double pot=0;
    int i,j,k,n;
    n=int(Rv/A)*8;
    for(i=-n;i<n;++i)
        for(j=-n;j<n;++j)
            for(k=-n;k<n;++k){
                xr=x0+i*a1+j*a2+k*a3;
                if((mod(x-xr)<Rv)&&(mod(x)<radius))
                    pot+=LATTICE_psudo_pot(x-xr);
            }
    return pot;
}

int LATTICE_build(mat &LATTICE, const double radius){
    // LATTICE : 3*N mat keep the all N lattice points
    // A       : lattice constant
    // radius  : radius of the particle
    vec pos(3);
    int i,j,k,n;
    int I,J,K,N;
    N=4*int(4*PI/3*radius*radius*radius/A/A/A*1.1);
    I=J=K=int(2*radius/A*3.1);
    LATTICE.set_size(3,N);
    n=0;
    for(i=-I;i<I;++i)
        for(j=-J;j<J;++j)
            for(k=-K;k<K;++k){
                pos=i*a1+j*a2+k*a3;
                if(mod(pos)<=radius)
                    LATTICE.col(n++)=pos;
            }
    N=n;
    LATTICE.reshape(3,N);
    return N;
}

int LATTICE_distance(const vec a, const vec b){
    //return the order of distance of two lattice points
    double dis;
    dis=mod(a-b);
    if(dis<0.5*A)
        return 0;
    else if(dis<0.8*A)
        return 1;
    else if(dis<1.1*A)
        return 2;
    else if(dis<1.3*A)
        return 3;
    else if(dis<1.5*A)
        return 4;
    else if(dis<1.8*A)
        return 5;
    else
        return 6;
}

complex<double> H_wavefunction(const double Z,
                               const unsigned n,
                               const unsigned l,
                               const int m,
                               const vec r){
    using boost::math::laguerre;
    using boost::math::spherical_harmonic;
    double rho=2*Z*r(0)/n;
    double Rnl;
    Rnl=sqrt(pow(2.*Z/n,3)*FACTORIAL[n-l-1]/2/n/pow(FACTORIAL[n+l],1));
    Rnl=Rnl*exp(-rho/2)*pow(rho,l)*laguerre(n-l-1,2*l+1,rho);
#ifdef DEBUG_LATTICE
    if(isnan(Rnl))
    cout<<"Rnl is nan!!!!!r="<<r<<endl;
#endif
    return Rnl*spherical_harmonic(l,m,r(1),r(2));
}

double LATTICE_matrixele(const vec a, const vec b){
    //return the matrix element of two sites
    //for the same site return 0
    //for the nearest return 1
    int dis;
    dis=LATTICE_distance(a,b);
    if(dis==0)
        return Hs0;
    else if(dis==1)
        return Hs1;
    else if(dis==2)
        return Hs2;
    else if(dis==3)
        return Hs3;
    else if(dis==4)
        return Hs4;
    else if(dis==5)
        return Hs5;
    else
        return 0;
}

void LATTICE_matrix(mat &ma, const int N, const mat LATTICE){
    //build the tight binding matrix
    ma.zeros(N,N);
    int i,j;
    for(i=0;i<N;++i)
        for(j=0;j<N;++j){
            ma(i,j)=LATTICE_matrixele(LATTICE.col(i),LATTICE.col(j));
            ma(j,i)=ma(j,i);
        }
}

complex<double> LATTICE_integral(complex<double> (*f1)(vec),
                                 complex<double> (*f2)(vec),
                                 double (*v)(vec),
                                 vec R1,
                                 vec R2){
    complex<double> inte=0;
    double r,theta,phi;
    vec xr;

}

