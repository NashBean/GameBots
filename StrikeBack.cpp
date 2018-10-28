#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//-------------------------------------------------------------------
const int STRIKE_BACK_MAJOR_VERSION = 3;
const int STRIKE_BACK_MINOR_VERSION = 8;//b 

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
struct turnData
{
    int break_speed = 250;
    int break_distance = 50;
    int close_speed = 250;
    int close_distance = 200;
    int approach_speed = 300;//300;//250 450
    int approach_distance = 450;//300;//250 450
    int distance_adjustment = 50;
    int speed_adjustment = 50;

    int turn_around_speed = 145;
    int turn_around_angle = 170;
    int u_turn_speed = 175; 
    int u_turn_angle = 110;
    int drift_speed = 200;
    int drift_angle = 50;
    int hard_turn_speed = 225;
    int hard_turn_angle = 40;
    int light_turn_speed = 550;
    int light_turn_angle = 7;
    int top_speed = 777;
    
    int angle=0;
    int skid=0;
    
};

struct checkPoint
{
    turnData tData;    
    Position loca;//location
    int dist, angl;
 
    bool operator ==(checkPoint& other)
    {
        if(loca == other.loca)   return true;
        return false;
    };
   
    void update(checkPoint& other)
    {
        dist = other.dist; 
        angl = other.angl;
    };

    void set(int px, int py,int di,int ai)
    {loca.set(px,py); dist = di; angl=ai;};
    
    void set(checkPoint &cp )
    {loca.set(cp.loca); dist = cp.dist; angl=cp.angl;};
    

    bool close(Position& aride)
    {
        if(aride.distance(loca) < tData.close_distance) return true;//was 200 , 150 works better
        else return false;
    };
    bool approach_close(Position& aride)
    {
        if(aride.distance(loca) < tData.approach_distance) return true;//320 then 500
        else return false;
    };

    bool turning()
    {
        if(abs(angl)< 7) return false;//42 was best was 74 was last 45 working
        else return true;
    };
    bool strait()
    {
        if(angl< 7) return true;
        else return false;
    };
    void display()
    {       
	cerr<<"turning angle:"<<endl;//<<angl<<" distance:"<< dist <<" skid:"<< tData.skid <<endl;
    };
};
//-------------------------------------------------------------------

struct cockpit
{
    turnData defaltTurnData;
    int lap=0;
    int lap_time=0;
    int last_lap_time=0;
    int cv = -1;
    int ed = -1;//TODO init opp.distance(current);

    int next_index = -1;
    int last_index = -1;
    int track_index = 0;
    vector<checkPoint> track;
    
    void addCheckPoint(checkPoint& cp){track.push_back(cp);};//todo track.init();
    
    void updateCheckPoint(checkPoint& cp)//, int index)
    {
        for(size_t c=0; c<track.size(); c++)
        { 
            if(cp == track[c]) 
            {
                track[c].update(cp);   
                c=track.size();  
            } 
        }
    };
    
    void logCheckPoint(checkPoint& cp )
    {
        lap_time++;
        if(!lap)
        {
            if(!track.size()) 
            { addCheckPoint(cp); last_index=0;}//start point
            else if(next_index == -1)
            {addCheckPoint(cp); next_index=1;}//first check point
            else if(cp == track[0]  && next_index!=0)
            {
                int temp_time=last_lap_time;
                last_lap_time = lap_time;
                lap++;
                lap_time=0;
                track[0].update(cp);
                next_index=1;
                last_index=0;
               // cerr << "Lap:"<<lap<<"  Lap Time="<<last_lap_time<<endl;
            }
            else if(cp == track[0])
            {
                track[0].update(cp);
            }
            else if(cp == track[next_index])
            {
                track[next_index].update(cp);
            }
            else //if(cp != track[nextCPindex])
            {
                last_index=next_index;
                next_index++;
                addCheckPoint(cp);
            }
        }
        else if(lap)
        {
            if(cp == track[0] && next_index!=0)
            {
                int temp_time=last_lap_time;
                last_lap_time = lap_time;
                lap++;
                lap_time=0;
                track[0].update(cp);
                next_index=1;
                last_index=0;
            }
            else if(cp == track[0])
            {
                track[0].update(cp);
            }
            else if(next_index!=next_index)
            {
                last_index=next_index;
                next_index++;
                track[next_index].update(cp);
            }
            else 
            {
                track[next_index].update(cp);
            }
        }
       else
        {
    	//cerr<<"error: case not expected in cockpit.logCheckPoint(&cp) :"<<endl;
    	track[next_index].display();
        }
     };
    
