#include <bits/stdc++.h>
using namespace std;

struct MemoryEfficientUnionFind{
    // union find but only use node that used in query
    // by using map data structure
    map<int,int> link;
    map<int,int> size;
    int component = 0;
        
    int find(int x){
        create(x);
        if(x != link[x])link[x] = find(link[x]);
        return link[x];
    }
    
    void create(int x){
        if(link.find(x)==link.end()){
            link[x] = x;
            size[x] = 1;
            component++;
        }
    }

    void unite(int a,int b){
        a=find(a);
        b=find(b);
        if(a==b)return;
        if(size[a]<size[b])swap(a,b);
        size[a]+=size[b];
        link[b]=a;
        component--;
    }
};





