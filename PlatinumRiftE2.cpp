#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
//-------------------------------------------------------------------------
const int PLATINUM_RIFT_E2_MAJOR_VERSION = 0;
const int PLATINUM_RIFT_E2_MINOR_VERSION = 7;
//-------------------------------------------------------------------------

struct Player
{
    int id;
    int platinum;
};
//-------------------------------------------------------------------------

struct Link
{
    int id;
    int zone1;
    int zone2;
    Link& operator =(Link & l)
    {
        id=l.id;
        zone1=l.zone1;
        zone2=l.zone2;
        return *this;
    };

};
//-------------------------------------------------------------------------

struct Zone
{
    int id;
    int platinum;
    int ownerId; // the player who owns this zone (-1 otherwise)
    int podsP0; // player 0's PODs on this zone
    int podsP1; // player 1's PODs on this zone
    //int podsP2; // player 2's PODs on this zone (always 0 for a two player game)
    //int podsP3; // player 3's PODs on this zone (always 0 for a two or three player game)
    int visible;
    int priority;
    int demand;
    vector<Link> link;
    
    Zone():link(0){demand=1;};
    ~Zone(){if(link.size()) link.clear();};
    Zone& operator =(Zone & z)
    {
        id=z.id;
        platinum=z.platinum;
        ownerId=z.ownerId;
        podsP0=z.podsP0;
        podsP1=z.podsP1;
//        podsP2=z.podsP2;
//        podsP3=z.podsP3;
    
        priority=z.priority;
        demand=z.demand;
        
        link.resize(z.link.size());
        for(size_t i=0; i<link.size(); i++)
        {
            link[i].id = z.link[i].id;
            link[i].zone1 = z.link[i].zone1;
            link[i].zone2 = z.link[i].zone2;
        }
        return *this;
    };
    
    int foeCount(int myid)
    {
        int result=0;
        if(myid==0) result=podsP1;//+podsP2+podsP3;
        else if(myid==1) result=podsP0;//+podsP2+podsP3;
 //       else if(myid==2) result=podsP0+podsP1;//+podsP3;
 //       else if(myid==3) result=podsP0+podsP1;//+podsP2;
        return result;
    };
    int hasMyPod(int myid)
    {
        int result=0;
        if(myid==0) result=podsP0;
        else if(myid==1) result=podsP1;
//        else if(myid==2) result=podsP2;
//        else if(myid==3) result=podsP3;
        return result;
    };

};
//-------------------------------------------------------------------------

struct Earth
{
    int my_id;
    int platinum;
    vector<Zone> zone;
    vector<Link> link;
    vector<Player> player;

    // AI Varables
    int plat_plus=0;
    int demand_adj=0;
    int border_adj=2;
    
    Earth():zone(0), link(0), player(0){platinum=0;};
    ~Earth()
    {
        if(zone.size()) zone.clear();
        if(link.size()) link.clear();
        if(player.size()) player.clear();
    };
    void addLink(Link& l)
    {
        link.push_back(l);
        for(int i=0; i<zone.size(); i++)
        {
            if(l.zone1== i) 
            { 
                zone[i].link.push_back(l); 
                i=zone.size();
            }
            else if(l.zone2== i) 
            { 
                l.zone2 = l.zone1;
                l.zone1 = i;
                zone[i].link.push_back(l); 
                i=zone.size();
            }
        }
    };

