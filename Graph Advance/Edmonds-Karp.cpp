#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3;
int n;
int capacity[maxn][maxn] = {};
vector<int> adj[maxn];

void add_edge(int from, int to, int cap){
    adj[from].pb(to);
    adj[to].pb(from);
    capacity[from][to] += cap;
}

int bfs(int source, int sink, vector<int>& parent) {
    const int inf = 1e9;
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({source, inf});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) 
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == sink)
                    return new_flow;
                q.push({next, new_flow});
            }
    }

    return 0;
}

int maxflow(int source, int sink) {
    int flow = 0;
    vector<int> parent(n + 1);
    int new_flow;

    while (new_flow = bfs(source, sink, parent)) {
        flow += new_flow;
        int cur = sink;
        while (cur != source) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}
