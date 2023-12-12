#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int from, to, cap, cost;
    Edge(int a, int b, int x, int c) : from(a), to(b), cap(x), cost(c) {}
};

const int maxn = 1e3;
vector<int> adj[maxn];
vector<Edge> edges;
const int inf = 1e9;

void add_edge(int from, int to, int cap, int cost){
    int m = edges.size();
    edges.emplace_back(from, to, cap, cost);
    edges.emplace_back(to, from, 0, -cost);
    adj[from].push_back(m);
    adj[to].push_back(m+1);
}

void SPFA(int n, int source, vector<int>& dist, vector<int>& p) {
    dist = vector<int>(n + 1, inf);
    p = vector<int>(n + 1, -1);
    dist[source] = 0;
    bool inq[n+1] = {};
    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (auto m : adj[u]){
            int v, cap, cost;
            v = edges[m].to;
            cap = edges[m].cap;
            cost = edges[m].cost;
            if (cap > 0 && dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                p[v] = m;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int min_cost_flow(int n, int F, int source, int sink) {
    // TIme Complexity : O(F*m*n)
    int current_flow = 0;
    int cost = 0;
    vector<int> dist, p;
    while (current_flow < F) {
        SPFA(n, source, dist, p);
        if (dist[sink] == inf)
            break;

        int flow = F - current_flow;
        int cur = sink;
        while (cur != source) {
            int id = p[cur];
            int prev = edges[id].from;
            flow = min(flow, edges[id].cap);
            cur = prev;
        }

        current_flow += flow;
        cost += flow * dist[sink];
        cur = sink;
        while (cur != source) {
            int id = p[cur];
            int prev = edges[id].from;
            edges[id].cap -= flow;
            edges[id^1].cap += flow;
            cur = prev;
        }
    }

    return (current_flow < F) ? -1 : cost;
}
