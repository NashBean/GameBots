//
//  BotCleanPartiallyObservable.cpp
//
//
//  Created by nash on 11/22/15.
//  Copyright 2015 iBean Software.
//  All rights reserved.
//

#include<iostream>
#include<vector>

const int MzE_MAJOR_VERSION = 1;
const int MzE_MINOR_VERSION = 0;

using namespace std;
#define GRID_SIZE  5
#define V_D 1 

bool dirt_in_view(int row, int col, vector<string>& board) 
{
    //bool result = false;
    //int r=0, c=0, gh, gw;
    //int cdr, cdc, closest=V_D*3;
    //init row
    //if(row-V_D>0) r = row-V_D;
    //if(row+V_D<GRID_SIZE) gh = row+V_D;
    //else 
    //   gh = GRID_SIZE;
    //init col
    //if(col-V_D>0) c = col-V_D;
    //if(col+V_D<GRID_SIZE) gw = col+V_D;
    //else 
    //    gw = GRID_SIZE;
    
    //    for(r=0; r<GRID_SIZE; ++r)
    //      for(c=0; c<GRID_SIZE; ++c)
    //            if(board[r][c] == 'd')
    //              if(closest > (abs(r-row)+abs(c-col)))
    //            {
    //              if(r==row && c==col) 
    //                      {cout <<"CLEAN" << endl; return true;}
    //              closest = (abs(r-row)+abs(c-col));
    //            cdr=r; cdc=c;
    //        }
    //  if(closest==(3*V_D)) return false;
    
    //LEFT, RIGHT, UP and DOWN or CLEAN   
    if(board[row][col] == 'd') {cout <<"CLEAN" << endl; return true;}
    else if(row>0 && board[row-1][col]=='d') 
    {cout <<"UP"<<endl; return true;}
    else if(row>0 && col<GRID_SIZE-1 && board[row-1][col+1]=='d') 
    {cout<<"UP"<<endl; return true;}
    else if(col<GRID_SIZE-1 && board[row][col+1]=='d')
    {cout<<"RIGHT"<<endl; return true;}
    else if(row<GRID_SIZE-1 && col<GRID_SIZE-1 && board[row+1][col+1]=='d')
    {cout<<"RIGHT"<<endl; return true;}
    else if(row<GRID_SIZE-1 && board[row+1][col]=='d')
    {cout<<"DOWN"<<endl; return true;}
    else if(row<GRID_SIZE-1 && col>0 && board[row+1][col-1]=='d')
    {cout<<"DOWN"<<endl; return true;}
    else if(col>0 && board[row][col-1]=='d')
    {cout<<"LEFT"<<endl; return true;}
    else if(row>0 && col>0 && board[row-1][col-1]=='d')
    {cout<<"LEFT"<<endl; return true;}
    /*
     cdr = cdr - row;
     cdc = cdc - col;
     if(cdr!=0 || cdc !=0)
     {
     if(cdr < 0) {
     cout<<"UP" << endl; 
     return true;
     }
     else if(cdc > 0) { 
     cout<<"RIGHT" << endl; 
     return true;
     }
     else if(cdr > 0) { 
     cout<< "DOWN" << endl; 
     return true;
     }
     else if(cdc < 0) { 
     cout<< "LEFT" << endl; 
     return true;
     }
     }
     //*/
    return false;
};

void next_move(int row, int col, vector<string>& board) 
{
    int mean;
    if(!dirt_in_view(row, col, board))
    {
        mean = (GRID_SIZE/2)+1;
        if(row < mean && col < GRID_SIZE-1)
        {cout << "RIGHT" << endl;}
        else if(row < GRID_SIZE-1 && col > mean)
        {cout << "DOWN" << endl;}
        else if(row > mean && col > V_D)
        {cout << "LEFT" << endl;}
        else {cout << "UP" << endl;}
    }
};
int main(void) {
    int pos[2];
    vector <string> board;
    cin>>pos[0]>>pos[1];
    for(int i=0;i<5;i++) {
        string s;cin >> s;
        board.push_back(s);
    }
    next_move(pos[0], pos[1], board);
    return 0;
}

