#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
//-------------------------------------------------------------------------------------
// Coded by: NashBean 2018
// https//iBeanSoftware.github.io/index.html
const int Coders_Caribbean_MAJOR_VERSION = 1;
const int Coders_Caribbean_MINOR_VERSION = 7;
//-------------------------------------------------------------------------------------

const int GRID_WIDTH=23;
const int GRID_HIGHT=21;

//-------------------------------------------------------------------------------------

struct Position 
{
    int x, y;
    Position(){x=y=0;};
    Position(int ax, int ay){x=ax;y=ay;};
    //    Position(const  Position& a){x=a.x;y=a.y;};
    ~Position(){};
    
    Position& operator =(Position& other)
    {
        x=other.x;
        y=other.y;
        return *this;
    };
    
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
    
    int distance(Position& a)
    {
        return find_distance(a.x,a.y);
    };
    
	bool is_neighbour(int px, int py) 
	{
    	if (px == x  &&  py == y)
        	return false;
    	else if (abs(px-x) <= 1 && abs(py-y) <= 1)
        	return true;
    	return false;
	};

    bool is_even()
    {
        if(!y) return false;
        else if((y%2) == 0) return false;//even on one base
        else return true;//odd on one base
    };
	
};
//-------------------------------------------------------------------

struct	HexGrid
{
    int ref[GRID_WIDTH][GRID_HIGHT];
    
	HexGrid(){zero();};
	~HexGrid(){};
	
    void setValue(Position& p, int val)
    {
        ref[p.x][p.y] = val;
    };
	
	
	void scan_state()
	{
    	for(int	a=0; a<GRID_WIDTH; ++a) 
        	for(int	b=0; b<GRID_HIGHT; ++b) 
            	std::cin >> ref[a][b];
	};
	
	bool in_bounds(Position&	p)
	{
		if(p.x < 0 || p.y < 0)	return false;
		else if(p.x >= GRID_WIDTH && p.y >= GRID_HIGHT)	return false;
		return	true;
	};
    
	
	bool is_corner(Position&	p)
	{
		if(p.x == 0 && p.y == 0)	return true;
		else if(p.x == 0 && p.y == GRID_HIGHT-1)	return true;
		else if(p.x == GRID_WIDTH-1 && p.y == 0)	return true;
		else if(p.x == GRID_WIDTH-1 && p.y == GRID_HIGHT-1)	return true;
		return	false;
	};
	
	bool is_edge(Position&	p)
	{
		if(p.x == 0 || p.y == 0)	return true;
		else if(p.x == GRID_WIDTH-1 || p.y == GRID_HIGHT-1)	return true;
		return	false;
	};
    
    void movePos(Position& pos, int arg1)// arg1 = direction 0@ 3 OClock 1@ 1:30 OCLOCK ... 5@ 4:30 OCLOCK
    {

        if(pos.is_even())
        {
            if(!arg1) { pos.x = 1 + pos.x; }
            else if(arg1==1) { pos.y = -1 + pos.y; }
            else if(arg1==2) { pos.x = -1+pos.x; pos.y = -1+pos.y; }
            else if(arg1==3) { pos.x = -1+pos.x; }
            else if(arg1==4) { pos.x = -1+pos.x; pos.y = 1+pos.y; }
            else if(arg1==5) { pos.y = 1+pos.y; }
        }   
        else
        {
            if(!arg1) { pos.x = 1 + pos.x; }
            else if(arg1==1) { pos.x = 1+pos.x; pos.y = -1+pos.y; }
            else if(arg1==2) { pos.y = -1+pos.y; }
            else if(arg1==3) { pos.x = -1+pos.x; }
            else if(arg1==4) { pos.y = 1+pos.y; }
            else if(arg1==5) { pos.x = 1+pos.x; pos.y = 1+pos.y; }
        }  
        
        if(pos.x>=GRID_WIDTH) pos.x= GRID_WIDTH-1;
        if(pos.y>=GRID_HIGHT) pos.y= GRID_HIGHT-1;
        if(pos.x<0) pos.x= 0;
        if(pos.y<0) pos.y= 0;
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

    void zero()
    {
        for(int	a=0; a<GRID_WIDTH; ++a) 
        	for(int	b=0; b<GRID_HIGHT; ++b) 
            	ref[a][b]=0;
    };   

    void clear()
    {
        for(int	a=0; a<GRID_WIDTH; ++a) 
        	for(int	b=0; b<GRID_HIGHT; ++b) 
            	ref[a][b]=-1;
    };   
    
};
//-------------------------------------------------------------------------------------

struct Entity
{
    int id;
    string type;
    Position pos;
    int arg1, arg2, arg3, arg4;
    
