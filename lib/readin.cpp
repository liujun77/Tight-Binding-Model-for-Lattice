// *****************************************************************************
// *** readin.cpp                                                            ***
// *** Jun Liu 2014-02-16                                                    ***
// *** Reading the input file                                                ***
// *****************************************************************************

#include <sstream>

using namespace std;

namespace jun{

int is_check_in(string str, string check){
    //check if the word check is in check
    istringstream input_str(str);
    string temp;
    while(!input_str.eof()){
        input_str>>temp;
        if(temp==check)
            return 1;
    }
    return 0;
}

}
