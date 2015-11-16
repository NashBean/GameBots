//
//  main.cpp
//  TicTacToe
//
//  Created by nash on 10/25/15.
//---------------------------------------------------------------------

#include <iostream>
#include <vector>
//---------------------------------------------------------------------

struct tttBoard 
{
    //empty = 0
    //players = 1 and 2
    //  0-8 tic tac toe board
    std::vector<short> ref;
    
    tttBoard():ref(9){zero();};
    ~tttBoard(){if(ref.size()) ref.clear();};
    
    bool isEmpty(short index){return (ref[index]==0);};   
    void setRow1(short c1,short c2,short c3){ref[0]=c1;ref[1]=c2;ref[2]=c3;};   
    void setRow2(short c1,short c2,short c3){ref[3]=c1;ref[4]=c2;ref[5]=c3;};   
    void setRow3(short c1,short c2,short c3){ref[6]=c1;ref[7]=c2;ref[8]=c3;};   
    //void setTurn(short player){ref[9]=player;};   
    void zero(){for(int i=0;i<9;++i) ref[i]=0;};  
};
//---------------------------------------------------------------------

short checkTwoInRow(tttBoard& board, short l) 
{
	int result = -1;
	
	//	(board[0] boad[1] board[2]) 
	//	(board[3] boad[4] board[5]) 
	//	(board[6] boad[7] board[8]) 
	
	if(board.ref[0]==l && board.ref[1]==l && board.isEmpty(2)) result = 2;
    else if(board.ref[0]==l && board.ref[2]==l && board.isEmpty(1)) result = 1;
    else if(board.ref[1]==l && board.ref[2]==l && board.isEmpty(0)) result = 0;
    
    else if(board.ref[3]==l && board.ref[4]==l && board.isEmpty(5)) result = 5;
    else if(board.ref[3]==l && board.ref[5]==l && board.isEmpty(4)) result = 4;
    else if(board.ref[4]==l && board.ref[5]==l && board.isEmpty(3)) result = 3;
    
    else if(board.ref[6]==l && board.ref[7]==l && board.isEmpty(8)) result = 8;
    else if(board.ref[6]==l && board.ref[8]==l && board.isEmpty(7)) result = 7;
    else if(board.ref[7]==l && board.ref[8]==l && board.isEmpty(6)) result = 6;
    
    else if(board.ref[0]==l && board.ref[3]==l && board.isEmpty(6)) result = 6;
    else if(board.ref[0]==l && board.ref[6]==l && board.isEmpty(3)) result = 3;
    else if(board.ref[3]==l && board.ref[6]==l && board.isEmpty(0)) result = 0;
    
    else if(board.ref[1]==l && board.ref[4]==l && board.isEmpty(7)) result = 7;
    else if(board.ref[1]==l && board.ref[7]==l && board.isEmpty(4)) result = 4;
    else if(board.ref[4]==l && board.ref[7]==l && board.isEmpty(1)) result = 1;
    
    else if(board.ref[2]==l && board.ref[5]==l && board.isEmpty(8)) result = 8;
    else if(board.ref[2]==l && board.ref[8]==l && board.isEmpty(5)) result = 5;
    else if(board.ref[5]==l && board.ref[8]==l && board.isEmpty(2)) result = 2;
    
    else if(board.ref[0]==l && board.ref[4]==l && board.isEmpty(8)) result = 8;
    else if(board.ref[0]==l && board.ref[8]==l && board.isEmpty(4)) result = 4;
    else if(board.ref[4]==l && board.ref[8]==l && board.isEmpty(0)) result = 0;
    
    else if(board.ref[2]==l && board.ref[4]==l && board.isEmpty(6)) result = 6;
    else if(board.ref[2]==l && board.ref[6]==l && board.isEmpty(4)) result = 4;
    else if(board.ref[4]==l && board.ref[6]==l && board.isEmpty(2)) result = 2;
    
    
    return result;	
}
//---------------------------------------------------------------------

short checkForTrap(tttBoard& board, short l) 
{
	int result = -1;
	
	//	(board[0] boad[1] board[2]) 
	//	(board[3] boad[4] board[5]) 
	//	(board[6] boad[7] board[8]) 
	
	if(board.ref[0]==l && board.ref[1]==l && board.isEmpty(2)) result = 2;
    else if(board.ref[0]==l && board.ref[2]==l && board.isEmpty(1)) result = 1;
    else if(board.ref[1]==l && board.ref[2]==l && board.isEmpty(0)) result = 0;
    
    else if(board.ref[3]==l && board.ref[4]==l && board.isEmpty(5)) result = 5;
    else if(board.ref[3]==l && board.ref[5]==l && board.isEmpty(4)) result = 4;
    else if(board.ref[4]==l && board.ref[5]==l && board.isEmpty(3)) result = 3;
    
    else if(board.ref[6]==l && board.ref[7]==l && board.isEmpty(8)) result = 8;
    else if(board.ref[6]==l && board.ref[8]==l && board.isEmpty(7)) result = 7;
    else if(board.ref[7]==l && board.ref[8]==l && board.isEmpty(6)) result = 6;
    
    else if(board.ref[0]==l && board.ref[3]==l && board.isEmpty(6)) result = 6;
    else if(board.ref[0]==l && board.ref[6]==l && board.isEmpty(3)) result = 3;
    else if(board.ref[3]==l && board.ref[6]==l && board.isEmpty(0)) result = 0;
    
    else if(board.ref[1]==l && board.ref[4]==l && board.isEmpty(7)) result = 7;
    else if(board.ref[1]==l && board.ref[7]==l && board.isEmpty(4)) result = 4;
    else if(board.ref[4]==l && board.ref[7]==l && board.isEmpty(1)) result = 1;
    
    return result;
}
//---------------------------------------------------------------------

void displayMove(short index)
{
    int x,y;
    if(index<3){x=index;y=0;}
    else if(index<6){x=index-3;y=1;}   
    else if(index<9){x=index-6;y=2;}  
    std::cout << x << ' ' << y << std::endl;
};
//---------------------------------------------------------------------

int main (int argc, const char * argv[])
{
    tttBoard board; 
    short player,foe,value;
    int t1,t2,t3;
    
    std::cin.clear();
    std::cin  >> t1 >> t2 >> t3;  
    board.setRow1(t1,t2,t3);   
    std::cin  >> t1 >> t2 >> t3;  
    board.setRow2(t1,t2,t3);   
    std::cin  >> t1 >> t2 >> t3;  
    board.setRow3(t1,t2,t3);   
    std::cin  >> player;
    
    if (player==1) foe=2;
    else    foe=1;
    
    value = checkTwoInRow(board, player);
    if(value == -1) value = checkTwoInRow(board, foe);
    if(value == -1) value = checkForTrap(board, player);
    
    if(value == -1)
    {
        if(board.isEmpty(4)) value = 4;
        else if(board.isEmpty(8)) value = 8;
        else if(board.isEmpty(0)) value = 0;
        else if(board.isEmpty(5)) value = 5;
        else if(board.isEmpty(3)) value = 3;
        else if(board.isEmpty(2)) value = 2;
        else if(board.isEmpty(1)) value = 1;
        else if(board.isEmpty(7)) value = 7;
        else if(board.isEmpty(6)) value = 6;
    }

    displayMove(value);
    
    return 0;
}

