// *****************************************************************************
// *** Constants for Physics                                                 ***
// *** Jun Liu 2014-02-09                                                    ***
// *****************************************************************************

namespace jun{

extern const double PI=3.141592653589793238462643;
extern const double AU_EV=27.2113834;        //1 a.u. of energy in eV
extern const double A0_NM=0.0529177208;      //1 Bohr radius in nm
extern const double C_AU=137.03599971;       //1/alfa=speed of light in a.u.

//Factorial generation
long *FACTORIAL;

int CONST_factorial_generator(unsigned n){
    unsigned i;
    FACTORIAL=new long[n];
    FACTORIAL[0]=1L;
    for(i=1;i<=n;++i){
        FACTORIAL[i]=FACTORIAL[i-1]*i;
    }
    return 1;
}

}