    Entity() 
    {
        id=0;
        type="unknown"; 
        arg1=arg2=arg3=arg4=-1; 
    };
    Entity(int n_id, string n_type, int n_x, int n_y, int n_arg1, int n_arg2, int n_arg3, int n_arg4) 
    { 
        id=n_id; 
        type=n_type; 
        arg1=n_arg1; arg2=n_arg2; arg3=n_arg3; arg4=n_arg4;
    };
    Entity(int n_id, string n_type, Position n_pos, int n_arg1, int n_arg2, int n_arg3, int n_arg4) 
    {
        id=n_id; 
        type=n_type; 
        pos.x =n_pos.x; 
        pos.y =n_pos.y; 
        arg1=n_arg1; arg2=n_arg2; arg3=n_arg3; arg4=n_arg4;
    };
    ~Entity(){};
    
    Entity& operator =(Entity& other)
    {
        id=other.id;
        type=other.type;
        pos=other.pos;
        arg1=other.arg1;
        arg2=other.arg2;
        arg3=other.arg3;
        arg4=other.arg4;
        return *this;
    };
    
};
//-------------------------------------------------------------------------------------

struct Map
{
    HexGrid grid;
    vector<Entity> entities;
    
    Map() {};
    Map(vector<Entity>& entts)
    {
        entities.clear();
        for(size_t c=0; c<entts.size(); c++)
        {
            entities.push_back(entts[c]);
            add2grid(entts[c]);
        }
    };
    ~Map(){if(entities.size()) entities.clear();};

    Map& operator =(Map& other)
    {
        setEntities(other.entities);
        return *this;
    };
    
    void setEntities(vector<Entity>& oe)
    {
        entities.clear();
        for(size_t c=0; c<oe.size(); c++)
        {
            entities.push_back(oe[c]);
            add2grid(oe[c]);
        }
    };
    
    void add2grid(Entity& e)
    {
        grid.setValue(e.pos, e.id);//(-1+entities.size()));
        if(e.type == "SHIP")
        {
            Position pos = e.pos;//center of ship
            grid.movePos(pos, e.arg1);// front gun pos 
            grid.setValue(pos, e.id);
            pos = e.pos;// center of ship
            grid.movePos(pos, opposetDirection(e.arg1));//ship back
            grid.setValue(pos, e.id);
        }
    };

    int opposetDirection(int d)
    {
        if(d==0) return 3;
        else if(d==1) return 4;
        else if(d==2) return 5;
        else if(d==3) return 0;
        else if(d==4) return 1;
        else if(d==5) return 2;
        else cerr << "out-of-rang in opposetDirection(int d) function." <<endl;
        return -1;
    };
    
    void addEntity(Entity& e)
    {
        entities.push_back(e);
        add2grid(e);
    };
        
    void moveMap()
    {
        grid.clear();
        for(size_t c=0; c<entities.size(); c++)
        {
            moveEntity(entities[c]);
            add2grid(entities[c]);
        }
    };
 
    bool inRange(Position& p1, Position& p2, int range)
    {
        if(p2.distance(p1)<=range) 
            return true; 
        return false; 
    };

    int getInRangeID(Position& p, int range)
    {
        int lrx, hrx, lry, hry;
        lrx = p.x - range;
        hrx = p.x + range;
        lry = p.y - range;
        hry = p.y + range;
        for(int y=lry; y<=hry; y++)
        {
            for(int x=lrx; x<=hrx; x++)
            {
                if(grid.ref[x][y]>-1)
                {
                    p.x=x; 
                    p.y=y; 
                    return grid.ref[x][y];
                }
            }
        }
        return -1; 
    };

    void clear()
    {
        grid.clear();
        entities.clear();
    };

    void moveEntity(Entity& e)
    {
        if(e.arg2>0) grid.movePos(e.pos, e.arg1);  
        if(e.arg2>1) grid.movePos(e.pos, e.arg1);  
    };

};
//-------------------------------------------------------------------------------------


struct Radar
{
    Map last_map;
    Map curr_map;
    vector<Entity> entity_query;
    
    int entityIndexWithID(int id, Map& map)
    {
        for(size_t c=0; c<map.entities.size(); c++)
        {
            if(map.entities[c].id == id) return c; 
        }
        cerr << "id was not found in entries!" << endl;
        return -1;
    };
    
    void bleep()
    {
        last_map = curr_map;
        curr_map.setEntities(entity_query);
    };
        
    bool isFoeShip(Entity& fs)
    {
        if(fs.type=="SHIP" &&  !(fs.arg4))
        { return true;}
        return false;
    };
    
