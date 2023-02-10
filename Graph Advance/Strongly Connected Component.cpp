#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
const int maxn = 2e5+5;
int n,m;
vector<int> adj[maxn], revadj[maxn];
bool vis[maxn];
vector<int> order, comptmp;
int component[maxn];
vector<int> new_node;
vector<int> sccadj[maxn];

void dfs1(int node){
    vis[node] = true;
    for(int nxt : adj[node])
        if(!vis[nxt])
            dfs1(nxt);
    
    order.push_back(node);
}

void dfs2(int node){
    vis[node] = true;
    comptmp.push_back(node);
    for(int nxt : revadj[node])
        if(!vis[nxt])
            dfs2(nxt);
}

void kosaraju(){
    for(int i=1;i<=n;i++)
        if(!vis[i])
            dfs1(i);
    
    reverse(order.begin(), order.end());

    for(int i=0;i<maxn;i++)vis[i] = false;
    for(int node : order)
        if(!vis[node]){
            dfs2(node);

            int representation = comptmp.front();
            for(int member : comptmp)component[member] = representation;
            new_node.push_back(representation);

            comptmp.clear();
        }

    for(int i=1;i<=n;i++)
        for(int nxt : adj[i]){
            int a = component[i];
            int b = component[nxt];
            if(a != b)
                sccadj[a].push_back(b);
        }
    
}

