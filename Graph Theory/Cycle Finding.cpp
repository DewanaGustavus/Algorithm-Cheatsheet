#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;

int n, m;
vector<int> adj[maxn];
bool vis[maxn], used[maxn];
vector<int> city;
bool found = false;

void dfs(int node) {
    if(found)return;
    if(vis[node]) {
        if(used[node]) {
            city.push_back(node);
            found = true;
        }
        return;
    }

    vis[node] = true;
    city.push_back(node);
    used[node] = true;
    for(int nxt : adj[node]) {
        dfs(nxt);
        if(found)return;
    }
    city.pop_back();
    used[node] = false;
}

vector<int> cycle_finding() {
    for(int i=1;i<=n;i++) {
        if(!found && !vis[i]) {
            dfs(i);
        }
    }

    vector<int> cycle;
    if(!found) {
        cycle.push_back(-1);
    }else {
        bool foundlast = false;
        vector<int> ans;
        n = city.size();
        for(int i=0;i<n;i++) {
            if(city[i] == city[n-1]) {
                foundlast = true;
            }
            if(foundlast) {
                ans.push_back(city[i]);
            }
        }
    }
    return cycle;
}
