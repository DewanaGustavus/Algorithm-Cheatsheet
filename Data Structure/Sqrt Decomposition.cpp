#include <bits/stdc++.h>
using namespace std;

struct SqrtArray{
    vector<int> sqrtarray;
    vector<int> array;
    int length;
    int k;
    SqrtArray(vector<int> array){ // O(n) precompute
        length = array.size();
        this->array = array;
        k = (int)sqrt(length) + 1;
        sqrtarray.assign(k,0);
        for(int i=0;i<length;i++)sqrtarray[i/k]+=array[i];
    }

    void update(int idx, int value){ // (O(1))
        sqrtarray[idx/k] -= array[idx];
        sqrtarray[idx/k] += value;
        array[idx] = value;
    }

    int sumrange(int l, int r){ // O(sqrt(n))
        int sum = 0;
        int i = l;

        while(i%k!=0 && i<=r)sum += array[i++];
        while(i+k<=r){
            sum += sqrtarray[i/k];
            i += k;
        }
        while(i<=r)sum += array[i++]; 
        
        return sum;
    }
};
