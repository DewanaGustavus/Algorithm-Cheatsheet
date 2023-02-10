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

bool negativecycle(){ // RUN BELLMANFORD FIRST
    // Time Complexity : O(m)
    for(auto edge:edges){ 
        int start,end,weight;
        tie(start,end,weight) = edge; 
        if(dist[start] + weight < dist[end])return true; 
    }
    return false; 
}