    void bump_back_approach()
    {
        checkPoint& cp = track[last_index];

        if(cp.tData.approach_distance>=cp.tData.distance_adjustment)
        { cp.tData.approach_distance -=  cp.tData.distance_adjustment;}
        else
        { cp.tData.approach_distance = 0;}
        
        if(cp.tData.approach_speed > cp.tData.speed_adjustment)
        { cp.tData.approach_speed -=  cp.tData.speed_adjustment;}
        else
        { cp.tData.approach_speed = 0;}
    };

    void bump_up_approach()
    {
        checkPoint& cp = track[last_index];
        cp.tData.approach_distance +=  cp.tData.distance_adjustment;
        cp.tData.approach_speed +=  cp.tData.speed_adjustment;
    };
    
    void display()
    {
    checkPoint& cp = track[next_index];
	cerr<<"turning angle:"<<cp.angl<<" skid:"<< cp.tData.skid <<endl;
    };

    
    int tapBrake()
	{//brake
    checkPoint& cp = track[next_index];
    turnData& td = cp.tData;
    //int td.distance_adjustment;
    //int td.speed_adjustment;
		
		if(cp.dist>5 && cp.dist < td.break_distance ) 
		{
		    if(cv>100) return -2;// {a_ride.reverse_thrust(100); }
		    else return 0;//{a_ride.reverse_thrust(cv);}
		}
		else if(cp.dist < td.close_distance) 
		{
		    if(cv<td.close_speed) return 1;// a_ride.bump_up_thrust; 
		    else if(cv>(td.close_speed-150)) return -2;// a_ride.bump_up_thrust; 
		    else if(cv>td.close_speed) return -1;//a_ride.bump_down_thrust;
		    else return 0;//a_ride.wait();
		} 
		else if(cp.dist < td.approach_distance) 
		{
		    if(cv<td.approach_speed) return 1;//a_ride.bump_up_thrust; 
		    else if(cv>td.approach_speed) return -1;//a_ride.bump_down_thrust;
		    else return 0;//a_ride.wait();
		}
		else {return 0;}//thrust = 0;
	};
    
	int adjTurnSpeed()// -1=down o=wait 1=up
	{//todo change cv to speed and check everything as you do it.

        cerr << "adjTurnSpeed "<< endl;

        if(last_index<0 || next_index<0) return 0;

        checkPoint& cp = track[last_index];
        cerr << "assign checkPoint "<< endl;
        turnData& td = cp.tData;
        cerr << "assign turn data"<<  cp.angl<< endl;
		// take out abs to figure out what direction
		int a =cp.angl;
        cerr << "a "<< a<<endl;
		a = abs(a);
		

		if(a>td.turn_around_angle && cv < td.turn_around_speed) {return 1;}// {a_ride.bump_up_thrust();}
		else if(a>td.turn_around_angle && cv > td.turn_around_speed) {return -1;}// {a_ride.bump_down_thrust();}
		else if(a>td.u_turn_angle && cv < td.u_turn_speed) {return 1;}// { a_ride.bump_up_thrust();}
		else if(a>td.u_turn_angle && cv > td.u_turn_speed) {return -1;}// { a_ride.bump_down_thrust();}
		else if(a>td.drift_angle  && cv < td.drift_speed) {return 1;}// { a_ride.bump_up_thrust();}
		else if(a>td.drift_angle  && cv > td.drift_speed) {return -1;}// { a_ride.bump_down_thrust();}
		else if(a>td.hard_turn_angle && cv < td.hard_turn_speed) {return 1;}// { a_ride.bump_up_thrust();}
		else if(a>td.hard_turn_angle && cv > td.hard_turn_speed) {return -1;}// { a_ride.bump_down_thrust();}
		else if(a>td.light_turn_angle && cv < td.light_turn_speed) {return 1;}// { a_ride.bump_up_thrust();}
		else if(a>td.light_turn_angle && cv > td.light_turn_speed) {return -1;}// { a_ride.bump_down_thrust();}
		else if(cv < td.top_speed) {return 2;}// {a_ride.bump_up_thrust();}
		else if(cv > td.top_speed)  {return -1;}//{a_ride.bump_down_thrust();}
	    else {return 0;}// {a_ride.wait();}
//	td.diplay();
	};
};


