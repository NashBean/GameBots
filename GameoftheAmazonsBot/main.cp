//
//  main.cpp
//  GameoftheAmazonsBot
//
//  Created by nash on 1/10/16.
//  Copyright 2016 iBean Software. 
//  All rights reserved.
//
//Nash's Game of the Amazons Bot
// -----------------------------------------------

#include <iostream>
#include <vector>

// -----------------------------------------------

#define GRID_SIZE 10

// -----------------------------------------------
const int GotA_MAJOR_VERSION = 0;
const int GotA_MINOR_VERSION = 7;
// -----------------------------------------------
// -----------------------------------------------

struct Position 
{
    int x, y;
    Position(){x=y=0;};
    Position(int ax, int ay){x=ax;y=ay;};
    //    Position(const  Position& a){x=a.x;y=a.y;};
    ~Position(){};
    
	void set(int px, int py){x=px;y=py;}; 
	void set(Position& a){x=a.x;y=a.y;}; 
    
    int find_distance(int px, int py)
    {
        int   result=0;
        if (x>px) result+=x-px;
        else if(x<px) result+=px-x;
        if (y>py) result+=y-py;
        else if(y<py) result+=py-y;
        return result;
    };
    
	bool is_neighbour(int px, int py) 
	{
    	if (px == x  &&  py == y)
        	return false;
    	else if (abs(px-x) <= 1 && abs(py-y) <= 1)
        	return true;
    	return false;
	};
};
// -----------------------------------------------

struct	GotAGrid
{
    int ref[GRID_SIZE][GRID_SIZE];
    
	GotAGrid(){zero();};
	~GotAGrid(){};
	
	void scan_state()
	{
    	for(int	a=0; a<GRID_SIZE; ++a) 
        	for(int	b=0; b<GRID_SIZE; ++b) 
            {
            	std::cin >> ref[a][b];
            }
	};
	
	bool in_bounds(Position&	p)
	{
		if(p.x < 0 || p.y < 0)	return false;
		else if(p.x >= GRID_SIZE && p.y >= GRID_SIZE)	return false;
		return	true;
	};
    
	
	bool is_corner(Position&	p)
	{
		if(p.x == 0 && p.y == 0)	return true;
		else if(p.x == 0 && p.y == GRID_SIZE-1)	return true;
		else if(p.x == GRID_SIZE-1 && p.y == 0)	return true;
		else if(p.x == GRID_SIZE-1 && p.y == GRID_SIZE-1)	return true;
		return	false;
	};
	
	bool is_edge(Position&	p)
	{
		if(p.x == 0 || p.y == 0)	return true;
		else if(p.x == GRID_SIZE-1 || p.y == GRID_SIZE-1)	return true;
		return	false;
	};
    
    bool isOpen(Position& p)
    {
        if(in_bounds(p))if(ref[p.x][p.y]==0) return true;
        return false;
    };
    
	int safe(Position&	p)
	{
		int result=8;	
		if(is_corner(p))
		{result=result-5;}
		else if(is_edge(p))
		{result=result-3;}
		
		Position	temp;
        temp.set(p.x-1, p.y-1);
		if(in_bounds(temp))if(ref[temp.x][temp.y]!=0)--result;
        temp.set(p.x, p.y-1);
		if(in_bounds(temp))if(ref[temp.x][temp.y]!=0)--result;
        temp.set(p.x+1, p.y-1);
		if(in_bounds(temp))if(ref[temp.x][temp.y]!=0)--result;
        temp.set(p.x-1, p.y);
		if(in_bounds(temp))if(ref[temp.x][temp.y]!=0)--result;
        temp.set(p.x+1, p.y);
		if(in_bounds(temp))if(ref[temp.x][temp.y]!=0)--result;
        temp.set(p.x-1, p.y+1);
		if(in_bounds(temp))if(ref[temp.x][temp.y]!=0)--result;
        temp.set(p.x, p.y+1);
		if(in_bounds(temp))if(ref[temp.x][temp.y]!=0)--result;
        temp.set(p.x+1, p.y+1);
		if(in_bounds(temp))if(ref[temp.x][temp.y]!=0)--result;
		
		return	result;
	};
    
