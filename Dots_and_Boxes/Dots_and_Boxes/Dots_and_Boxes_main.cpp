//
//  Created by nash.
//  Copyright© 2015+ iBean Software. All rights reserved.
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware


#include <iostream>
#include <vector>

const int DaB_MAJOR_VERSION = 3;
const int DaB_MINOR_VERSION = 2;

#define BaR_SIZE 5

enum Box_Value {bv_top=1,bv_right=2,bv_bottem=4,bv_left=8,bv_taken=16,bv_path=32};
enum Box_Direct {bd_north,bd_east,bd_south,bd_west,bd_any};


struct BaR_Box 
{
    int row, col;//row, colom
    int val, lcount, pcount;//value, line_count ,no_line_enum      
    
    BaR_Box():row(0),col(0),val(0),lcount(0),pcount(0){};
    ~BaR_Box(){};
    BaR_Box& operator =(const BaR_Box& b)
    {
        row=b.row; col=b.col;
        val=b.val; lcount=b.lcount;
        pcount=b.pcount;
        return *this;
    };
    void setPos(int r, int c)
    {
        row = r;
        col = c;
    };
    void setMoveVal(int v)
    {
        val = v;
    };
    void calcLineCount()
    {
        lcount=pcount=0;
        if(val & bv_top) ++lcount;
        else ++pcount;
        if(val & bv_right) ++lcount;
        else ++pcount;
        if(val & bv_bottem) ++lcount;
        else ++pcount;
        if(val & bv_left) ++lcount;
        else ++pcount;
    };
    void calc()
    {
        calcLineCount();
        if (lcount == 4) 
        {
            val |= bv_taken;
        }
        else if(lcount == 2) 
        {
            val |= bv_path;
        }
    };
    bool isOpen()
    {
        return  (pcount);
    };
    bool isPath()
    {
        return  (val & bv_path);
    };
    bool isTaken()
    {
        return  (val & bv_taken);
    };
    bool northOpen()
    {
        return  !(val & bv_top);
    };
    bool eastOpen()
    {
        return !(val & bv_right);
    };
    bool southOpen()
    {
        return !(val & bv_bottem);
    };
    bool westOpen()
    {
        return !(val & bv_left);
    };
};

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
    void setMovePos(BaR_Box& p)
    {
        row = p.row;
        col = p.col;
    };
    void setMoveVal(int v)
    {
        value = v;
    };
};

