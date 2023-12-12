#include <bits/stdc++.h>
using namespace std;

struct FenwickPURQ{
    // Point Update Range Query
    vector<int> binaryindextree;
    vector<int> original;
    int length;
    FenwickPURQ(vector<int> array){ // O(n log(n))
        length = array.size();
        original = array;
        binaryindextree = vector<int>(length+1);
        for(int i=0;i<length;i++)update(i,array[i]);
    }
    void update(int idx, int value){ // O(log(n))
        for(++idx; idx<=length ; idx+=idx&-idx){
            binaryindextree[idx] += value;
        }
    }
    int prefixsum(int idx){ // O(log(n))
        int total = 0;
        for(++idx; idx>=1 ; idx-=idx&-idx){
            total += binaryindextree[idx];
        }
        return total;
    }
    int sumrange(int l, int r){ // O(log(n))
        return prefixsum(r) - prefixsum(l-1);
    }
};

struct FenwickRUPQ{
    // Range Update Point Query
    vector<int> binaryindextree;
    vector<int> original;
    int length;
    FenwickRUPQ(vector<int> array){ // O(n log(n))
        length = array.size();
        original = array;
        binaryindextree = vector<int>(length+1);
        for(int i=0;i<length;i++)rangeupdate(i,i,array[i]);
    }
    void update(int idx, int value){ // O(log(n))
        for(++idx; idx<=length ; idx+=idx&-idx){
            binaryindextree[idx] += value;
        }
    }
    void rangeupdate(int l, int r, int val) { // O(log(n))
        update(l, val);
        update(r + 1, -val);
    }
    int value(int idx){ // O(log(n))
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx){
            ret += binaryindextree[idx];
        }
        return ret;
    }
};

struct FenwickRURQ{
    // Range Update Range Query
    vector<int> BIT1;
    vector<int> BIT2;
    vector<int> original;
    int length;
    FenwickRURQ(vector<int> array){ // O(n log(n))
        length = array.size();
        original = array;
        BIT1 = vector<int>(length+2);
        BIT2 = vector<int>(length+2);
        for(int i=0;i<length;i++)rangeupdate(i, i,array[i]);
    }
    void update(vector<int> &BIT, int idx, int value){ // O(log(n))
        for(; idx<=length ; idx+=idx&-idx){
            BIT[idx] += value;
        }
    }
    void rangeupdate(int l, int r, int val) { // O(log(n))
        l++;r++;
        update(BIT1, l, val);
        update(BIT1, r + 1, -val);
        update(BIT2, l, val*(l-1));
        update(BIT2, r + 1, -val*r);
    }
    int sum(vector<int> &BIT, int idx){ // O(log(n))
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx){
            ret += BIT[idx];
        }
        return ret;
    }
    int prefixsum(int idx){
        return sum(BIT1, idx)*(idx + 1) - sum(BIT2, idx);
    }
    int sumrange(int l, int r){
        return prefixsum(r) - prefixsum(l-1);
    }
};

