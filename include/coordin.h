// *****************************************************************************
// *** coordin.h                                                             ***
// *** transform the coordinate in lattice                                   ***
// *****************************************************************************

#ifndef COORDIN_H
#define COORDIN_H

namespace jun{

double mod(const arma::vec a);
    //return the module of a vector

arma::vec cardetospher(const arma::vec carde);

arma::vec sphertocarde(const arma::vec spher);

arma::vec trans_coord(const arma::vec R1,
                           const arma::vec R2,
                           const arma::vec r1);
    //at origin R1, the point r1=(r,theta,phi)
    //to origin R2, return (r',theta',phi')

}

#endif
