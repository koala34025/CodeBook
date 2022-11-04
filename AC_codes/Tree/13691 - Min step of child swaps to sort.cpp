#include <iostream>
using namespace std;
#define ll long long

const int mxN = 3e5;
int arr[mxN];
ll ans = 0;

void solve(int l, int r)
{
    if(l == r)
        return;

    int mid = (l+r)/2;

    solve(l, mid);
    solve(mid+1, r);

    if(arr[l] > arr[mid+1]){
        ans += (ll)1;
        for(int i=0; (l+i)!=(mid+1); i++){
            int temp = arr[l+i];
            arr[l+i] = arr[i+mid+1];
            arr[i+mid+1] = temp;
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while(t--){
        ans = 0;
        int n;
        cin >> n;
        for(int i=0; i<n; i++){
            cin >> arr[i];
        }
        solve(0, n-1);

        bool ok = true;
        for(int i=0; i<n-1; i++){
            if(arr[i] > arr[i+1]){
                ok = false;
                break;
            }
        }
        if(ok)
            cout << ans << '\n';
        else
            cout << "-1\n";
    }
}
