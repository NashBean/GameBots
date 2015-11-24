//
//  MazeEscape_main.cpp
//
//
//  Created by nash on 11/22/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//
const int MzE_MAJOR_VERSION = 0;
const int MzE_MINOR_VERSION = 6;


#include<iostream>
#include<vector>
using namespace std;
#define GRID_SIZE  3
//#define V_D 1 

string move2exit(int r,int c, vector<string>& board)
{
    if(r == 0 && c == 1) return "UP";
    else if(r == 1 && c == 2) return "RIGHT";
    else if(r == 1 && c == 0) return "LEFT";
    else if(r == 2 && c == 1) return "DOWN";
    
    else if(r == 0 && c == 0 && board[0][1]!='#') return "UP";
    else if(r == 0 && c == 0 && board[1][0]!='#') return "LEFT";
    else if(r == 0 && c == 2 && board[0][1]!='#') return "UP";
    else if(r == 0 && c == 2 && board[1][2]!='#') return "RIGHT";
    else if(r == 3 && c == 2 && board[1][2]!='#') return "RIGHT";
    else if(r == 3 && c == 2 && board[2][1]!='#') return "DOWN";
    else if(r == 3 && c == 0 && board[1][2]!='#') return "RIGHT";
    else if(r == 3 && c == 0 && board[2][1]!='#') return "DOWN";
    return "UP"; 
};
void next_move(int plyr, vector<string>& board) 
{
    bool iswall=false;
    for(int r=0; r<GRID_SIZE; ++r)
        for(int c=0; c<GRID_SIZE; ++c)
        {
            if(board[r][c] == 'e')
            {cout << move2exit(r, c, board) << endl; return;}
            if(board[r][c] == '#') iswall=true;
        }
    if(!iswall){cout << "UP" << endl; return;}
    else if(board[1][0]=='#' && board[0][1]!='#')
    {cout << "UP" << endl; return;}
    else if(board[2][0]=='#' && board[1][0]!='#')
    {cout << "LEFT" << endl; return;}
    else if(board[0][1]=='#' && board[1][2]!='#')
    {cout << "RIGHT" << endl; return;}
    else if(board[1][2]=='#' && board[1][2]!='#')
    {cout << "RIGHT" << endl; return;}
    else if(board[0][1]=='#' && board[1][2]=='#' && board[3][1]!='#')
    {cout << "RIGHT" << endl; return;}
    else if(board[0][1]!='#')
    {cout << "UP" << endl; return;}
    else if(board[1][2]!='#')
    {cout << "RIGHT" << endl; return;}
    else if(board[3][1]!='#')
    {cout << "DOWN" << endl; return;}
    else if(board[1][0]!='#')
    {cout << "LEFT" << endl; return;}
    
};

int main(void) {
    int player;
    vector <string> board;
    cin>>player;
    for(int i=0;i<5;i++) {
        string s;cin >> s;
        board.push_back(s);
    }
    next_move(player, board);
    return 0;
}