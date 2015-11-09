// *****************************************************************************
// *** coordin.cpp                                                           ***
// *** transform the coordinate in lattice                                   ***
// *****************************************************************************

#include <cmath>
#include <iostream>
#include <armadillo>
#include "../include/const.h"
#include "../include/errors.h"

using namespace std;
using namespace arma;
using jun::PI;

namespace jun{

double mod(const vec a){
    //return the module of a vector
    double re=0;
    unsigned i;
    for(i=0;i<a.n_rows;++i){
        re+=a(i)*a(i);
    }
    return sqrt(re);
}

vec cardetospher(const vec carde){
    vec spher(3);
    double rho;
    if(carde.n_rows!=3)
        return spher.zeros();
    spher(0)=mod(carde);
    if(spher(0)==0)
        return spher.zeros();
    rho=sqrt(carde(0)*carde(0)+carde(1)*carde(1));
    if(rho==0&&carde(2)>0){
        spher(2)=0;
        spher(1)=0;
        return spher;
    }
    if(rho==0&&carde(2)<0){
        spher(2)=0;
        spher(1)=PI;
        return spher;
    }
    if(carde(1)>=0)
        spher(2)=acos(carde(0)/rho);
    else
        spher(2)=2*PI-acos(carde(0)/rho);
    spher(1)=acos(carde(2)/spher(0));
    #ifdef DEBUG_COORDIN
        if(isnan(spher(2))){
            jun::error("in cardetospher: phi is nan!");
            jun::error("input is ",carde);

        }
        if(isnan(spher(0))){
            jun::error("in cardetospher: r is nan!");
            jun::error("input is ",carde);
        }
        if(isnan(spher(1))){
            jun::error("in cardetospher: theta is nan!");
            jun::error("input is ",carde);
        }
    #endif
        return spher;
}

vec sphertocarde(const vec spher){
    vec carde(3);
    carde(0)=spher(0)*sin(spher(1))*cos(spher(2));
    carde(1)=spher(0)*sin(spher(1))*sin(spher(2));
    carde(2)=spher(0)*cos(spher(1));
    #ifdef DEBUG_COORDIN
        if(isnan(carde(0))){
            jun::error("in sphertocarde: x is nan!");
            jun::error("input is ",spher);
        }
        if(isnan(carde(1))){
            jun::error("in sphertocarde: y is nan!");
            jun::error("input is ",spher);
        }
        if(isnan(carde(2))){
            jun::error("in sphertocarde: z is nan!");
            jun::error("input is ",spher);
        }
    #endif
    return carde;
}

vec trans_coord(const vec R1, const vec R2, const vec r1){
    //at origin R1, the point r1=(r,theta,phi)
    //to origin R2, return (r',theta',phi')
    vec carde(3);
    carde=R1+sphertocarde(r1)-R2;
    return cardetospher(carde);
}

}
