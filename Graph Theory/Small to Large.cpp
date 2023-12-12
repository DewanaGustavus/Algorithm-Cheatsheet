#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;

struct Node {
    vector<int> vec = vector<int>(0);
    int size() {return vec.size();}
    void clear() {vec.clear();}
    void insert(int val) {vec.push_back(val);}
    int getans() {
        // TODO add some info and getting answer
        return vec.size();
    }
};

Node nodes[maxn];
int useidx[maxn];

// small to large
void combine(int parent, int child) {
    int idxp = useidx[parent];
    int idxc = useidx[child];
    if(nodes[idxp].size() < nodes[idxc].size()) {
        useidx[parent] = idxc;
        swap(idxp, idxc);
    }
    for(int val : nodes[idxc].vec) {
        nodes[idxp].insert(val);
    }
    nodes[idxc].clear();
};

vector<int> adj[maxn];
int ans[maxn];
void dfs(int node, int prev = -1) {
    for(int nxt : adj[node]) {
        if(nxt == prev)continue;
        dfs(nxt, node);
        combine(node, nxt);
    }
    
    ans[node] = nodes[useidx[node]].getans();
}

int main() {
    int n;cin>>n;
    int a[n];
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i < n; i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0; i < n; i++) {
        nodes[i + 1].insert(a[i]);
        useidx[i + 1] = i + 1;    
    }

    dfs(1);

    for(int i = 0; i < n; i++) {
        cout << ans[i + 1] << " ";
    }
    cout << endl;
    
    
    return 0;
}


