#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define f first
#define s second 
typedef vector<int>vi; 
typedef pair<int,int>pi;

const int MAX = 2e5 + 5;
const int INF = 1e9 + 5;

int v[MAX];
int seg[MAX*4];

int build(int ind, int low, int high){
    if(low==high) return seg[ind] = v[low];
    int mid = (low+high)/2;
    return seg[ind] = max( build(2*ind, low, mid), build(2*ind+1, mid+1, high) );
}

int update(int ind, int low, int high, int target, int value){
    if(target < low || high < target) return seg[ind];
    if(low == high) return seg[ind] -= value;
    int mid = (low+high)/2;
    return seg[ind] = max(update(2*ind, low, mid, target, value), update(2*ind+1, mid+1, high, target, value));
}

int query(int ind, int low, int high, int m, int n){
    if(seg[ind] < m) return 0;

    if(low == high) {
        update(1, 0, n-1, low, m);
        return low + 1;
    }
    
    int mid = (low+high)/2;
    if(seg[2*ind] >= m){
        return query(2*ind, low, mid, m, n);
    }
    else if(seg[2*ind+1] >= m){
        return query(2*ind+1, mid+1, high, m, n);
    }
}


int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    
    int n, q; cin >> n >> q; 
    for(int i = 0; i < n; i++) cin >> v[i];

    build(1, 0, n-1);

    while(q--){
        int m; cin >> m;
        cout << query(1, 0, n-1, m, n) << endl;
    }
}