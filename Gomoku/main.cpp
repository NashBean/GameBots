//
//  main.cpp
//  Gomoku
//
//  Created by nash on 5/8/16.
//  Copyright 2016 iBean Software. All rights reserved.
//  http://nashbean.github.io/index.html

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <utility>
#include <vector>

#define N 10

using namespace std;
#define GRID_COL N
#define GRID_ROW N
const int Gmk_MAJOR_VERSION = 1;
const int Gmk_MINOR_VERSION = 7;// last sumitted version for contest

// -----------------------------------------------
// CONVERTED FROM ANOTHER GAME BOT
// -----------------------------------------------

struct Position 
{
    int x, y;
    Position(){x=y=0;};
    Position(int ax, int ay){x=ax;y=ay;};
    //    Position(const  Position& a){x=a.x;y=a.y;};
    ~Position(){};
    
    bool operator ==(Position& other)
    {
        if(x == other.x && y == other.y)
            return true;
        return false;
    };
    
    bool operator !=(Position& other)
    {
        if(x == other.x && y == other.y)
            return false;
        return true;
    };
    
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
    
	int is_neighbour(int px, int py) 
	{
    	if (px == x  &&  py == y)
        	return false;
    	else if (abs(px-x) == 1 && abs(py-y) == 0)
        	return 2;
    	else if (abs(px-x) == 0 && abs(py-y) == 1)
        	return 1;
    	else if (((px-x) > 0 && (py-y) > 0) ||
                 ((px-x) < 0 && (py-y) < 0))
        	return 3;
    	else if (((px-x) > 0 && (py-y) < 0) ||
                 ((px-x) < 0 && (py-y) > 0))
        	return 4;
        else return 0;
        
    	return false;
	};
    
	int is_neighbour(Position& p)
    {
        return is_neighbour(p.x, p.y);
    };
    
};
// -----------------------------------------------

struct runNrow 
{
    std::vector<Position> ref;
    int dir;//0=null 1=north_south 2=east_west 3=back_slash 4=foward_slash
    int is_posible;
    
    runNrow():ref(0){ref.reserve(5);dir=0;is_posible=true;};
    runNrow(Position& p1, Position& p2):ref(2)
    {
        ref[0] = p1; ref[1] = p2;
        
        if(p1.x == p2.x && p1.y == p2.y)  dir = 0; 
        else if(p1.x == p2.x)  dir = 1; //1=north_south
        else if(p1.y == p2.y) dir = 2;//2=east_west 
        else if(p1.x > p2.x && p1.y > p2.y) dir = 3; // 3=back_slash
        else if(p1.x < p2.x && p1.y < p2.y) dir = 3; // 3=back_slash
        else if(p1.x < p2.x && p1.y > p2.y) dir = 4; // 4=foward_slash
        else if(p1.x > p2.x && p1.y < p2.y) dir = 4; // 4=foward_slash
        else dir=0;
        
    };
    ~runNrow(){ref.clear();};
    
    bool operator ==(runNrow& other)
    {
        if(ref.size() != other.ref.size()) return false;
        for (int i=0; i<ref.size(); ++i) 
        {
            if (ref[i] != other.ref[i]) return false;   
        }
        return true;
    };
    
    bool operator !=(runNrow& other)
    {
        if(ref.size() != other.ref.size()) return true;
        for (int i=0; i<ref.size(); ++i) 
        {
            if (ref[i] != other.ref[i]) return true;   
        }
        return false;
    };
    
	void set(std::vector<Position>& nv)
    {
        ref.resize(nv.size());
        for (int i=0; i<ref.size(); ++i) 
        {
            ref[i] = nv[i];   
        }
    }; 
    
    void addPosition(Position nP)
    {
        ref.push_back(nP);
    };
};
// -----------------------------------------------

struct	GotAGrid
{
    int ref[GRID_COL][GRID_ROW];
    
	GotAGrid(){zero();};
	~GotAGrid(){};
	
	void scan_state()
	{
    	for(int	a=0; a<GRID_ROW; ++a) 
        	for(int	b=0; b<GRID_COL; ++b) 
            {
            	std::cin >> ref[a][b];
            }
	};
	
