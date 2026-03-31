#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    int n, a ,b; cin >> n >> a >> b;
    vi v(n);

    FOR(i,0,n){
        int x; cin >> x;
        v[i] = x%(a+b);
    }

    sort(all(v));

    FOR(i,0,n-1){
        if(v[i+1]-v[i] >= b){
            cout << "Yes" << endl;
            return;
        }
    }
    if(v[n-1]-v[0] >= b) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}