//
//  Ghosts_main.h
//
//
//  Created by nash on 11/24/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//

#ifndef iBS_GhostMain_h
#define iBS_GhostMain_h

const int Ghost_MAJOR_VERSION = 1;
const int Ghost_MINOR_VERSION = 0;

#include <cstdio>
#include <vector>
#include <cstdlib>

int max_value;
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
int absolute_difference(int i1, int i2 ) 
{
    int a = abs((i1) - (i2));
    return a;
}
bool divisible_by(int n, int b)
{
    if(b>0)
    {
        int dt = n/b;
        if((dt*b) == n) return true;
    }
    return false;
}
int  GCD(int a, int b)
{
    int gcd = 1;
    
    for(int i=1;i<=a && i<=b;i++)
    {
        if(a%i==0 && b%i == 0)
        {
            gcd=i;
        }
    }
    return gcd;
}
int gcd_r( int x, int y )
{
    if( x < y )
        return gcd_r( y, x );
    
    int f = x % y;
    if( f == 0 )
        return y;
    else
        return gcd_r( y, f );
}
void PreCalcGCD(Matrix& m,int max)
{   
    m.a.resize(max+1);
    for(int i=1;i<max;i++)
        m.a[i].resize(max);
    
    for(int i=1;i<max;i++)
        for(int j=1;j<max;j++) 
        {
            m.a[i][j] = GCD(i, j);
        }
}

int preGCD(int a, int b)
{
    static bool have_calc_GCD = false;
    static Matrix m;
    if(!have_calc_GCD) {PreCalcGCD(m, max_value); have_calc_GCD=true;}
    return m.a[a][b];    
}

struct apartment
{
    int town;
    int street;
    int house;
    int apart;
    
    //The difference between the town number and the street number is divisible by 3.
    bool condition1()
    {
        int t = absolute_difference(town, street);
        return divisible_by(t, 3);
    }
    //The sum of the street number and the house number is divisible by 5.
    bool condition2()
    {
        int t = street + house;
        return divisible_by(t, 5);
    }
    //The product of the town number and the house number is divisible by 4.
    bool condition3()
    {
        int t = town * house;
        return divisible_by(t, 4);
    }
    //The greatest common divisor of the town number and the apartment number is 1.
    bool condition4()
    {
        //if(GCD(town, apart) == 1) return true;
        // if(GCD(town, apart) == 1) return true;
        if(gcd_r(town, apart) == 1) return true;
        return false;
    }
    
};
#endif // iBS_GhostMain_h


int main()
{
    int A;
    int B;
    int C;
    int D;
    //cin >> A >> B >> C >> D;
    if(scanf("%d %d %d %d", &A, &B, &C, &D))
    {
        apartment apt;
 //       int aptc=A*B*C*D; // apartment count
        if(A>max_value) max_value=A;
        if(B>max_value) max_value=B;
        if(C>max_value) max_value=C;
        if(D>max_value) max_value=D;
        int goust_count=0;
        for(int a=1; a<=A; ++a){
            apt.town = a;
            for(int b=1; b<=B; ++b){
                apt.street = b;
                for(int c=1; c<=C; ++c){
                    apt.house = c;
                    for(int d=1; d<=D; ++d)
                    {
                        apt.apart = d;
                        if(apt.condition1() && apt.condition2() 
                           && apt.condition3() && apt.condition4())
                            ++goust_count;
                    }
                }
            }
        }
        printf("%d\n", goust_count);
    }
    
    return 0;
}


