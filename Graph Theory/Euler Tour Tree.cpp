#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
vector<int> adj[maxn];
bool vis[maxn];
int subtreesize[maxn];
int eulertouridx[maxn];
int eulerarray[maxn];
int idx = 0;

void dfs(int node){
    vis[node] = 1;
    eulerarray[idx] = node;
    eulertouridx[node] = idx++;
    subtreesize[node] = 1;
    for(int nxt : adj[node]){
        if(vis[nxt])continue;
        dfs(nxt);
        subtreesize[node] += subtreesize[nxt];
    }
}
