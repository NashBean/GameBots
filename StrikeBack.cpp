#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//-------------------------------------------------------------------
const int STRIKE_BACK_MAJOR_VERSION = 2;
const int STRIKE_BACK_MINOR_VERSION = 10;

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
        if(aride.distance(loca) < 50) return true;//was 200 , 150 works better
        else return false;
    };
    bool simi_close(Position& aride)
    {
        if(aride.distance(loca) < 100) return true;//300
        else return false;
    };
    bool approach_close(Position& aride)
    {
        if(aride.distance(loca) < 300) return true;//320
        else return false;
    };

    bool turning()
    {
        if(abs(angl)< 3) return false;// was 74 was last 45 working
        else return true;
    };
    bool strait()
    {
        if(angl== 0) return true;
        else return false;
    };
};
//-------------------------------------------------------------------

struct ride
{
    Position current, next, last, opp, oppLast;
    checkPoint cp, cpLast;
    int cv, ed; // costant valosaty, enamy distance
    int x,y,thrust;
    int reset_thrust=0;
    bool boost=true;
    int approach_cv = 300;//250 450
    int break_cv = 100;
    int close_cv = 150;
    int simi_close_cv = 200;// was 200 & 400
    int u_turn1_cv = 100;
    int u_turn2_cv = 125;
    int u_turn3_cv = 150;
    int turn_around1_cv = 200;
    int turn_around2_cv = 250;
    int turn_around3_cv = 300;
    int drift1_cv = 500;
    int drift2_cv = 550;
    int drift3_cv = 600;
    int stear1_cv = 650;
    int stear2_cv = 700;
    int stear3_cv = 750;
    int fly_cv = 950;
    
    vector<checkPoint> cp_lst;
    
    
    void loopData(int ix, int iy, int cpx, int cpy, int cpd, int cpa, int oppx, int oppy)
    {
        last.set(current);
        current.set(ix,iy);
        cpLast.set(cp);
        cp.set(cpx,cpy,cpd,cpa);
        oppLast.set(opp);
        opp.set(oppx,oppy);
        
        if(reset_thrust) {  thrust=reset_thrust; reset_thrust=0;}
        if(cp.loca != cpLast.loca) thrust = 7;
        
    };
    
    void bump_up_thrust()
    {
        if(thrust<98)  thrust += 2;
        else thrust =100;    
        cerr<<"cv:"<<cv<<" thrust:"<< thrust<< " angle:" <<cp.angl <<endl;
    };

    void bump_down_thrust()
    {
        if(thrust>0)  thrust -= 1;
        else thrust = 0;    
        cerr<<"cv:"<<cv<<" thrust:"<< thrust<< " angle:" <<cp.angl <<endl;
    };

    void reverse_thrust()
    {
        reset_thrust = thrust;
        x=last.x; y=last.y;
        if(cv>300)  thrust = 100;
        else thrust =50;    
        cerr<<"cv:"<<cv<<" thrust:"<< thrust<< " angle:" <<cp.angl <<endl;
    };
    
    std::string getResult()
    {
        std::string result=std::string();
        cv = last.distance(current);
        ed = opp.distance(current);
        
        x=cp.loca.x; y=cp.loca.y;
        
        
        if(cp.close(current))
        {//brake
        
            if(cp.dist < 20)//was20
            {
                if(cv > (break_cv+50)) reverse_thrust();
                else if(cv < break_cv) bump_up_thrust();
                else if(cv > break_cv) bump_down_thrust();
            }
            else if(cp.dist < 40)//50
            {
                if(cv > (break_cv+100)) bump_up_thrust();
                else if(cv < break_cv) bump_up_thrust();
                else if(cv > break_cv) bump_down_thrust();
            }
            else 
            {
                if(cv < close_cv) bump_up_thrust();
                else if(cv > close_cv) bump_down_thrust();
            }
        }
 
        else if(cp.simi_close(current))
        { 
            if(cv<simi_close_cv) bump_up_thrust();
            else if(cv>simi_close_cv) bump_down_thrust();
            cerr<<"cv:"<<std::to_string(cv)<<" turning simi_close"<<endl;
        }
        
 		else if(cp.approach_close(current))
		{// approach
            if(cv<approach_cv) bump_up_thrust();
            else if(cv>approach_cv) bump_down_thrust();
		}

        else if(cp.turning())
        { // turning
            int a = abs(cp.angl);
  
            if(a>170 && cv < u_turn1_cv)bump_up_thrust();
            else if(a>170 && cv > u_turn1_cv) bump_down_thrust();
            else if(a>160 && cv < u_turn2_cv)bump_up_thrust();
            else if(a>160 && cv > u_turn2_cv) bump_down_thrust();
            else if(a>140 && cv < u_turn3_cv)bump_up_thrust();
            else if(a>140 && cv > u_turn3_cv) bump_down_thrust();
            
            else if(a>120 && cv < turn_around1_cv) bump_up_thrust();
            else if(a>120 && cv > turn_around1_cv) bump_down_thrust();
            else if(a>100 && cv < turn_around2_cv) bump_up_thrust();
            else if(a>100 && cv > turn_around2_cv) bump_down_thrust();
            else if(a>75 && cv < turn_around3_cv) bump_up_thrust();
            else if(a>75 && cv > turn_around3_cv) bump_down_thrust();
    
            else if(a>45  && cv < drift1_cv) bump_up_thrust();
            else if(a>45  && cv > drift1_cv) bump_down_thrust();
            else if(a>30  && cv < drift2_cv) bump_up_thrust();
            else if(a>30  && cv > drift2_cv) bump_down_thrust();
            else if(a>20  && cv < drift3_cv) bump_up_thrust();
            else if(a>20  && cv > drift3_cv) bump_down_thrust();
    
    
            else if(a>15 && cv < stear1_cv) bump_up_thrust();
            else if(a>15 && cv > stear1_cv) bump_down_thrust();
            else if(a>10 && cv < stear2_cv) bump_up_thrust();
            else if(a>10 && cv > stear2_cv) bump_down_thrust();
            else if(a>7 && cv < stear3_cv) bump_up_thrust();
            else if(a>7 && cv > stear3_cv) bump_down_thrust();
    
            else if(cv < fly_cv) bump_up_thrust();
            else if(cv > fly_cv) bump_down_thrust();

        cerr<<"cv:"<<cv<<" thrust:"<< thrust<< " angle:" <<cp.angl << " turning"<<endl;
        }
        else if(ed < 35)// && cv>200)was 25
        {// bump
            reset_thrust = thrust;
                 x=opp.x; y=opp.y;
                 thrust = 100;
        cerr<<"cv:"<<cv<<" thrust:"<< thrust<< " angle:" <<cp.angl << " thrust bump"<<endl;
        }
       else if(boost && cp.strait() && cp.dist>3000)
        {reset_thrust=thrust; thrust=1000; boost=false;
        cerr<<"cv:"<<cv<<" thrust:"<< thrust<< " angle:" <<cp.angl <<endl;
        }
        else
        { thrust = 100;}
        
        if(thrust>100)
        {   result = std::to_string(x) +" "+ std::to_string(y) +" "+ "BOOST";}
        else
        {   result = std::to_string(x) +" "+ std::to_string(y) +" "+ std::to_string(thrust);}

        cerr<<"cv:"<<cv<<" thrust:"<< thrust<< " angle:" <<cp.angl <<endl;
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

