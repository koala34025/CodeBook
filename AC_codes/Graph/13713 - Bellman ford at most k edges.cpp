#include <iostream>
using namespace std;

const int mxN = 1e3+3;
int edge[mxN][mxN];
int n, e;
int s, f, k;
int dist[mxN];

int main()
{
    cin >> n >> e;
    cin >> s >> f >> k;

    for(int i=0; i<n+1; i++){
        for(int j=0; j<n+1; j++){
            edge[i][j] = 1e9;
        }
    }

    for(int i=0; i<e; i++){
        int u, v, w;
        cin >> u >> v >> w;
        edge[u][v] = w;
    }

    for(int i=0; i<n+1; i++)
        dist[i] = 1e9;

    dist[s] = 0;

    for(int i=0; i<k; i++){
        for(int j=0; j<n+1; j++){
            for(int k=0; k<n+1; k++){
                dist[k] = min(dist[k], dist[j]+edge[j][k]);
            }
        }
    }

    cout << (dist[f] == 1e9 ? -1 : dist[f]) << '\n';
}
