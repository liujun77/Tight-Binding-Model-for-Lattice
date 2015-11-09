#include <iostream>
#include <cmath>
#include <complex>
#include <armadillo>
#include <lapacke.h>
#include <lapacke_utils.h>

//#define lapack_complex_float std::complex<float>
//#define lapack_complex_double std::complex<double>

using namespace std;
using namespace arma;

lapack_int arma_ZHEGV(lapack_int itype, cx_mat A, cx_mat B, vec &W){
    lapack_int n,m;
    n=A.n_cols;
    m=A.n_rows;
    lapack_complex_double a[n*m];
    lapack_complex_double b[n*m];
    double w[n];
    int i,re;
    for(i=0;i<n*m;++i){
        a[i]=A(i);
        b[i]=B(i);
    }
    re=LAPACKE_zhegv(LAPACK_COL_MAJOR,itype,'N','U',n,a,m,b,m,w);
    for(i=0;i<n;++i)
        W(i)=w[i];
    return re;
}

int main(){
    cx_mat A(10,10),B(10,10);
    vec W(10);
    int i;
    A.zeros();
    B.zeros();
    A(1,2)=A(2,1)=10;
    for(i=0;i<10;++i)
        B(i,i)=1;
    B(1,1)=2;
    B(2,2)=4;
    int re;
    re=arma_ZHEGV(1,A,B,W);
    W.print("W:");
    return 0;
}
