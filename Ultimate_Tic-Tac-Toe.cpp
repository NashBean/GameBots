#include <iostream>
#include <string>
#include <vector>
//#include <algorithm>

using namespace std;

//
//  main.cpp
//  TicTacToe
//
//  Created by nash on 10/25/15.
//---------------------------------------------------------------------

//#include <iostream>
//#include <vector>
//---------------------------------------------------------------------
const int ULTIMAT_TTT_MAJOR_VERSION = 0;
const int ULTIMAT_TTT_MINOR_VERSION = 1;

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
    void setValue(short player, int index){ref[index]=player;};   
    void setValue(short player, int x, int y)
    {
        if(y==0){setValue(player,x);}
        else if(y==1){setValue(player,(x+3));}
        else if(y==2){setValue(player,(x+6));}  
    };
    void zero(){for(int i=0;i<9;++i) ref[i]=0;};  
    int validMoveCount(){int result=0; for(int i=0;i<9;++i) if(ref[i]=0) result++; return result;};  
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
};
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
};
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


int main()
{
    tttBoard board; 
    short player,foe,value;

    // game loop
    while (1) {
            int row;
            int col;
        int opponentRow;
        int opponentCol;
//Line 1: 2 space separated integers opponentRow and opponentCol, the opponent's last action (-1 -1 for the first turn). 
        cin >> opponentRow >> opponentCol; cin.ignore();
        int validActionCount;
//Line 2: the number of valid actions for this turn, validActionCount. 
        cin >> validActionCount; cin.ignore();
        if(opponentRow==-1) {player=1; foe=2;}
        else if(validActionCount==8){player=2; foe=1;}

        if(opponentRow!=-1) {board.setValue(foe, opponentRow, opponentCol);}

        for (int i = 0; i < validActionCount; i++) {
//Next validActionCount lines: 2 space separated integers row and col, the coordinates you're allowed to play at.
            cin >> row >> col; cin.ignore();
        }
        
        if(validActionCount == board.validMoveCount())
        {
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
        }
        else
        {
        //Line 1: 2 space separated integers row and col.
        cout << row <<" "<< col<< endl;
        }
    }
}
