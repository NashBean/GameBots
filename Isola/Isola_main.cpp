//
//  main.cpp
//  Isola
//
//  Created by nash on 10/25/15.
//

#include <iostream>
#include <vector>
#define GRID_SIZE 7
#define GRID_MID 3

const int MzE_MAJOR_VERSION = 1;
const int MzE_MINOR_VERSION = 2;

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

struct	IsolaGrid
{
    int ref[GRID_SIZE][GRID_SIZE];
    
	IsolaGrid(){zero();};
	~IsolaGrid(){};
	
	void scan_state()
	{
    	for(int	a=0; a<GRID_SIZE; ++a) 
        	for(int	b=0; b<GRID_SIZE; ++b) 
            	std::cin >> ref[a][b];
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
    void start_game()
    {
        ref[4][0]=2;
        ref[4][GRID_SIZE-1]=1;
    };   
    void zero()
    {
        for(int	a=0; a<GRID_SIZE; ++a) 
        	for(int	b=0; b<GRID_SIZE; ++b) 
            	ref[a][b]=0;
        
    };   
    
};

struct	IsolaLogic
{
    std::vector<Position> my_moves;
    std::vector<Position> foe_moves;
	Position	me,	foe,	next_move,next_remove;
	int	my_id,	foe_id;
	
    IsolaLogic():my_moves(0),foe_moves(0){my_moves.reserve(8);foe_moves.reserve(8);};
    
	void	scan_id()
	{
       	std::cin >> my_id;
       	if(my_id==1)foe_id=2;
       	else	foe_id=1;
	};
	
	void	learn_grid(IsolaGrid&	g)
	{
        Position    temp;
        for(int	b=0; b<GRID_SIZE; ++b) 
            for(int	c=0; c<GRID_SIZE; ++c) 
            {
                if(g.ref[b][c] == my_id) 
                { me.set(b, c); }
                else if(g.ref[b][c] == foe_id) 
                { foe.set(b,c); }
            }
        for(int	b=0; b<GRID_SIZE; ++b) 
            for(int	c=0; c<GRID_SIZE; ++c) 
            {
                if(g.ref[b][c] == 0)
                {
                    
                    if(me.is_neighbour( b, c)) 
                    { temp.set(b,c);my_moves.push_back(temp);}
                    else if(foe.is_neighbour( b, c))
                    {temp.set(b,c); foe_moves.push_back(temp);}
                }
            }
	};
	
    void	proc_moves(IsolaGrid&	g)
	{
		int	mysize=my_moves.size();
		if(!mysize);//Game	Over
		else if(mysize==1)
		{
            next_move.set(my_moves[0]);
        }
		else 
		{
			int	slist[mysize],ssmall=GRID_SIZE,sbig=0,bigc=0;
			int	i;
			
			for(i=0;i<mysize;++i)
			{
				slist[i]=g.safe(my_moves[i]);
				if(slist[i]<ssmall)ssmall=slist[i];
				if(slist[i]>sbig){sbig=slist[i];}
			}
			for(i=0;i<mysize;++i)
				if(slist[i]==sbig){bigc++;}
			if(bigc==1)
			{
				for(i=0;i<mysize;++i)
					if(slist[i]==sbig)
                    {
						next_move.set(my_moves[i]);
                        break;
                    }
			}
			if(bigc==2)
            {   
                int bigmove[2];   
                bigc=0;
				for(i=0;i<mysize;++i)
					if(slist[i]==sbig)
                    {
						bigmove[bigc]=i;
                        bigc++;
                    }
                if (my_moves[bigmove[0]].find_distance(GRID_MID, GRID_MID)<my_moves[bigmove[1]].find_distance(GRID_MID, GRID_MID)) 
                {
                    next_move.set(my_moves[bigmove[0]]);
                }
                else  next_move.set(my_moves[bigmove[1]]);
                
            }
			if(bigc==3)
            {
                int bigindex[bigc];
                bigc=0;
				for(i=0;i<mysize;++i)
					if(slist[i]==sbig)
                    {
						bigindex[bigc]=i;
                        bigc++;
                    }
                if (my_moves[0].find_distance(GRID_MID, GRID_MID)<my_moves[1].find_distance(GRID_MID, GRID_MID)) 
                {
                    next_move.set(my_moves[0]);
                }
                else  if (my_moves[1].find_distance(GRID_MID, GRID_MID)<my_moves[2].find_distance(GRID_MID, GRID_MID))  
                    next_move.set(my_moves[1]);
                else
                    next_move.set(my_moves[2]);
                
            }
			else
			{
				if(my_id==1)
				{
                    for(i=0;i<mysize;++i)
                        if(slist[i]==sbig)
                        {
                        	next_move.set(my_moves[i]);
                        	break;
                        }
				}
				else
				{
                    for(i=mysize-1;i>=0;--i)
                        if(slist[i]==sbig)
                        {
                        	next_move.set(my_moves[i]);
                        	break;
                        }
				}
			}
		};
	};
    void	proc_remove(IsolaGrid&	g)
	{
		int	mysize=foe_moves.size();
		if(!mysize);//Game	Over
		else if(mysize==1)
		{
            next_remove.set(foe_moves[0]);
        }
		else 
		{
			int	slist[mysize],ssmall=GRID_SIZE,sbig=0,bigc=0;
			int	i;
			
			for(i=0;i<mysize;++i)
			{
				slist[i]=g.safe(foe_moves[i]);
				if(slist[i]<ssmall)ssmall=slist[i];
				if(slist[i]>sbig){sbig=slist[i];}
			}
			for(i=0;i<mysize;++i)
				if(slist[i]==sbig){bigc++;}
			if(bigc==1)
			{
				for(i=0;i<mysize;++i)
					if(slist[i]==sbig)
					{
						next_remove.set(foe_moves[i]);
						break;
					}
			}
			else
			{
				if(foe_id==1)
				{
                    for(i=0;i<mysize;++i)
                        if(slist[i]==sbig)
                        {
                        	next_remove.set(foe_moves[i]);
                        	break;
                        }
				}
				else
				{
                    for(i=mysize-1;i>=0;--i)
                        if(slist[i]==sbig)
                        {
                        	next_remove.set(foe_moves[i]);
                        	break;
                        }
				}
			}
		};
	};
	
	void	output_move()
	{
        std::cout << next_move.x << ' ' << next_move.y << std::endl;
        // Output the position of square to remove
        std::cout << next_remove.x << ' ' << next_remove.y << std::endl;
	};
	
};

int main(int argc, const char * argv[]) {
    
	IsolaGrid	grid;
	IsolaLogic	brain;
    
	grid.scan_state();
    //grid.start_game();
	brain.scan_id();
    //brain.my_id=1;brain.foe_id=2;
	brain.learn_grid(grid);
	brain.proc_moves(grid);
	brain.proc_remove(grid);
    brain.output_move();
    
  	return 0;
}