struct Ride
{
    Position current, next, last, opp, oppLast;
    checkPoint cp, cpLast;
    int cv, ed; // costant valosaty, enamy distance
    int x,y,thrust;
    int bump_distance = 50;//50 is good  was 30
    int reset_thrust=0;
    bool boost=true;
    
    cockpit pit; 
    turnData& tD=pit.defaltTurnData;
    void loopData(int ix, int iy, int cpx, int cpy, int cpd, int cpa, int oppx, int oppy)
    {
        last.set(current);
        current.set(ix,iy);
        cpLast.set(cp);
        cp.set(cpx,cpy,cpd,cpa);
        oppLast.set(opp);
        opp.set(oppx,oppy);
        
        if(reset_thrust) {  thrust=reset_thrust; reset_thrust=0;}
    };

    // TODO bool isSkidding() {    };
    
    void reverse_thrust()
    {
        reset_thrust = thrust;
        thrust = 100;
        x=last.x; y=last.y;
    };
    
    void reverse_thrust(int thr)
    {
        reset_thrust = thrust;
        x=last.x; y=last.y;
        thrust = thr;
    };

    void bump_opp()
    {
        reset_thrust = thrust;
		x=opp.x; y=opp.y;
    	 thrust = 100;
	};
    
    void bump_up_thrust()
    {
        if(thrust<95)  {thrust += 5;}
        else {thrust =100; }   
    };

    void bump_down_thrust()
    {
        if(thrust>5)  {thrust -= 5;}
        else {thrust = 0;}    
    };

    void bump_thrust(int targetCV)
    {    
        if(cv > (targetCV+150)) {reverse_thrust();}
        else if (cv > (targetCV)) {bump_down_thrust();}
        else {bump_up_thrust();}
    };

    void tapBrake()
    {
	  int adjspeed = pit.tapBrake();
	  if(adjspeed == 1 ) {bump_up_thrust();}
	  else if(adjspeed > 1 ) 
	  { for(size_t b=0; b<adjspeed; b++)
	            {bump_up_thrust();     }
	  }
	  else if(adjspeed == -1) {bump_down_thrust();}
	  else if(adjspeed < -1)
	  { reverse_thrust();  }
	  else {bump_down_thrust();}
    };

	void adj_turn_speed()
	{
	  //*/  
	  int adjspeed = pit.adjTurnSpeed();
	  if(adjspeed == 1 ) {bump_up_thrust();}
	  else if(adjspeed > 1 ) 
	  { thrust=100; }
	  else if(adjspeed == -1) {bump_down_thrust();}
	  else if(adjspeed < -1)
	  { reverse_thrust();  }
	  else {bump_down_thrust();}
	};

    string getResult()
    {
        string result="";
        cv = last.distance(current);
        ed = opp.distance(current);
        x=cp.loca.x; y=cp.loca.y;
        
        if(ed < bump_distance)
        { 	bump_opp(); }
        else if(cp.close(current))
        {
            tapBrake();
        //    int appBrake = pit.tapBrake();
        //    if(appBrake>0){bump_up_thrust();}
        //    else if(appBrake==-1){bump_down_thrust();}
        //    else if(appBrake<-1) {reverse_thrust();}
        //    else {bump_down_thrust();}
        }
        else if(cp.turning())// turning
        { 	adj_turn_speed(); }
        else if(boost && cp.angl<1 && cp.dist>4000)
        {	reset_thrust=thrust; thrust=1000; boost=false;  }
        else { thrust = 100;}
        
        if(thrust>100)
        {   result = std::to_string(x) +" "+ std::to_string(y) +" "+ "BOOST";}
        else
        {   result = std::to_string(x) +" "+ std::to_string(y) +" "+ std::to_string(thrust);}

        
        cerr<<" output x="<< x <<" output y="<< y <<endl;
        cerr<<" output="<< result <<endl;

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
    Ride myRide;//My Ride
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

        myRide.loopData(x,y,nextCheckpointX,nextCheckpointY,nextCheckpointDist,nextCheckpointAngle,opponentX,opponentY);
        cout << myRide.getResult() << endl;       
    };
}
//-------------------------------------------------------------------


    
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
struct turnData
{
    int break_speed = 250;
    int break_distance = 50;
    int close_speed = 250;
    int close_distance = 200;
    int approach_speed = 300;//300;//250 450
    int approach_distance = 450;//300;//250 450
    int distance_adjustment = 50;
    int speed_adjustment = 50;

