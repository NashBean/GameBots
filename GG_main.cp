//
//  GG_main.cpp
//
//
//  Created by nash on 11/26/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//

const int GG_MAJOR_VERSION = 0;
const int GG_MINOR_VERSION = 9;

/*/
 A few distributive properties of modulo are as follows:
 1. ( a + b ) % c = ( ( a % c ) + ( b % c ) ) % c
 2. ( a * b ) % c = ( ( a % c ) * ( b % c ) ) % c
 3. ( a – b ) % c = ( ( a % c ) - ( b % c ) ) % c ( see notes at bottom )
 4. ( a / b ) % c NOT EQUAL TO ( ( a % c ) / ( b % c ) ) % c
 So, modulo is distributive over +, * and - but not / . 
//*/

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

long long excla(int n) // ! math function
{
    long long result = n;
    for(int i=n-1; i>0; --i)
        result= result * i;
    return result;
}

long long permutation(int n, int r, long long m)
{
    long long result = (excla(n));
    return  (result / excla(n-r))%m;
}

long long get_permutations_modulo_count(int N, long long M, string& S)
{
    int G;
    int L;
    G=L=0;
    for(int i=0; i<S.size(); ++i)
    {
        if(S[i] == 'G') ++G;
        else if (S[i] == 'L') ++L;
    }
    long long result = permutation(G, L, M);
    return result;
}

int main(){
    int N;
    long long M;
    cin >> N >> M;
    string S;
    cin >> S;
    cout << get_permutations_modulo_count(N, M, S) <<endl;
    return 0;
}



