//
//  BotCleanStochastic.cpp
//
//
//  Created by nash on 11/22/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//

#include<iostream>
#include<vector>
using namespace std;
#define GRID_SIZE  5

void nextMove(int row, int col, vector<string>& board) 
{
    int cdr, cdc, closest=GRID_SIZE*2;
    for(int r=0; r<GRID_SIZE; ++r)
        for(int c=0; c<GRID_SIZE; ++c)
            if(board[r][c] == 'd')
            {
                if(r==row && c==col) 
                {cout<<"CLEAN"<<endl; return;}
                else
                { cdr=r; cdc=c;}
            }
    //LEFT, RIGHT, UP and DOWN or CLEAN                        
    cdr = cdr - row; cdc = cdc - col;
    if(cdr!=0 || cdc !=0)
    {
        if(cdr < 0) { cout<<"UP"<<endl;}
        else if(cdr > 0) { cout<<"DOWN"<<endl;}
        else if(cdc < 0) { cout<<"LEFT"<<endl;}
        else if(cdc > 0) { cout<<"RIGHT"<<endl;}
    }
}
int main(void) {
    int pos[2];
    vector <string> board;
    cin>>pos[0]>>pos[1];
    for(int i=0;i<5;i++) {
        string s;
        cin >> s;
        board.push_back(s);
    }
    nextMove(pos[0], pos[1], board);
    return 0;
}
