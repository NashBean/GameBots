//
//  Created by nash.
//  Copyright� 2015+ iBean Software. All rights reserved.
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware


#include <iostream>
#include <vector>

const int DaB_MAJOR_VERSION = 2;
const int DaB_MINOR_VERSION = 10;

#define BaR_SIZE 5

enum Box_Value {bv_top=1,bv_right=2,bv_bottem=4,bv_left=8,bv_taken=16,bv_path=32};
enum Box_Direct {bd_north,bd_east,bd_south,bd_west,bd_any, bd_none};
enum Path_Type {pt_Unknown, pt_ConEdge, pt_OinMiddle, pt_EdgetoEdge, pt_Corner, 
    pt_1onEdge, pt_2onEdge, pt_3onEdge, pt_4onEdge};

//   C on Edge      O in Middle    Edge to Edge        Corner
//   _   _   _       _ _ _ _ _       _ _ _ _ _         _ _ _ _
//  |_|     |_|     |_|_|_|_|_|     |_|_|_|_|_|      _|_|_|_|_|
//  |_|_|_|_|_|     |_|  _  |_|     |_|_|_|_|_|     |_|_|_|_|_|
//  |_|_|_|_|_|     |_| |_| |_|     |_|_|_|_|       |_|_|_|_|_|
//  |_|_|_|_|_|     |_|_ _ _|_|     |  _ _ _ _|     |_|_|_|_|_|
//  |_|_|_|_|_|     |_|_|_|_|_|     | |_|_|_|_|     |_|_|_|_|_|

//   2 on Edge       3 on Edge       4 on Edge       1 on Edge
//   _     _ _       _       _       _               _ _ _ _ _
//  |_|_ _|_|_|     |_|_ _ _|_|     |_|_ _ _ _|     |_|_|_|_|_|
//  |_|_|_|_|_|     |_|_|_|_|_|     |_|_|_|_|_|     |_|_|_   _
//  |_|_|_|_|_|     |_|_|_|_|_|     |_|_|_|_|_|     |_|_|_|_|_|
//  |_|_|_|_|_|     |_|_|_|_|_|     |_|_|_|_|_|     |_|_|_|_|_|
//  |_|_|_|_|_|     |_|_|_|_|_|     |_|_|_|_|_|     |_|_|_|_|_|

struct Position 
{
    int x, y;
    Position(){x=y=0;};
    Position(int ax, int ay){x=ax;y=ay;};
    Position(Position& a){x=a.x;y=a.y;};
    ~Position(){};
	void set(int px, int py){x=px;y=py;}; 
	void set(Position& a){x=a.x;y=a.y;}; 
};

//* REM Switch
struct BaR_Box 
{
    int row, col;//row, colom
    int val, lcount, pcount;//value, line_count ,no_line_enum 
    int runID, runType;
    
    
    BaR_Box():row(0),col(0),val(0),lcount(0),pcount(0),runID(0), runType(pt_Unknown){};
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
            runID = 0;
        }
        else
            runID = -1;
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

/*/
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
//*/

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
    void setMovePos(Position& p)
    {
        row = p.x;
        col = p.y;
    };
    void setMoveVal(int v)
    {
        value = v;
    };
};

//* REM Switch

struct BaR_Grid
{
    int player, total_lines;
    
    //int box[BaR_SIZE][BaR_SIZE];
    BaR_Box b2[BaR_SIZE][BaR_SIZE];
    
	BaR_Grid():total_lines(0){zero();};
    
