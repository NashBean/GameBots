//
//  Created by nash.
//  Copyright© 2015+ iBean Software. All rights reserved.
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware


#include <iostream>
#include <vector>

const int DaB_MAJOR_VERSION = 4;
const int DaB_MINOR_VERSION = 7;

#define BaR_SIZE 5

enum Box_Value {bv_top=1,bv_right=2,bv_bottem=4,bv_left=8};
enum Box_Direct {bd_north,bd_east,bd_south,bd_west,bd_none};
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

int getOpDir(int bd)
{
    if(bd == bd_north) return bd_south;
    else if(bd == bd_east) return bd_west; 
    else if(bd == bd_south) return bd_north; 
    else if(bd == bd_west) return bd_east; 
    return bd_none;
};

struct BaR_Box 
{
    int row, col;//row, colom
    int val, lcount, pcount;//value, line_count ,no_line_enum 
    // int runID, runType;
    
    
    BaR_Box():row(0),col(0),val(0),lcount(0),pcount(0){};//,runID(0), runType(pt_Unknown){};
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
    void setVal(int v)
    {
        val = v;
        calc();
    };
    void setBox(int r, int c, int v)
    {
        setPos(r, c);
        setVal(v);
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
        /*
         if (lcount == 4) 
         {
         if(!(val & bv_taken)) 
         val |= bv_taken;
         }
         else if(lcount == 2) 
         {
         if(!(val & bv_path)) 
         val |= bv_path;
         runID = 0;
         }
         else
         runID = -1;
         //*/
    };
    bool isOpen()
    {
        return (lcount < 4);
    };
    bool isPath()
    {
        return  (lcount == 2);
    };
    bool isTaken()
    {
        return  (lcount == 4);
    };
    bool northOpen()
    {
        if(val & bv_top) return false;
        return true;
    };
    bool eastOpen()
    {
        if(val & bv_right) return false;
        return true;
    };
    bool southOpen()
    {
        if(val & bv_bottem) return false;
        return true;
    };
    bool westOpen()
    {
        if(val & bv_left) return false;
        return true;
    };
    bool isDirOpen(int bd)
    {
        if(bd == bd_north) return northOpen();
        else if(bd == bd_east) return eastOpen(); 
        else if(bd == bd_south) return southOpen(); 
        else if(bd == bd_west) return westOpen(); 
        //    else if(bd == bd_any) return (northOpen()||eastOpen()||southOpen()||westOpen());
        
        return false;  
    };
};

struct next_move 
{
    int row, col, dir;
    
    next_move():row(0), col(0), dir(0){};
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
        dir = v;
    };
};

struct BaR_Grid
{
    int player, total_lines;
    
    int boxV[BaR_SIZE][BaR_SIZE];
    int lCount[BaR_SIZE][BaR_SIZE];
    int pID[BaR_SIZE][BaR_SIZE];
    int pType[BaR_SIZE][BaR_SIZE];
    
	BaR_Grid():total_lines(0){zero();};
    
