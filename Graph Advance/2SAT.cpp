#include <bits/stdc++.h>
using namespace std;

const int maxn = 4e5 + 5;
int n;
vector<int> adj[maxn], revadj[maxn];
bool vis[maxn];
vector<int> order, comp(maxn, -1);
vector<bool> assignment(maxn, false);

void dfs1(int node){
    vis[node] = true;
    for (int nxt : adj[node]) 
        if (!vis[nxt])
            dfs1(nxt);
    order.push_back(node);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u : revadj[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve_2SAT() {
    n *= 4;
    for(int i = 0; i < n; ++i)
        if(!vis[i])
            dfs1(i);

    for (int i = 0, j = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    n /= 4;
    return true;
}

void add_disjunction(int a, bool na, int b, bool nb) {
    // add edge in clause form (a v b) ^ (b v c) ...
    // na and nb signify whether a and b are to be negated 
    a = 2*a ^ na;
    b = 2*b ^ nb;
    int neg_a = a ^ 1;
    int neg_b = b ^ 1;
    adj[neg_a].push_back(b);
    adj[neg_b].push_back(a);
    revadj[b].push_back(neg_a);
    revadj[a].push_back(neg_b);
}