	bool in_bounds(Position&	p)
	{
		if(p.x < 0 || p.y < 0)	return false;
		else if(p.x >= GRID_COL || p.y >= GRID_ROW)	return false;
		return	true;
	};
    
	
	bool is_corner(Position&	p)
	{
		if(p.x == 0 && p.y == 0)	return true;
		else if(p.x == 0 && p.y == GRID_ROW-1)	return true;
		else if(p.x == GRID_COL-1 && p.y == 0)	return true;
		else if(p.x == GRID_COL-1 && p.y == GRID_ROW-1)	return true;
		return	false;
	};
	
	bool is_edge(Position&	p)
	{
		if(p.x == 0 || p.y == 0)	return true;
		else if(p.x == GRID_COL-1 || p.y == GRID_ROW-1)	return true;
		return	false;
	};
    
    bool isOpen(Position& p)
    {
        if(in_bounds(p))
            if(ref[p.x][p.y]==0) return true;
        return false;
    };
    
    int north_south_posible(Position& point,int pid)
    {
        Position temp = Position(point);
        bool run_flag=true;
        int spots=1, have=0;
        
        do
        {
            temp.x = temp.x + 1;
            if(temp.x>=GRID_ROW) run_flag = false; 
            else if(isOpen(temp)) spots++;
            else if(ref[temp.x][temp.y] == pid) 
            {
                have++;
                spots++;
            }
            else run_flag = false; 
        }while (run_flag);
        
        temp.set(point);
        run_flag = true;
         
        do{
            temp.x = temp.x - 1;
            if(temp.x<0) run_flag = false; 
            else if(isOpen(temp)) spots++;
            else if(ref[temp.x][temp.y] == pid) 
            {
                have++;
                spots++;
            }
            else run_flag = false; 
            
        }while (run_flag);
        
        if(spots >= 5) return have;
        
        return false;
    };
    
    int east_west_posible(Position& point,int pid)
    {
        Position temp = Position(point);
        bool run_flag=true;
        int spots=1, have=0;
        
         
        do{
            temp.y = temp.y + 1;
            if(temp.y>=GRID_COL) run_flag = false; 
            else if(isOpen(temp)) spots++;
            else if(ref[temp.x][temp.y] == pid) 
            {
                have++;
                spots++;
            }
            else run_flag = false; 
        }while (run_flag);
        
        temp.set(point);
        run_flag = true;
         
        do{
            temp.y = temp.y - 1;
            if(temp.y<0) run_flag = false; 
            else if(isOpen(temp)) spots++;
            else if(ref[temp.x][temp.y] == pid) 
            {
                have++;
                spots++;
            }
            else run_flag = false; 
            
        }while (run_flag);
        
        if(spots >= 5) return have;
        
        return false;
    };
    
    int back_slash_posible(Position& point,int pid)
    {
        Position temp = Position(point);
        bool run_flag=true;
        int spots=1, have=0;
        
        if(ref[temp.x][temp.y] == pid) ++have;
        
        do{
            temp.x = temp.x + 1;
            temp.y = temp.y + 1;
            if(temp.y>=GRID_COL || temp.x>=GRID_ROW) run_flag = false; 
            else if(isOpen(temp)) spots++;
            else if(ref[temp.x][temp.y] == pid) 
            {
                have++;
                spots++;
            }
            else run_flag = false; 
        }while (run_flag);
        
        temp.set(point);
        run_flag = true;
        do{
            temp.x = temp.x - 1;
            temp.y = temp.y - 1;
            if(temp.y<=0 || temp.x <=0) run_flag = false; 
            else if(isOpen(temp)) spots++;
            else if(ref[temp.x][temp.y] == pid) 
            {
                have++;
                spots++;
            }
            else run_flag = false; 
            
        }while (run_flag);
        
        if(spots >= 5) return have;
        
        return 0;
    };
    
