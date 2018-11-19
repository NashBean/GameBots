#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
//-------------------------------------------------------------------------
const int PLATINUM_RIFT_MAJOR_VERSION = 0;
const int PLATINUM_RIFT_MINOR_VERSION = 5;
//-------------------------------------------------------------------------

struct Player
{
    int id;
    int platinum;
};
//-------------------------------------------------------------------------

struct Zone
{
    int id;
    int platinum;
    int ownerId; // the player who owns this zone (-1 otherwise)
    int podsP0; // player 0's PODs on this zone
    int podsP1; // player 1's PODs on this zone
    int podsP2; // player 2's PODs on this zone (always 0 for a two player game)
    int podsP3; // player 3's PODs on this zone (always 0 for a two or three player game)
    int foeCount(int myid)
    {
        int result=0;
        if(myid==0) result=podsP1+podsP2+podsP3;
        else if(myid==1) result=podsP0+podsP2+podsP3;
        else if(myid==2) result=podsP0+podsP1+podsP3;
        else if(myid==3) result=podsP0+podsP1+podsP2;
        return result;
    };
    int hasMyPod(int myid)
    {
        int result=0;
        if(myid==0) result=podsP0;
        else if(myid==1) result=podsP1;
        else if(myid==2) result=podsP2;
        else if(myid==3) result=podsP3;
        return result;
    };

};
//-------------------------------------------------------------------------

struct Link
{
    int id;
    int zone1;
    int zone2;
};
//-------------------------------------------------------------------------

struct Earth
{
    int my_id;
    int platinum;
    vector<Zone> zone;
    vector<Link> link;
    vector<Player> player;
    
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

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==-1) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if((zone[zonelink[c].zone2].ownerId!=my_id) && (zone[zonelink[c].zone2].foeCount(my_id)<1)) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";;
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].platinum &&(zone[zonelink[c].zone2].ownerId!=my_id) 
                    && (zone[zonelink[c].zone2].foeCount(my_id)<(zone[zonelink[c].zone2].hasMyPod(my_id)))) 
                 {
                     if(!result.empty()) result=result+" "+to_string(zone[zonelink[c].zone1].hasMyPod(my_id))+" ";
                     else result=to_string(zone[zonelink[c].zone1].hasMyPod(my_id))+" ";;
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }


             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].platinum &&(zone[zonelink[c].zone2].ownerId!=my_id) 
                    && (zone[zonelink[c].zone2].foeCount(my_id)<=(zone[zonelink[c].zone2].hasMyPod(my_id)))) 
                 {
                     if(!result.empty()) result=result+" "+to_string(zone[zonelink[c].zone1].hasMyPod(my_id))+" ";
                     else result=to_string(zone[zonelink[c].zone1].hasMyPod(my_id))+" ";;
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId!=my_id 
                     && (zone[zonelink[c].zone2].foeCount(my_id)<(zone[zonelink[c].zone2].hasMyPod(my_id)))) 
                 {
                     if(!result.empty()) result=result+" "+to_string(zone[zonelink[c].zone1].hasMyPod(my_id))+" ";
                     else result=to_string(zone[zonelink[c].zone1].hasMyPod(my_id))+" ";;
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }
             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==my_id && zone[zonelink[c].zone2].hasMyPod(my_id)<1) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==my_id && zone[zonelink[c].zone2].hasMyPod(my_id)<2) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==my_id && zone[zonelink[c].zone2].hasMyPod(my_id)<zone[zonelink[c].zone1].hasMyPod(my_id)) 
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
    
    string getPodPurchaseCommand()
    {
        string result="";
        int amount=0; 
        if(platinum) amount =(platinum/20);
        if(amount) // neutral zone with platinum
        {
            for(int i=zone.size()-1; i>=0 && amount; i--)
            {
                if(zone[i].platinum && zone[i].ownerId==-1)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                    }
            }
        }
        if(amount) // ownerId with platinum
        {
            for(int i=0; i<zone.size(); i++)
            {
                if(zone[i].ownerId==-1 )
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                       if(!amount)i=-1;
                       }
            }
        }
        if(amount) // ownerId and neutral zone
        {
            for(int i=0; i<zone.size() ; i++)
            {
                if(zone[i].platinum && zone[i].ownerId==my_id && zone[i].hasMyPod(my_id)<=7)
                    {
                        if(zone[i].hasMyPod(my_id)<6 && amount>2)
                        {
                        if(!result.empty()) result=result +" 2 ";
                        else result = "2 ";
                        }
                        else
                        {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        }
                        result = result + to_string(zone[i].id);
                        amount--;
                        if(!amount)i=-1;
                    }
            }
        }
        if(amount) // ownerId and neutral zone
        {
            for(int i=0; i<zone.size() ; i++)
            {
                if(zone[i].ownerId==my_id && zone[i].hasMyPod(my_id)<2)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                        if(!amount)i=-1;
                    }
            }
        }
        if(amount) // ownerId and neutral zone
        {
            for(int i=zone.size()-1; i>=0 ; i--)
            {
                if(zone[i].ownerId==my_id && zone[i].hasMyPod(my_id)<1)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                        if(!amount)i=-1;
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
        earth.zone.push_back(zone);
    }
    for (int i = 0; i < linkCount; i++) 
    {
        Link link;
        //int zone1;
        //int zone2;
        cin >> link.zone1 >> link.zone2; cin.ignore();
        earth.link.push_back(link);
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
                >> earth.zone[i].podsP2 >> earth.zone[i].podsP3; cin.ignore();
            if(zId != i) cerr << "Zone ID "<< zId<<" did not match i "<< i<<", in main loop." << endl;
        }

        // movement commands 
        cout << earth.getMovementCommand() << endl;
        //POD purchase 
        cout << earth.getPodPurchaseCommand() << endl;
    }
}
{
    int id;
    int zone1;
    int zone2;
};
//-------------------------------------------------------------------------

