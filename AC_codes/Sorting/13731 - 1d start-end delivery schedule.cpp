// pair<int, int> is just right to avoid mle
// heapsort and then merge Xs of second=0 to avoid tle

// not enough memory for unique vectors
// so just iterate and skip redundant pairs
// focus on the last duplicated pair in ri
// and the first duplicated pair in le
// helped by chrisyang >:I

#include <iostream>
using namespace std;
#define ll long long
#include <vector>

const int mxN = 5e5+5;
int n, m;
vector<pair<int, int>> ri;
vector<pair<int, int>> le;
vector<pair<int, int>> ri2;
vector<pair<int, int>> le2;

void swap(pair<int, int> &p1, pair<int, int> &p2){
    pair<int, int> temp = p1;
    p1 = p2;
    p2 = temp;
}

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(vector<pair<int, int>> &arr, int N, int i)
{

    // Initialize largest as root
    int largest = i;

    // left = 2*i + 1
    int l = 2 * i + 1;

    // right = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < N && arr[l].first > arr[largest].first)
        largest = l;

    // If right child is larger than largest
    // so far
    if (r < N && arr[r].first > arr[largest].first)
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
    }
}

// Main function to do heap sort
void heapSort(vector<pair<int, int>> &arr, int N)
{

    // Build heap (rearrange array)
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);

    // One by one extract an element
    // from heap
    for (int i = N - 1; i > 0; i--) {

        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main()
{
    cin >> n >> m;
    ri2.push_back({0, 0});
    ri2.push_back({m, 0});
    le2.push_back({m, 0});
    le2.push_back({0, 0});

    for(int i=0; i<n; i++){
        int s, e;
        cin >> s >> e;
        if(s < e){
            ri2.push_back({s, 1});
            ri2.push_back({e, -1});
            //le.push_back({s, 0});
            //le.push_back({e, 0});
        }
        else{
            le2.push_back({s, 1});
            le2.push_back({e, -1});
            //ri.push_back({s, 0});
            //ri.push_back({e, 0});
        }
    }
	
    //sort(ri.begin(), ri.end());
    heapSort(ri2, ri2.size());
    //sort(le.begin(), le.end());
    heapSort(le2, le2.size());

    int i = 0, j = 0;
    while(i < ri2.size() && j < le2.size()){
        if(ri2[i].first < le2[j].first){
            ri.push_back(ri2[i]);
            le.push_back({ri2[i].first, 0});
            i++;
        }
        else{
            ri.push_back({le2[j].first, 0});
            le.push_back(le2[j]);
            j++;
        }
    }
    while(i < ri2.size()){
        ri.push_back(ri2[i]);
        le.push_back({ri2[i].first, 0});
        i++;
    }
    while(j < le2.size()){
        ri.push_back({le2[j].first, 0});
        le.push_back(le2[j]);
        j++;
    }
    ri2.clear();
    le2.clear();

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

        ans += (ll)(le[i+1].first - ri[i].first) * (right_cnt + left_cnt);
    }
    cout << ans << '\n';
}
