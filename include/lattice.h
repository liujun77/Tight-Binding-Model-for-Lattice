// *****************************************************************************
// *** lattice.h                                                             ***
// *** lattice building and tight binding matrix building                    ***
// *****************************************************************************

#ifndef LATTICE_H
#define LATTICE_H

int LATTICE_build(arma::mat &LATTICE, const double a, const double radius);
// LATTICE : 3*N mat keep the all N lattice points
// a       : lattice constant
// radius  : radius of the particle

int LATTICE_distance(const arma::vec a, const arma::vec b, const double lac);
//return the order of distance of two lattice points

double LATTICE_matrixele(const arma::vec a,
                         const arma::vec b,
                         const double lac);
//return the matrix element of two sites
//for the same site return 0
//for the nearest return 1

void LATTICE_matrix(arma::mat &ma,
                    const int N,
                    const arma::mat LATTICE,
                    const double lac);
//build the tight binding matrix

#endif