struct Earth
{
    int my_id;
    int platinum;
    vector<Zone> zone;
    vector<Link> link;
    vector<Player> player;
    
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

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==-1) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if((zone[zonelink[c].zone2].ownerId!=my_id) && (zone[zonelink[c].zone2].foeCount(my_id)<(zone[zonelink[c].zone2].hasMyPod(my_id)))) 
                 {
                     if(!result.empty()) result=result+" "+to_string(zone[zonelink[c].zone2].hasMyPod(my_id))+" ";
                     else result=to_string(zone[zonelink[c].zone2].hasMyPod(my_id))+" ";;
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId!=my_id && (zone[zonelink[c].zone2].foeCount(my_id)<2)) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==my_id && zone[zonelink[c].zone2].hasMyPod(my_id)<1) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==my_id && zone[zonelink[c].zone2].hasMyPod(my_id)<2) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==my_id && zone[zonelink[c].zone2].hasMyPod(my_id)<zone[zonelink[c].zone2].hasMyPod(my_id)) 
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
    
    string getPodPurchaseCommand()
    {
        string result="";
        int amount=0; 
        if(platinum) amount =(platinum/20);
        if(amount) // neutral zone with platinum
        {
            for(int i=zone.size()-1; i>=0 && amount; i--)
            {
                if(zone[i].platinum && zone[i].ownerId==-1)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                    }
            }
        }
        if(amount) // ownerId with platinum
        {
            for(int i=0; i<zone.size(); i++)
            {
                if(zone[i].ownerId==-1 )
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                       if(!amount)i=-1;
                       }
            }
        }
        if(amount) // ownerId and neutral zone
        {
            for(int i=0; i<zone.size() ; i++)
            {
                if(zone[i].platinum && zone[i].ownerId==my_id && zone[i].hasMyPod(my_id)<5)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                        if(!amount)i=-1;
                    }
            }
        }
        if(amount) // ownerId and neutral zone
        {
            for(int i=0; i<zone.size() ; i++)
            {
                if(zone[i].ownerId==my_id && zone[i].hasMyPod(my_id)<2)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                        if(!amount)i=-1;
                    }
            }
        }
        if(amount) // ownerId and neutral zone
        {
            for(int i=zone.size()-1; i>=0 ; i--)
            {
                if(zone[i].ownerId==my_id)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                        if(!amount)i=-1;
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
        earth.zone.push_back(zone);
    }
    for (int i = 0; i < linkCount; i++) 
    {
        Link link;
        //int zone1;
        //int zone2;
        cin >> link.zone1 >> link.zone2; cin.ignore();
        earth.link.push_back(link);
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
                >> earth.zone[i].podsP2 >> earth.zone[i].podsP3; cin.ignore();
            if(zId != i) cerr << "Zone ID "<< zId<<" did not match i "<< i<<", in main loop." << endl;
        }

        // movement commands 
        cout << earth.getMovementCommand() << endl;
        //POD purchase 
        cout << earth.getPodPurchaseCommand() << endl;
    }
}
{
    int id;
    int zone1;
    int zone2;
};
//-------------------------------------------------------------------------

