#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<b;i++)
#define all(x) x.begin(), x.end()
using pii = pair<int,int>;
#define pb push_back
#define sz(x) x.size()
#define deb(x) cerr << #x << "= " << x << "\n";
#define deb2(x,y) cerr << #x << "= " << x << ", "<< #y << "= " << y << "\n";
//ctrl+alt+a p/ accepted

void solve(){
    int n; cin >> n;
    vi v(n);
    FOR(i,0,n) cin >> v[i];
    FOR(i,1,11){
        for(int j = 0 + (10*(i-1)); j < min(n, (10*i)); j++){
            if(v[j] > (10*i)){
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--)
    solve();
    return 0;
}