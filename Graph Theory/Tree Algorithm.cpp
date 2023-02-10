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
bool visited[maxn];
int n;
int maxdist;
int maxnode;

int dfs(int node, int dist){
    visited[node] = true;
    if(dist > maxdist){ 
        maxnode = node;
        maxdist = dist;
    }
    
    for(auto next:adj[node]){
        if(visited[next])continue;
        dfs(next, dist + 1);
    }
}
int diameter(){
    // Time Complexity : O(n + m)
    maxdist = -1;
    maxnode = -1;
    dfs(1, 1); 

    maxdist = -1;
    for(int i=1;i<=n;i++)visited[i]=false;

    dfs(maxnode, 1); 
    return maxdist;
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
