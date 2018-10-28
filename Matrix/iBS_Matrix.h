//
//  iBS_Matrix.h
//  https://github.com/NashBean/GameBots/Matrix/iBS_Matrix.h 
//
//  Created by Nash Bean on 11/29/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//

#ifndef iBS_Matrix_h
#define iBS_Matrix_h

const int Matrix_MAJOR_VERSION = 1;
const int Matrix_MINOR_VERSION = 1;

#include <iostream>
#include <vector>
namespace iBS
{
// move rem to switch 32 bit int - 64 bit int ...
#define int_t int 
//#define int_t uint32_t 
//#define int_t uint64_t
//#define int_t longlong

struct Matrix 
{  //  Must have a space between > > below, or will not work
    std::vector<std::vector<int_t> > a; 
    
    Matrix& operator =(Matrix& o)
    {
        a.resize(o.a.size());
        for(size_t i=0;i<a.size();i++)
            a[i].resize(o.a[i].size());
        for(size_t i=0;i<a.size();i++) 
            for(int j=0;j<a[i].size();j++) 
            {
                a[i][j] = o.a[i][j];
            }
        return *this;
    }
    
    Matrix& operator +(Matrix& o)
    {
        for(size_t i=0;i<a.size();i++) 
            for(size_t j=0;j<a[i].size();j++) 
            {
                a[i][j] = a[i][j] + o.a[i][j];
            }
        return *this;
    }
    Matrix& operator -(Matrix& o)
    {
        for(size_t i=0;i<a.size();i++) 
            for(size_t j=0;j<a[i].size();j++) 
            {
                a[i][j] = a[i][j] - o.a[i][j];
            }
        return *this;
    }
    Matrix& operator *(Matrix& o)
    {
        if(a[0].size() != o.a.size()) return *this;
        
        Matrix tm;
        tm.a.resize(a.size());
        for(size_t i=0;i<tm.a.size();i++)
            tm.a[i].resize(o.a[0].size());
        
        for(size_t i=0;i<tm.a.size();i++) 
            for(size_t j=0;j<tm.a[i].size();j++) 
            {
                tm.a[i][j] = 0;
                for (size_t c=0; c<a[i].size(); c++) 
                {
                    tm.a[i][j] += a[i][c] * o.a[c][j];
                }
                
            }
        *this = tm;
        return *this;
    }
    Matrix& operator ^(int power)// more then 32 bit int may be to much
    {
        Matrix  tM2;
        tM2 = *this;

    //   not <= below \/ because first time counts as 2
        for(size_t i=1; i<power; ++i)
            *this = (*this) * (tM2);
        
        return *this;
    }
    
    void print()
    {
        for(size_t i=0;i<a.size();i++) 
        {
            for(size_t j=0;j<a[i].size();j++) 
            {
                std::cout << a[i][j] << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}; // ens of Matrix struct

}; // end of namespace iBS

#endif // iBS_Matrix_h