    int closestFoe(int sid, Position& pos)//ship id
    {
        int result = -1; // returns -1 if no ship in range
        int myindex = entityIndexWithID(sid, curr_map); //my ship index
        int foei=-1; // foe ship index
        int dist =GRID_WIDTH+GRID_HIGHT;
        vector<Entity> foe_ships;
        for(size_t i=0; i<curr_map.entities.size(); i++)
        {//distance
            if(isFoeShip(curr_map.entities[i]))
            { foe_ships.push_back(curr_map.entities[i]); }
        }
        
        if(foe_ships.size())
        {
            Map map;
            Position tp;
                // dist     turns
                // 1        1  
                //2-4       2
                //5-7       3
                // 8-10     4
            for(size_t i=0; i<foe_ships.size(); i++)
            {
                map.addEntity(foe_ships[i]);
            }
            
            //      turn    1
            map.moveMap();
            if(myindex <0) return result;
            tp=curr_map.entities[myindex].pos;
            map.grid.movePos(tp, curr_map.entities[myindex].arg1);
            foei = map.getInRangeID(tp, 1);
            if(foei>=0) {pos=tp; return foei;}

            //      turn    2
            map.moveMap();
            tp=curr_map.entities[myindex].pos;
            map.grid.movePos(tp, curr_map.entities[myindex].arg1);
            foei = map.getInRangeID(tp, 4);
            if(foei>=0) {pos=tp; return foei;}

            //      turn    3
            map.moveMap();
            tp=curr_map.entities[myindex].pos;
            map.grid.movePos(tp, curr_map.entities[myindex].arg1);
            foei = map.getInRangeID(tp, 7);
            if(foei>=0) {pos=tp; return foei;}

            //      turn    4
            map.moveMap();
            tp=curr_map.entities[myindex].pos;
            map.grid.movePos(tp, curr_map.entities[myindex].arg1);
            foei = map.getInRangeID(tp, 10);
            if(foei>=0) {pos=tp; return foei;}
            
        }

        cerr << "____ New Closest Foe Function ____" <<endl;
        cerr << "  my index=" << myindex << " my  id=" << sid <<endl;
        cerr << " foe index=" <<foei << " foe id=" << curr_map.entities[foei].id <<endl;
        return result;
    };
};

struct Barrel
{
    int id;
    Position pos;
    int arg3;
    int timer=-1;//hmmm

    int how_full(){return arg3;};
};
//-------------------------------------------------------------------------------------

struct CannonBall
{
    int id;
    Position pos;
    int foe_id;
    int ToI;//Time of Impact = 1
};
//-------------------------------------------------------------------------------------

struct Mine
{
    int id;
    Position pos;
};
//-------------------------------------------------------------------------------------

struct Ship//SHIP
{
    int id;
    Position pos;
//    Position cannon_pos;
    int turn=0;
    int stuck=0;
    int cannon_cool_down=0;
    int mine_cool_down=0;
    int move2center=0;
    int arg1, arg2, arg3, arg4;
    string command_string;
    
        
    int dir(){return arg1;};//direction
    int speed(){return arg2;};

    void next_turn(Ship& shp, Radar& r)
    {
      ++turn;
      if(pos == shp.pos) stuck++;
      
      pos = shp.pos;
      arg1= shp.arg1;
      arg2= shp.arg2;
      arg3= shp.arg3;
      arg4= shp.arg4;
    };

    void cool_down()
    {
        if(cannon_cool_down) 
            --cannon_cool_down; 
        if(mine_cool_down) 
            --mine_cool_down;
    };
   
    void move_center()
    {        
        Position cp = Position(GRID_WIDTH/2, GRID_HIGHT/2);
        move2center--;
        move(cp);
    }
    void move_center(int t)
    {        
        Position cp = Position(GRID_WIDTH/2, GRID_HIGHT/2);
        move2center=t;
        move(cp);
    }
    
    bool is_booz_low() { if(arg3 < 37) return true; else return false; };
    bool is_booz_good() { if(arg3 > 80) return true; else return false; };
    bool is_booz_full() { if(arg3 > 93) return true; else return false; };
    bool is_booz_low(int v) { if(arg3 < v) return true; else return false; };
    bool is_booz_good(int v) { if(arg3 > v) return true; else return false; };
    bool is_booz_full(int v) { if(arg3 > v) return true; else return false; };
    bool is_mine(){return arg4;};
   // bool fire_ready(Position& p) { if(!cannon_cool_down && in_range(p)) return true; else return false; };
    void fire(Position& p)
    {
        cannon_cool_down=1;    
        stringstream ss;
        ss << "FIRE ";
        ss << p.x;
        ss << " ";
        ss << p.y;
        command_string = ss.str();
    };
    void mine()
    {command_string = "MINE"; mine_cool_down=4; if(cannon_cool_down) --cannon_cool_down;};//remiber where my mine is
    