struct BaR_Grid
{
    int player;
    //int box[BaR_SIZE][BaR_SIZE];
    BaR_Box b2[BaR_SIZE][BaR_SIZE];
	BaR_Grid(){};//{zero();};
    void getInput()
    {   
        int r,c;
        int temp;
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                std::cin >> temp;
              //  box[r][c] = temp;
                b2[r][c].setPos(r, c);
                b2[r][c].setMoveVal(temp);
                b2[r][c].calc();
            }
        std::cin >> player;
    };
    void getTestInput()
    {   
        int r,c;
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                b2[r][c].setPos(r, c);
                b2[r][c].setMoveVal(0);
                b2[r][c].calc();
            }
        player = 1;
    };
    void getTestInput2()
    {   
        int r,c;
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                b2[r][c].setPos(r, c);
                b2[r][c].setMoveVal(bv_top | bv_bottem);
                b2[r][c].calc();
            }
        player = 1;
    };
    void getTestInput3()
    {   
        int r,c,a=1;
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                if (a == 1) 
                {
                    b2[r][c].setPos(r, c);
                    b2[r][c].setMoveVal(bv_left | bv_top);
                    b2[r][c].calc();
                    ++a;
                }
                if (a == 2) 
                {
                    b2[r][c].setPos(r, c);
                    b2[r][c].setMoveVal(bv_top | bv_right);
                    b2[r][c].calc();
                     a = 0;
                }
                else
                {
                    b2[r][c].setPos(r, c);
                    b2[r][c].setMoveVal(bv_bottem);
                    b2[r][c].calc();
                    ++a;
                }
                b2[0][1].val |= bv_top;
                b2[0][1].val |= bv_right;
                b2[0][1].val |= bv_left;
                b2[0][1].calc();
                //b2[0][1].val |= bv_left;
                
            }
        player = 1;
    };
    void getTestInput4()
    {   
        getTestInput3();
        
        
        b2[1][0].val |= bv_left;
        b2[1][0].calc();
        b2[3][0].val |= bv_left;
        b2[3][0].calc();
        
    };
    void print_grid()
    {
        std::cout << " ";
        for(int	b=0; b<BaR_SIZE; ++b)
        {
            if(b2[0][b].val & bv_top) 
                std::cout << "_";
            else
                std::cout << " ";
            std::cout << " ";
        }
        std::cout << std::endl;
        for(int	a=0; a<BaR_SIZE; ++a)
        {
            for(int	b=0; b<BaR_SIZE; ++b)
            {
                if(b == 0) 
                {
                    if(b2[a][b].val & bv_left)
                        std::cout << "|";
                    else
                        std::cout << " ";
                }
                if(b2[a][b].val & bv_bottem)
                    std::cout << "_";
                else
                    std::cout << " ";
                if(b2[a][b].val & bv_right)
                    std::cout << "|";
                else
                    std::cout << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    };
	void zero()
    {
        for(int	a=0; a<BaR_SIZE; ++a) 
        	for(int	b=0; b<BaR_SIZE; ++b) 
            	b2[a][b].val=0;
    };   
};

struct BaR_Boxes 
{
    std::vector<BaR_Box> box; // box
    
    BaR_Boxes():box(0){box.reserve(25);};
    BaR_Boxes(std::vector<BaR_Box>& v):box(v.size())
    {   
        for (size_t i=0; i<box.size(); ++i) 
        {   box[i]=v[i];   }
    };
    ~BaR_Boxes()
    {
        if(box.size()) box.clear();
    };
    BaR_Boxes& operator=(const BaR_Boxes& x)
    {
        box.resize(x.box.size());   
        for (size_t i=0; i<box.size(); ++i) 
        {   box[i]=x.box[i];   }
        return *this;
    };
    
    bool contains(BaR_Box& bx)
    {
        for(int i=box.size()-1; i>=0; --i) 
            if (box[i].row == bx.row && box[i].col == bx.col) return true; 
        return false;
    };
    
    bool getBox(int r, int c, BaR_Box& b)
    {
        for(int i=box.size()-1; i>=0; --i) 
            if (box[i].row == r && box[i].col == c) 
            {
                b=box[i];    
                return true;
            }
        return false;
    };
    
    bool contains(int r, int c)
    {
        for(int i=box.size()-1; i>=0; --i) 
            if (box[i].row == r && box[i].col == c) return true; 
        return false;
    };
    
    void add(BaR_Box& bx)
    {
        if(!contains(bx)) box.push_back(bx);
    };
    
    int boxCount(){return box.size();};
    
    bool canGoNorth(BaR_Grid& grid, BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.row == 0) return false;
        else if(grid.b2[bx.row-1][bx.col].isOpen()) return false;
        abx = grid.b2[bx.row-1][bx.col];
        return true;
    };
    bool canGoEast(BaR_Grid& grid, BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.col == BaR_SIZE-1) return false;
        else if(grid.b2[bx.row][bx.col+1].isOpen()) return false;
        abx = grid.b2[bx.row][bx.col+1];
        return true;
    };
    bool canGoSouth(BaR_Grid& grid, BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.row == BaR_SIZE-1) return false;
        else if(grid.b2[bx.row+1][bx.col].isOpen()) return false;
        abx = grid.b2[bx.row+1][bx.col];
        return true;
    };
    bool canGoWest(BaR_Grid& grid, BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.col == 0) return false;
        else if(grid.b2[bx.row][bx.col-1].isOpen()) return false;
        abx = grid.b2[bx.row][bx.col-1];
        return true;
    };
    void setGrid(BaR_Grid& grid)
    {
        if(box.size()) box.clear();
        BaR_Box tbox = BaR_Box();
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                { 	
                    box.push_back(grid.b2[r][c]);
                }
    };
    
    
    void setMoves(BaR_Grid& grid)
    {
        if(box.size()) box.clear();
        BaR_Box tbox = BaR_Box();
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if ((grid.b2[r][c].isOpen() )) 
                {   
                    tbox=grid.b2[r][c];
                    box.push_back(tbox);
                }
    };
    
    bool pathinDirection(BaR_Grid& grid,  BaR_Box& bx, int dir)
    {
        if (bx.lcount != 2) return false;//bd_north,bd_east,bd_south,bd_west
        BaR_Box tbox= BaR_Box();
        
        if(dir == bd_north)
        {
            if(bx.northOpen() && canGoNorth(grid, bx, tbox)) 
            { add(tbox); dir = bd_north; return true; }
            if(bx.eastOpen() && canGoEast(grid, bx, tbox)) 
            { add(tbox); dir = bd_east; return true;}
            if(bx.westOpen() && canGoWest(grid, bx, tbox)) 
            { add(tbox); dir = bd_west; return true; }
        } 
        else if(dir == bd_east)
        {
            if(bx.northOpen() && canGoNorth(grid, bx, tbox)) 
            { add(tbox); dir = bd_north; return true; }
            if(bx.eastOpen() && canGoEast(grid, bx, tbox)) 
            { add(tbox); dir = bd_east; return true; }
            if(bx.southOpen() && canGoSouth(grid, bx, tbox)) 
            { add(tbox); dir = bd_south; return true; }
        } 
        else if(dir == bd_south)
        {
            if(bx.westOpen() && canGoWest(grid, bx, tbox)) 
            { add(tbox); dir = bd_west; return true; }
            if(bx.eastOpen() && canGoEast(grid, bx, tbox)) 
            { add(tbox); dir = bd_east; return true; }
            if(bx.southOpen() && canGoSouth(grid, bx, tbox)) 
            { add(tbox); dir = bd_south; return true; }
        } 
        else if(dir == bd_west)
        {
            if(bx.westOpen() && canGoWest(grid, bx, tbox)) 
            { add(tbox); dir = bd_west; return true; }
            if(bx.northOpen() && canGoNorth(grid, bx, tbox)) 
            { add(tbox); dir = bd_north; return true; }
            if(bx.southOpen() && canGoSouth(grid, bx, tbox)) 
            { add(tbox); dir = bd_south; return true; }
        } 
        
        return false;
    };
    
    void setPath(BaR_Grid& grid, BaR_Box& bx)
    {
        BaR_Box tbox[2];
        int direct[2];
        int w = 0;
        if(box.size()) box.clear();
        add(bx);
        if (bx.lcount != 2) return;//bd_north,bd_east,bd_south,bd_west
        if (bx.northOpen() && canGoNorth(grid, bx, tbox[w])) 
        { add(tbox[w]); direct[w] = bd_north; ++w; }
        if (bx.eastOpen() && canGoEast(grid, bx, tbox[w])) 
        { add(tbox[w]); direct[w] = bd_east; ++w;}
        if (bx.southOpen() && canGoSouth(grid, bx, tbox[w])) 
        { add(tbox[w]); direct[w] = bd_south; ++w;}
        if (bx.westOpen() && canGoWest(grid, bx, tbox[w])) 
        { add(tbox[w]); direct[w] = bd_west; ++w; }
        if(w==0) return;
        
        for(int i=0; i<10; ++i) 
            if (!pathinDirection(grid, tbox[0], direct[0]))   break;
        //        while(pathinDirect(grid,  tbox[0], direct[0]));
        if(w>1)
            for(int i=0; i<10; ++i) 
                if (!pathinDirection(grid, tbox[1], direct[1]))   break;
        //            while(pathinDirect(grid, tbox[1], direct[1]));
        return;
    };
    void print_boxes()
    {
        
    };
};


