//
//  BotClean.cpp
//
//
//  Created by nash on 11/22/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//
/*
Domains Contests Rank Leaderboard Companies BETA 

NashBean

All Domains Artificial Intelligence Bot Building BotClean

Badge Progress(Details)
Points: 105.31 Rank: 3777
BotClean
by dheeraj

Problem
Submissions
Leaderboard
Discussions

Submitted 3 minutes ago
Download All Games
Opponent
Results
(Won/Tied/Lost)
Games
JudgeBot
4/0/0
View Game

Submitted Code

Language: C++
Open in editor
//*/

#include<iostream>
#include<vector>
using namespace std;
#define GRID_SIZE  5

void next_move(int row, int col, vector<string>& board) 
{
    //vector<int> d;
    int cdr, cdc, closest=GRID_SIZE*2;
    for(int r=0; r<GRID_SIZE; ++r)
        for(int c=0; c<GRID_SIZE; ++c)
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
};
                        
                        int main(void) {
                            
                            int pos[2];
                            
                            vector<string> board;
                            
                            cin>>pos[0]>>pos[1];
                            
                            for(int i=0;i<GRID_SIZE;i++) {
                                string s;cin >> s;
                                board.push_back(s);
                            }
                            next_move(pos[0], pos[1], board);
                            return 0;
                        }
