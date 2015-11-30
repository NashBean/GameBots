//
//  BotUtils.h
//
//
//  Created by nash on 11/24/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//

#ifndef iBS_BotUtils_h
#define iBS_BotUtils_h

const int BotUtils_MAJOR_VERSION = 1;
const int BotUtils_MINOR_VERSION = 1;

#include <iostream>
#include <cstdio>
#include <vector>

long long factorial(int n,int M)
{
    long long ans=1;
    while(n>=1)
    {
        ans=(ans*n)%M;
        n--;
    } 
    return ans;
}

//Fermat Little Theorem.
long long fast_pow(long long base, long long n,long long M) 
{
    if(n==0)
        return 1;
    if(n==1)
        return base;
    long long halfn=fast_pow(base,n/2,M);
    if(n%2==0)
        return ( halfn * halfn ) % M;
    else
        return ( ( ( halfn * halfn ) % M ) * base ) % M;
}

long long findMMI_fermat(int n,int M)
{
    return fast_pow(n,M-2,M);
}

int  GCD1(int a, int b)
{
    int gcd = 1;
    for(int i=2;i<=a && i<=b;i++)
    {
        if(a%i==0 && b%i == 0)
        {
            gcd=i;
        }
    }
    return gcd;
}


void printEnglishRepresentation(int x)
{
    std::string anser = "";
    if(x == 1) anser = "one";    
    else if(x == 2) anser = "two"; 
    else if(x == 3) anser = "three";    
    else if(x == 4) anser = "four";    
    else if(x == 5) anser = "five";    
    else if(x == 6) anser = "six";    
    else if(x == 7) anser = "seven";    
    else if(x == 8) anser = "eight";    
    else if(x == 9) anser = "nine";  
    
    std::cout << anser << std::endl;    
}

void printOddorEven(int x)
{
    int t = x/2; // x >0
    if(x == (t*2))
        std::cout << "even" << std::endl;
    else
        std::cout << "odd" << std::endl;
}

int max_of_four(int a, int b, int c, int d) {
    int max = 0;
    if(a>max) max = a;
    if(b>max) max = b;
    if(c>max) max = c;
    if(d>max) max = d;
    return max;
}

int sum_of_two_int(int a, int b) 
{
    return a + b;
}

int sum_of_four(int a, int b, int c, int d) {
    int sum = 0;
    sum += a;
    sum += b;
    sum += c;
    sum += d;
    return sum;
}

void absolute_difference(int *a,int *i1, int*i2 ) 
{
     (*a) = abs((*i1) - (*i2));
}

void update(int *a,int *b) 
{
    int temp = (*a);
    (*a) = (temp + (*b));
    (*b) = abs(temp - (*b));
}
struct rect3
{	// 3 corners of rectangle
	// Corners  ax,ay  bx,by  dx,dy
	int ax, ay;
	int bx, by;
	int dx, dy;	
	bool isPointInside(int x,int y)
	{
		//# Point in x, y
		int bax = bx - ax;
		int bay = by - ay;
		int dax = dx - ax;
		int day = dy - ay;
		if ((x - ax) * bax + (y - ay) * bay < 0.0) return false;
		if ((x - bx) * bax + (y - by) * bay > 0.0) return false;
		if ((x - ax) * dax + (y - ay) * day < 0.0) return false;
		if ((x - dx) * dax + (y - dy) * day > 0.0) return false;
		return true;			
	};
	void print()
	{
		//cout<<ax<<','<< ay << ' ';
		//cout<<bx<<','<< by << ' ';
		//cout<<dx<<','<< dy << endl;
	};
};


std::vector<int> parseInts(std::string str) 
{
    std::vector<int> rv;//result vector
    /*
    std::stringstream ss = str;
    ss = std::stringstream(str);
    char ch;
    int a;
    while(ss >> a)
    {
        rv.push_back(a);
        ss >> ch;
        if(ch == '\n') break;
    }
     //*/
    return rv;
}

struct Matrix 
{
    std::vector<std::vector<int> > a; 
    
    Matrix& operator +(Matrix& o)
    {
        for(int i=0;i<a.size();i++) 
            for(int j=0;j<a[i].size();j++) 
            {
                a[i][j] = a[i][j] + o.a[i][j];
            }
        return *this;
    }
};

#endif // iBS_BotIOFunctions_h