// 4/6, runtime error

#include <iostream>
using namespace std;
#define ll long long
#include <vector>

const int mxN = 2e6;
int n, m;
vector<ll> ri(mxN);
vector<ll> le(mxN);

int main()
{
    cin >> n >> m;
    for(int i=0; i<n; i++){
        ll s, e;
        cin >> s >> e;
        if(s < e){
            ri[s] += 1;
            ri[e] -= 1;
        }
        else{
            le[s] += 1;
            le[e] -= 1;
        }
    }

    // ri[i] = num of toward paths between i, i+1
    for(int i=1; i<m; i++){
        ri[i] += ri[i-1];
    }
    // le[i] = num of backward paths between i-1, i
    for(int i=m-1; i>0; i--){
        le[i] += le[i+1];
    }
    // left shift le[]
    // So, le[i] = num of backward paths between i, i+1
    for(int i=0; i<m ;i++){
        le[i] = le[i+1];
    }

    for(int i=0; i<m; i++){
        if(ri[i] > le[i]){
            le[i] = ri[i]-1;
        }
        else{
            ri[i] = le[i]+1;
        }
    }

    ll ans = 0;
    for(int i=0; i<m; i++){
        ans += ri[i] + le[i];
    }
    cout << ans << '\n';
}
