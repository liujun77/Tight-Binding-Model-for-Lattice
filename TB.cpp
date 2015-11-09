#include <fstream>
#include <armadillo>
#include <iostream>
#include "include/const.h"
#include "include/lattice.h"
#include "include/readin.h"
#include <string>
#include "include/coordin.h"

using namespace std;
using namespace arma;
using jun::read;
using jun::CONST_factorial_generator;

double Hs0;
double Hs1;
double Hs2;
double Hs3;
double Hs4;
double Hs5;
vec a1(3),a2(3),a3(3);

void sample_input(void){
    ofstream file_s;
    file_s.open("input.in");
    file_s<<"a = "<<"4.0"<<endl;
    file_s<<"radius = "<<"20.0"<<endl;
    file_s.close();
}

int program(string file_in){
    double a,
           //lattice const
           radius;
           //radius of the particle
    mat    ma,
           //tight binding matrix to slove the eigenenergy
           LATTICE;
           //keep the points coordingnate of the lattice
    int    flag,
           N;
           //number of states
    vec    eigval;
           //keep the eigenenergy
           //fcc lattice basis set
    a1<<0.5<<endr<<0.5<<endr<<0<<endr;
    a2<<0.5<<endr<<0<<endr<<0.5<<endr;
    a3<<0<<endr<<0.5<<endr<<0.5<<endr;
    a1=a1*a;
    a2=a2*a;
    a3=a3*a;
    #ifdef DEBUG
        cout<<"================================================="<<endl;
        a1.print("a1:");a2.print("a2");a3.print("a3");
        cout<<"done! basis set"<<endl;
    #endif
    //ifstream filein;
    ofstream fileout;
    string file_out;
    file_out=file_in+".out";
    //filein.open(file_in.c_str());
    fileout.open(file_out.c_str());

    //read parameter from input file
    if(!(flag=read(&a,file_in,"a"))){
        cerr<<"a is not defined"<<endl;
        return -1;
    }
    if(!(flag=read(&radius,file_in,"radius"))){
        cerr<<"radius is not defined"<<endl;
        return -1;
    }
    if(!(flag=read(&Hs0,file_in,"Hs0"))){
        cerr<<"Hs0 is not defined"<<endl;
        return -1;
    }
    if(!(flag=read(&Hs1,file_in,"Hs1"))){
        cerr<<"Hs1 is not defined"<<endl;
        return -1;
    }
    if(!(flag=read(&Hs2,file_in,"Hs2"))){
        cerr<<"Hs2 is not defined"<<endl;
        return -1;
    }
    if(!(flag=read(&Hs3,file_in,"Hs3"))){
        cerr<<"Hs3 is not defined"<<endl;
        return -1;
    }
    if(!(flag=read(&Hs4,file_in,"Hs4"))){
        cerr<<"Hs4 is not defined"<<endl;
        return -1;
    }
    if(!(flag=read(&Hs5,file_in,"Hs5"))){
        cerr<<"Hs5 is not defined"<<endl;
        return -1;
    }
#ifdef DEBUG
    cout<<"================================================="<<endl;
    cout<<" a= "<<a<<", radius= "<<radius<<endl;
    cout<<" Hs0= "<<Hs0<<endl;
    cout<<" Hs1= "<<Hs1<<endl;
    cout<<" Hs2= "<<Hs2<<endl;
    cout<<" Hs3= "<<Hs3<<endl;
    cout<<" Hs4= "<<Hs4<<endl;
    cout<<" Hs5= "<<Hs5<<endl;
    cout<<"done! read"<<endl;
#endif
    N=LATTICE_build(LATTICE,a,radius);
#ifdef DEBUG
    cout<<"================================================="<<endl;
    mat L2;
    L2=trans(LATTICE);
    //L2.print("L2");
    int i_d;
    ofstream file_d("lattice.txt");
    for(i_d=0;i_d<N;++i_d){
        file_d<<L2(i_d,0)<<"\t"<<L2(i_d,1)<<"\t"<<L2(i_d,2)<<endl;
    }
    file_d.close();
    cout<<"N="<<N<<endl;
    //L2.save("lattice.txt",arma_ascii);
    cout<<"done! LATTICE_build"<<endl;
#endif
#ifdef EXITA
    return 0;
#endif
    LATTICE_matrix(ma,N,LATTICE,a);
    eigval=eig_sym(ma);
    eigval.print(fileout);
    fileout.close();
    return 1;
}

int main(int argv, const char* argc[]){
    int i;
    string file_in;
    CONST_factorial_generator(100);
    if(argv<2){
        cerr<<"need a input file"<<endl;
        sample_input();
        return -1;
    }
    for(i=1;i<argv;++i){
        file_in=argc[i];
        program(file_in);
    }
    return 0;
}