    void calc()
    {
        total_lines=0;
        int r,c;
        for (r=0; r<BaR_SIZE; ++r) 
            if (boxV[r][c] & bv_top) ++total_lines;
        
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                if (c == 0 && (boxV[r][c] & bv_left)) ++total_lines;
                if (boxV[r][c] & bv_right) ++total_lines;
                if (boxV[r][c] & bv_bottem) ++total_lines;
            }
        
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                BaR_Box tbox = BaR_Box();
                tbox.setPos(r, c);
                tbox.setVal(boxV[r][c]);
                lCount[r][c] = tbox.lcount;
            }
        
        initpathfinder();
    };
    
    // ***todo*** there is bug in this function *****************************
    void initpathfinder()
    {
        bool anywithoutID=false;
        int pathcount=1;//first path has to be > 0
        BaR_Box tbox = BaR_Box();
        
        //  anywithoutID  check loop and set pathcount
        for(int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
            {
                if((lCount[r][c] == 2 && pID[r][c] < 1)) 
                {   
                    anywithoutID = true;
                }
                else if(lCount[r][c] == 2 && pID[r][c] > 0 && pID[r][c] > pathcount)
                {
                    pathcount = pID[r][c];
                }
            }//  anywithoutID  check loop
        
        while(anywithoutID) 
        {
            anywithoutID = false;
            //  anywithoutID  check loop
            for(int r=0; r<BaR_SIZE; ++r) 
                for (int c=0; c<BaR_SIZE; ++c) 
                {
                    if((lCount[r][c] == 2 && pID[r][c] < 1)) 
                    {   
                        anywithoutID = true;
                        ++pathcount;
                        // pID[r][c] = pathcount;
                        setPath(r, c, pathcount);
                    }
                }//  anywithoutID  check loop
            
            
            //  anywithoutID  check loop without else if
            for(int r=0; r<BaR_SIZE; ++r) 
                for (int c=0; c<BaR_SIZE; ++c) 
                {
                    if((lCount[r][c] == 2 && pID[r][c] < 1)) 
                    {   
                        anywithoutID = true;
                    }
                }//  anywithoutID  check loop
        }
    };
    
    
    void getInput()
    {   
        int r,c;
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                std::cin >> boxV[r][c];
            }
        std::cin >> player;
        calc();
    };
    
    void addMove(next_move& nm)
    {
        /* need to correct
         if((b2[nm.row][nm.col].isDirOpen(nm.dir)))
         {
         boxV[nm.row][nm.col] |= nm.dir;
         }
         if ((b2[nm.row-1][nm.col].isDirOpen(getOpDir(nm.dir)))) //change to opiset dir
         {
         boxV[nm.row-1][nm.col] |= getOpDir(nm.dir);// change to opiset dir
         
         }
         //*/
    };
    
    void getTestInput()
    {   
        int r,c;
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                boxV[r][c]= 0;
            }
        player = 1;
    };
    void getTestInput2()// nomove left
    {   
        int r,c;
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                boxV[r][c] = (bv_top | bv_bottem | bv_left | bv_right);
            }
        player = 1;
    };
    void getTestInput3()//fix addMove(tmove)
    {   
        int r,c,a=1;
        next_move tmove = next_move();
        for (r=0; r<BaR_SIZE; ++r) 
            for (c=0; c<BaR_SIZE; ++c) 
            {
                if (a == 1) 
                {
                    tmove.setMovePos(r, c);
                    tmove.setMoveVal(bd_south);
                    addMove(tmove);
                    tmove.setMoveVal(bd_east);
                    addMove(tmove);
                    ++a;
                }
                if (a == 2) 
                {
                    tmove.setMovePos(r, c);
                    tmove.setMoveVal(bd_north);
                    addMove(tmove);
                    a = 0;
                }
                else
                {
                    tmove.setMovePos(r, c);
                    tmove.setMoveVal(bd_west);
                    ++a;
                }
            }
        player = 1;
    };
    void getTestInput4()
    {   
        getTestInput3();
        next_move amove = next_move();
        
        amove.setMovePos(1, 0);
        amove.setMoveVal(bd_west);
        addMove(amove);
        amove.setMovePos(3, 0);
        addMove(amove);
        
    };
    void getTestInput5()
    {   
        next_move amove = next_move();
        
        amove.setMovePos(1, 0);
        amove.setMoveVal(bd_west);
        addMove(amove);
        amove.setMovePos(3, 0);
        addMove(amove);
        
    };
    
    bool hasBestDirection(BaR_Box& b, int& dir)
    {
        //int temp=0;
        // temp = b.val;
        BaR_Box tb = BaR_Box();
        
        if(b.westOpen())
        {
            if(lCount[b.row][b.col] == 3 || b.col == 0)
            {
                dir = bd_west; return true;
            }
            if(lCount[b.row][b.col-1] != 2) 
            {
                dir = bd_west; return true;
            }
        }
        if(b.southOpen())
        {
            if(lCount[b.row][b.col] == 3 || b.row == BaR_SIZE-1)
            {
                dir = bd_south; return true;
            }
            if(lCount[b.row+1][b.col] != 2) 
            {
                dir = bd_south; return true;
            }
        }
        if(b.eastOpen())
        {
            if(lCount[b.row][b.col] == 3 || b.col == BaR_SIZE-1)
            {
                dir = bd_east; return true;
            }
            if(boxV[b.row][b.col+1] != 2) 
            {
                dir = bd_east; return true;
            }
        }
        if(b.northOpen())
        {
            if(lCount[b.row][b.col] == 3 || b.row == 0)
            {
                dir = bd_north;
            }
            if(lCount[b.row-1][b.col] != 2) 
            {
                dir = bd_north; return true;
            }
        }
        return false;
    };
    bool hasADirection(int r,int c, int& dir)
    {
        int tempV=0;
        tempV = boxV[r][c];
        BaR_Box b = BaR_Box();
        b.setPos(r, c);
        b.setVal(boxV[r][c]);
        
        if(b.westOpen())
        {
            if(lCount[b.row][b.col] == 3 || c == 0)
            {
                dir = bd_west; return true;
            }
            dir = bd_west; return true;
        }
        if(b.southOpen())
        {
            if(lCount[b.row][b.col] == 3 || b.row == BaR_SIZE-1)
            {
                dir = bd_south; return true;
            }
            dir = bd_south; return true;
        }
        if(b.eastOpen())
        {
            if(lCount[b.row][b.col] == 3 || b.col == BaR_SIZE-1)
            {
                dir = bd_east; return true;
            }
            dir = bd_east; return true;
        }
        if(b.northOpen())
        {
            if(lCount[b.row][b.col] == 3 || b.row == 0)
            {
                dir = bd_north;
            }
            dir = bd_north; return true;
        }
        return false;
    };
    void print_grid()
    {
        std::cout << " ";
        for(int	b=0; b<BaR_SIZE; ++b)
        {
            if(boxV[0][b] & bv_top) 
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
                    if(boxV[a][b] & bv_left)
                        std::cout << "|";
                    else
                        std::cout << " ";
                }
                if(boxV[a][b] & bv_bottem)
                    std::cout << "_";
                else
                    std::cout << " ";
                if(boxV[a][b] & bv_right)
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
            {
                boxV[a][b]=0;
                lCount[a][b]=0;
                pID[a][b]=-1;
                pType[a][b]=pt_Unknown;
            }
    };  
    bool canGoNorth(BaR_Box& bx)
    {
        if(bx.row == 0) return false;
        else if(lCount[bx.row-1][bx.col]>3) return false;
        
        return true;
    };
    
    bool canGoEast(BaR_Box& bx)
    {
        if(bx.col == BaR_SIZE-1) return false;
        else if(lCount[bx.row][bx.col+1]<4) return true;
        return false;
    };
    bool canGoSouth(BaR_Box& bx)
    {
        if(bx.row == BaR_SIZE-1) return false;
        else if(lCount[bx.row+1][bx.col]<4)  return true;
        return false;
    };
    bool canGoWest(BaR_Box& bx)
    {
        if(bx.col == 0) return false;
        else if(lCount[bx.row][bx.col-1]<4) return true;
        return false;
    };
    
    int countBoxesWith(int lines)
    {
        int result=0;
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if ((lCount[r][c] == lines)) 
                {   
                    ++result;
                }
        return result;
    };
    /*
     bool getBoxWith(int lines, BaR_Box& bx)
     {
     BaR_Box rbox=BaR_Box();
     for (int r=0; r<BaR_SIZE; ++r) 
     for (int c=0; c<BaR_SIZE; ++c) 
     if ((lCount[r][c] == lines)) 
     {   
     bx = b2[r][c];
     return true;
     }
     return false;
     
     };
     //*/
    int countRunID(int id)
    {
        int result = 0;
        
        for(int r=0; r<BaR_SIZE; ++r) 
            for(int c=0; c<BaR_SIZE; ++c) 
            {
                if((lCount[r][c] < 4) && pID[r][c] == id) 
                {
                    ++result;
                }
            }
        return result;
    };
    bool pathinDirection(BaR_Box& bx, int& dir)
    {
        if (bx.lcount != 2) return false;//bd_north,bd_east,bd_south,bd_west
        // BaR_Box tbox= BaR_Box();
        
        if(dir == bd_north)
        {
            if(bx.northOpen() && canGoNorth(bx)) 
            { dir = bd_north; return true; }
            if(bx.eastOpen() && canGoEast(bx)) 
            { dir = bd_east; return true;}
            if(bx.westOpen() && canGoWest(bx)) 
            { dir = bd_west; return true; }
        } 
        else if(dir == bd_east)
        {
            if(bx.northOpen() && canGoNorth(bx)) 
            { dir = bd_north; return true; }
            if(bx.eastOpen() && canGoEast(bx)) 
            { dir = bd_east; return true; }
            if(bx.southOpen() && canGoSouth(bx)) 
            { dir = bd_south; return true; }
        } 
        else if(dir == bd_south)
        {
            if(bx.westOpen() && canGoWest(bx)) 
            { dir = bd_west; return true; }
            if(bx.eastOpen() && canGoEast(bx)) 
            { dir = bd_east; return true; }
            if(bx.southOpen() && canGoSouth(bx)) 
            { dir = bd_south; return true; }
        } 
        else if(dir == bd_west)
        {
            if(bx.westOpen() && canGoWest(bx)) 
            { dir = bd_west; return true; }
            if(bx.northOpen() && canGoNorth(bx)) 
            { dir = bd_north; return true; }
            if(bx.southOpen() && canGoSouth(bx)) 
            { dir = bd_south; return true; }
        } 
        
        return false;
    };// looks good
    
    void setPath(int rw, int cl, int id)
    {
        BaR_Box sbox = BaR_Box();
        sbox.setPos(rw, cl);
        sbox.setVal(boxV[rw][cl]);
        if (lCount[rw][cl] != 2 || id<0) return;
        pID[rw][cl] = id;
        BaR_Box head = sbox;//b2[rw][cl];
        BaR_Box tail = sbox;//b2[rw][cl];
        bool headmoved = false;
        int sdirect = bd_none, direct2 = bd_none;//chage to unknown
        //bd_north,bd_east,bd_south,bd_west,bd_any,bd_none
        int runtype = pt_Unknown;
        //Path_Type {pt_Unknown, pt_ConEdge, pt_OinMiddle, pt_EdgetoEdge, pt_Corner, pt_2onEdge}
        if(head.northOpen() && canGoNorth(head)) 
        { 
            if(pID[head.row][head.col]<1) 
            {
                // pID[head.row][head.col] = id;
                head.row -= 1;
                head.setVal(boxV[head.row][head.col]);
                pID[head.row][head.col] = id;
                sdirect = bd_north;
                headmoved = true;
            }
        }
        if(!headmoved && head.eastOpen() && canGoEast(head)) 
        { 
            if(pID[head.row][head.col]<1) 
            {
                head.col += 1;
                head.setVal(boxV[head.row][head.col]);
                pID[head.row][head.col] = id;
                //pID[head.row][head.col] = id;
                sdirect = bd_east;
                headmoved = true;
            }
        }
        if(!headmoved && head.southOpen() && canGoSouth(head)) 
        { 
            if(pID[head.row][head.col]<1) 
            {
                //pID[head.row][head.col] = id;
                head.row += 1;
                head.setVal(boxV[head.row][head.col]);
                pID[head.row][head.col] = id;
                sdirect = bd_south;
                headmoved = true;
            }
        }
        if(!headmoved && head.westOpen() && canGoWest(head)) 
        { 
            if(pID[head.row][head.col]<1) 
            {
                //pID[head.row][head.col] = id;
                head.col -= 1;
                head.setVal(boxV[head.row][head.col]);
                pID[head.row][head.col] = id;
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
                if(pID[head.row][head.col]<1)
                {
                    pID[head.row][head.col] = id;
                }
                else if(pID[head.row][head.col] == id) // stops ifanant loop
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
                    if(pID[tail.row][tail.col]<1)
                    {
                        pID[tail.row][tail.col] = id;
                    }
                    else if(pID[tail.row][tail.col] == id) 
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
                if(pID[r][c] == id)    
                    pType[r][c] = runtype; 
            }
        
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
        if(!contains(bx)) 
            box.push_back(bx);
    };
    
    int boxCount(){return box.size();};
    
    
    void setGrid(BaR_Grid& grid)
    {
        if(box.size()) box.clear();
        BaR_Box tbox = BaR_Box();
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
            { 	
                tbox.setPos(r, c);
                tbox.setVal(grid.boxV[r][c]);
                box.push_back(tbox);
            }
    };
    
    
    void setMoves(BaR_Grid& grid)
    {
        if(box.size()) box.clear();
        BaR_Box tbox = BaR_Box();
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if ((grid.lCount[r][c]<4 )) 
                {   
                    tbox.setPos(r, c);
                    tbox.setVal(grid.boxV[r][c]);
                    box.push_back(tbox);
                }
    };
    
    void setliners(BaR_Grid& grid, int lines)
    {
        if(box.size()) box.clear();
        BaR_Box tbox = BaR_Box();
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if ((grid.lCount[r][c] == lines)) 
                {   
                    tbox.setPos(r, c);
                    tbox.setVal(grid.boxV[r][c]);
                    box.push_back(tbox);
                }
    };
};


