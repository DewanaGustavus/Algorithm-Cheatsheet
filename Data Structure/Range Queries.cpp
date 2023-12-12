#include <bits/stdc++.h>
using namespace std;

struct StaticQueries{ // minimum, maximum sparse table
    vector<int> prefixsum;
    vector<vector<int>> mintable;
    vector<vector<int>> maxtable;

    StaticQueries(vector<int> array){
        int length = array.size();
        prefixsum = vector<int>(length+1);
        prefixsum[0]=0;
        for(int i=1;i<=length;i++)prefixsum[i]=array[i-1] + prefixsum[i-1];

        mintable = vector<vector<int>>(length, vector<int>((int)log2(length)+1));
        maxtable = vector<vector<int>>(length, vector<int>((int)log2(length)+1));
        for(int i=0;i<length;i++){
            mintable[i][0]=array[i];
            maxtable[i][0]=array[i];
        }
        for(int j=1; (1<<j)<=length ;j++)
            for(int i=0; (i-1+(1<<j))<length ;i++){
                mintable[i][j] = min(
                    mintable[i][j-1],
                    mintable[i+(1<<(j-1))][j-1]
                );
                maxtable[i][j] = max(
                    maxtable[i][j-1],
                    maxtable[i+(1<<(j-1))][j-1]
                );
        }
    }

    int sumrange(int l, int r){ // O(1)
        return prefixsum[r-1] - prefixsum[l-2];
    }

    int minrange(int l, int r){ // O(1)
        int j = (int)log2(r - l + 1);
        return min(
            mintable[l][j],
            mintable[r+1-(1<<j)][j]
        );
    }

    int maxrange(int l, int r){ // O(1)
        int j = (int)log2(r - l + 1);
        return max(
            maxtable[l][j],
            maxtable[r+1-(1<<j)][j]
        );
    }
};

struct DiffArray{
    int length;
    vector<int> array;
    vector<int> diffarr;
    DiffArray(vector<int> arr){ // O(n)
        array = arr;
        length = array.size();
        diffarr = vector<int>(length);
        diffarr[0]=array[0];
        for(int i=1;i<length;i++)diffarr[i]=(array[i]-array[i-1]);
    }
    void update(int l, int r, int value){ // O(1)
        diffarr[l]+=value;
        if(r<length-1)diffarr[r+1]-=value;
    }
    void restore(){ // O(n)
        array[0] = diffarr[0];
        for(int i=1;i<length;i++)array[i]=diffarr[i]+array[i-1];
    }
};

struct Prefsum2D{
    int n,m;
    vector<vector<int>> prefsum;
    Prefsum2D(vector<vector<int>> arr2d){
        n = arr2d.size();
        m = arr2d[0].size();
        prefsum = vector<vector<int>>(n+1, vector<int>(m+1));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                prefsum[i][j] = prefsum[i-1][j] + prefsum[i][j-1] - 
                prefsum[i-1][j-1] + arr2d[i-1][j-1];
    }

    int sumrange(int x1,int y1,int x2,int y2){ // 1 indexing
        return prefsum[x1-1][y1-1] - prefsum[x2][y1-1] - prefsum[x1-1][y2] + prefsum[x2][y2];
    }

};

