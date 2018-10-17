#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//-------------------------------------------------------------------
const int STRIKE_BACK_MAJOR_VERSION = 1;
const int STRIKE_BACK_MINOR_VERSION = 1;

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

struct checkPoint
{
    Position loca;
    int dist,angl;
    
    void set(int px, int py,int di,int ai)
    {loca.set(px,py); dist = di; angl=ai;};
    
    void set(checkPoint &cp )
    {loca.set(cp.loca); dist = cp.dist; angl=cp.angl;};
    
    bool close(Position& aride)
    {
        if(aride.distance(loca) < 100) return true;
        else return false;
    };
    bool simi_close(Position& aride)
    {
        if(aride.distance(loca) < 400) return true;
        else return false;
    };

    bool turning()
    {
        if(abs(angl)< 74) return false;
        else return true;
    };
    bool strait()
    {
        if(abs(angl)== 0) return true;
        else return false;
    };
};
//-------------------------------------------------------------------

struct ride
{
    Position current, next, last, opp, oppLast;
    checkPoint cp, cpLast;
    int cv; // costant valosaty
    int x,y,thrust;
    int nexdtX, nextY;
    bool boost=true;
    
    void loopData(int ix, int iy, int cpx, int cpy, int cpd, int cpa, int oppx, int oppy)
    {
        last.set(current);
        current.set(ix,iy);
        cpLast.set(cp);
        cp.set(cpx,cpy,cpd,cpa);
        oppLast.set(opp);
        opp.set(oppx,oppy);
    };
    
    std::string getResult()
    {
        std::string result=std::string();
        cv = last.distance(current);
        
        x=cp.loca.x; y=cp.loca.y;
        if(cp.close(current))
        {//brake
            if(cp.dist < 7) 
            {
                 x=last.x; y=last.y;
                if(cv>100)  thrust = 100;
                else thrust = cv;
            }
            else if(cp.dist < 50 && (cv>550)) //was < 50
            {
             //   thrust = 20; x=last.x; y=last.y;
                 x=last.x; y=last.y;
                 thrust = 100;
            }
            else if(cp.dist < 60 && cv>570) thrust = 20;
            else if(cp.dist < 80 && cv>640) thrust = 42;//was 42
            else if(cv>700) thrust = 50;
            else if(cv<550) thrust =100;
            else thrust = 80;
        }
        else if(cp.turning())
        { thrust = 47;   
            cerr<<"cv:"<<std::to_string(cv)<<" turning 0 thrust"<<endl;
        }
        else if(boost && cp.strait() && cp.dist>3000)
        {thrust=1000;
            cerr<<"cv:"<<std::to_string(cv)<<" boost"<<endl;}
        else if(cp.simi_close(current)&& cv>700)
        { thrust = 85; cerr<<"cv:"<<std::to_string(cv)<<" turning simi_close"<<endl;}
        else
        { thrust = 100;}
        
        if(thrust>100)
        {   result = std::to_string(x) +" "+ std::to_string(y) +" "+ "BOOST";}
        else
        {   result = std::to_string(x) +" "+ std::to_string(y) +" "+ std::to_string(thrust);}

        return result; 
        
    };
    
};
//-------------------------------------------------------------------

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    ride mr=ride();//My Ride
    // game loop
    while (1) 
    {
        
        int x;
        int y;
        int nextCheckpointX; // x position of the next check point
        int nextCheckpointY; // y position of the next check point
        int nextCheckpointDist; // distance to the next checkpoint
        int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
        int opponentX;
        int opponentY;
        cin >> opponentX >> opponentY; cin.ignore();
    //*/
        mr.loopData(x,y,nextCheckpointX,nextCheckpointY,nextCheckpointDist,nextCheckpointAngle,opponentX,opponentY);
        cout << mr.getResult() << endl;       
      }
}
//-------------------------------------------------------------------