    string getMovementCommand()
    {
        string result="";
        for(int i=0; i<zone.size(); i++)
        {
            if(zone[i].hasMyPod(my_id))
            {
             vector<Link> zonelink;
             for(int c=0; c<link.size(); c++)
             {
                 if(link[c].zone1==i) 
                 {
                     Link alink;
                     alink.zone1=i;
                     alink.zone2=link[c].zone2;
                     zonelink.push_back(alink);
                 }
                 else if(link[c].zone2==i)
                 {
                     Link alink;
                     alink.zone1=i;
                     alink.zone2=link[c].zone1;
                     zonelink.push_back(alink);
                 }
             }
            
             bool temp_flag=false;
             do{
                 temp_flag=false;
                 for(int c=0; c<zonelink.size()-1; c++)
                 {
                     if(zone[zonelink[c+1].zone2].platinum > (zone[zonelink[c].zone2].platinum )) 
                     {
                         if(!temp_flag)temp_flag=true;
                         Link tz;
                         tz= zonelink[c];
                         zonelink[c] = zonelink[c+1];
                         zonelink[c+1] = tz;
                     }
                 }
            }while(temp_flag);
            
             temp_flag=true;
             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId != my_id) 
                 {
                     temp_flag=false;
                     zone[zonelink[c].zone1].demand = zone[zonelink[c].zone1].demand+border_adj;
                 }
             }
             if(temp_flag && !zone[i].platinum && zone[i].demand)
             { zone[i].demand =0; }
             else if(temp_flag && zone[i].platinum && zone[i].demand != (zone[i].platinum+plat_plus))
             { zone[i].demand = zone[i].platinum+plat_plus; }
                
        
            
             for(int c=0; c<zonelink.size(); c++) //Nuetral Zone
             {
                 if(zone[zonelink[c].zone2].ownerId==-1) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++) // foe I can take with platium
             {
                 if(zone[zonelink[c].zone2].platinum &&(zone[zonelink[c].zone2].ownerId!=my_id) 
                    && (zone[zonelink[c].zone2].foeCount(my_id)<(zone[zonelink[c].zone1].hasMyPod(my_id)))) 
                 {
                     if(!result.empty()) result=result+" "+to_string(zone[zonelink[c].zone1].hasMyPod(my_id))+" ";
                     else result=to_string(zone[zonelink[c].zone1].hasMyPod(my_id))+" ";;
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
                 else if(zone[zonelink[c].zone2].platinum &&(zone[zonelink[c].zone2].ownerId!=my_id) 
                    && (zone[zonelink[c].zone2].foeCount(my_id)>=(zone[zonelink[c].zone1].hasMyPod(my_id)))) 
                {
                   zone[zonelink[c].zone1].demand =  1+zone[zonelink[c].zone2].foeCount(my_id);        
                }
             }

             for(int c=0; c<zonelink.size(); c++)//  unocupied foe zone
             {
                 if((zone[zonelink[c].zone2].ownerId!=my_id) && (zone[zonelink[c].zone2].foeCount(my_id)<1)) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";;
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)// foe I can take
             {
                 if(zone[zonelink[c].zone2].ownerId!=my_id 
                     && (zone[zonelink[c].zone2].foeCount(my_id)<(zone[zonelink[c].zone1].hasMyPod(my_id)))) 
                 {
                     if(!result.empty()) result=result+" "+to_string(zone[zonelink[c].zone1].hasMyPod(my_id))+" ";
                     else result=to_string(zone[zonelink[c].zone1].hasMyPod(my_id))+" ";;
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }
             
             for(int c=0; c<zonelink.size(); c++)//need more pods in zone2
             {
                 if(zone[zonelink[c].zone2].ownerId==my_id 
                 && zone[zonelink[c].zone2].hasMyPod(my_id)<zone[zonelink[c].zone2].demand) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

           }
        }
        
        
        if(result.empty()) result="WAIT";
        return result;
    };
    
};
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

int main()
{
    Earth earth;
    int playerCount; // the amount of players (2 to 4)
//    int myId; // my player ID (0, 1, 2 or 3)
    int zoneCount; // the amount of zones on the map
    int linkCount; // the amount of links between all zones
    cin >> playerCount >> earth.my_id >> zoneCount >> linkCount; cin.ignore();
    
    for (int i = 0; i < zoneCount; i++) 
    {
        Zone zone;
        //int zoneId; // this zone's ID (between 0 and zoneCount-1)
        //int platinumSource; // the amount of Platinum this zone can provide per game turn
        cin >> zone.id >> zone.platinum; cin.ignore();
        zone.priority = zone.platinum;
        earth.zone.push_back(zone);
    }
    for (int i = 0; i < linkCount; i++) 
    {
        Link link;
        //int zone1;
        //int zone2;
        cin >> link.zone1 >> link.zone2; cin.ignore();
        earth.addLink(link);
        //earth.link.push_back(link);
    }

    // game loop
    while (1) {
       // int platinum; // my available Platinum
        cin >> earth.platinum; cin.ignore();
        for (int i = 0; i < zoneCount; i++) 
        {
            int zId; // this zone's ID
            
            //int ownerId; // the player who owns this zone (-1 otherwise)
            //int podsP0; // player 0's PODs on this zone
            //int podsP1; // player 1's PODs on this zone
            //int podsP2; // player 2's PODs on this zone (always 0 for a two player game)
            //int podsP3; // player 3's PODs on this zone (always 0 for a two or three player game)
            cin >> zId >> earth.zone[i].ownerId >> earth.zone[i].podsP0 >> earth.zone[i].podsP1 
                >> earth.zone[i].visible >> earth.zone[i].platinum; cin.ignore();
            
            if(zId != i) cerr << "Zone ID "<< zId<<" did not match i "<< i<<", in main loop." << endl;
        }

        // movement commands 
        cout << earth.getMovementCommand() << endl;
        //POD purchase 
        cout << "WAIT" << endl;
    }
}
