//******************************************************************************
//***   arma_lapacke.cpp                                                     ***
//******************************************************************************

#include <complex>
#include <armadillo>
#include <lapacke.h>
#include <lapacke_utils.h>

using namespace arma;

lapack_int arma_ZHEGV(lapack_int itype,
                      char jobz,
                      char uplo,
                      cx_mat &A,
                      cx_mat &B,
                      vec &W){
    lapack_int re,n,ma,mb;
    n=A.n_cols;
    ma-A.n_rows;
    mb=B.n_rows;
    lapack_complex_double a[n*ma];
    lapack_complex_double b[n*mb];
    double w[n];
    int i;
    for(i=0;i<n*ma;++i)
        a[i]=A(i);
    for(i=0;i<n*mb;++i)
        b[i]=B(i);
    re=LAPACKE_zhegv(LAPACK_COL_MAJOR,itype,jobz,uplo,n,a,ma,b,mb,w);
    for(i=0;i<n;++i)
        W(i)=w[i];
    for(i=0;i<n*ma;++i)
        A(i)=a[i];
    for(i=0;i<n*mb;++i)
        B(i)=b[i];
    return re;
}
