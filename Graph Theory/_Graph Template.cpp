#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
const int maxn = 2e5+5;
int n,m;
vector<int> adj[maxn];
bool visited[maxn];


// adding new edge
// adjacency list
void pushgraph(int a, int b, int direct=0){
    adj[a].push_back(b);
    if(!direct)adj[b].push_back(a);
}

void inputgraph(int direct=0){
    int a,b;cin>>a>>b;
    adj[a].push_back(b);
    if(!direct)adj[b].push_back(a);
}


// weighted adjacency list
vector<pair<int,int>> adj[maxn];
void pushweight(int a, int b, int w, int direct=0){
    adj[a].push_back({b,w});
    if(!direct)adj[b].push_back({a,w});
}

// reseting adjacency list and visited node
void reset(){
    for(int i=1;i<=n;i++){
        visited[i] = false;
        adj[i].clear();
    }
}

