//
//  Created by nash.
//  Copyright© 2015+ iBean Software. All rights reserved.
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware


#include <iostream>
#include <vector>

const int DaB_MAJOR_VERSION = 3;
const int DaB_MINOR_VERSION = 0;

#define BaR_SIZE 5

enum Box_Value {bv_top=1,bv_right=2,bv_bottem=4,bv_left=8,bv_taken=16,bv_path=32};
enum Box_Direct {bd_north,bd_east,bd_south,bd_west};


struct BaR_Box 
{
    int row, col;//row, colom
    int val, lcount, path;//value, line_count ,no_line_enum      
    
    BaR_Box():row(0),col(0),val(0),lcount(0),path(0){};
    ~BaR_Box(){};
    BaR_Box& operator =(const BaR_Box& b)
    {
        row=b.row; col=b.col;
        val=b.val; lcount=b.lcount;
        path=b.path;
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
        lcount=0;
        if(val & bv_top) ++lcount;
        if(val & bv_right) ++lcount;
        if(val & bv_bottem) ++lcount;
        if(val & bv_left) ++lcount;
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
        return  !(val & bv_taken);
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
    int box[BaR_SIZE][BaR_SIZE];
	BaR_Grid(){zero();};
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
                box[r][c] = (bv_top | bv_bottem);
        player = 1;
    };
	void zero()
    {
        for(int	a=0; a<BaR_SIZE; ++a) 
        	for(int	b=0; b<BaR_SIZE; ++b) 
            	box[a][b]=0;
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
        for(int i=box.size()-1; i>0; --i) 
            if (box[i].row == bx.row && box[i].col == bx.col) return true; 
        return false;
    };
    
    bool contains(int r, int c)
    {
        for(int i=box.size()-1; i>0; --i) 
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
        else if(grid.box[bx.row-1][bx.col] >= 0x0f ) return false;
        abx.setPos(bx.row-1, bx.col);
        abx.setMoveVal(grid.box[bx.row-1][bx.col]);
        abx.calc();
        return true;
    };
    bool canGoEast(BaR_Grid& grid, BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.col == BaR_SIZE-1) return false;
        else if(grid.box[bx.row][bx.col+1]  >= 0x0f ) return false;
        abx.setPos(bx.row, bx.col+1);
        abx.setMoveVal(grid.box[bx.row][bx.col+1]);
        abx.calc();
        return true;
    };
    bool canGoSouth(BaR_Grid& grid, BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.row == BaR_SIZE-1) return false;
        else if(grid.box[bx.row+1][bx.col]  >= 0x0f ) return false;
        abx.setPos(bx.row+1, bx.col);
        abx.setMoveVal(grid.box[bx.row+1][bx.col]);
        abx.calc();
        return true;
    };
    bool canGoWest(BaR_Grid& grid, BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.col == 0) return false;
        else if(grid.box[bx.row][bx.col-1]  >= 0x0f ) return false;
        abx.setPos(bx.row, bx.col-1);
        abx.setMoveVal(grid.box[bx.row][bx.col-1]);
        abx.calc();
        return true;
    };
    void setGrid(BaR_Grid& grid)
    {
        if(box.size()) box.clear();
        BaR_Box tbox = BaR_Box();
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                { 	
                    tbox.row=r; tbox.col=c;
                    tbox.val=grid.box[r][c];
                    tbox.calc();
                    box.push_back(tbox);
                }
    };
    
    
    void setMoves(BaR_Grid& grid)
    {
        if(box.size()) box.clear();
        BaR_Box tbox = BaR_Box();
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if (!(grid.box[r][c]  >= 0x0f )) //0x0f = 00001111
                {   // if input grid dose not have bv_taken set
                	//if((grid.box[r][c] & bv_top) && (grid.box[r][c] & bv_bottem) 
                    //   && (grid.box[r][c] & bv_left) && (grid.box[r][c] & bv_right))
                	//{cout << "input_error"}
                	//else
                	//{
                    tbox.row=r; tbox.col=c;
                    tbox.val=grid.box[r][c];
                    tbox.calc();
                    box.push_back(tbox);
                	//}
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
};

struct BaR_Dinamics 
{
    std::vector<BaR_Boxes> boxes; // box
    int total_lines;
    
    BaR_Dinamics():boxes(0), total_lines(0){boxes.reserve(7);};
    BaR_Dinamics(std::vector<BaR_Boxes>& v):boxes(v.size())
    {   
        for (size_t i=0; i<boxes.size(); ++i) 
        {   boxes[i]=v[i];   }
    };
    ~BaR_Dinamics()
    {
        if(boxes.size()) boxes.clear();
    };
    void calc_total_lines()
    {
        total_lines=0;
        for (int i=0; i<boxes[0].box.size(); ++i)
        {
            if (boxes[0].box[i].row == 0) 
            {
                if (boxes[0].box[i].val & bv_top) ++total_lines;
            }
            if (boxes[0].box[i].col == 0) 
            {
                if (boxes[0].box[i].val & bv_left) ++total_lines;
            }
            if (boxes[0].box[i].val & bv_right) ++total_lines;
            if (boxes[0].box[i].val & bv_bottem) ++total_lines;
        }    
    };
    void init_board(BaR_Grid& grid)
    {
        BaR_Boxes tempBoxes = BaR_Boxes();
        
        // index 0 = whole grid
        tempBoxes.setGrid(grid);
        boxes.push_back(tempBoxes);
        
        // index 1 = all open boxes
        tempBoxes.setMoves(grid);
        boxes.push_back(tempBoxes);
        
        calc_total_lines();
        
        // index 2 > will connected paths
        //if(total_lines > 29)
            //find paths
            
        
        
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
    int getOptions(int v)
   //* 
    {
        int result=0;
        if(v & bv_top) ++result;
        if(v & bv_right) ++result;
        if(v & bv_bottem) ++result;
        if(v & bv_left) ++result;
        return result;
    };//*/
    
    void getBestMoveBox(BaR_Grid& grid, BaR_Box& b)
    {
        int o;
        
        for(o=0; o<moves.boxCount();++o)
            if(moves.box[o].lcount == 3)
            { b=moves.box[o]; return; }
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
        	else if(getOptions(grid.box[b.row+1][b.col]) != 2) 
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
        	else if(getOptions(grid.box[b.row][b.col+1]) != 2) 
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
        	else if(getOptions(grid.box[b.row-1][b.col]) != 2) 
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
        	else if(getOptions(grid.box[b.row][b.col-1]) != 2) 
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
            tbox=moves.box[0];
        else if(moves.box.size() == 25 && firstmoveisset)
        	nm=firstMove;
        else
            getBestMoveBox(grid, tbox);
        
        if(!firstmoveisset || moves.box.size() != 25)
        {
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
    /* rem switch
     grid.getTestInput();
     /*/
    grid.getInput();
    //*/
    // logic.setFirstMove(1,2,bd_east);
    
    logic.setNextMove2(grid, nm);
    
    std::cout << nm.row << " ";
    std::cout << nm.col << " ";
    std::cout << nm.value << std::endl;
	
    return 0;
}

