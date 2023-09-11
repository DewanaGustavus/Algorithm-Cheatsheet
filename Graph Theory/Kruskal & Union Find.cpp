#include <bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int> link, size;
    int n, component;
    DSU(int length){
        n = length;
        component = length;
        link = vector<int>(n+1);
        size = vector<int>(n+1, 1);
        iota(link.begin(), link.end(), 0);
    }
    
    int find(int x){ // O(log(n))
        if(x != link[x])link[x] = find(link[x]);
        return link[x];
    }

    void unite(int a,int b){ // O(log(n))
        a=find(a); 
        b=find(b);
        if(a==b)return; 
        if(size[a]<size[b])swap(a,b); 
        size[a]+=size[b]; 
        link[b]=a; 
        component--;
    }
};


const int maxn = 2e5+5;
int n,m;
tuple<int,int,int> edges[maxn]; // {w,a,b}
int kruskalmst(){
    // Time Complexity : O(m log(m)) sort + O(m log(n)) run
    sort(edges, edges+m); 
    DSU container(n+1); 
    int ans = 0;

    for(int i=0;i<m;i++){
        auto edge = edges[i]; 
        int start, end, weight;
        tie(weight, start, end) = edge;
        if(container.find(start) != container.find(end)){ 
            container.unite(start, end); 
            ans += weight;
        }
    }

    return ans;
}

