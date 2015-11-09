#ifndef CONST_H
#define CONST_H

// *****************************************************************************
// *** Constants for Physics                                                 ***
// *** Jun Liu 2014-02-09                                                    ***
// *****************************************************************************

namespace jun{

extern const double PI;//=3.141592653589793238462643,
extern const double AU_E;//=27.2113834
                    //1 a.u. of energy in eV
extern const double A0_NM;//=0.0529177208
                    //1 Bohr radius in nm
extern const double C_AU;//=137.03599971
                    //1/alfa=speed of light in a.u.

//Factorial generation
extern long *FACTORIAL;

int CONST_factorial_generator(unsigned n);

}

#endif