    int foward_slash_posible(Position& point,int pid)
    {
        Position temp = Position(point);
        bool run_flag=true;
        int spots=1, have=0;
        
        do{
            temp.x = temp.x - 1;
            temp.y = temp.y + 1;
            if(temp.y>=GRID_COL || temp.x<0) run_flag = false; 
            else if(isOpen(temp)) spots++;
            else if(ref[temp.x][temp.y] == pid)
            {
                have++;
                spots++;
            }
            else run_flag = false; 
        }while (run_flag);
        
        temp.set(point);
        run_flag = true;
        do{
            temp.x = temp.x + 1;
            temp.y = temp.y - 1;
            if(temp.y>=GRID_COL || temp.x <0) run_flag = false; 
            else if(isOpen(temp)) spots++;
            else if(ref[temp.x][temp.y] == pid) 
            {
                have++;
                spots++;
            }
            else run_flag = false; 
            
        }while (run_flag);
        
        if(spots >= 5) return have;
        
        return false;
    };
    
    void start_game()
    {
        ref[5][5]=1;
        ref[6][6]=1;
        ref[7][7]=1;
        ref[8][8]=1;
        ref[5][4]=1;
        ref[6][4]=1;
        //ref[3][9]=1;
        
        ref[4][5]=2;
        ref[7][3]=2;
        ref[4][4]=2;
        ref[9][9]=2;
        ref[4][3]=2;
        ref[4][6]=2;

        //ref[9][3]=2;
        //ref[9][6]=2;
    };   
    void zero()
    {
        for(int	a=0; a<GRID_COL; ++a) 
        	for(int	b=0; b<GRID_ROW; ++b) 
            	ref[a][b]=0;
        
    };   
    //------------------------------------------
    //-------------------
    // Gomoku add ons
    //-------------------
    
};
// -------------------------------------------

struct GotAPlayer
{
    int id;
    std::vector<Position> Q; //open spots
    std::vector<int> dir_count;
    std::vector<Position> Q1; //past moves
    std::vector<runNrow> R2;// 2 in row
    std::vector<runNrow> R3;// 3 in row
    std::vector<runNrow> R4;// 4 in row
    std::vector<runNrow> R5;// 5 or more in row
    
    GotAPlayer():Q(0), Q1(0),R2(0),R3(0),R4(0),R5(0)
    {
        Q.reserve(20);
        Q1.reserve(20);
        R2.reserve(4);
        R3.reserve(4);
        R4.reserve(4);
        R5.reserve(4);
    };
    
    void print()
    {
        int i;
        
        cout << "Q1:  ";
        for (i=0; i<Q1.size(); ++i) 
        {
           cout << Q1[i].x << ' ' << Q1[i].y << endl; 
        }
        cout << endl;

        cout << "R2:  ";
        for (i=0; i<R2.size(); ++i) 
        {
            if (R2[i].is_posible) 
                cout << "posible dir: ";
            else
                cout << "NOT a posible dir: ";

            cout <<i<< " Direction: " << R2[i].dir << endl;
            for (int i2=0; i2<R2[i].ref.size(); ++i2) 
            {
                cout << R2[i].ref[i2].x << ' ' << R2[i].ref[i2].y << ",  "; 
                
            }
            cout << endl; 
        }
        cout << endl;

        cout << "R3:  ";
        for (i=0; i<R3.size(); ++i) 
        {
            for (int i2=0; i2<R3[i].ref.size(); ++i2) 
            {
                cout << R3[i].ref[i2].x << ' ' << R3[i].ref[i2].y << ",  "; 
                
            }
            cout << endl; 
        }
        cout << endl;

        
        cout << "R4:  ";
        for (i=0; i<R4.size(); ++i) 
        {
            for (int i2=0; i2<R4[i].ref.size(); ++i2) 
            {
                cout << R4[i].ref[i2].x << ' ' << R4[i].ref[i2].y << ",  "; 
                
            }
            cout << endl; 
        }
        cout << endl;
        
    };
    
    int getTotalMoves()
    {
        return Q1.size();
    };
    
