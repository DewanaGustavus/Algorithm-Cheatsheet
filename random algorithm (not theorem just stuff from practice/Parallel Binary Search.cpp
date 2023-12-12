#include <bits/stdc++.h>
using namespace std;
 
#define range(i,s,e)        for(int i=s;i<e;i++)
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define print(var)          cout<<(var)<<endl;
#define int long long
#define vi vector<int>
#define all(vec)    (vec).begin(), (vec).end()
const int maxn = 2e5+5;

struct DSU{
    vector<int> link, size;
    int n, component;
    DSU(){}
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

    void reset() {
        component = n;
        fill(all(size), 1);
        iota(link.begin(), link.end(), 0);
    }
};

int n,m;
tuple<int,int,int> edges[maxn]; // {w,a,b}
vi is_first_mst(maxn);
DSU container;

void kruskalmst1(){
    // Time Complexity : O(m log(m)) sort + O(m log(n)) run
    container.reset();

    for(int i=0;i<m;i++){
        int start, end, weight;
        tie(weight, start, end) = edges[i];
        if(container.find(start) != container.find(end)){ 
            container.unite(start, end);
            is_first_mst[i] = 1;
        }
    }
}

bool kruskalmst2(){
    // Time Complexity : O(m log(m)) sort + O(m log(n)) run
    container.reset();

    for(int i=0;i<m;i++){
        if(is_first_mst[i])continue;
        int start, end, weight;
        tie(weight, start, end) = edges[i];
        if(container.find(start) != container.find(end)){ 
            container.unite(start, end); 
        }
    }

    return container.component == 1;
}

int l[maxn], r[maxn];
vi binserqueue[maxn];
int ans = 0;
void binser() { // paralel binser
    int mid1 = m / 2;
    range(idx,0,m) {
        if(is_first_mst[idx]) {
            binserqueue[mid1].push_back(idx);
            l[idx] = 0;
            r[idx] = m - 1;
        }
    }

    int processamount = n - 1;
    while(processamount > 0) { // at most LOG(M) by binser
        container.reset();
        range(mid,0,m) { // MST
            int start, end, weight;
            if(!is_first_mst[mid]){
                tie(weight, start, end) = edges[mid];
                if(container.find(start) != container.find(end)){ 
                    container.unite(start, end); 
                }
            }

            while(!binserqueue[mid].empty()) {
                int idx = binserqueue[mid].back();
                binserqueue[mid].pop_back();

                tie(weight, start, end) = edges[idx];
                if(l[idx] >= r[idx]) { // edges[idx] is replaced by edges[mid]
                    int mididx = l[idx] + is_first_mst[l[idx]];
                    int midweight;
                    tie(midweight, start, end) = edges[mididx];
                    ans += midweight - weight + 1;
                    processamount--;
                }else{
                    if(container.find(start) == container.find(end)){
                        r[idx] = mid;
                    }else {
                        l[idx] = mid + 1;
                    }
                    int newmid = (l[idx] + r[idx]) / 2;
                    binserqueue[newmid].push_back(idx);
                }
            }
        }
    }
}

int32_t main(){
    fastIO
    // https://tlx.toki.id/problems/icpc-jakarta-2022/L
   
    cin>>n>>m;
    range(i,0,m){
        int a,b,x;
        cin>>a>>b>>x;
        edges[i] = {x,a,b};
    }
    sort(edges, edges+m); 
    container = DSU(n);
    kruskalmst1();
    
    if(kruskalmst2()){
        binser();
        print(ans)
    }else{
        print(-1)
    }
    
    
    return 0;
}
