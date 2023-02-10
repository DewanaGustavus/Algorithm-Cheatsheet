#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, u;
    long long cap, flow = 0;
    Edge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    // Time Complexity : O(V^2 * E)
    const long long inf = 1e18;
    vector<Edge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int source, sink;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int source, int sink) : n(n), source(source), sink(sink){
        adj.resize(n+1);
        level.resize(n+1);
        ptr.resize(n+1);
    }

    void add_edge(int v, int u, long long cap){
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs(){
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for(int id : adj[v]){
                if(edges[id].cap - edges[id].flow < 1)
                    continue;
                if(level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[sink] != -1;
    }

    long long dfs(int v, long long pushed){
        if(pushed == 0 || v == sink)return pushed;
        for(int& cid = ptr[v];cid < adj[v].size();cid++){
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow(){
        long long flow = 0;
        while(true){
            fill(level.begin(), level.end(), -1);
            level[source] = 0;
            q.push(source);

            if(!bfs())break;

            fill(ptr.begin(), ptr.end(), 0);
            while(long long pushed = dfs(source, inf))
                flow += pushed;
        }
        return flow;
    }
};