    void calc()
    {
        total_lines=0;
        for(int	b=0; b<BaR_SIZE; ++b)
        {
            if(b2[0][b].val & bv_top) 
                ++total_lines;
        }
        for(int	a=0; a<BaR_SIZE; ++a)
        {
            for(int	b=0; b<BaR_SIZE; ++b)
            {
                if(b == 0) 
                {
                    if(b2[a][b].val & bv_left)
                        ++total_lines;
                }
                if(b2[a][b].val & bv_bottem)
                    ++total_lines;
                if(b2[a][b].val & bv_right)
                    ++total_lines;
            }
        }
// -----------ERRor somewhere in this chunk
       /*
        bool anywithoutID=0;
        int pathcount=0;
        BaR_Box tbox = BaR_Box();
        
        //  anywithoutID  check loop and set pathcount
        for(int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
            {
                if((b2[r][c].lcount == 2 && b2[r][c].runID < 1)) 
                {   
                    anywithoutID = true;
                }
                else if(b2[r][c].lcount == 2 && b2[r][c].runID > 0)
                {
                    if(b2[r][c].runID > pathcount) pathcount = b2[r][c].runID;
                }
            }//  anywithoutID  check loop
        
        while(anywithoutID) 
        {
            anywithoutID = false;
            //  anywithoutID  check loop
            for(int r=0; r<BaR_SIZE; ++r) 
                for (int c=0; c<BaR_SIZE; ++c) 
                {
                    if((b2[r][c].lcount == 2 && b2[r][c].runID < 1)) 
                    {   
                        anywithoutID = true;
                        ++pathcount;
                        b2[r][c].runID = pathcount;
                        setPath(b2[r][c], pathcount);
                    }
                }//  anywithoutID  check loop
            
            
            //  anywithoutID  check loop without else if
            for(int r=0; r<BaR_SIZE; ++r) 
                for (int c=0; c<BaR_SIZE; ++c) 
                {
                    if((b2[r][c].lcount == 2 && b2[r][c].runID < 1)) 
                    {   
                        anywithoutID = true;
                    }
                }//  anywithoutID  check loop
        }
//*/
        
        
    };
    void init(BaR_Grid& grid)
    {
    };

    
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
                total_lines+=b2[r][c].lcount; 
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
                b2[r][c].setMoveVal(bv_top | bv_bottem | bv_left | bv_right);
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
                    ++a;
                }
                if (a == 2) 
                {
                    b2[r][c].setPos(r, c);
                    b2[r][c].setMoveVal(bv_top | bv_right);
                    a = 0;
                }
                else
                {
                    b2[r][c].setPos(r, c);
                    b2[r][c].setMoveVal(bv_bottem);
                    ++a;
                }
                // b2[0][1].val |= bv_top;
                // b2[0][1].val |= bv_right;
                // b2[0][1].val |= bv_left;
                //b2[0][1].val |= bv_left;
                
            }
        player = 1;
    };
    void getTestInput4()
    {   
        getTestInput3();
        
        
        b2[1][0].val |= bv_left;
        b2[3][0].val |= bv_left;
        
    };
    void getTestInput5()
    {   
        
        
        
        b2[1][0].val |= bv_left;
        b2[3][0].val |= bv_left;
        
    };
    
    bool hasBestDirection(BaR_Box& b, int& dir)
    {
        int temp=0;
        temp = b.val;
        BaR_Box tb = BaR_Box();
        
        if(b.westOpen())
        {
            if(b.lcount == 3 || b.col == 0)
            {
                dir = bd_west; return true;
            }
            if(b2[b.row][b.col-1].lcount != 2) 
            {
                dir = bd_west; return true;
            }
        }
        if(b.southOpen())
        {
            if(b.lcount == 3 || b.row == BaR_SIZE-1)
            {
                dir = bd_south; return true;
            }
            if(b2[b.row+1][b.col].lcount != 2) 
            {
                dir = bd_south; return true;
            }
        }
        if(b.eastOpen())
        {
            if(b.lcount == 3 || b.col == BaR_SIZE-1)
            {
                dir = bd_east; return true;
            }
            if(b2[b.row][b.col+1].lcount != 2) 
            {
                dir = bd_east; return true;
            }
        }
        if(b.northOpen())
        {
            if(b.lcount == 3 || b.row == 0)
            {
                dir = bd_north;
            }
            if(b2[b.row-1][b.col].lcount != 2) 
            {
                dir = bd_north; return true;
            }
        }
        return false;
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
    bool canGoNorth(BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.row == 0) return false;
        else if(b2[bx.row-1][bx.col].isOpen()) return false;
        abx = b2[bx.row-1][bx.col];
        return true;
        
    };
    bool canGoEast(BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.col == BaR_SIZE-1) return false;
        else if(b2[bx.row][bx.col+1].isOpen()) return false;
        abx = b2[bx.row][bx.col+1];
        return true;
    };
    bool canGoSouth(BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.row == BaR_SIZE-1) return false;
        else if(b2[bx.row+1][bx.col].isOpen()) return false;
        abx = b2[bx.row+1][bx.col];
        return true;
    };
    bool canGoWest(BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.col == 0) return false;
        else if(b2[bx.row][bx.col-1].isOpen())return false; 
        abx = b2[bx.row][bx.col-1];
        return true;
    };
    int countRunID(int id)
    {
        int result = 0;
        
        for(int r=0; r<BaR_SIZE; ++r) 
            for(int c=0; c<BaR_SIZE; ++c) 
            {
                if(b2[r][c].isOpen() && b2[r][c].runID == id) 
                {
                    ++result;
                }
            }
        return result;
    };
    bool pathinDirection(BaR_Box& bx, int& dir)
    {
        if (bx.lcount != 2) return false;//bd_north,bd_east,bd_south,bd_west
        BaR_Box tbox= BaR_Box();
        
        if(dir == bd_north)
        {
            if(bx.northOpen() && canGoNorth(bx, tbox)) 
            { dir = bd_north; return true; }
            if(bx.eastOpen() && canGoEast(bx, tbox)) 
            { dir = bd_east; return true;}
            if(bx.westOpen() && canGoWest(bx, tbox)) 
            { dir = bd_west; return true; }
        } 
        else if(dir == bd_east)
        {
            if(bx.northOpen() && canGoNorth(bx, tbox)) 
            { dir = bd_north; return true; }
            if(bx.eastOpen() && canGoEast(bx, tbox)) 
            { dir = bd_east; return true; }
            if(bx.southOpen() && canGoSouth(bx, tbox)) 
            { dir = bd_south; return true; }
        } 
        else if(dir == bd_south)
        {
            if(bx.westOpen() && canGoWest(bx, tbox)) 
            { dir = bd_west; return true; }
            if(bx.eastOpen() && canGoEast(bx, tbox)) 
            { dir = bd_east; return true; }
            if(bx.southOpen() && canGoSouth(bx, tbox)) 
            { dir = bd_south; return true; }
        } 
        else if(dir == bd_west)
        {
            if(bx.westOpen() && canGoWest(bx, tbox)) 
            { dir = bd_west; return true; }
            if(bx.northOpen() && canGoNorth(bx, tbox)) 
            { dir = bd_north; return true; }
            if(bx.southOpen() && canGoSouth(bx, tbox)) 
            { dir = bd_south; return true; }
        } 
        
        return false;
    };
    
    void setPath(BaR_Box& sbox, int id)
    {
        if (b2[sbox.row][sbox.col].lcount != 2 || id<1) return;
        b2[sbox.row][sbox.col].runID = id;
        BaR_Box head = b2[sbox.row][sbox.col];
        BaR_Box tail = b2[sbox.row][sbox.col];
        bool headmoved = false;
        int sdirect = bd_none, direct2 = bd_none;//chage to unknown
        //bd_north,bd_east,bd_south,bd_west,bd_any,bd_none
        int runtype = pt_Unknown;
        //Path_Type {pt_Unknown, pt_ConEdge, pt_OinMiddle, pt_EdgetoEdge, pt_Corner, pt_2onEdge}
        if(head.northOpen() && canGoNorth(tail, head)) 
        { 
            if(head.runID<1) 
            {
                head.runID = id;
                sdirect = bd_north;
                headmoved = true;
            }
        }
        if(!headmoved && head.eastOpen() && canGoEast(tail, head)) 
        { 
            if(head.runID<1) 
            {
                head.runID = id;
                sdirect = bd_east;
                headmoved = true;
            }
        }
        if(!headmoved && head.southOpen() && canGoSouth(tail, head)) 
        { 
            if(head.runID<1) 
            {
                head.runID = id;
                sdirect = bd_south;
                headmoved = true;
            }
        }
        if(!headmoved && head.westOpen() && canGoWest(tail, head)) 
        { 
            if(head.runID<1) 
            {
                head.runID = id;
                sdirect = bd_west;
                headmoved = true;
            }
        }
        if (!headmoved) return;
        direct2 = sdirect; // save sdirect for tail
        while (headmoved) // head loop
        {                                      
            if(!pathinDirection(head, direct2))  headmoved = false;
            else
            {
                if(head.runID<1)
                {
                    head.runID = id;
                }
                else if(head.runID == id) // stops ifanant loop
                {
                    runtype = pt_OinMiddle;
                    headmoved = false;
                }
                else
                {       
                    headmoved = false;
                    std::clog << "2 runs crossed";
                }
                
            }
        }
        //todo add stop tail if runtype = OinMiddle
        //else
        if(runtype == pt_OinMiddle || runtype != pt_Corner)
        {
            setRunType(id, runtype);
        }
        else
        {
            headmoved = true; //reuse for tail
            while (headmoved) // tail loop
            {                                     
                if(!pathinDirection(tail, sdirect))  headmoved = false;
                else
                {
                    if(tail.runID<1)
                    {
                        tail.runID = id;
                    }
                    else if(tail.runID == id) 
                    {
                        headmoved = false;
                    }
                    else
                    {       
                        headmoved = false;
                        std::clog << "2 runs crossed";
                    }
                    
                }
            }//tail loop
        } 
        return;
    };
