#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Coded by: NashBean 2018
// https//iBeanSoftware.github.io/index.html
const int MARS_LANDER_MAJOR_VERSION = 0;
const int MARS_LANDER_MINOR_VERSION = 3;

/**
 * Save the Planet.
 * Use less Fossil Fuel.
 **/

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

 struct MarsSurface 
 {
     int min_lz_size=10;
     vector<Position> pes;
     int lz_startX;
  //   int lz_midX;
     int lz_endX;
     
     void plotPosition(Position p)
     {
         pes.push_back(p);   
     };
     
     void find_LZ()
     {
         cerr<<"-----------  find_LZ  -------------"<<endl;
         if(!pes.size()) return;
         int last_y, flat_first, flat_last;
         int isLevel = false;
         last_y=pes[0].y;
         cerr<<"  pes.size="<<pes.size()<<endl;
         for(int c=1; c< pes.size(); c++)
         {
             if(pes[c].y==pes[c-1].y)
             {
                 if(isLevel == false)
                 {
                     flat_first = c-1;
                     flat_last = c;
                     lz_startX=pes[c-1].x;
                     lz_endX=pes[c].x;
                     cerr<<"      flat_first & last set "<<flat_first<<endl;
                     isLevel++;// = true;
                 }
             }
         }

     };
     
     bool inLZ(int cx)
     {
         if(cx >= lz_endX) return false;
         else if(cx<= lz_startX) return false;
         else return true;
     }
     
  };


 struct MarsLander
 {
     int max_vs=40, min_vs=-40, max_hs=20, min_hs=-20;
    Position pos;
    int HS; // the horizontal speed (in m/s), can be negative.
    int VS; // the vertical speed (in m/s), can be negative.
    int F; // the quantity of remaining fuel in liters.
    int R; // the rotation angle in degrees (-90 to 90).
    int P; // the thrust power (0 to 4).
    
    MarsSurface surf;
   
    string targetRotation(int tr)
    {
     cerr<<" taget Rotation started: tr="<<to_string(tr)<<" HS="<<to_string(HS)<<endl;
     string result="";
       if(R > tr)
        {
            if(R <= (tr+15)) {result= to_string(tr);}
            else {result= to_string((R-15));}
        }
        else if(R<tr)
        {
            if(R >= (tr-15)) {result= to_string(tr);}
            else {result= to_string((R+15));}
        }
        else{result= to_string(tr);}
     cerr<<" taget Rotation ending: tr="<<to_string(tr)<<" HS="<<to_string(HS)<<endl;
        
        return result;
    };
    
    string targetPower(int tp) 
    {
        string result;
        cerr<<" targetPower       : power="<<to_string(P)<<" target Power="<<to_string(tp)<<endl;
        if(P<tp){result=to_string((P+1));}
        else if(P>tp){result=to_string((P-1));}
        else{result=to_string((tp));}
        cerr<<" targetPower       : power="<<to_string(P)<<"        VS="<<to_string(VS)<<endl;
        return result;
    };
    
    string calcResult()
    {
        int r=R, t=P; 
        string result;
     //   if(HS==0 && VS==0){return "0 0";}
     //   int tempx = surf.lz_midX;
        int lzstart= surf.lz_startX;
        int lzend= surf.lz_endX;
        int alt_flag=0;

        cerr<<" CalcResult started: HS="<<to_string(HS)<<" VS="<<to_string(VS)<<endl;
        cerr<<" CalcResult        : pos x="<<to_string(pos.x)<<" pos y="<<to_string(pos.y)<<endl;
        cerr<<" CalcResult   : lz start x="<<to_string(lzstart)<<" end x="<<to_string(lzend)<<endl;


        if(abs(HS) >= (max_hs*2))
        {
            if(HS >= max_hs)
            {result = targetRotation(30);}
            else if(HS <= min_hs)        
            {result = targetRotation(-30);}
        }

        else if(abs(HS) >= (max_hs-1))
        {
            if(HS >= max_hs)
            {result = targetRotation(30);}
            else if(HS <= min_hs)        
            {result = targetRotation(-30);}
        }
        else if(abs(HS) < (max_hs-7) && !surf.inLZ(pos.x))
        {
            if(pos.x >= lzend)
            {result = targetRotation(30);}
            else if(pos.x <= lzstart)        
            {result = targetRotation(-30);}
            else if(abs(HS) > 3)
            {
                if(HS>0) {result = targetRotation(-30);}
                else if(HS<0) {result = targetRotation(30);}
                else{result = targetRotation(0);}
            }
            else 
            { result = targetRotation(0);}
        }
        else if(pos.x >= lzend)
        {
        
            if(pos.x > (lzend+2000))
            {
                result=targetRotation(30);
            }// 2000 away
            else if(pos.x > (lzend+1500)) 
            {
            result=targetRotation(20);}// 1500 away
            else if(pos.x > (lzend+1000)) 
            {
            result=targetRotation(10);}// 1500 away
            else if(pos.x > lzend) // closest lz edge 
            {
            result=targetRotation(0); }
            else
            {
            if(abs(HS) > (max_hs/2) ) {result=targetRotation(-15);}
            else if(abs(HS) < (max_hs/2) ) {result=targetRotation(15);}
            else{result=targetRotation(0);}
            }
        }
        else if(pos.x <= lzstart)
        {
            if(pos.x < (lzstart-2000))
            {result=targetRotation(-30);}// 2000 away
            else if(pos.x < (lzstart-1500)) 
            {result=targetRotation(-20);}// 1500 away
            else if(pos.x < (lzstart-1000)) 
            {result=targetRotation(-10);}// 1500 away
            else if(pos.x < lzstart && HS) // closest lz edge 
            { result=targetRotation(0); }
            else
            {
            if(abs(HS) > (max_hs/2) ) {result=targetRotation(15);}
            else{result=targetRotation(0);}
            }
        }
        else 
        {
            if(HS >3)
            result=targetRotation(-15);
            else if(HS < -3)
            result=targetRotation(15);
            else
            result=targetRotation(0);
        }
        
        result = result + " ";
   //     if((abs(HS)>max_hs)) {result = result + targetPower(4);}
        if(VS <= (min_vs+7)) {result = result + targetPower(4);}
        else if(VS < (min_vs)) {result = result + targetPower(3);}
        else if(VS > (min_vs-7)) {result = result + targetPower(2);}
        else if(VS > (min_vs-10)) {result = result + targetPower(1);}
        else if(VS > 0) {result = result + targetPower(0);}
        else {result = result + targetPower(3);}

        
        if(result.size()>=3)  return result;
        else return "0 4";
    };
 };
 
 int main()
 {
    MarsLander lander;
    int N; // the number of points used to draw the surface of Mars.
    int fx,fy;
    string result="-20 3";
    cin >> N; cin.ignore();
    for (int i=0; i < N; i++) 
    {
        Position p;
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> p.x >> p.y; cin.ignore();
        lander.surf.plotPosition(p);//pes.push_back(p);
    }
    lander.surf.find_LZ();
    
    // game loop
    while (1) 
    {
 /*/
        int X;
        int Y;
        int HS; // the horizontal speed (in m/s), can be negative.
        int VS; // the vertical speed (in m/s), can be negative.
        int F; // the quantity of remaining fuel in liters.
        int R; // the rotation angle in degrees (-90 to 90).
        int P; // the thrust power (0 to 4).
        cin >> X >> Y >> HS >> VS >> F >> R >> P; cin.ignore();

        if(X < 2000){ result = "-30 3";}
        else if(X < 2500) {result = "-20 3";}
        else if(X < 3000) 
        {
            if(VS < -20) result = "-10 4";
            else result = "-10 3";
        }
        else if(X < 4000) //{result = "0 4";}
        {
            if(VS<-20) result = "0 4";
            else result = "0 3";
        }
        else
        {
        if(HS > 10 ) {result = "20 4";}
        else if(VS < 20 ) {result = "0 3";}
        else if(VS > 37 ) {result = "0 4";}
        }
        cout << result << endl;

 /*/
         cin >> lander.pos.x >> lander.pos.y >> lander.HS >> lander.VS 
             >> lander.F >> lander.R >> lander.P; cin.ignore();
            
         result = lander.calcResult();
         cout << result << endl;
//*/

    }
 }
