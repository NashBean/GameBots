#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//-------------------------------------------------------------------
const int STRIKE_BACK_MAJOR_VERSION = 2;
const int STRIKE_BACK_MINOR_VERSION = 4;

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
        if(aride.distance(loca) < 100) return true;//was 200 , 150 works better
        else return false;
    };
    bool simi_close(Position& aride)
    {
        if(aride.distance(loca) < 150) return true;//300
        else return false;
    };
    bool aproch_close(Position& aride)
    {
        if(aride.distance(loca) < 200) return true;//320
        else return false;
    };

    bool turning()
    {
        if(abs(angl)< 10) return false;// was 74 was last 45 working
        else return true;
    };
    bool strait()
    {
        if(abs(angl)<= 10) return true;
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
    int aproch_cv = 300;//250 450
    int break_cv = 50;
    int close_cv = 175;
    int simi_close_cv = 250;// was 200 & 400
    int turn_around_cv = 100;
    int drift_cv = 200;
    int stear_cv = 300;
    
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
        if(cp.loca != cpLast.loca) thrust = 0;
        
    };
    
    void bump_up_thrust()
    {
        if(thrust<96)  thrust += 5;
        else thrust =100;    
    };

    void bump_down_thrust()
    {
        if(thrust>5)  thrust -= 5;
        else thrust = 0;    
    };

    void reverse_thrust()
    {
        reset_thrust = thrust;
        x=last.x; y=last.y;
        if(cv>100)  thrust = 100;
        else thrust =20;    
    };
    
    std::string getResult()
    {
        std::string result=std::string();
        cv = last.distance(current);
        ed = opp.distance(current);
        
        x=cp.loca.x; y=cp.loca.y;
        
        
        if(cp.close(current))
        {//brake
        
            if(cp.dist < 7)//was20
            {
                if(cv > (break_cv+10)) reverse_thrust();
                else if(cv < break_cv) bump_up_thrust();
                else if(cv > break_cv) bump_down_thrust();
            }
            else if(cp.dist < 14)//50
            {
                if(cv > (break_cv+20)) bump_up_thrust();
                else if(cv < break_cv) bump_up_thrust();
                else if(cv > break_cv) bump_down_thrust();
            }
            else 
            {
                if(cv < close_cv) bump_up_thrust();
                else if(cv > close_cv) bump_down_thrust();
            }
            
   /*         
            if(cp.dist < 20 && cv>400)  {reverse_thrust(); }
            else if(cp.dist < 20 && cv<400) 
            {
                if(cv<100 && cp.angl<5)  thrust = 70;
                else if(cv<200 && cp.angl<14)  thrust = 40;
                else if(cv<300 && cp.angl>30)  thrust = 20;
                else thrust = 30;// maby 40
            }
            else if(cp.dist < 14 && (cv>400)) 
            {reverse_thrust();}
            else if(cp.dist < 50 && (cv<200)) 
            {
                 thrust = 32;
            }
            else if(cp.dist < 50 && cv>550) reverse_thrust();//was 20
            else if(cp.dist < 100 && cv<450) bump_up_thrust();//thrust = 42;//was 42
            else if(cp.dist < 100 && cv>600) reverse_thrust() ;// last 2 was 725 42  - 400 2
            //else if(cv>725) thrust = 2;// was 725 42  - 400 2
            //else if(cv>675) thrust = 22;//was 675  - 350 22
            else thrust = 20;// was 42
            //*/
        }
       // else if(cp.simi_close(current)&& cv<simi_close_cv  )//200)        { bump_up_thrust//thrust = 22;         cerr<<"cv:"<<std::to_string(cv)<<" turning simi_close"<<endl;}
       // else if(cp.simi_close(current)&& cv>simi_close_cv)//400) bump_down_thrust()//thrust = 12;       cerr<<"cv:"<<std::to_string(cv)<<" turning simi_close"<<endl;}
        
        else if(cp.simi_close(current))
        { 
            if(cv<simi_close_cv) bump_up_thrust();
            else if(cv>simi_close_cv) bump_down_thrust();
            cerr<<"cv:"<<std::to_string(cv)<<" turning simi_close"<<endl;
        }
        
 		else if(cp.aproch_close(current))
		{
            if(cv<aproch_cv) bump_up_thrust();
            else if(cv>aproch_cv) bump_down_thrust();
           // if(cv > 750) thrust = 70; else if(cv > 350) thrust = 80; else  thrust = 100;   
		}

        else if(cp.turning())
        { 
            int a = abs(cp.angl);

            if(a>155) thrust=7;
            else if(a>125) thrust=14;
            else if(a>110) thrust=24;
            else if(a>90) thrust=34;
            else if(a>55) thrust=44;
            else if(a>45) thrust=47;
            else if(a>35)thrust=54;
            else if(a>25)thrust=57;
            else if(a>15)thrust=64;
            else thrust=67;
  
  
        if(a>120 && a<165 && cv < turn_around_cv) bump_up_thrust();
        else if(a>120 && a<165  && cv > turn_around_cv) bump_down_thrust();
        else if(a>90 && a<121  && cv < drift_cv) bump_up_thrust();
        else if(a>90 && a<121  && cv > drift_cv) bump_down_thrust();
        else if(a<91 && cv < stear_cv) bump_up_thrust();
        else if(a<91 && cv > stear_cv) bump_down_thrust();

        //    if(a >110 && cv > 350) thrust = 2;
        //    else if(a > 110 && cv < 100) thrust = 20;// was 20 then 40
        //    else if(a > 90 && cv > 350) thrust = 14; //was 350 & 14 added abve line
        //    else if(a > 90 && cv < 350) thrust = 14;
        //    else if(a > 60 && cv > 350) thrust = 20;
        //    else if(a > 60 && cv < 350) thrust = 20;
        //    else if(a > 45 && cv > 350) thrust = 22;
        //    else if(a > 45 && cv < 350) thrust = 32;
        //    else if(a > 15 && cv > 350) thrust = 22;
        //    else if(a > 15 && cv < 350) thrust = 32;
        //    else if(cv > 350) thrust = 22;
        //    else if(cv < 350) thrust = 42;
        //    else            thrust = 30;   
            cerr<<"cv:"<<cv<<" turning thrust "<< thrust <<endl;
        }
        else if(ed < 35)// && cv>200)was 25
        {// bump
            reset_thrust = thrust;
                 x=opp.x; y=opp.y;
                 thrust = 100;
                 cerr<<"cv:"<<std::to_string(cv)<<" Bump speed"<<endl;
        }
       else if(boost && cp.strait() && cp.dist>3000)
        {reset_thrust=thrust; thrust=1000; boost=false;
            cerr<<"cv:"<<std::to_string(cv)<<" boost"<<endl;}
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

