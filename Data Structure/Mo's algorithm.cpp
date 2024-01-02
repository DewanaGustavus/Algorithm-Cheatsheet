#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5+1;
const int sqrtn = sqrt(maxn) + 1;
int s[maxn] = {};
int cnt = 0;

struct querytype{
    int l, r, idx;
    bool operator < (querytype x)const{
        pair<int,int> p1 = {l/sqrtn, r};
        pair<int,int> p2 = {x.l/sqrtn, x.r};
        return p1 < p2;
    }
};

void insert(int num){
    if(s[num]++ == 0)cnt++;
}

void del(int num){
    if(s[num]-- == 1)cnt--;
}

int getans() {
    return cnt;
}

int main(){
    int n,q;
    cin>>n>>q;
    vector<querytype> queRyS;
    int arr[n];
    for(int& num : arr)cin>>num;
    
    for(int i=0;i<q;i++){
        int l,r;
        cin>>l>>r;
        l--;r--;
        querytype qi = {l,r,i};
        queRyS.push_back(qi);
    }

    sort(queRyS.begin(), queRyS.end());
    
    int idx = 1;
    map<int,int> indexcomp;
    for(int& num : arr){
        if(indexcomp[num] == 0)indexcomp[num] = idx++;
        num = indexcomp[num];
    }
    int ans[q];
    int l=0,r=-1;
    // Mo's Algorithm
    for(auto queri : queRyS){
        while(l > queri.l)insert(arr[--l]);
        while(r < queri.r)insert(arr[++r]);
        while(l < queri.l)del(arr[l++]);
        while(r > queri.r)del(arr[r--]);
        ans[queri.idx] = getans();
    }
    
    for(int i=0;i<q;i++){
        cout << ans[i] << endl;
    }


    return 0;
}
