//
//  tttLogic.h
//
//
//  Created by nash on 10/25/15.
//  Copyright 2015 iBean Software.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef iBS_tttLogic_h
#define iBS_tttLogic_h
#include <vector>

struct tttBoard 
{
    //empty = 0
    //players = 1 and 2
    std::vector<short> ref;
    //  0-8 tic tac toe board
    //  9 player's turn
    
    tttBoard():ref(10){zero();};
    ~tttBoard(){if(ref.size()) ref.clear();};
    
    bool isEmpty(short index){return (ref[index]==0);};   
    void setRow1(short c1,short c2,short c3){ref[0]=c1;ref[1]=c2;ref[2]=c3;};   
    void setRow2(short c1,short c2,short c3){ref[3]=c1;ref[4]=c2;ref[5]=c3;};   
    void setRow3(short c1,short c2,short c3){ref[6]=c1;ref[7]=c2;ref[8]=c3;};   
    void setTurn(short player){ref[9]=player;};   
    void zero(){for(int i=0;i<9;++i) ref[i]=0; ref[9]=1;};  
};

struct move 
{
    short x,y;  
    
    void setMove(short index)
    {
        if(index<3){x=index;y=0;}
        else if(index<6){x=index-3;y=1;}   
        else if(index<9){x=index-6;y=2;}   
    };
};

class tttLogic 
{
public:
    move getNextMove(tttBoard& board);
    
    short checkTwoInRow(tttBoard& board, short l);
    short checkForTrap(tttBoard& board, short l);
    short isWin(tttBoard& board);
};


#endif // iBS_tttLogic_h