struct BaR_Logic 
{
    BaR_Boxes moves;
    BaR_Grid tgrid;
    BaR_Logic():moves(), tgrid(),firstMove()
    {firstmoveisset=false;};
    ~BaR_Logic()
    {};
    // v2.7 
    int getOptions(int v)
    {
        int result=0;
        if(v & bv_top) ++result;
        if(v & bv_right) ++result;
        if(v & bv_bottem) ++result;
        if(v & bv_left) ++result;
        return result;
    };
    
    void getBestMoveBox(BaR_Grid& grid, BaR_Box& b)
    {
        int o;
        
        for(o=0; o<moves.boxCount();++o)
            if(moves.box[o].lcount == 3)
            { b=moves.box[o]; return; }
        // check for open corners
        //*
        for(o=0; o<moves.boxCount();++o)
        {
            if (moves.box[o].row == 0 && moves.box[o].col == BaR_SIZE-1) 
            {
                if(moves.box[o].lcount < 2)
                    b=moves.box[o]; return;
            }
            if (moves.box[o].row == BaR_SIZE-1 && moves.box[o].col == BaR_SIZE-1) 
            {
                if(moves.box[o].lcount < 2)
                    b=moves.box[o]; return;
            }
            if (moves.box[o].row == BaR_SIZE-1 && moves.box[o].col == 0) 
            {
                if(moves.box[o].lcount < 2)
                    b=moves.box[o]; return;
            }
            if (moves.box[o].row == 0 && moves.box[o].col == 0) 
            {
                if(moves.box[o].lcount < 2)
                    b=moves.box[o]; return;
            }
        }//*/
        
        
        for(o=0; o<moves.boxCount();++o)
            if(moves.box[o].lcount == 1)
            { b=moves.box[o]; return; }
        for(o=0; o<moves.boxCount();++o)
            if(moves.box[o].lcount == 0)
            { b=moves.box[o]; return; }
        
        // check for open corners
        /*
         for(o=0; o<moves.boxCount();++o)
         {
         if (moves.box[o].row == 0 && moves.box[o].col == BaR_SIZE-1) 
         {
         b=moves.box[o]; return;
         }
         if (moves.box[o].row == BaR_SIZE-1 && moves.box[o].col == BaR_SIZE-1) 
         {
         b=moves.box[o]; return;
         }
         if (moves.box[o].row == BaR_SIZE-1 && moves.box[o].col == 0) 
         {
         b=moves.box[o]; return;
         }
         if (moves.box[o].row == 0 && moves.box[o].col == 0) 
         {
         b=moves.box[o]; return;
         }
         }//*/
        
        int tint=0, lowest=25, loopstop=0;
        int pcount[20];
        for(o=0; o<moves.boxCount();++o)
        {
            if(moves.box[o].lcount == 2)
            {
                tint = grid.pID[moves.box[o].row][moves.box[o].col];
                ++pcount[tint];
            }
        }        
        loopstop = tint+1;
        tint=0;
        for(o=1; o<loopstop;++o)
        {
            if(pcount[o] >0 &&pcount[o] < lowest)
            {
                tint = o;
                lowest = pcount[grid.pID[moves.box[o].row][moves.box[o].col]];
            }
        }    
        for(o=0; o<moves.boxCount();++o)
        {
            if(grid.pID[moves.box[o].row][moves.box[o].col] == tint)
            {
            	b=moves.box[o]; return;
            }
        }        
       	b=moves.box[0]; 
        return;
        /* *todo* is grid counting lines
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
         //*/
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
            else if(getOptions(grid.boxV[b.row][b.col+1]) != 2) 
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
            else if(getOptions(grid.boxV[b.row+1][b.col]) != 2) 
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
            else if(getOptions(grid.boxV[b.row][b.col-1]) != 2) 
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
            else if(getOptions(grid.boxV[b.row-1][b.col]) != 2) 
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
    
    void setNextMove(BaR_Grid& grid, next_move& nm)
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
        else if(grid.total_lines < 1 && firstmoveisset)
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
    
    
    //   v2.7 above  
    void getBestMoveBox2(BaR_Grid& grid, BaR_Box& b)
    {
        
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if(grid.lCount[r][c] == 3)
                { b.setPos(r, c);b.setVal(grid.boxV[r][c]); return; }
        
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if(grid.lCount[r][c] == 1)
                { b.setPos(r, c);b.setVal(grid.boxV[r][c]); return; }
        
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if(grid.lCount[r][c] == 0)
                { b.setPos(r, c);b.setVal(grid.boxV[r][c]); return; }
        
        
        //std::vector<BaR_Boxes> arun;
        /// look for shortes run
        int pathcount = 1, path[26],shortestpath=26, shortindex=0;
        //       BaR_Boxes pathes[25];
        BaR_Boxes temp = BaR_Boxes();
        
        //*
        //   int flag=0, c;
        // pathes[pathcount].setPath(grid, moves.box[0]);
        // arun.push_back(temp);
        
        // you are here revewing code
        while ((path[pathcount] = grid.countRunID(pathcount))) 
        {
            if(path[pathcount] < shortestpath) 
            {
                shortestpath = path[pathcount];
                shortindex = pathcount;
            }
            ++pathcount;  
        }
        // sortest path loop
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if(grid.pID[r][c] == shortindex)
                { b.setPos(r, c);b.setVal(grid.boxV[r][c]); return; }
        
        // no other anser loop
        for (int r=0; r<BaR_SIZE; ++r) 
            for (int c=0; c<BaR_SIZE; ++c) 
                if(grid.lCount[r][c] < 4)
                { b.setPos(r, c);b.setVal(grid.boxV[r][c]); return; }
        
        std::clog << " move was not found"<<std::endl;
        return;
    };
    
    int getBestDirection2(BaR_Grid& grid, BaR_Box& b)
    {
        
        int tdir=0;
        tdir = 0;//grid.boxV[b.row][b.col];
        
        if(b.southOpen())
        {
         	if(grid.lCount[b.row][b.col] == 3 || b.row == BaR_SIZE-1)
        	{
        		return bd_south;
        	}
        	else if(grid.lCount[b.row+1][b.col] != 2) 
        	{
                return bd_south;
        	}
        }
        if(b.eastOpen())
        {
         	if(grid.lCount[b.row][b.col] == 3 || b.col == BaR_SIZE-1)
        	{
        		return bd_east;
        	}
        	else if(grid.lCount[b.row][b.col+1] != 2) 
        	{
                return bd_east;
        	}
        }
        if(b.northOpen())
        {
         	if(grid.lCount[b.row][b.col] == 3 || b.row == 0)
        	{
        		return bd_north;
        	}
        	else if(grid.lCount[b.row-1][b.col] != 2) 
        	{
                return bd_north;
        	}
        }
        if(b.westOpen())
        {
         	if(grid.lCount[b.row][b.col] == 3 || b.col == 0)
        	{
        		return bd_west;
        	}
        	else if(grid.lCount[b.row][b.col-1] != 2) 
        	{
                return bd_west;
        	}
        }
        
        // add more logic
        // ***todo***
        // hide this box and look for another move box
        if(grid.hasADirection(b.row, b.col, tdir))
            return tdir;
        std::clog<< "box given with no direction"<<std::endl;
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
        int tdir=bd_none;//,mCount=0;
        
        moves.setMoves(grid);
        BaR_Box tbox = BaR_Box(); // temp box
        if (moves.box.size() == 0) {std::clog<< "noMove"<<std::endl;return;}//Game Over
        // set Move poition
        else if (moves.box.size() == 1) 
        {
            tbox=moves.box[0];
            tbox.setPos(moves.box[0].row, moves.box[0].col);
            tbox.setVal(grid.boxV[tbox.row][tbox.col]);
            nm.setMovePos(tbox.row, tbox.col);
            if (!grid.hasBestDirection(tbox, tdir)) 
            {
                if (!grid.hasADirection(tbox.row, tbox.col, tdir)) {
                    std::clog<<"noMove"<<std::endl;
                }
                
            }
            nm.setMoveVal(tdir);
        }
        else if(grid.total_lines < 1 && firstmoveisset)
        {
            nm=firstMove;
        }
        else
        {
            
            getBestMoveBox2(grid, tbox);
            nm.setMovePos(tbox.row, tbox.col);
            if(!grid.hasBestDirection(tbox, tdir)) 
            {
                if(!grid.hasADirection(tbox.row, tbox.col, tdir)) 
                {
                    std::clog<<"noMove"<<std::endl;
                }
                
            }
            
            nm.setMoveVal(tdir);
        }
    }; 
    
    void setNextMove3(BaR_Grid& grid, next_move& nm)
    {
        BaR_Box tbox = BaR_Box(); // temp box
        BaR_Boxes moves2 = BaR_Boxes();
        BaR_Boxes moves3 = BaR_Boxes();
        
        moves.setMoves(grid);
        moves2.setliners(grid, 2);
        moves3.setliners(grid, 3);
        
        int tdir;
        //*  for debugging only
        //    std::cout << "Total Lines = " << grid.total_lines << std::endl;
        //    std::cout << "Total Moves = " << moves.boxCount() << std::endl;
        //std::cout << "Total with 0 Lines = " <<.boxCount() << std::endl;
        //std::cout << "Total with 1 Line = " << .boxCount() << std::endl;
        //    std::cout << "Total with 2 Lines = " << moves2.boxCount() << std::endl;
        //    std::cout << "Total with 3 Lines = " << moves3.boxCount() << std::endl;
        //*/
        
        if (moves.boxCount() == 0) {std::clog<< "noMove";return;}//Game Over
        // set Move poition
        else if(moves.boxCount() == 1) 
        {
            tbox=moves.box[0];
            nm.setMovePos(tbox.row, tbox.col);
            nm.setMoveVal(getBestDirection2(grid, tbox));
        }
        else if(moves3.boxCount())//&&NoSacNeeded(grid)   //last line
        {
            tbox=moves3.box[0];
            nm.setMovePos(tbox.row, tbox.col);
            nm.setMoveVal(getBestDirection2(grid, tbox));
        }
        else if(grid.total_lines < 1 && firstmoveisset)
        {
            nm=firstMove;
        }
        else if(moves.boxCount() == moves2.boxCount())//only paths left
        {
            //  grid.calc_all_paths();
            //  tbox=data.BoB[data.getShortestPathIndex()].box[0];
            // ----- todo  ---------
            // pf.getBestMove(grid);
            getBestMoveBox2(grid, tbox);
            nm.setMovePos(tbox.row, tbox.col);
            nm.setMoveVal(getBestDirection2(grid, tbox));
        }
        else
        {
            getBestMoveBox2(grid, tbox);
            if(grid.hasBestDirection(tbox, tdir)) 
            {
                nm.setMovePos(tbox.row, tbox.col);
                nm.setMoveVal(tdir);
            }
            else
            {
                grid.lCount[tbox.row][tbox.col] = 4;
                // grid.b2[tbox.row][tbox.col].pcount =0;
                getBestMoveBox2(grid, tbox);
                nm.setMovePos(tbox.row, tbox.col);
                nm.setMoveVal(getBestDirection2(grid, tbox));
            }
            
        }
        if (nm.row == 0 && nm.col == 0 && nm.dir == bd_south) 
        {
            for (int i=moves.boxCount()-1; i<=0; --i) 
            {
                if (!(nm.row == 0 && nm.col == 0 && nm.dir == bd_south)) 
                {
                    nm.setMovePos(moves.box[i].row, moves.box[i].col);
                    nm.setMoveVal(getBestDirection2(grid, tbox));
                }
                
            } 
        }
        
        //   if (data.BoB.size()>5) 
        //       std::cout << "Total Paths = " << (data.BoB.size()-5) << std::endl;
        
    };   
    void setNextMove4(BaR_Grid& grid, next_move& nm)
    {
        BaR_Box tbox = BaR_Box();
        int mc[5], totalmoves=0;// Moves Count
        
        for (int i=0; i<5; ++i) 
        {
            mc[i] = grid.countBoxesWith(i);
            totalmoves += mc[i];
        }
        
        int tdir;
        /*  for debugging only
         std::cout << "Total Lines = " << grid.total_lines << std::endl;
         std::cout << "Total Boxes = " << totalmoves << std::endl;
         for (int i=0; i<5; ++i) 
         {std::cout << "Total with " <<i<<" Lines = " <<mc[i] << std::endl;}
         //*/
        
        if (totalmoves == 0) {std::clog<< "noMove";return;}//Game Over
        // set Move poition
        else if(totalmoves == 1) 
        {
            for (int i=0; i<5; ++i) 
            {
                if(mc[i])
                    for (int r=0; r<BaR_SIZE; ++r) 
                    {
                        for (int c=0; c<BaR_SIZE; ++c) 
                        {
                            if(grid.pID[r][c] == i)
                            {
                                tbox.setPos(r, c);
                                tbox.setVal(grid.boxV[r][c]);
                                nm.setMovePos(r, c);
                                nm.setMoveVal(getBestDirection2(grid, tbox));
                            }
                        }
                    }
            }
            
        }
        else if(totalmoves == mc[2])//only paths left
        {//***todo***     get best path move   ******************************
            //  grid.calc_all_paths();
            //  tbox=data.BoB[data.getShortestPathIndex()].box[0];
            // ----- todo  ---------
            // pf.getBestMove(grid);
            //&&NoSacNeeded(grid)  
            getBestMoveBox(grid, tbox);
            nm.setMovePos(tbox.row, tbox.col);
            nm.setMoveVal(getBestDirection2(grid, tbox));
        }
        else if(mc[3]) //last line
        {
            for (int r=0; r<BaR_SIZE; ++r) 
                for (int c=0; c<BaR_SIZE; ++c) 
                    if(grid.lCount[r][c] == 3)
                    {
                        tbox.setPos(r, c);
                        tbox.setVal(grid.boxV[r][c]);
                        nm.setMovePos(r, c);
                        nm.setMoveVal(getBestDirection2(grid, tbox));
                    }
        }
        else if(grid.total_lines < 1 && firstmoveisset)
        {
            nm=firstMove;
        }
        else
        {
            getBestMoveBox2(grid, tbox);
            if(grid.hasBestDirection(tbox, tdir)) 
            {
                nm.setMovePos(tbox.row, tbox.col);
                nm.setMoveVal(tdir);
            }
            else
            {
                grid.lCount[tbox.row][tbox.col] = 4;
                getBestMoveBox2(grid, tbox);
                nm.setMovePos(tbox.row, tbox.col);
                nm.setMoveVal(getBestDirection2(grid, tbox));
            }
            
        }
        if (nm.row == 0 && nm.col == 0 && nm.dir == bd_south) 
        {
            for (int i=moves.boxCount()-1; i<=0; --i) 
            {
                if (!(nm.row == 0 && nm.col == 0 && nm.dir == bd_south)) 
                {
                    nm.setMovePos(moves.box[i].row, moves.box[i].col);
                    nm.setMoveVal(getBestDirection2(grid, tbox));
                }
                
            } 
        }
    };   
    
    void setFirstMove(int r, int c, int d)
    {
    	// r == row c == col  d == Box_Direct
    	//enum Box_Direct {bd_north,bd_east,bd_south,bd_west};
		firstMove.row = r;
		firstMove.col = c;
		firstMove.dir = d;
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
     getSelfInput(grid);
     grid.getTestInput();// input, input2, input3, input4
     grid.print_grid();
     /*/
    grid.getInput();
    //*/
    logic.setFirstMove(4,2,bd_north);
    
    logic.setNextMove(grid, nm);
    
    
    
    std::cout << nm.row << " ";
    std::cout << nm.col << " ";
    std::cout << nm.dir << std::endl;
    
    
    return 0;
}