    void GetMoves(std::vector<Position>& p_v, Position start)
    {
        Position	temp;
        
        temp.set(start.x-1, start.y-1);// SW
        while(isOpen(temp)) 
        {
            p_v.push_back(temp);  
            temp.set(temp.x-1, temp.y-1);// SW
        }
        temp.set(start.x, start.y-1);// W
        while(isOpen(temp)) 
        {
            p_v.push_back(temp);  
            temp.set(temp.x, temp.y-1);// W
        }
        temp.set(start.x+1, start.y-1);//NW
        while(isOpen(temp)) 
        {
            p_v.push_back(temp);  
            temp.set(temp.x+1, temp.y-1);//NW
        }
        temp.set(start.x-1, start.y);//S
        while(isOpen(temp)) 
        {
            p_v.push_back(temp);  
            temp.set(temp.x-1, temp.y);//S
        }
        temp.set(start.x+1, start.y);//N
        while(isOpen(temp)) 
        {
            p_v.push_back(temp);  
            temp.set(temp.x+1, temp.y);//N
        }
        temp.set(start.x-1, start.y+1);//SE
        while(isOpen(temp)) 
        {
            p_v.push_back(temp);  
            temp.set(temp.x-1, temp.y+1);//SE
        }
        temp.set(start.x, start.y+1);//E
        while(isOpen(temp)) 
        {
            p_v.push_back(temp);  
            temp.set(temp.x, temp.y+1);//E
        }
        temp.set(start.x+1, start.y+1);//NE
        while(isOpen(temp)) 
        {
            p_v.push_back(temp);  
            temp.set(temp.x+1, temp.y+1);//NE
        }
    };

    void start_game()
    {
        ref[0][3]=1;
        ref[0][6]=1;
        ref[3][0]=1;
        ref[3][9]=1;

        ref[6][0]=2;
        ref[6][9]=2;
        ref[9][3]=2;
        ref[9][6]=2;
    };   
    void zero()
    {
        for(int	a=0; a<GRID_SIZE; ++a) 
        	for(int	b=0; b<GRID_SIZE; ++b) 
            	ref[a][b]=0;
        
    };   
    
};
// -------------------------------------------

struct GotAPlayer
{
    int id;
    //Position Q[4];
    //int dir_count[4];
    //std::vector<Position> Q_moves;
    std::vector<Position> Q;
    std::vector<int> dir_count;
    std::vector<Position> Q1_moves;
    std::vector<Position> Q2_moves;
    std::vector<Position> Q3_moves;
    std::vector<Position> Q4_moves;
    
    GotAPlayer():Q(4), dir_count(4),Q1_moves(0),Q2_moves(0),Q3_moves(0),Q4_moves(0)
    {
        
        Q1_moves.reserve(14);
        Q2_moves.reserve(14);
        Q3_moves.reserve(14);
        Q4_moves.reserve(14);
    };
    
