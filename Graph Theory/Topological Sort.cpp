#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
int n,m;
vector<int> adj[maxn];
bool visited[maxn];

vector<int> topological;
void toposortdfs(int node){
    visited[node] = true;
    for(auto next:adj[node]){
        if(visited[next])continue;
        toposortdfs(next);
    }
    topological.push_back(node); 
}
 
void toposort(){
    // Time Complexity : O(n + m)
    for(int i = 1; i <= n; i++){ 
        if(visited[i])continue;
        toposortdfs(i); 
    }
    reverse(topological.begin(), topological.end());
}
