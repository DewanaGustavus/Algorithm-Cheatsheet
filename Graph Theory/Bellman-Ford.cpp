#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
const int maxn = 2e5+5;
int n;
tuple<int,int,int> edges[maxn];
vector<int> dist(maxn, inf);

void bellmanford(int node){
    // Time Complexity : O(n*m)
    dist[node]=0; 
    for(int i=1;i<n;i++)
        for(auto edge:edges){ 
            int start,end,weight;
            tie(start,end,weight) = edge;
            dist[end] = min(dist[end], dist[start] + weight); 
        }
}

bool negativecycle(){
    // Time Complexity : O(m)
    bellmanford();
    for(auto edge:edges){ 
        int start,end,weight;
        tie(start,end,weight) = edge; 
        if(dist[start] + weight < dist[end])return true; 
    }
    return false; 
}

vector<int> adj[maxn];
bool SPFA(int s) {
    vector<int> cnt(n+1, 0);
    vector<bool> inqueue(n+1, false);
    queue<int> q;

    dist[s] = 0;
    q.push(s);
    inqueue[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inqueue[u] = false;
        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inqueue[v]) {
                    q.push(v);
                    inqueue[v] = true;
                    cnt[v]++;
                    if (cnt[v] > n)
                        return false;  // negative cycle
                }
            }
        }
    }
    return true;
}