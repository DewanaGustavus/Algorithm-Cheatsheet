#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+5;
const int LOG = log2(maxn) + 2;
vector<int> adj[maxn];
int parent[maxn][LOG] = {};
int binlift[maxn][LOG] = {};
int value[maxn];
int depth[maxn] = {};
int root = 1;
int n;

void operation(int a, int b) {return a + b;} // tree operation

void changedfs(int node, int prev){ // change from arbitrary tree into parent child
    depth[node] = depth[prev] + 1;
    for(auto next:adj[node]){
        if(next == node)continue;
        parent[next][0] = node;
        changedfs(next, node);
    }
}

void build(){
    parent[root] = root;
    depth[root] = 0;
    changedfs(root, root);

    for(int node=1;node<=n;node++) {
        // value on node
        binlift[node][0] = value[node];
    }
    
    for(int j=1;j<LOG;j++) 
        for(int node=1;node<=n;node++){ 
            parent[node][j] = parent[parent[node][j-1]][j-1]; 
            binlift[node][j] = operation(binlift[node][j-1], binlift[parent[node][j-1]][j-1]);
        }
}

int getans(int a, int b) {
    // querying from path a to b what is operation result after applying to all value
    if(depth[a] < depth[b])swap(a,b);
    int k = depth[a] - depth[b];

    int ansa = 0;
    int ansb = 0;
    for(int j = LOG - 1;j>=0;j--) {
        if(k & (1 << j)){
            ansa = operation(ansa, binlift[a][j]);
            a = parent[a][j];
        }
    }

    if(a == b){
        ansa = operation(ansa, binlift[a][0]);
        return ansa;
    }
    for(int j=LOG - 1;j >= 0;j--) {
        if(parent[a][j] != parent[b][j]) {
            ansa = operation(ansa, binlift[a][j]);
            a = parent[a][j];
            ansb = operation(ansb, binlift[b][j]);
            b = parent[b][j];
        }
    }
    
    ansa = operation(ansa, binlift[a][1]);
    ansb = operation(ansb, binlift[b][0]);
    ansa = operation(ansa, ansb);
    return ansa;
}

int dist(int a, int b){ // O(log(n))
    return depth[a] + depth[b] - 2*depth[lca(a,b)];
}
