// not enough memory for unique vectors
// so just iterate and skip redundant pairs
// focus on the last duplicated pair in ri 
// and the first duplicated pair in le
// helped by chrisyang >:I

#include <iostream>
using namespace std;
#define ll long long
#include <vector>
#include <algorithm>

const int mxN = 5e5+5;
int n, m;
vector<pair<int, ll>> ri;
vector<pair<int, ll>> le;

int main()
{
    cin >> n >> m;
    ri.push_back({0, 0});
    ri.push_back({m, 0});
    le.push_back({m, 0});
    le.push_back({0, 0});

    for(int i=0; i<n; i++){
        int s, e;
        cin >> s >> e;
        if(s < e){
            ri.push_back({s, 1});
            ri.push_back({e, -1});
            le.push_back({s, 0});
            le.push_back({e, 0});
        }
        else{
            le.push_back({s, 1});
            le.push_back({e, -1});
            ri.push_back({s, 0});
            ri.push_back({e, 0});
        }
    }

    sort(ri.begin(), ri.end());
    sort(le.begin(), le.end());

    int len = ri.size();
    for(int i=1; i<len; i++){
        ri[i].second += ri[i-1].second;
    }
    for(int i=len-2; i>=0; i--){
        le[i].second += le[i+1].second;
    }

    ll ans = 0;
    for(int i=0; i<len; i++){
        while(i+1 != len && (ri[i+1].first == ri[i].first)){
            i++;
        }
        if(i+1 == len) break;

        ll right_cnt = ri[i].second;
        ll left_cnt = le[i+1].second;

        if(right_cnt > left_cnt){
            left_cnt = right_cnt - 1;
        }
        else{
            right_cnt = left_cnt + 1;
        }

        ans += (le[i+1].first - ri[i].first) * (right_cnt + left_cnt);
    }
    cout << ans << '\n';
}