private:
    void setRunType(int id, int runtype)
    {
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
            {
                if(b2[r][c].runID == id)    
                    b2[r][c].runType = runtype; 
            }
        
    };
    
};

/*/

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
//*/
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
        abx.setPos(bx.row-1, bx.col);
        abx.setMoveVal(grid.b2[bx.row-1][bx.col].val);
        abx.calc();
        return true;
    };
    bool canGoEast(BaR_Grid& grid, BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.col == BaR_SIZE-1) return false;
        else if(grid.b2[bx.row][bx.col+1].isOpen()) return false;
        abx.setPos(bx.row, bx.col+1);
        abx.setMoveVal(grid.b2[bx.row][bx.col+1].val);
        abx.calc();
        return true;
    };
    bool canGoSouth(BaR_Grid& grid, BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.row == BaR_SIZE-1) return false;
        else if(grid.b2[bx.row+1][bx.col].isOpen()) return false;
        abx.setPos(bx.row+1, bx.col);
        abx.setMoveVal(grid.b2[bx.row+1][bx.col].val);
        abx.calc();
        return true;
    };
    bool canGoWest(BaR_Grid& grid, BaR_Box& bx, BaR_Box& abx)
    {
        if(bx.col == 0) return false;
        else if(grid.b2[bx.row][bx.col-1].isOpen()) return false;
        abx.setPos(bx.row, bx.col-1);
        abx.setMoveVal(grid.b2[bx.row][bx.col-1].val);
        abx.calc();
        return true;
    };
    
    void setMoves(BaR_Grid& grid)
    {
        if(box.size()) box.clear();
        BaR_Box tbox = BaR_Box();
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if (!(grid.b2[r][c].isOpen() )) 
                {   // if input grid dose not have bv_taken set
                	//if((grid.b2[r][c] & bv_top) && (grid.b2[r][c] & bv_bottem) 
                    //   && (grid.b2[r][c] & bv_left) && (grid.b2[r][c] & bv_right))
                	//{cout << "input_error"}
                	//else
                	//{
                    tbox.row=r; tbox.col=c;
                    tbox.val=grid.b2[r][c].val;
                    tbox.calc();
                    box.push_back(tbox);
                	//}
                }
    };
    
    bool pathinDirect(BaR_Grid& grid,  BaR_Box& bx, int dir)
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
            if (!pathinDirect(grid, tbox[0], direct[0]))   break;
        //        while(pathinDirect(grid,  tbox[0], direct[0]));
        if(w>1)
            for(int i=0; i<10; ++i) 
                if (!pathinDirect(grid, tbox[1], direct[1]))   break;
        //            while(pathinDirect(grid, tbox[1], direct[1]));
        return;
    };
};