    int turn_around_speed = 145;
    int turn_around_angle = 170;
    int u_turn_speed = 175; 
    int u_turn_angle = 110;
    int drift_speed = 200;
    int drift_angle = 50;
    int hard_turn_speed = 225;
    int hard_turn_angle = 40;
    int light_turn_speed = 550;
    int light_turn_angle = 7;
    int top_speed = 777;
    
    int angle=0;
    int skid=0;
    
};

struct checkPoint
{
    turnData tData;    
    Position loca;//location
    int dist, angl;
 
    bool operator ==(checkPoint& other)
    {
        if(loca == other.loca)   return true;
        return false;
    };
   
    void update(checkPoint& other)
    {
        dist = other.dist; 
        angl = other.angl;
    };

    void set(int px, int py,int di,int ai)
    {loca.set(px,py); dist = di; angl=ai;};
    
    void set(checkPoint &cp )
    {loca.set(cp.loca); dist = cp.dist; angl=cp.angl;};
    

    bool close(Position& aride)
    {
        if(aride.distance(loca) < tData.close_distance) return true;//was 200 , 150 works better
        else return false;
    };
    bool approach_close(Position& aride)
    {
        if(aride.distance(loca) < tData.approach_distance) return true;//320 then 500
        else return false;
    };

    bool turning()
    {
        if(abs(angl)< 7) return false;//42 was best was 74 was last 45 working
        else return true;
    };
    bool strait()
    {
        if(angl< 7) return true;
        else return false;
    };
    void display()
    {       
	cerr<<"turning angle:"<<endl;//<<angl<<" distance:"<< dist <<" skid:"<< tData.skid <<endl;
    };
};
//-------------------------------------------------------------------

struct cockpit
{
    turnData defaltTurnData;
    int lap=0;
    int lap_time=0;
    int last_lap_time=0;
    int cv = -1;
    int ed = -1;//TODO init opp.distance(current);

    int next_index = -1;
    int last_index = -1;
    int track_index = 0;
    vector<checkPoint> track;
    
    void addCheckPoint(checkPoint& cp){track.push_back(cp);};//todo track.init();
    
    void updateCheckPoint(checkPoint& cp)//, int index)
    {
        for(size_t c=0; c<track.size(); c++)
        { 
            if(cp == track[c]) 
            {
                track[c].update(cp);   
                c=track.size();  
            } 
        }
    };
    
    void logCheckPoint(checkPoint& cp )
    {
        lap_time++;
        if(!lap)
        {
            if(!track.size()) 
            { addCheckPoint(cp); last_index=0;}//start point
            else if(next_index == -1)
            {addCheckPoint(cp); next_index=1;}//first check point
            else if(cp == track[0]  && next_index!=0)
            {
                int temp_time=last_lap_time;
                last_lap_time = lap_time;
                lap++;
                lap_time=0;
                track[0].update(cp);
                next_index=1;
                last_index=0;
               // cerr << "Lap:"<<lap<<"  Lap Time="<<last_lap_time<<endl;
            }
            else if(cp == track[0])
            {
                track[0].update(cp);
            }
            else if(cp == track[next_index])
            {
                track[next_index].update(cp);
            }
            else //if(cp != track[nextCPindex])
            {
                last_index=next_index;
                next_index++;
                addCheckPoint(cp);
            }
        }
        else if(lap)
        {
            if(cp == track[0] && next_index!=0)
            {
                int temp_time=last_lap_time;
                last_lap_time = lap_time;
                lap++;
                lap_time=0;
                track[0].update(cp);
                next_index=1;
                last_index=0;
            }
            else if(cp == track[0])
            {
                track[0].update(cp);
            }
            else if(next_index!=next_index)
            {
                last_index=next_index;
                next_index++;
                track[next_index].update(cp);
            }
            else 
            {
                track[next_index].update(cp);
            }
        }
       else
        {
    	//cerr<<"error: case not expected in cockpit.logCheckPoint(&cp) :"<<endl;
    	track[next_index].display();
        }
     };
    
    void bump_back_approach()
    {
        checkPoint& cp = track[last_index];

        if(cp.tData.approach_distance>=cp.tData.distance_adjustment)
        { cp.tData.approach_distance -=  cp.tData.distance_adjustment;}
        else
        { cp.tData.approach_distance = 0;}
        
        if(cp.tData.approach_speed > cp.tData.speed_adjustment)
        { cp.tData.approach_speed -=  cp.tData.speed_adjustment;}
        else
        { cp.tData.approach_speed = 0;}
    };

