#include <bits/stdc++.h>
using namespace std;

class MemoryEfficientUnionFind{
    // union find but only use node that used in query
    // by using map data structure
public:
    map<int,int> link;
    map<int,int> size;
        
    int find(int x){
        int temp=x;
        while(x!=link[x])x=link[x];
        link[temp]=x;        
        return x;
    }
    
    void create(int x){
        if(link.find(x)==link.end()){
            link[x] = x;
            size[x] = 1;
        }
    }

    void unite(int a,int b){
        create(a);
        create(b);

        a=find(a);
        b=find(b);
        if(a==b)return;
        if(size[a]<size[b])swap(a,b);
        size[a]+=size[b];
        link[b]=a;
    }
};