struct BaR_Logic 
{
    BaR_Boxes moves;
    
    BaR_Logic():moves(),firstMove()
    {firstmoveisset=false;};
    //    BaR_Logic(std::vector<position>& vp):my_moves(0){my_moves.push_back(vp);};
    ~BaR_Logic()
    {};
    
    void getBestMoveBox(BaR_Grid& grid, BaR_Box& b)
    {
        int o;
        
        for(o=0; o<moves.boxCount();++o)
        {
            if(moves.box[o].lcount == 3)
            { b=moves.box[o]; return; }
            std::cout << moves.box[o].row << " ";
            std::cout << moves.box[o].col << " ";
            std::cout << moves.box[o].val << " ";
            if (moves.box[o].val<10) 
                std::cout << " ";
            std::cout << moves.box[o].lcount << " ";
            std::cout << moves.box[o].pcount << std::endl;
        }
        for(o=0; o<moves.boxCount();++o)
            if(moves.box[o].lcount == 1)
            { b=moves.box[o]; return; }
        for(o=0; o<moves.boxCount();++o)
            if(moves.box[o].lcount == 0)
            { b=moves.box[o]; return; }
        
        std::vector<BaR_Boxes> arun;
        BaR_Boxes temp = BaR_Boxes();
        int flag=0, c;
        
        temp.setPath(grid, moves.box[0]);
        arun.push_back(temp);
        
        for(o=1; o<moves.boxCount();++o)
        {
            flag = 0;
            for(int i=0; i<arun.size(); ++i) 
                if(arun[i].contains(moves.box[o])) 
                {i=arun.size(); ++flag;}
            if(!flag)
            {
                temp.setPath(grid, moves.box[o]);
                arun.push_back(temp);
            }
        }
        c = arun[0].boxCount();
        flag = 0;
        for(int i=1; i<arun.size(); ++i) 
            if(arun[i].boxCount() < c)
            {c=arun[i].boxCount(); flag = i;}
        b=arun[flag].box[0];
        return;
    };
    