    void GetQMoves(GotAGrid& g)
    {
        Position	temp;
        for (int i=0; i<4; ++i) 
        {
            dir_count[i] = g.safe(Q[i]);
            if(i == 0) 
            {
                g.GetMoves(Q1_moves, Q[i]);
            }
            else if(i == 1) 
            {
                g.GetMoves(Q2_moves, Q[i]);
            }
            else if(i == 2) 
            {
                g.GetMoves(Q3_moves, Q[i]);
            }
            else if(i == 3) 
            {
                g.GetMoves(Q4_moves, Q[i]);
            }
        }
    };

    
    int GetTotalMoves()
    {
        int result = 0;
        
        result += Q1_moves.size();
        result += Q2_moves.size();
        result += Q3_moves.size();
        result += Q4_moves.size();
        return result;
    };
    int GetQwithLeastDir()
    {
        int result;
        int leastdir = 9;
        
        for (int i=0; i<4; ++i) 
        {
            if(dir_count[i] < leastdir)
            {
                leastdir = dir_count[i];
                result = i;
            }
        }
        return result;
    };
    void set_only_move(Position& move_from, Position& move_to)
    {
        if(Q1_moves.size()) 
        {
            move_from.set(Q[0]);
            move_to.set(Q1_moves[0]);
        }
        else if(Q2_moves.size()) 
        {
            move_from.set(Q[1]);
            move_to.set(Q2_moves[0]);
        }
        else if(Q3_moves.size()) 
        {
            move_from.set(Q[2]);
            move_to.set(Q3_moves[0]);
        }
        else if(Q4_moves.size()) 
        {
            move_from.set(Q[3]);
            move_to.set(Q4_moves[0]);
        }
    };
    void set_least_dir_move(Position& from, Position& to)
    {
        int id = GetQwithLeastDir();
        
        from.set(Q[id]);
        if(id == 0) to.set(Q1_moves[0]);
        else if(id == 1) to.set(Q2_moves[0]);
        else if(id == 2) to.set(Q3_moves[0]);
        else if(id == 3) to.set(Q4_moves[0]);
        
    };
};
// -----------------------------------------------

struct	GotABrain
{
   // std::vector<Position> my_moves;
   // std::vector<Position> foe_moves;
    
	Position next_move_from, next_move_to, next_arrow;
    GotAPlayer my, foe; 
    int arrow_count;
    
//int	my_id,	foe_id;
	
    GotABrain():next_move_from(),next_move_to(),next_arrow(), my(), foe(){};
    
	void	scan_id()
	{
       	std::cin >> my.id;
       	if(my.id==1)foe.id=2;
       	else	foe.id=1;
	};
	
	void	learn_grid(GotAGrid&	g)
	{
        Position    temp;
        int my_qcount=0, foe_qcount=0;
        arrow_count = 0;
       
        for(int	b=0; b<GRID_SIZE; ++b) 
            for(int	c=0; c<GRID_SIZE; ++c) 
            {
                if(g.ref[b][c] == my.id) 
                { my.Q[my_qcount].set(b, c);  ++my_qcount;}
                else if(g.ref[b][c] == foe.id) 
                { foe.Q[foe_qcount].set(b,c); ++foe_qcount;}
                else if(g.ref[b][c] == -1) ++ arrow_count;
            }
        
        my.GetQMoves(g);
        foe.GetQMoves(g);
        
	};
	
    void	proc_moves(GotAGrid&	g)
	{
        int	mytotalmoves=my.GetTotalMoves();
		if(!mytotalmoves);//Game	Over
        
		else if(mytotalmoves==1)
		{
            my.set_only_move(next_move_from, next_move_to);
        }
		else 
		{
            
            //todo set from and to moves with more logic
            my.set_least_dir_move(next_move_from, next_move_to);
			
		};
	};
    void proc_arrow(GotAGrid&	g)
	{
        std::vector<Position> pap;
        pap.reserve(14);
        next_arrow.set(next_move_to);
        g.GetMoves(pap, next_arrow);
        
        for (int i=pap.size()-1; i>=0; --i) 
        {
            if(g.isOpen(pap[i]))
                next_arrow = pap[i];	
        }
        
	};
	
	void	output_move()
	{
        std::cout << next_move_from.x << ' ' << next_move_from.y << std::endl;
        std::cout << next_move_to.x << ' ' << next_move_to.y << std::endl;
        std::cout << next_arrow.x << ' ' << next_arrow.y << std::endl;
	};
	
};
// -----------------------------------------------------------------------

int main (int argc, const char * argv[])
{
	GotAGrid	grid = GotAGrid();
	GotABrain	brain = GotABrain();
/*/ 
	grid.scan_state();
	brain.scan_id();
/*/
    grid.start_game();
    brain.my.id=1;brain.foe.id=2;
//*/     
	brain.learn_grid(grid);
	brain.proc_moves(grid);
	brain.proc_arrow(grid);
    brain.output_move();

    return 0;
}

