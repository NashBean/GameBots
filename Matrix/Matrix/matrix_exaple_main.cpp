//
//  main.cpp
//  Matrix
//
//  Created by nash on 11/27/15.
//  Copyright 2015 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "iBS_Matrix.h"



int main (int argc, const char * argv[])
{ //tm to the power of 100
    iBS::Matrix tM;
    tM.a.resize(3);
    for (int cs=0; cs<3; ++cs) 
    {
        tM.a[cs].resize(3);
    }
    tM.a[0][0] = 1;
    tM.a[0][1] = 1;
    tM.a[0][2] = 0;
    tM.a[1][0] = 0;
    tM.a[1][1] = 1;
    tM.a[1][2] = 0;
    tM.a[2][0] = 0;
    tM.a[2][1] = 0;
    tM.a[2][2] = 1;
    
    std::cout << "Matrix Before:" << std::endl;
    tM.print();
    
    std::cout << "Matrix ^ 100 =" << std::endl;
    tM = tM ^ 100; // ^ operator build in now
    
   // std::cout << "After" << std::endl;
    tM.print();
    
    return 0;
}

