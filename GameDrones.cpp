#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Coded by: NashBean 2018
// https//iBeanSoftware.github.io/index.html
const int GAME_DRONES_MAJOR_VERSION = 0;
const int GAME_DRONES_MINOR_VERSION = 3;

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
};
//-------------------------------------------------------------------

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
ine 1: 4 integers P ID D Z separated by a space.
P: number of players in the game (2 to 4 players),
ID: id of your player (0, 1, 2, or 3),
D: Number of drones in each team (3 to 11),
Z: Number of zones on the map (4 to 8).
Z Following lines: the position X Y of the center of a zone (integers, separated by a space). 
A zone is a circle with a radius of 100 units.
 **/
//-----------------------------------------------

 struct Zone
 {
     const int radius = 100;
     Position cp;// center point
     int tid=-1;// controlling team id 
 };
//-----------------------------------------------

 struct Map
 {
    const int width=4000;
    const int hight=1800;
     vector<Zone> zones;
     
     Map():zones(0){};
     ~Map(){if(zones.size()) zones.clear();};
 };
//-----------------------------------------------

 struct Drone
 {
     Position pos;
 };
//-----------------------------------------------
 
 struct Player
 {
     int id;
     vector<Drone> drones;
     
     Player():drones(0){};
     ~Player(){if(drones.size()) drones.clear();};
     string calcResult(int d, Map& m)// drone ID
     {
         static int si=0;
         stringstream ss;
         if(0)
         {
             ss << m.zones[si].cp.x;
             ss << " ";
             ss << m.zones[si].cp.y;
             
             si++;
             if(si >= m.zones.size()) si=0;
         }
         else if(m.zones.size() > (d+1))
         {
             ss << m.zones[d+1].cp.x;
             ss << " ";
             ss << m.zones[d+1].cp.y;
         }
         else if(m.zones.size() > d)
         {
             ss << m.zones[0].cp.x;
             ss << " ";
             ss << m.zones[0].cp.y;
         }
         else if(m.zones.size() > (d-m.zones.size()))
         {
             
             ss << m.zones[1].cp.x;
             ss << " ";
             ss << m.zones[1].cp.y;
         }
         else 
         {
             
             ss << m.zones[0].cp.x;
             ss << " ";
             ss << m.zones[0].cp.y;
         }

         return ss.str();
     };
 };
//-----------------------------------------------
 
int main()
{
    int P; // number of players in the game (2 to 4 players)
    int ID; // ID of your player (0, 1, 2, or 3)
    int D; // number of drones in each team (3 to 11)
    int Z; // number of zones on the map (4 to 8)
    cin >> P >> ID >> D >> Z; cin.ignore();
    
    vector<Player> players(P);
    for(int c=0; c<P; c++)
    {players[c].id=c; players[c].drones.resize(D);}
    Map map; map.zones.resize(Z);
    for (int i = 0; i < Z; i++) 
    {
        //int X; // corresponds to the position of the center of a zone. A zone is a circle with a radius of 100 units.
        //int Y;
        //cin >> X >> Y; cin.ignore();
        //Map.zones[i].cp.x=X;
        //Map.zones[i].cp.y=Y;
        cin >> map.zones[i].cp.x >> map.zones[i].cp.y; cin.ignore();
    }

    // game loop
    while (1) {
        for (int i = 0; i < Z; i++) 
        {
        //    int TID; // ID of the team controlling the zone (0, 1, 2, or 3) or -1 if it is not controlled. The zones are given in the same order as in the initialization.
        //    cin >> TID; cin.ignore();
            cin >> map.zones[i].tid; cin.ignore();
        }
        for (int i = 0; i < P; i++) {
            for (int j = 0; j < D; j++) {
              //  int DX; // The first D lines contain the coordinates of drones of a player with the ID 0, the following D lines those of the drones of player 1, and thus it continues until the last player.
              //  int DY;
              //  cin >> DX >> DY; cin.ignore();
                cin >> players[i].drones[j].pos.x >> players[i].drones[j].pos.y; cin.ignore();
            }
        }
        for (int i = 0; i < D; i++) 
        {
            cout << players[ID].calcResult(i, map) << endl;
            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;


            // output a destination point to be reached by one of your drones. The first line corresponds to the 
            //first of your drones that you were provided as input, the next to the second, etc.
         //   cout << "20 20" << endl;
        }
    }
}
//-----------------------------------------------
//-----------------------------------------------
