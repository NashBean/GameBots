//
//  tttLogic.cpp
//
//
//  Created by nash on 10/25/15.
//  Copyright 2015 iBean Software.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include "tttLogic.h"

move tttLogic::getNextMove(tttBoard& board)
{
    move result;  
    short computer=board.ref[9],foe,value; 
    if (computer==1) foe=2;
    else    foe=1;
    
    value = checkTwoInRow(board, computer);
    if(value == -1) value = checkTwoInRow(board, foe);
    if(value == -1) value = checkForTrap(board, computer);
    
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
    
    result.setMove(value);
    return result;
}

short tttLogic::checkTwoInRow(tttBoard& board, short l) 
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

short tttLogic::checkForTrap(tttBoard& board, short l) 
{
	short result = -1;
	
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

short tttLogic::isWin(tttBoard& board)
{
	short result = 0;//returns 9 if tie
	
	if(board.ref[0]==board.ref[1] && board.ref[1]==board.ref[2]) result = board.ref[1];
	else if(board.ref[3]==board.ref[4] && board.ref[4]==board.ref[5]) result = board.ref[4];
	else if(board.ref[6]==board.ref[7] && board.ref[7]==board.ref[8]) result = board.ref[7];
	else if(board.ref[0]==board.ref[3] && board.ref[3]==board.ref[6]) result = board.ref[3];
	else if(board.ref[1]==board.ref[4] && board.ref[4]==board.ref[7]) result = board.ref[4];
	else if(board.ref[2]==board.ref[5] && board.ref[5]==board.ref[8]) result = board.ref[5];
	else if(board.ref[0]==board.ref[4] && board.ref[4]==board.ref[8]) result = board.ref[4];
	else if(board.ref[2]==board.ref[4] && board.ref[4]==board.ref[6]) result = board.ref[4];
    else 
    {
        bool blank_flag = false;
        
        for (int i=0; i<9; i++) 
        {
            if(board.ref[i] == 0) blank_flag = true;
        }
        if(!blank_flag) result = 9;//tie
    }

    return result;
	
}


