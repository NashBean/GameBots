//
//  Dots_and_Boxes_main1.cpp
//  Dots_and_Boxes
//
//  Created by nash on 11/16/15.
//  Copyright 2015 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <vector>

const int DaB_MAJOR_VERSION = 1;
const int DaB_MINOR_VERSION = 5;

#define BaR_SIZE 5

enum Box_Value {bv_top=1,bv_right=2,bv_bottem=4,bv_left=8,bv_taken=16};


struct next_move 
{
    int row, col, value;
    
    next_move():row(0), col(0), value(0){};
    ~next_move(){};
    
    void setMovePos(int r, int c)
    {
        row = r;
        col = c;
    };
    void setMoveVal(int v)
    {
        value = v;
    };
};

struct BaR_Grid
{
    int player;
    //* rem switch
    int box[BaR_SIZE][BaR_SIZE];
    BaR_Grid(){zero();};
    /*/
     std::vector<uint8_t,uint8_t> box;
     BaR_Grid():box(BaR_SIZE,BaR_SIZE){};
     ~BaR_Grid(){if(box.size()) box.clear();};
     //*/
    void getInput()
    {   
        int r,c;
        int temp;
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                std::cin >> temp;
                box[r][c] = temp;
            }
        std::cin >> player;
    };
    void getTestInput()
    {   
        int r,c;
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
                box[r][c] = 3;
        player = 1;
    };
    void zero()
    {
        for(int	a=0; a<BaR_SIZE; ++a) 
            for(int	b=0; b<BaR_SIZE; ++b) 
                box[a][b]=0;
    };   
};
struct BaR_Logic 
{
    std::vector<int> my_row;
    std::vector<int> my_col;
    std::vector<int> my_opt;
    
    BaR_Logic():my_row(0),my_col(0),my_opt(0){};
    ~BaR_Logic()
    {
        if(my_row.size()) my_row.clear();
        if(my_col.size()) my_col.clear();
        if(my_opt.size()) my_opt.clear();
    };
    int getOptions(int v)
    {
        int result=0;
        if(v & bv_top) ++result;
        if(v & bv_right) ++result;
        if(v & bv_bottem) ++result;
        if(v & bv_left) ++result;
        return result;
    };
    
    void setMyMoves(BaR_Grid& grid)
    {
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if ((grid.box[r][c] != (bv_top | bv_right | bv_bottem | bv_left )) 
                {
                         my_row.push_back(r);
                        my_col.push_back(c);
                        int temp = getOptions(grid.box[r][c]);
                        my_opt.push_back(temp);
                }
    };
    void setNextMove(BaR_Grid& grid, next_move& nm)
    {
        setMyMoves(grid);
        
        // set Move poition
        if (my_row.size() == 0) {std::cout<< "noMove";return;}//Game Over
        if (my_row.size() == 1) 
        {
            nm.setMovePos(my_row[0], my_col[0]);
            //nm.setMovePos(my_moves[0]);
        }
        else
        {
            int o;
            bool nopos = true;
            for(o=0; o<my_opt.size();++o)
                if(my_opt[o] == 3)
                {
                    nm.setMovePos(my_row[o], my_col[o]);
                    nopos = false;
                    o = my_opt.size();
                }
            if(nopos)
                for(o=0; o<my_opt.size();++o)
                    if(my_opt[o] == 1)
                    {
                        nm.setMovePos(my_row[o], my_col[o]);
                        nopos = false;
                        o = my_opt.size();
                    }
            if(nopos)
            {
                for(o=0; o<my_opt.size();++o)
                    if(my_opt[o] == 0)
                    {
                        nm.setMovePos(my_row[o], my_col[o]);
                        nopos = false;
                        o = my_opt.size();
                    }
            }
            if(nopos) 	nm.setMovePos(my_row[0], my_col[0]);
            
        }
        
        // set Move Value
        int temp=0;
        bool nopos=true;
        temp = grid.box[nm.row][nm.col];
        
        if(!(temp & bv_bottem))
        {
            if(getOptions(grid.box[nm.row][nm.col]) == 3)
            {
                nm.value = 2;
                nopos=false;
            }
            else if(nm.row == BaR_SIZE-1)
            {
                nm.value = 2;
                nopos=false;
            }
            else if(getOptions(grid.box[nm.row+1][nm.col]) != 2) 
            {
                nm.value = 2;
                nopos=false;
            }
        }
        if(nopos)
            if(!(temp & bv_right))
            {
                if(getOptions(grid.box[nm.row][nm.col]) == 3)
                {
                    nm.value = 1;
                    nopos=false;
                }
                else if(nm.col == BaR_SIZE-1)
                {
                    nm.value = 1;
                    nopos=false;
                }
                else if(getOptions(grid.box[nm.row][nm.col+1]) != 2) 
                {
                    nm.value = 1;
                    nopos=false;
                }
            }
        if(nopos)
            if(!(temp & bv_left))
            {
                if(getOptions(grid.box[nm.row][nm.col]) == 3)
                {
                    nm.value = 3;
                    nopos=false;
                }
                else if(nm.col == 0)
                {
                    nm.value = 3;
                    nopos=false;
                }
                else if(getOptions(grid.box[nm.row][nm.col-1]) != 2) 
                {
                    nm.value = 3;
                    nopos=false;
                }
            }
        //if(temp & bv_top) 
        if(nopos) 
            if(!(temp & bv_top))
            {
                if(getOptions(grid.box[nm.row][nm.col]) == 3)
                {
                    nm.value = 0;
                    nopos=false;
                }
                else if(nm.row == 0)
                {
                    nm.value = 0;
                    nopos=false;
                }
                else if(getOptions(grid.box[nm.row][nm.col-1]) != 2) 
                {
                    nm.value = 0;
                    nopos=false;
                }
            }
        if(nopos) 
        {
            if(!(temp & bv_bottem))
                nm.value = 2;
            else if(!(temp & bv_right))
                nm.value = 1;
            else if(!(temp & bv_top))
                nm.value = 0;
            else if(!(temp & bv_left))
                nm.value = 3;
        }
    };   
    
};


int main()
{
    BaR_Grid grid = BaR_Grid();
    BaR_Logic logic = BaR_Logic();
    next_move nm = next_move();
    /* rem switch
     grid.getTestInput();
     /*/
    grid.getInput();
    //*/
    logic.setNextMove(grid, nm);
    
    std::cout << nm.row << " ";
    std::cout << nm.col << " ";
    std::cout << nm.value << std::endl;
    
    return 0;
}
