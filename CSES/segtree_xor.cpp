#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define f first
#define s second 
typedef vector<int>vi; 
typedef pair<int,int>pi;

const int MAX = 2e5 + 5;
const int INF = 0;

int v[MAX];
int seg[MAX*4];

int build(int ind, int low, int high){
    if(low==high) return seg[ind] = v[low];
    int mid = (low+high)/2;
    return seg[ind] = build(2*ind, low, mid) ^ build(2*ind+1, mid+1, high) ;
}

int query(int ind, int low, int high, int l, int r){
    if(r < low || high < l) return INF;
    if(l <= low && high <= r) return seg[ind];
    int mid = (low+high)/2;
    return query(2*ind, low, mid, l, r) ^ query(2*ind+1, mid+1, high, l, r);
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    
    int n, q; cin >> n >> q; 
    for(int i = 0; i < n; i++) cin >> v[i];

    build(1, 0, n-1);

    while(q--){
        int a, b; cin >> a >> b;
        a--;b--;
        cout << query(1, 0, n-1, a, b) << endl;
    }
}