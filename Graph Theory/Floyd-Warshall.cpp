#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
const int maxn = 2e5+5;
int n;
int adj[maxn][maxn]={};
int dist[maxn][maxn];

void floydwarshall(){
    // Time Complexity : O(n^3)
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) { 
        if (i == j) dist[i][j] = 0; 
        else if (adj[i][j])dist[i][j]=adj[i][j]; 
        else dist[i][j] = inf; 
    }

    for (int k = 1; k <= n; k++) 
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) { 
        dist[i][j] = min(dist[i][j], 
                        dist[i][k]+dist[k][j]); 
    }
}
