#include <bits/stdc++.h>
using namespace std;

const int mxN = 505;
float dis[mxN][mxN], c;
int n, m, q, a, b;

int main()
{
    cin >> n >> m >> q;
    for(int i=0; i<mxN; i++){
        for(int j=0; j<mxN; j++){
            dis[i][j] = 0.0;
        }
    }
    for(int i=0; i<m; i++){
        cin >> a >> b >> c;
        dis[a][b] = max(dis[a][b], c);
        dis[b][a] = max(dis[b][a], c);
    }
    for(int i=0; i<mxN; i++)
        dis[i][i] = 1.0;

    for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                dis[i][j] = max(dis[i][j], dis[i][k]*dis[k][j]);

    while(q--){
        cin >> a >> b;
        cout << fixed << setprecision(5) << dis[a][b] << '\n';
    }
}
