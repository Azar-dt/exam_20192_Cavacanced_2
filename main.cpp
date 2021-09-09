#include <bits/stdc++.h>
#include "graph.hpp"

using namespace std; 

void read_file(Graph& g, map<string,string>& vertex) { 
    fstream fi("data.txt", ios::in); 
    if (fi.fail()) { 
        cout<<"Cannot open file !!!"<<endl; 
        return ; 
    }
    int m, n; 
    fi>>m>>n; 
    for(int i=0; i<m; i++) { 
        string id, name; 
        fi>>id>>name; 
        insert_vertex(g,id); 
        vertex[id] = name; 
    }
    for(int i=0; i<n; i++) { 
        string u,v; 
        double w; 
        fi>>u>>v>>w; 
        insert_edge(g,u,v,w); 
        insert_edge(g,v,u,w); 
    }
    fi.close(); 
    return; 
}

void find_best_friend(Graph g, map<string,string> vertex) { 
    string inputID; 
    cout<<"Please input id : "; cin>>inputID; 
    double maxW = 0; 
    for (auto x: g[inputID]) {
        maxW = max(maxW, x.second); 
    }
    if(maxW == 0) {
        cout<<-1<<endl;
        return; 
    } else { 
        cout<<maxW<<endl; 
        for(auto x:g[inputID]) { 
            if(x.second == maxW) { 
                cout<<x.first<<" "<<vertex[x.first]<<endl;  
            }
        }
    }
    return; 
} 

void check_bridge_relationship(Graph g) { 
    string id1, id2; 
    cout<<"Please input 2 id to check : "; 
    cin>>id1>>id2; 
    cout<<Dijkstra(g, id1, id2)<<endl; 
    return; 
}

void find_common_friends(Graph g, map<string,string> vertex) { 
    string id1, id2; 
    cout<<"Please input 2 id : "; 
    cin>>id1>>id2; 
    // int numCommonFriends = 0; 
    vector<string> commonFriends; 
    map<string,double> :: iterator g_id2_end = g[id2].end();
    for(auto x:g[id1]) { 
        if(g[id2].find(x.first) != g_id2_end) { 
            commonFriends.push_back(x.first);  
        } 
    } 
    if(commonFriends.size() == 0) { 
        cout<<-1; 
        return; 
    } else { 
        cout<<commonFriends.size()<<endl; 
        for(auto x:commonFriends) { 
            cout<<x<<" "<<vertex[x]<<endl; 
        }
    }
    return; 
}

int main() { 
    int func = 0; 
    Graph g; 
    map <string,string> vertex; 
    do { 
        cout<<"\t\tMENU\t\t"<<endl; 
        cout<<"1. Print data"<<endl; 
        cout<<"2. Find best friend"<<endl; 
        cout<<"3. Check bridge relationship"<<endl; 
        cout<<"4. Find common friends"<<endl; 
        cout<<"5. Exit"<<endl;
        cout<<"Choose function : "; cin>>func; 
        switch (func)
        {
        case 1:
            read_file(g, vertex); 
            for(auto x:vertex) { 
                cout<<x.first<<" "<<x.second<<endl; 
            }
            for(auto x:g) {
                for(auto y:g[x.first]) { 
                    cout<<x.first<<" "<<y.first<<" "<<y.second<<endl;  
                }
            }
            break;
        case 2: 
            find_best_friend(g, vertex);
            break; 
        case 3: 
            check_bridge_relationship(g); 
            break; 
        case 4: 
            find_common_friends(g, vertex); 
            break; 
        default:
            break;
        } 
    } while (func!=5); 
}