struct Earth
{
    int my_id;
    int platinum;
    vector<Zone> zone;
    vector<Link> link;
    vector<Player> player;
    
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

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==-1) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if((zone[zonelink[c].zone2].ownerId!=my_id) && (zone[zonelink[c].zone2].foeCount(my_id)<1)) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId!=my_id && (zone[zonelink[c].zone2].foeCount(my_id)<2)) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==my_id && zone[zonelink[c].zone2].hasMyPod(my_id)<1) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==my_id && zone[zonelink[c].zone2].hasMyPod(my_id)<2) 
                 {
                     if(!result.empty()) result=result+" 1 ";
                     else result="1 ";
                     result = result +to_string(zonelink[c].zone1)+" "+to_string(zonelink[c].zone2);
                 }
             }

             for(int c=0; c<zonelink.size(); c++)
             {
                 if(zone[zonelink[c].zone2].ownerId==my_id && zone[zonelink[c].zone2].hasMyPod(my_id)<zone[zonelink[c].zone2].hasMyPod(my_id)) 
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
    
    string getPodPurchaseCommand()
    {
        string result="";
        int amount=0; 
        if(platinum) amount =(platinum/20);
        if(amount) // neutral zone with platinum
        {
            for(int i=zone.size()-1; i>=0 && amount; i--)
            {
                if(zone[i].platinum && zone[i].ownerId==-1)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                    }
            }
        }
        if(amount) // ownerId with platinum
        {
            for(int i=0; i<zone.size(); i++)
            {
                if(zone[i].ownerId==-1 )
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                       if(!amount)i=-1;
                       }
            }
        }
        if(amount) // ownerId and neutral zone
        {
            for(int i=0; i<zone.size() ; i++)
            {
                if(zone[i].platinum && zone[i].ownerId==my_id && zone[i].hasMyPod(my_id)<5)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                        if(!amount)i=-1;
                    }
            }
        }
        if(amount) // ownerId and neutral zone
        {
            for(int i=0; i<zone.size() ; i++)
            {
                if(zone[i].ownerId==my_id && zone[i].hasMyPod(my_id)<2)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                        if(!amount)i=-1;
                    }
            }
        }
        if(amount) // ownerId and neutral zone
        {
            for(int i=zone.size()-1; i>=0 ; i--)
            {
                if(zone[i].ownerId==my_id)
                    {
                        if(!result.empty()) result=result +" 1 ";
                        else result = "1 ";
                        result = result + to_string(zone[i].id);
                        amount--;
                        if(!amount)i=-1;
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
        earth.zone.push_back(zone);
    }
    for (int i = 0; i < linkCount; i++) 
    {
        Link link;
        //int zone1;
        //int zone2;
        cin >> link.zone1 >> link.zone2; cin.ignore();
        earth.link.push_back(link);
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
                >> earth.zone[i].podsP2 >> earth.zone[i].podsP3; cin.ignore();
            if(zId != i) cerr << "Zone ID "<< zId<<" did not match i "<< i<<", in main loop." << endl;
        }

        // movement commands 
        cout << earth.getMovementCommand() << endl;
        //POD purchase 
        cout << earth.getPodPurchaseCommand() << endl;
    }
}