    void check4Q1(GotAGrid& ag)
    {
        
        for(int r=0; r<GRID_ROW; ++r) 
        {
        	for(int c=0; c<GRID_COL; ++c) 
            {
                if(ag.ref[r][c] == id) Q1.push_back(Position(r, c));
            }
        }
    };
    
    void check4R2_5(GotAGrid& ag)
    {   
        if(Q1.size() < 2) return;
        
        for (int i=0; i<Q1.size()-1; ++i) 
        {
            
            for(int i2=i+1; i2<Q1.size(); ++i2) 
            {
                int n=Q1[i].is_neighbour(Q1[i2]);
                if(n)
                {
                    runNrow Trnr = runNrow(Q1[i], Q1[i2]);
                    Trnr.dir = n;
                    
                    R2.push_back(Trnr);
                }
            }
        }
        
        for (int i=0; i<R2.size(); ++i) 
        {
            
            if (R2[i].dir == 1) 
            {
                if((R2[i].is_posible = ag.north_south_posible(R2[i].ref[0], id)))
                {
                    if(R2[i].is_posible == 3)
                        R3.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                    else if(R2[i].is_posible == 4)
                        R4.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                    else if(R2[i].is_posible > 4)
                        R4.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                }
            }
            else if (R2[i].dir == 2) 
            {
                if((R2[i].is_posible = ag.east_west_posible(R2[i].ref[0], id)))
                {
                    if(R2[i].is_posible == 3)
                        R3.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                    else if(R2[i].is_posible == 4)
                        R4.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                    else if(R2[i].is_posible > 4)
                        R4.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                }
                    
            }
            else if (R2[i].dir == 3) 
            {
                if((R2[i].is_posible = ag.back_slash_posible(R2[i].ref[0], id)))
                {
                    if(R2[i].is_posible == 3)
                        R3.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                    else if(R2[i].is_posible == 4)
                        R4.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                    else if(R2[i].is_posible > 4)
                        R4.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                }
            }
            else if (R2[i].dir == 4) 
            {
                if((R2[i].is_posible = ag.foward_slash_posible(R2[i].ref[0], id)))
                {
                    if(R2[i].is_posible == 3)
                        R3.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                    else if(R2[i].is_posible == 4)
                        R4.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                    else if(R2[i].is_posible > 4)
                        R4.push_back(runNrow(R2[i].ref[0], R2[i].ref[1]));
                }
            }
            else R2[i].is_posible = 0;
            
            
            
        }
        
    };
    
    // check for pairs(Q2) with spaces inbetween them
    
    
    void check4runs(GotAGrid& ag)
    {
        check4Q1(ag);
        check4R2_5(ag);
        
        /*
         int r,c;
         int cpi;
         Position p[6];
         for(int pi=0; pi<6; ++pi) 
         {
         p[pi] = Position();
         }
         // horizen check 
         for(r=0; r<GRID_ROW; ++r) 
         {
         cpi=0;
         
         for(c=0; c<GRID_COL; ++c) 
         {
         if(ag.ref[r][c] == id) 
         {
         p[cpi].set(r,c);
         ++cpi;
         }
         else
         {
         if(cpi>0 && ag.east_west_posible(p[0], id)) 
         {
         for(int c=0; c<=cpi; ++c) 
         {
         if(cpi == 1) 
         {
         R2.push_back(runNrow(p[0],p[1]));
         }
         else if(cpi == 2) 
         {
         runNrow t = runNrow(p[0], p[1]);
         t.addPosition(p[3]);
         R3.push_back(t);
         
         }
         else 
         {
         runNrow t = runNrow(p[0], p[1]);
         t.addPosition(p[3]);
         t.addPosition(p[4]);
         R4.push_back(t);
         }
         }     
         } 
         cpi=0;
         }
         
         }
         }
         
         // vertical check
         for(c=0; c<GRID_COL; ++c) 
         {
         cpi=0;
         for(r=0; r<GRID_ROW; ++r) 
         {
         if(ag.ref[r][c] == id) 
         {
         p[cpi].set(r,c);
         ++cpi;
         }
         else
         {
         if(cpi>0 && ag.north_south_posible(p[0], id)) 
         {
         for(int c=0; c<=cpi; ++c) 
         {
         if(cpi == 1) 
         {
         R2.push_back(runNrow(p[0],p[1]));
         }
         else if(cpi == 2) 
         {
         runNrow t = runNrow(p[0], p[1]);
         t.addPosition(p[3]);
         R3.push_back(t);
         
         }
         else 
         {
         runNrow t = runNrow(p[0], p[1]);
         t.addPosition(p[3]);
         t.addPosition(p[4]);
         R4.push_back(t);
         }
         }     
         } 
         cpi=0;
         }
         
         }
         }
         //*/
    };
};
// -----------------------------------------------


