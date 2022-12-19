// william lin method
// CSES Distince Values Queries + Euler Tour on tree

#include <bits/stdc++.h>
using namespace std;

struct node
{
    int sum;
} segtree[1<<19];

const int mxN = 2e5+5;
int n;
int arr[mxN];
vector<int> edge[mxN];
int timer = 0;
int st[mxN];
int en[mxN];
int colr[mxN];
vector<pair<int, int>> queries[mxN];
int ans[mxN];

void dfs(int node, int parent)
{
    st[node] = timer++;
    for(auto e : edge[node]){
        if(e == parent) continue;
        dfs(e, node);
    }
    en[node] = timer-1;
}

void upd(int pos, int x, int idx=1, int l=0, int r=n-1)
{
    if(r <= l){
        segtree[idx].sum = x;
        return;
    }
    int m = (l+r)/2;
    if(pos <= m)
        upd(pos, x, idx*2, l, m);
    else
        upd(pos, x, idx*2+1, m+1, r);
    segtree[idx].sum = segtree[idx*2].sum + segtree[idx*2+1].sum;
}

int qry(int ql, int qr, int idx=1, int l=0, int r=n-1)
{
    if(ql <= l && qr >= r){
        return segtree[idx].sum;
    }
    int m = (l+r)/2;

    return (ql <= m ? qry(ql, qr, idx*2, l, m) : 0)
         + (m < qr ? qry(ql, qr, idx*2+1, m+1, r) : 0);
}

int main()
{
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }
    for(int i=0; i<n-1; i++){
        int a, b;
        cin >> a >> b;
        a--, b--;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    dfs(0, -1);
    // rearrange color
    for(int i=0; i<n; i++){
        int star = st[i];
        colr[star] = arr[i];
    }

    for(int i=0; i<n; i++){
        int star = st[i];
        int endd = en[i];
        queries[star].push_back({endd, i});
    }

    map<int, int> last;
    for(int i=n-1; i>=0; i--){
        int color = colr[i];

        if(last.count(color) != 0)
            upd(last[color], 0);

        last[color] = i;
        upd(i, 1);

        for(auto [endd, num] : queries[i]){
            ans[num] = qry(i, endd);
        }
    }

    for(int i=0; i<n; i++){
        cout << ans[i] << ' ';
    }
	cout << '\n';
}
