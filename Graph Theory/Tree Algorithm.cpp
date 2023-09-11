#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
vector<int> adj[maxn];

int subtree[maxn]={};
void subtreedfs(int root, int prev = -1){
    // Time Complexity : O(n + m)
    subtree[root] = 1; 
    for(auto next : adj[root]){ 
        if(next == prev)continue; 
        subtreedfs(next, root); 
        subtree[root] += subtree[next]; 
    }
}

const int maxn = 2e5+5;
int n;
int maxdist;
int maxnode;
vector<int> diameter;

void dfs1(int node, int dist, int prev = -1){
    if(dist > maxdist){ 
        maxnode = node;
        maxdist = dist;
    }
    
    for(auto next:adj[node]){
        if(next == prev)continue;
        dfs1(next, dist + 1, node);
    }
}

bool founded;
void dfs2(int node, int dist, int prev = -1) {
    diameter.pb(node);
    if(dist == maxdist)founded = true;
    if(founded)return;

    for(auto next:adj[node]){
        if(next == prev)continue;
        dfs2(next, dist + 1, node);
        if(founded)return;
    }
    diameter.pop_back();
}

void finddiameter(){
    // Time Complexity : O(n + m)
    maxdist = -1;
    maxnode = -1;
    dfs1(1, 1); 

    maxdist = -1;

    dfs1(maxnode, 1);

    founded = false;
    dfs2(maxnode, 1);
}


const int maxn = 2e5+5;
int n;
vector<int> adj[maxn];
vector<int> parent(maxn);
bool visited[maxn];

void changedfs(int node){ // change from arbitrary tree into parent child
    visited[node] = true;
    for(auto next:adj[node]){
        if(visited[next])continue;
        parent[next] = node;
        changedfs(next);
    }
}