    int getBestDirection(BaR_Grid& grid, BaR_Box& b)
    {
        
        int temp=0;
        temp = b.val;
        
        if(b.southOpen())
        {
         	if(b.lcount == 3 || b.row == BaR_SIZE-1)
        	{
        		return bd_south;
        	}
        	else if(grid.b2[b.row+1][b.col].lcount != 2) 
        	{
                return bd_south;
        	}
        }
        if(b.eastOpen())
        {
         	if(b.lcount == 3 || b.col == BaR_SIZE-1)
        	{
        		return bd_east;
        	}
        	else if(grid.b2[b.row][b.col+1].lcount != 2) 
        	{
                return bd_east;
        	}
        }
        if(b.northOpen())
        {
         	if(b.lcount == 3 || b.row == 0)
        	{
        		return bd_north;
        	}
        	else if(grid.b2[b.row-1][b.col].lcount != 2) 
        	{
                return bd_north;
        	}
        }
        if(b.westOpen())
        {
         	if(b.lcount == 3 || b.col == 0)
        	{
        		return bd_west;
        	}
        	else if(grid.b2[b.row][b.col-1].lcount != 2) 
        	{
                return bd_west;
        	}
        }
        
        // add more logic
        if(b.southOpen())
            return bd_south;
        else if(b.eastOpen())
            return bd_east;
        else if(b.northOpen())
            return bd_north;
        //	else if(b.northOpen())
        return bd_west;
    };
    
    void setNextMove2(BaR_Grid& grid, next_move& nm)
    {
        moves.setMoves(grid);
        BaR_Box tbox = BaR_Box(); // temp box
        if (moves.box.size() == 0) {std::cout<< "noMove";return;}//Game Over
        // set Move poition
        else if (moves.box.size() == 1) 
        {
            tbox=moves.box[0];
            nm.setMovePos(tbox.row, tbox.col);
            nm.setMoveVal(getBestDirection(grid, tbox));
        }
      //  else if(moves.box.size() == 25 && firstmoveisset)
      //  	nm=firstMove;
        else
        {
            getBestMoveBox(grid, tbox);
            nm.setMovePos(tbox.row, tbox.col);
            nm.setMoveVal(getBestDirection(grid, tbox));
        }
    }; 
    
    void setFirstMove(int r, int c, int d)
    {
    	// r == row c == col  d == Box_Direct
    	//enum Box_Direct {bd_north,bd_east,bd_south,bd_west};
		firstMove.row = r;
		firstMove.col = c;
		firstMove.value = d;
		firstmoveisset = true;
    };
private:
	bool firstmoveisset;
    next_move firstMove;
};

int main()
{
    BaR_Grid grid = BaR_Grid();
    BaR_Logic logic = BaR_Logic();
    next_move nm = next_move();
    //* rem switch
     grid.getTestInput3();
     //grid.print_grid();
     /*/
    grid.getInput();
    //*/
//    logic.setFirstMove(2,2,bd_east);
    
    logic.setNextMove2(grid, nm);
    

    
    std::cout << nm.row << " ";
    std::cout << nm.col << " ";
    std::cout << nm.value << std::endl;
	
    return 0;
}

