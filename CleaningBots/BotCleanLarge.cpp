//
//  BotCleanLarge.cpp
//
//
//  Created by nash on 11/22/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//

#include<iostream>
#include<vector>
using namespace std;
void next_move(int row, int col, int gh, int gw, vector<string>& board) 
{
    int cdr, cdc, closest=gh+gw;
    for(int r=0; r<gh; ++r)
        for(int c=0; c<gw; ++c)
            if(board[r][c] == 'd')
                if(closest > (abs(r-row)+abs(c-col)))
                {
                    if(r==row && c==col) 
                    {cout<<"CLEAN"<<endl; return;}
                    closest = (abs(r-row)+abs(c-col));
                    cdr=r; cdc=c;
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
    int dim[2];
    vector <string> board;
    cin>>pos[0]>>pos[1];
    cin>>dim[0]>>dim[1];
    for(int i=0;i<dim[0];i++) {
        string s;cin >> s;
        board.push_back(s);
    }
    next_move(pos[0], pos[1], dim[0], dim[1], board);
    return 0;
}
