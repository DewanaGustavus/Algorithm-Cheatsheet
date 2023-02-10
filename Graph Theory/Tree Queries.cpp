#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
const int LOG = log2(maxn) + 2;
vector<int> adj[maxn];
vector<int> parent(maxn, -1);
vector<int> visited(maxn);
int ancestor[maxn][LOG];
int depth[maxn];
int root = 1;
int n;

void changedfs(int node, int currdepth = 0){ // change from arbitrary tree into parent child
    depth[node] = currdepth;
    visited[node] = true;
    for(auto next:adj[node]){
        if(visited[next])continue;
        parent[next] = node;
        changedfs(next, currdepth + 1);
    }
}

void build(){
    changedfs(root);
    parent[root] = root; 
    for(int node=1;node<=n;node++){
        ancestor[node][0] = parent[node]; 
    }
    
    for(int j=1;j<LOG;j++) 
        for(int node=1;node<=n;node++){ 
            ancestor[node][j] = ancestor[ancestor[node][j-1]][j-1]; 
        }
}

int k_ancestor(int node, int k){ // O(log(n))
    for(int j=0;j<LOG;j++){ 
        if(node == -1)break;
        if(k&(1<<j)) 
            node = ancestor[node][j]; 
    }
    return node;
}

int lca(int a, int b){ // O(log(n))
    if(depth[a] < depth[b])swap(a,b); 
    int k = depth[a] - depth[b]; 
    a = k_ancestor(a, k);
    
    if(a==b)return a;
    for(int j=LOG-1;j>=0;j--)
        if(ancestor[a][j] != ancestor[b][j]){ 
            a = ancestor[a][j];
            b = ancestor[b][j];
        }
    
    return ancestor[a][0]; 
}

int dist(int a, int b){ // O(log(n))
    return depth[a] + depth[b] - 2*depth[lca(a,b)];
}