struct BaR_Logic 
{
    std::vector<int> my_row;
    std::vector<int> my_col;
    std::vector<int> my_opt;
    BaR_Boxes moves;
    
    BaR_Logic():my_row(0),my_col(0),my_opt(0),moves(),firstMove()
    {firstmoveisset=false;};
    //    BaR_Logic(std::vector<position>& vp):my_moves(0){my_moves.push_back(vp);};
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
        Position p;
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if (!(grid.b2[r][c].isOpen())) //& bv_taken)) 
                {
                	if((grid.b2[r][c].val & bv_top) && (grid.b2[r][c].val & bv_bottem) 
                       && (grid.b2[r][c].val & bv_left) && (grid.b2[r][c].val & bv_right))
                	{p.x=r; p.y=c;}
                	else
                	{
                        my_row.push_back(r);
                        my_col.push_back(c);
                        int temp = getOptions(grid.b2[r][c].val);
                        my_opt.push_back(temp);
                	}
                    // p.set(r, c);
                    // my_moves.push_back(p);
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
        temp = grid.b2[nm.row][nm.col].val;
        
        if(!(temp & bv_bottem))
        {
         	if(getOptions(grid.b2[nm.row][nm.col].val) == 3)
        	{
        		nm.value = 2;
        		nopos=false;
        	}
       		else if(nm.row == BaR_SIZE-1)
        	{
                nm.value = 2;
                nopos=false;
        	}
        	else if(getOptions(grid.b2[nm.row+1][nm.col].val) != 2) 
        	{
                nm.value = 2;
                nopos=false;
        	}
        }
        if(nopos)
         	if(!(temp & bv_right))
        	{
        		if(getOptions(grid.b2[nm.row][nm.col].val) == 3)
        		{
        			nm.value = 1;
        			nopos=false;
        		}
        		else if(nm.col == BaR_SIZE-1)
        		{
        			nm.value = 1;
        			nopos=false;
        		}
        		else if(getOptions(grid.b2[nm.row][nm.col+1].val) != 2) 
        		{
        			nm.value = 1;
        			nopos=false;
        		}
        	}
        if(nopos)
        	if(!(temp & bv_left))
        	{
        		if(getOptions(grid.b2[nm.row][nm.col].val) == 3)
        		{
        			nm.value = 3;
        			nopos=false;
        		}
        		else if(nm.col == 0)
        		{
        			nm.value = 3;
        			nopos=false;
        		}
        		else if(getOptions(grid.b2[nm.row][nm.col-1].val) != 2) 
        		{
        			nm.value = 3;
        			nopos=false;
        		}
        	}
        //if(temp & bv_top) 
        if(nopos) 
        	if(!(temp & bv_top))
        	{
        		if(getOptions(grid.b2[nm.row][nm.col].val) == 3)
        		{
        			nm.value = 0;
        			nopos=false;
        		}
        		else if(nm.row == 0)
        		{
        			nm.value = 0;
        			nopos=false;
        		}
        		else if(getOptions(grid.b2[nm.row][nm.col-1].val) != 2) 
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
        
        if(b.eastOpen())
        {
         	if(b.lcount == 3 || b.col == BaR_SIZE-1)
        	{
        		return bd_east;
        	}
        	else if(getOptions(grid.b2[b.row][b.col+1].val) != 2) 
        	{
                return bd_east;
        	}
        }
        if(b.southOpen())
        {
         	if(b.lcount == 3 || b.row == BaR_SIZE-1)
        	{
        		return bd_south;
        	}
        	else if(getOptions(grid.b2[b.row+1][b.col].val) != 2) 
        	{
                return bd_south;
        	}
        }
        if(b.westOpen())
        {
         	if(b.lcount == 3 || b.col == 0)
        	{
        		return bd_west;
        	}
        	else if(getOptions(grid.b2[b.row][b.col-1].val) != 2) 
        	{
                return bd_west;
        	}
        }
        if(b.northOpen())
        {
         	if(b.lcount == 3 || b.row == 0)
        	{
        		return bd_north;
        	}
        	else if(getOptions(grid.b2[b.row-1][b.col].val) != 2) 
        	{
                return bd_north;
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
        grid.calc();
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
        else if(grid.total_lines < 2 && firstmoveisset)
        {
        	nm=firstMove;
        }
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
    /* rem switch
     grid.getTestInput3();
     /*/
    grid.getInput();
    //*/
     logic.setFirstMove(4,2,bd_north);
    logic.setNextMove2(grid, nm);
    
    std::cout << nm.row << " ";
    std::cout << nm.col << " ";
    std::cout << nm.value << std::endl;
	
    return 0;
}

