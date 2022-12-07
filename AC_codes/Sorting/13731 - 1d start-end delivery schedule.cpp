// 5/6 map tle, helped by chirsyang

#include <iostream>
using namespace std;
#define ll long long
#include <map>

const int mxN = 5e5+5;
int n, m;
map<int, ll> ri;
map<int, ll> le;

int main()
{
    cin >> n >> m;
    le[m] = ri[m] = le[0] = ri[0] = 0;
    for(int i=0; i<n; i++){
        int s, e;
        cin >> s >> e;
        if (!ri.count(s)) ri[s] = 0;
        if (!ri.count(e)) ri[e] = 0;
        if (!le.count(s)) le[s] = 0;
        if (!le.count(e)) le[e] = 0;
        if(s < e){
            ri[s] += 1;
            ri[e] -= 1;
        }
        else{
            le[s] += 1;
            le[e] -= 1;
        }
    }

    int prev = 0;
    for(auto it = ri.begin(); it != ri.end(); it++){
        it->second += prev;
        prev = it->second;
    }
    prev = 0;
    for(auto it = le.rbegin(); it != le.rend(); it++){
        it->second += prev;
        prev = it->second;
    }
    ll ans = 0;
    for (auto i = ri.begin(); i != ri.end(); ++i) {
        if (next(i) == ri.end()) break;
        auto j = next(i);
        ll r = ri[i->first], l = le[j->first];
        if (l < r-1) l = r-1;
        if (r < l+1) r = l+1;
        ans += (j->first-i->first)*(l+r);
    }
    cout << ans << '\n';
    return 0;
}
