//
//  BotScan.cpp
//
//
//  Created by nash on 11/24/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//
#ifndef iBS_BotScan_h
#define iBS_BotScan_h

const int BIO_MAJOR_VERSION = 1;
const int BIO_MINOR_VERSION = 1;

#include <iostream>
#include <cstdio>

using namespace std;

bool get_one_int(int& a)
{
    if(scanf("%d ", &a)) return true;
    return false;   
};

bool get_two_int(int& a, int& b)
{
    if(scanf("%d %d", &a, &b)) return true;
    return false;   
};

bool get_three_int(int& a, int& b, int& c)
{
    if(scanf("%d %d %d", &a, &b, &c)) return true;
    return false;   
};

int CIO_main() {
    //Input will consist of an int, long, long long, char, float and double
    int one;
    long two;
    long long three;
    char four;
    float five;
    double  six;
    if(scanf("%d %ld %lld %c %f %lf", &one, &two, &three, &four, &five, &six))
    {
        //cin >> one >> two >> three >> four >> five >> six;
        cout << one << endl;
        cout << two << endl;
        cout << three << endl;
        cout << four << endl;
        printf("%f \n", five);
        //cout << five << endl;
        printf("%lf \n", six);
        //cout << six << endl;// cout cut off all but one dec point
    }
    return 0;
}
#endif // iBS_BotScan

/*
 
 Int ("%d"): 32 Bit integer
 Long ("%ld"): 32 bit integer (same as Int for modern systems)
 Long Long ("%lld"): 64 bit integer
 Char ("%c"): Character type
 Float ("%f"): 32 bit real value
 Double ("%lf"): 64 bit real value
 
 //*/