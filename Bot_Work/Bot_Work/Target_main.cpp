//
//  Target_main.cpp
//
//
//  Created by nash on 11/25/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

long double calc_distance(long long x,long long y)
{ 
    
    long long int a,b;
    long long int c;
    //x=abs(x-0); y =abs(y-0);
  //todo  a = pow(x, 2);
  //todo  b = pow(y,2);
    c = a + b;
    return sqrt(c);  
}

long long int calc_score(vector<long long int>& R, vector<vector<long long int> >& shots)
{
    long long int result=0,p;
    long double temp = 0;
    for(long long int i = 0;i < shots.size();++i){
        if(shots[i][0]==0 && shots[i][1]==0) temp = 0;
        else if(shots[i][0]==0) temp = shots[i][1];
        else if(shots[i][1]==0) temp = shots[i][0];
        else temp = calc_distance(shots[i][0], shots[i][1]);
        p=0;
        for(long long int r = 0;r < R.size();++r)
        {
            if( temp <= R[r]) p = r+1;
            //else if(temp == R[r]) p = r+1;
        }
        result += p;
    }
    return result;
}

int target_main()
{
    long long int K;
    long long int N;
    cin >> K >> N;
    // scanf("%d %d",&K,&N);
    vector<long long int> R(K);
    for(long long int R_i = 0;R_i < K;R_i++){
        //scanf("%d", &R[R_i]); 
        cin >> R[R_i];
    }
    vector<vector<long long int> > x(N,vector<long long int>(2));
    for(long long int x_i = 0;x_i < N;x_i++){
        for(size_t x_j = 0;x_j < 2;x_j++){
            //scanf("%d",&x[x_i][x_j]); 
            cin >> x[x_i][x_j];
        }
    }
    cout << calc_score(R, x) << endl;
    
    return 0;
}
