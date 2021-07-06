#include <bits/stdc++.h>
#include "graph.hpp"

using namespace std; 

void read_file(Graph& g, map<string,string>& id) { 
    ifstream fi; 
    fi.open("data.txt"); 
    if (fi.is_open() == false) { 
        cout<<"CANNOT OPEN FILE "<<endl; 
        return; 
    }
    int m,n; 
    fi>>n>>m; 
    for(int i=1; i<=n; i++) { 
        string u,v; 
        fi>>u>>v; 
        insert_vertex(g,u); 
        id[u] = v;
    } 
    for(int i=1;i<=m;i++) { 
        string u,v; 
        double w; 
        fi>>u>>v>>w; 
        insert_edge(g,u,v,w); 
        insert_edge(g,v,u,w); 
        
    }
}

void find_bf(Graph g, map<string,string> id) { 
    string u; 
    cout<<"INPUT ID : "; cin>>u; 
    if(g[u].size()==0) { 
        cout<<"-1"<<endl; 
        return ; 
    }
    double max_d = 0; 
    for(auto v: g[u]) { 
        max_d = max(v.second,max_d); 
    }
    cout<<max_d<<endl; 
    for(auto v:g[u]) { 
        if(v.second == max_d) { 
            cout<<v.first<<" "<<id[v.first]<<endl; 
        }
    }
}

void check_bridging(Graph g) { 
    string u,v; 
    cout<<"INPUT 2 ID : "<<endl; 
    cin>>u>>v; 
    for(auto x:g[u]) { 
        if(x.first==v) { 
            cout<<"-1"<<endl; 
            return; 
        }
    }
    if(Dijkstra(g,u,v)==-1) cout<<"-1"<<endl;
    else { 
        cout<<"1"<<endl;
    }
} 

void find_common_friend(Graph g, map<string,string> id) { 
    string u,v; 
    cout<<"INPUT 2 ID : "<<endl; 
    cin>>u>>v; 
    set<string> s1; 
    for(auto x:g[u]) { 
        s1.insert(x.first); 
    }
    bool check = false; 
    set<string> res; 
    for(auto x:g[v]) { 
        if (s1.find(x.first)!=s1.end()) { 
            check = true;
            res.insert(x.first) ;  
        }
    }
    if(check == false) cout<<"-1"<<endl; 
    else { 
        cout<<res.size()<<endl; 
        for(auto x: res) { 
            cout<<x<<" "<<id[x]<<endl; 
        }
    }
}

int main() { 
    Graph g; 
    map <string, string> id;
    int func; 
    do { 
        fflush(stdin); 
        cout<<"\tEXAM 2019-2 :\t\t"<<endl; 
        cout<<"1. PRINT DATA"<<endl;
        cout<<"2. FIND BEST FRIEND"<<endl; 
        cout<<"3. CHECK BRIDGING RELATIONSHIP"<<endl ; 
        cout<<"4. FIND COMMON FRIENDS"<<endl ;  
        cout<<"5. EXIT"<<endl;
        cout<<"CHOOSE FUNCTION : "<<endl; 
        
        cin>>func; 
        switch (func)
        {
        case 1:
            read_file(g,id); 
            for(auto x:id) { 
                cout<<x.first<<" "<<x.second<<endl; 
            }
            break;
        case 2: 
            find_bf(g,id); 
            break;
        case 3: 
            check_bridging(g); 
            break;  
        case 4: 
            find_common_friend(g,id); 
            break; 
        case 5: 
            return 0; 
        default:
            break;
        }
    } while (1); 
    return 0; 
}