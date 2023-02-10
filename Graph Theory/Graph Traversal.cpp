#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
vector<int> adj[maxn];
bool visited[maxn];

void dfs(int node){
    // Time Complexity : O(n + m)
    visited[node] = true;
    for(auto next:adj[node]){ 
        if(visited[next])continue; 
        dfs(next); 
    }
}

void bfs(int node){
    // Time Complexity : O(n + m)
    queue<int> q;
    visited[node] = true; 
    q.push(node); 

    while(!q.empty()){ 
        int curr = q.front();q.pop(); 
        for(auto next:adj[curr]){ 
            if(visited[next])continue; 
            visited[next] = true;

            q.push(next); 
        }
    }
}