    void bump_up_approach()
    {
        checkPoint& cp = track[last_index];
        cp.tData.approach_distance +=  cp.tData.distance_adjustment;
        cp.tData.approach_speed +=  cp.tData.speed_adjustment;
    };
    
    void display()
    {
    checkPoint& cp = track[next_index];
	cerr<<"turning angle:"<<cp.angl<<" skid:"<< cp.tData.skid <<endl;
    };

    
    int tapBrake()
	{//brake
    checkPoint& cp = track[next_index];
    turnData& td = cp.tData;
    //int td.distance_adjustment;
    //int td.speed_adjustment;
		
		if(cp.dist>5 && cp.dist < td.break_distance ) 
		{
		    if(cv>100) return -2;// {a_ride.reverse_thrust(100); }
		    else return 0;//{a_ride.reverse_thrust(cv);}
		}
		else if(cp.dist < td.close_distance) 
		{
		    if(cv<td.close_speed) return 1;// a_ride.bump_up_thrust; 
		    else if(cv>(td.close_speed-150)) return -2;// a_ride.bump_up_thrust; 
		    else if(cv>td.close_speed) return -1;//a_ride.bump_down_thrust;
		    else return 0;//a_ride.wait();
		} 
		else if(cp.dist < td.approach_distance) 
		{
		    if(cv<td.approach_speed) return 1;//a_ride.bump_up_thrust; 
		    else if(cv>td.approach_speed) return -1;//a_ride.bump_down_thrust;
		    else return 0;//a_ride.wait();
		}
		else {return 0;}//thrust = 0;
	};
    
	int adjTurnSpeed()// -1=down o=wait 1=up
	{//todo change cv to speed and check everything as you do it.

        cerr << "adjTurnSpeed "<< endl;

        if(last_index<0 || next_index<0) return 0;

        checkPoint& cp = track[last_index];
        cerr << "assign checkPoint "<< endl;
        turnData& td = cp.tData;
        cerr << "assign turn data"<<  cp.angl<< endl;
		// take out abs to figure out what direction
		int a =cp.angl;
        cerr << "a "<< a<<endl;
		a = abs(a);
		

		if(a>td.turn_around_angle && cv < td.turn_around_speed) {return 1;}// {a_ride.bump_up_thrust();}
		else if(a>td.turn_around_angle && cv > td.turn_around_speed) {return -1;}// {a_ride.bump_down_thrust();}
		else if(a>td.u_turn_angle && cv < td.u_turn_speed) {return 1;}// { a_ride.bump_up_thrust();}
		else if(a>td.u_turn_angle && cv > td.u_turn_speed) {return -1;}// { a_ride.bump_down_thrust();}
		else if(a>td.drift_angle  && cv < td.drift_speed) {return 1;}// { a_ride.bump_up_thrust();}
		else if(a>td.drift_angle  && cv > td.drift_speed) {return -1;}// { a_ride.bump_down_thrust();}
		else if(a>td.hard_turn_angle && cv < td.hard_turn_speed) {return 1;}// { a_ride.bump_up_thrust();}
		else if(a>td.hard_turn_angle && cv > td.hard_turn_speed) {return -1;}// { a_ride.bump_down_thrust();}
		else if(a>td.light_turn_angle && cv < td.light_turn_speed) {return 1;}// { a_ride.bump_up_thrust();}
		else if(a>td.light_turn_angle && cv > td.light_turn_speed) {return -1;}// { a_ride.bump_down_thrust();}
		else if(cv < td.top_speed) {return 2;}// {a_ride.bump_up_thrust();}
		else if(cv > td.top_speed)  {return -1;}//{a_ride.bump_down_thrust();}
	    else {return 0;}// {a_ride.wait();}
//	td.diplay();
	};
};


struct Ride
{
    Position current, next, last, opp, oppLast;
    checkPoint cp, cpLast;
    int cv, ed; // costant valosaty, enamy distance
    int x,y,thrust;
    int bump_distance = 50;//50 is good  was 30
    int reset_thrust=0;
    bool boost=true;
    