struct GomokuLogic 
{
    //int grid[N][N];
    int x, y, id;
    vector <pair<int, int> > moves;
    
    GotAPlayer my, foe; 
    GotAGrid ag;
    Position next_move;
    GomokuLogic():next_move(), my(), foe()
    {
        ag = GotAGrid();
    };
    
    void getInput()
    {
        /*
        ag.scan_state();
        cin >> my.id;
        /*/
         ag.start_game();
         my.id=1;
         //*/
       	if(my.id==1)foe.id=2;
       	else	foe.id=1;
    };
    
    void getPossibleMoves()
    {
        
        // Get the possible moves
        for(int i = 0;i < N;++i)
            for(int j = 0;j < N;++j)
            {
                if(ag.ref[i][j] == 0)
                    moves.push_back(make_pair(i, j));
            }
        if(moves.size() == 0)
            assert(0);
    };
    
    
    void learnGrid()
    {
        // empty positions
        getPossibleMoves();
        my.check4runs(ag);
        foe.check4runs(ag);
        
    };
    
    void setRandMove()
    {
        // Select a random move
        srand(time(NULL));
        id = rand() % moves.size();
        x = moves[id].first, y = moves[id].second;
        
    };
    
    bool hasBestMove(std::vector<runNrow>& rnr_v, Position& p, int pid)
    {
        //for (int i=0; i<rnr_v.size(); ++i) 
        //{
        int i=0;
        for (i=0; i<rnr_v.size(); ++i) 
        {
            Position t = Position(rnr_v[i].ref[0]);
            int x,y;
            x=t.x; y=t.y;
            if(rnr_v[i].dir == 1)
            {
                do{
                    x++;
                    t.set(x, y);
                    
                    if(ag.isOpen(t))
                    {
                        p.set(t);
                        return true;
                    }
                    else if(ag.ref[x][y] != pid) break;
                    
                } while (x<GRID_ROW);
                
                t.set(rnr_v[i].ref[0]);
                
                do{
                    x--;
                    t.set(x, y);
                    
                    if(ag.isOpen(t))
                    {
                        p.set(t);
                        return true;
                    }
                    else if(ag.ref[x][y] != pid) break;
                    
                } while (x>0);
                
            }
            else if(rnr_v[i].dir == 2)
            {
                do{
                    y++;
                    t.set(x, y);
                    
                    if(ag.isOpen(t))
                    {
                        p.set(t);
                        return true;
                    }
                    else if(ag.ref[x][y] != pid) break;
                    
                } while (y<GRID_COL);
                
                t.set(rnr_v[i].ref[0]);
                
                do{
                    y--;
                    t.set(x, y);
                    
                    if(ag.isOpen(t))
                    {
                        p.set(t);
                        return true;
                    }
                    else if(ag.ref[x][y] != pid) break;
                    
                } while (y>0);
                
            }
            else if(rnr_v[i].dir == 3)
            {
                do{
                    x++; y++;
                    t.set(x, y);
                    
                    if(ag.isOpen(t))
                    {
                        p.set(t);
                        return true;
                    }
                    else if(ag.ref[x][y] != pid) break;
                } while (y<GRID_COL && x<GRID_ROW);
                
                t.set(rnr_v[i].ref[0]);
                
                do{
                    x--; y--;
                    t.set(x, y);
                    
                    if(ag.isOpen(t))
                    {
                        p.set(t);
                        return true;
                    }
                    else if(ag.ref[x][y] != pid) break;
                } while (y>=0 && x>=0);
                
            }
            else if(rnr_v[i].dir == 4)
            {
                do{
                    x++; y--;
                    t.set(x, y);
                    
                    if(ag.isOpen(t))
                    {
                        p.set(t);
                        return true;
                    }
                    else if(ag.ref[x][y] != pid) break;
                    
                } while (y>=0 && x<GRID_ROW);
                
                t.set(rnr_v[i].ref[0]);
                
                do{
                    x--; y++;
                    t.set(x, y);
                    
                    if(ag.isOpen(t))
                    {
                        p.set(t);
                        return true;
                    }
                    else if(ag.ref[x][y] != pid) break;
                    
                } while (y<GRID_COL && x>=0);
            }
        }
        
        return false;
    };
    
    
    void think()
    {
        Position tp = Position();
        learnGrid();
        
        if(!my.Q1.size())
        {
            if(ag.ref[4][4] == 0) x=y=4;
            else if(ag.ref[5][5] == 0) x=y=5;
            else if(ag.ref[6][6] == 0) x=y=6;
            else if(ag.ref[3][3] == 0) x=y=3;
        }
        else if(my.Q1.size() == 1)
        {
            if(ag.ref[6][6] == 0) x=y=6;
            else if(ag.ref[3][3] == 0) x=y=3;
            else if(ag.ref[9][9] == 0) x=y=9;
            else if(ag.ref[7][7] == 0) x=y=7;
        	
        }
        else if(hasBestMove(my.R4,tp, my.id))
        {
            x=tp.x;
            y=tp.y;
        }
        else if(hasBestMove(foe.R4,tp, foe.id))
        {
            x=tp.x;
            y=tp.y;
        }
        else if(hasBestMove(foe.R3,tp, foe.id))
        {
            x=tp.x;
            y=tp.y;
        }
        else if(hasBestMove(my.R3,tp, my.id))
        {
            x=tp.x;
            y=tp.y;
        }
        else if(hasBestMove(my.R2,tp, my.id))
        {
            x=tp.x;
            y=tp.y;
        }
        /*
         else if(my.R4.size())
         {
         Position temp = Position(my.R4[0].ref[0]);
         if (my.R4[0].dir == 2) 
         {
         temp.y= temp.y-1;
         if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
         else
         {
         temp.y= temp.y + 2;
         while (!ag.isOpen(temp)) 
         {
         temp.y = temp.y + 1;
         if(temp.y>=GRID_COL) 
         {
         setRandMove();
         temp.x=x;
         temp.y=y;
         break; 
         }
         }
         x=temp.x; y=temp.y;
         }
         }
         else // for vertical
         {
         temp.x= temp.x-1;
         if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
         else
         {
         temp.x= temp.x + 2;
         while (!ag.isOpen(temp)) 
         {
         temp.x = temp.x + 1;
         if(temp.x>=GRID_ROW) 
         {
         setRandMove();
         temp.x=x;
         temp.y=y;
         break; 
         }
         }
         x=temp.x; y=temp.y;
         }
         }
         }
         else if(foe.R4.size())
         {
         Position temp = Position(foe.R4[0].ref[0]);
         if (foe.R4[0].dir == 2) 
         {
         temp.y= temp.y-1;
         if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
         else
         {
         temp.y= temp.y + 2;
         while (!ag.isOpen(temp)) 
         {
         temp.y = temp.y + 1;
         if(temp.y>=GRID_COL) 
         {
         setRandMove();
         temp.x=x;
         temp.y=y;
         break; 
         }
         }
         x=temp.x; y=temp.y;
         }
         }
         else // for vertical
         {
         temp.x= temp.x-1;
         if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
         else
         {
         temp.x= temp.x + 2;
         while (!ag.isOpen(temp)) 
         {
         temp.x = temp.x + 1;
         if(temp.x>=GRID_ROW) 
         {
         setRandMove();
         temp.x=x;
         temp.y=y;
         break; 
         }
         }
         x=temp.x; y=temp.y;
         }
         }
         }
         else if(foe.R3.size())
         {
         Position temp = Position(foe.R3[0].ref[0]);
         if (foe.R3[0].dir == 2) 
         {
         temp.y= temp.y-1;
         if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
         else
         {
         temp.y= temp.y + 2;
         while (!ag.isOpen(temp)) 
         {
         temp.y = temp.y + 1;
         if(temp.y>=GRID_COL) 
         {
         setRandMove();
         temp.x=x;
         temp.y=y;
         break; 
         }
         }
         x=temp.x; y=temp.y;
         }
         }
         else // for harazonal
         {
         temp.x= temp.x-1;
         if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
         else
         {
         temp.x= temp.x + 2;
         while (!ag.isOpen(temp)) 
         {
         temp.x = temp.x + 1;
         if(temp.x>=GRID_ROW) 
         {
         setRandMove();
         temp.x=x;
         temp.y=y;
         break; 
         }
         }
         x=temp.x; y=temp.y;
         }
         }
         
         }
         else if(my.R3.size())
         {
         
         Position temp = Position(my.R3[0].ref[0]);
         if (my.R3[0].dir == 2) 
         {
         temp.y= temp.y-1;
         if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
         else
         {
         temp.y= temp.y + 2;
         while (!ag.isOpen(temp)) 
         {
         temp.y = temp.y + 1;
         if(temp.y>=GRID_COL) 
         {
         setRandMove();
         temp.x=x;
         temp.y=y;
         break; 
         }
         }
         x=temp.x; y=temp.y;
         }
         }
         else // for vertical
         {
         temp.x= temp.x-1;
         if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
         else
         {
         temp.x= temp.x + 2;
         while (!ag.isOpen(temp)) 
         {
         temp.x = temp.x + 1;
         if(temp.x>=GRID_ROW) 
         {
         setRandMove();
         temp.x=x;
         temp.y=y;
         break; 
         }
         }
         x=temp.x; y=temp.y;
         }
         }
         }
         else if(my.R2.size())
         {
         
         Position temp = Position(my.R2[0].ref[0]);
         if (my.R2[0].dir == 2) 
         {
         temp.y= temp.y-1;
         if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
         else
         {
         temp.y= temp.y + 2;
         while (!ag.isOpen(temp)) 
         {
         temp.y = temp.y + 1;
         if(temp.y>=GRID_COL) 
         {
         setRandMove();
         temp.x=x;
         temp.y=y;
         break; 
         }
         }
         x=temp.x; y=temp.y;
         }
         }
         else // for vertical
         {
         temp.x= temp.x-1;
         if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
         else
         {
         temp.x= temp.x + 2;
         while (!ag.isOpen(temp)) 
         {
         temp.x = temp.x + 1;
         if(temp.x>=GRID_ROW) 
         {
         setRandMove();
         temp.x=x;
         temp.y=y;
         break; 
         }
         }
         x=temp.x; y=temp.y;
         }
         }
         
         }
 
// last removed         
         else if(my.Q1.size())
        {
            
            Position temp = Position(my.Q1[0]);
            temp.y= temp.y-1;
            if(ag.isOpen(temp)) {x=temp.x; y=temp.y;}
            else
            {
                temp.y= temp.y + 2;
                while (!ag.isOpen(temp)) 
                {
                    temp.y = temp.y + 1;
                    if(temp.y>=GRID_COL) 
                    {
                        setRandMove();
                        temp.x=x;
                        temp.y=y;
                        break; 
                    }
                }
                x=temp.x; y=temp.y;
            }
        }
         //*/
        else
        {
            setRandMove();
        }
    };
    
    void printOutput()
    {
        cout << x << ' ' << y << endl;
        //*  for testing only
        cout << "---- My date ----" << endl;
        my.print();
        cout << "---- Foe data ----" << endl;
        foe.print();
        //*/
        
    };
    
};

int main()
{
    GomokuLogic gl;
    
    gl.getInput();
    
    gl.think();
    
    gl.printOutput();
    
    return 0;
}