    void move(Position& p)
    {
       // cammand_string.clear();
       stringstream ss;
       ss << "MOVE ";
       ss << p.x;
       ss << " ";
       ss << p.y;
       command_string = ss.str();
       cool_down();
    };
    void slow(){command_string = "SLOWER"; cool_down();};
    void wait(){command_string = "WAIT"; cool_down();};
    
};
//-------------------------------------------------------------------------------------

struct ShipCommand
{
    int myShipCount; // the number of remaining ships
    int entityCount; // the number of entities (e.g. ships, mines or cannonballs)
    vector<Ship> myShipsData;
    vector<Ship> myShips;
    vector<Ship> foeShips;
    vector<Barrel> barrels;
    vector<CannonBall> inComming;
    vector<Mine> myMines;
    vector<Mine> mine_warning;
//    vector<Entity> entities;
    Radar radar;

    void getLoopData()
    {
        //myShips.clear(); 
        foeShips.clear(); barrels.clear();
        inComming.clear(); mine_warning.clear();
        
        cin >> myShipCount;// cin.ignore();
        cin >> entityCount;// cin.ignore();
 
         for (int i = 0; i < entityCount; i++) 
        {
            Entity e;
            cin >> e.id >> e.type >> e.pos.x >> e.pos.y >> e.arg1 >> e.arg2 >> e.arg3 >> e.arg4;// cin.ignore();
            
            radar.entity_query.push_back(e);
            
            if(e.type == "SHIP")
            { 
                Ship ship;
                ship.id = e.id;
                ship.pos = e.pos;
                ship.arg1=e.arg1; ship.arg2=e.arg2; ship.arg3=e.arg3; ship.arg4=e.arg4;
                
                if(ship.is_mine()) 
                {
                    myShips.push_back(ship);
                }
                else { foeShips.push_back(ship); }
            }
            else if(e.type == "BARREL")
            {
                Barrel booz;
                booz.id=e.id;
                booz.pos=e.pos;
                booz.arg3=e.arg3;
                barrels.push_back(booz);
            }
            else if(e.type == "CANNONBALL")
            {
                CannonBall ball;
                ball.id=e.id;
                ball.pos=e.pos;
                ball.foe_id=e.arg1;
                ball.ToI=e.arg2;
                inComming.push_back(ball);
            }
        
            else if(e.type == "MINE")
            {    //!!!!
                Mine m;
                m.id=e.id;
                m.pos=e.pos;
                mine_warning.push_back(m);
            };//
        }
        radar.bleep();   
    };
    
    int closestBarrel(Position& sp)
    {
        
        int index=-1;
        int dist =GRID_WIDTH+GRID_HIGHT;
        
        for(size_t i=0; i<barrels.size(); i++)
        {//distance
            int d = barrels[i].pos.distance(sp);
            if(d<dist){ dist=d; index=i; }
        }
         cerr << "Closest Booz index=" << to_string(index) << " Booz Dist=" << to_string(dist) <<endl;
        return index;
    };
    
    void calcShipMove(int myi)
    {
        Position shipP = myShips[myi].pos;
        int cBooz = closestBarrel(shipP);
        int cFoe = -1;
        if(!myShips[myi].cannon_cool_down)
        {cFoe = radar.closestFoe(myi, shipP);}
        
        if(myShips[myi].is_booz_low(37) && cBooz>=0)
        {
            myShips[myi].move(barrels[cBooz].pos);
        }
        else if(cFoe >= 0)
        {
            myShips[myi].fire(shipP);
        }
        else if(!myShips[myi].is_booz_full(97) && cBooz>=0)
        {
            myShips[myi].move(barrels[cBooz].pos);
        }
        else if(!myShips[myi].mine_cool_down && myShips[myi].arg2>0)
        {
            myShips[myi].mine();
        }
        else if( myShips[myi].arg2>0)
        {
            myShips[myi].wait();
        }
        else
        {
            myShips[myi].move_center();
        }
     
    };  
    
    void calcMoves()
    {
        for (int i = 0; i < myShipCount; i++) 
        {
            calcShipMove(i);
        }
    };

    void outputMoves()
    {
        for (int i = 0; i < myShipCount; i++) 
        {
             cout << myShips[i].command_string << endl;
        }
       
    };
     
};


// To debug: cerr << "Debug messages..." << endl;
//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ShipCommand commander;

    // game loop
    while (1) 
    {
        commander.getLoopData();
        commander.calcMoves();
        commander.outputMoves();
    }
}