    cockpit pit; 
    turnData& tD=pit.defaltTurnData;
    void loopData(int ix, int iy, int cpx, int cpy, int cpd, int cpa, int oppx, int oppy)
    {
        last.set(current);
        current.set(ix,iy);
        cpLast.set(cp);
        cp.set(cpx,cpy,cpd,cpa);
        oppLast.set(opp);
        opp.set(oppx,oppy);
        
        if(reset_thrust) {  thrust=reset_thrust; reset_thrust=0;}
    };

    // TODO bool isSkidding() {    };
    
    void reverse_thrust()
    {
        reset_thrust = thrust;
        thrust = 100;
        x=last.x; y=last.y;
    };
    
    void reverse_thrust(int thr)
    {
        reset_thrust = thrust;
        x=last.x; y=last.y;
        thrust = thr;
    };

    void bump_opp()
    {
        reset_thrust = thrust;
		x=opp.x; y=opp.y;
    	 thrust = 100;
	};
    
    void bump_up_thrust()
    {
        if(thrust<95)  {thrust += 5;}
        else {thrust =100; }   
    };

    void bump_down_thrust()
    {
        if(thrust>5)  {thrust -= 5;}
        else {thrust = 0;}    
    };

    void bump_thrust(int targetCV)
    {    
        if(cv > (targetCV+150)) {reverse_thrust();}
        else if (cv > (targetCV)) {bump_down_thrust();}
        else {bump_up_thrust();}
    };

    void tapBrake()
    {
	  int adjspeed = pit.tapBrake();
	  if(adjspeed == 1 ) {bump_up_thrust();}
	  else if(adjspeed > 1 ) 
	  { for(size_t b=0; b<adjspeed; b++)
	            {bump_up_thrust();     }
	  }
	  else if(adjspeed == -1) {bump_down_thrust();}
	  else if(adjspeed < -1)
	  { reverse_thrust();  }
	  else {bump_down_thrust();}
    };

	void adj_turn_speed()
	{
	  //*/  
	  int adjspeed = pit.adjTurnSpeed();
	  if(adjspeed == 1 ) {bump_up_thrust();}
	  else if(adjspeed > 1 ) 
	  { thrust=100; }
	  else if(adjspeed == -1) {bump_down_thrust();}
	  else if(adjspeed < -1)
	  { reverse_thrust();  }
	  else {bump_down_thrust();}
	};

