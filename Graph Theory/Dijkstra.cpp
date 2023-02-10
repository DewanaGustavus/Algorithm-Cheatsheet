#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
const int maxn = 2e5+5;
int n;
vector<pair<int,int>> adj[maxn];
vector<int> dist(maxn, inf);
bool visited[maxn];

void dijkstra(int node){
    // Time Complexity : O(n + m log(m))
    dist[node]=0; 
    priority_queue<pair<int,int>> q; 
    q.push({0,node}); 

    while(!q.empty()){ 
        int curr = q.top().second;q.pop(); 
        if(visited[curr])continue; 
        visited[curr] = true;

        for(auto edge:adj[curr]){ 
            int next = edge.first;
            int weight = edge.second;
            if(dist[curr] + weight < dist[next]){ 
                dist[next] = dist[curr] + weight;
                q.push({-dist[next],next}); 
            }
        }
    }
}
