#ifndef ERRORS_H
#define ERRORS_H

// *****************************************************************************
// *** errors.h                                                              ***
// *** Error info output                                                     ***
// *** Jun Liu 2014-02-23                                                    ***
// *****************************************************************************

#include <string>
#include <iostream>

namespace jun{

template<typename T>

inline void error(std::string text, T val){
    std::cout<<"error: "<<text<<val<<std::endl;
}

inline void error(std::string text){
    std::cout<<"error: "<<text<<std::endl;
}

}

#endif