    string getResult()
    {
        string result="";
        cv = last.distance(current);
        ed = opp.distance(current);
        x=cp.loca.x; y=cp.loca.y;
        
        if(ed < bump_distance)
        { 	bump_opp(); }
        else if(cp.close(current))
        {
            tapBrake();
        //    int appBrake = pit.tapBrake();
        //    if(appBrake>0){bump_up_thrust();}
        //    else if(appBrake==-1){bump_down_thrust();}
        //    else if(appBrake<-1) {reverse_thrust();}
        //    else {bump_down_thrust();}
        }
        else if(cp.turning())// turning
        { 	adj_turn_speed(); }
        else if(boost && cp.angl<1 && cp.dist>4000)
        {	reset_thrust=thrust; thrust=1000; boost=false;  }
        else { thrust = 100;}
        
        if(thrust>100)
        {   result = std::to_string(x) +" "+ std::to_string(y) +" "+ "BOOST";}
        else
        {   result = std::to_string(x) +" "+ std::to_string(y) +" "+ std::to_string(thrust);}

        
        cerr<<" output x="<< x <<" output y="<< y <<endl;
        cerr<<" output="<< result <<endl;

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
    Ride myRide;//My Ride
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

        myRide.loopData(x,y,nextCheckpointX,nextCheckpointY,nextCheckpointDist,nextCheckpointAngle,opponentX,opponentY);
        cout << myRide.getResult() << endl;       
    };
}
//-------------------------------------------------------------------


    
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
        if(aride.distance(loca) < 200) return true;//was 200 , 150 works better
        else return false;
    };
    bool simi_close(Position& aride)
    {
        if(aride.distance(loca) < 400) return true;//300
        else return false;
    };
    bool approach_close(Position& aride)
    {
        if(aride.distance(loca) < 400) return true;//320
        else return false;
    };

    bool turning()
    {
        if(abs(angl)< 12) return false;//42 was best was 74 was last 45 working
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
    int u_turn1_cv = 75;
    int u_turn2_cv = 100;
    int u_turn3_cv = 125;
    int turn_around1_cv = 150;
    int turn_around2_cv = 200;
    int turn_around3_cv = 300;
    int drift1_cv = 350;
    int drift2_cv = 450;
    int drift3_cv = 500;
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
     //   if(cp.loca != cpLast.loca) thrust = 7;
    };
	
	void adj_turn_speed()
	{
		int a = abs(cp.angl);

		if(a>170 && cv < u_turn1_cv)bump_up_thrust();
		else if(a>170 && cv > u_turn1_cv) bump_down_thrust();
		else if(a>140 && cv < u_turn2_cv)bump_up_thrust();
		else if(a>140 && cv > u_turn2_cv) bump_down_thrust();
		else if(a>120 && cv < u_turn3_cv)bump_up_thrust();
		else if(a>120 && cv > u_turn3_cv) bump_down_thrust();
		
		else if(a>90 && cv < turn_around1_cv) bump_up_thrust();
		else if(a>90 && cv > turn_around1_cv) bump_down_thrust();
		else if(a>75 && cv < turn_around2_cv) bump_up_thrust();
		else if(a>75 && cv > turn_around2_cv) bump_down_thrust();
		else if(a>55 && cv < turn_around3_cv) bump_up_thrust();
		else if(a>55 && cv > turn_around3_cv) bump_down_thrust();

		else if(a>40  && cv < drift1_cv) bump_up_thrust();
		else if(a>40  && cv > drift1_cv) bump_down_thrust();
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

    void bump_opp()
    {
        reset_thrust = thrust;
		x=opp.x; y=opp.y;
    	 thrust = 100;
	};
    
    void bump_up_thrust()
    {
        if(thrust<96)  thrust += 4;
        else thrust =100;    
    };

    void bump_down_thrust()
    {
        if(thrust>3)  thrust -= 5;
        else thrust = 0;    
    };

    void bump_thrust(int targetCV)
    {
        if(cv > (targetCV+150)) reverse_thrust();
        else if (cv > (targetCV+1)) bump_down_thrust();
        else if (cv < (targetCV+1)) bump_up_thrust();
    };

	void approach()
	{
		if(cv > 750) thrust = 0;
		else if(cv > 650) thrust = 80;
		else  thrust = 90;   
	};
	
	void slow()
	{
        if(cv<400) { thrust = 42;}
        else if(cv>400){ thrust = 12; }
        else { thrust = 20;}
	};
	
	void brake()
	{//brake
		
		if(cp.dist < 20 && (cv>400)) {if(cv>100) reverse_thrust(100); else reverse_thrust(cv);}
		else if(cp.dist < 20 && cv<400) {if(cv<100) thrust=70; else if(cv<200) thrust=60; else if(cv<300) thrust=50; else thrust=20;} 
		else if(cp.dist < 40 && cv>400) {reverse_thrust(100);}
		else if(cp.dist < 50 && cv<400) {thrust =32;}
		else if(cp.dist < 100 && cv>400) thrust = 0;//was 20
		else if(cp.dist < 100 && cv<400) thrust = 30;//was 42
		else if(cv>400) thrust = 2;// was 725 42
		else if(cv>350) thrust = 22;//was 675
		else thrust = 44;
	};

    void reverse_thrust()
    {
        reset_thrust = thrust;
        x=last.x; y=last.y;
        if(cv>300)  thrust = 100;
        else thrust =50;    
        cerr<<"cv:"<<cv<<" thrust:"<< thrust<< " angle:" <<cp.angl <<endl;
    };
    
    void reverse_thrust(int thr)
    {
        reset_thrust = thrust;
        x=last.x; y=last.y;
        thrust = thr;
    };

    std::string getResult()
    {
        std::string result=std::string();
        cv = last.distance(current);
        ed = opp.distance(current);
        x=cp.loca.x; y=cp.loca.y;
        
        if(cp.close(current))
        {	brake();   }
        else if(cp.simi_close(current))
        { 	slow(); }
        else if(ed < 30 && cv>300)
        { 	bump_opp(); }
        else if(cp.turning())// turning
        { 	adj_turn_speed(); }
 		else if(cp.approach_close(current))
		{ 	approach(); }
        else if(boost && cp.strait() && cp.dist>3400)
        {	reset_thrust=thrust; thrust=1000; boost=false;  }
        else { thrust = 100;}
        
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

        mr.loopData(x,y,nextCheckpointX,nextCheckpointY,nextCheckpointDist,nextCheckpointAngle,opponentX,opponentY);
        cout << mr.getResult() << endl;       
      }
}
//-------------------------------------------------------------------

