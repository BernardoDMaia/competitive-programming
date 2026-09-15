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
    int n, k; cin >> n >> k;
    vi v(n+1,0);

    auto f = [&](auto &&self, int idx, int sum) -> void {
        if(idx == n){
            if((k-sum) % n == 0){
                v[idx] = (k-sum)/n;
                FOR(i,1,n+1) cout << v[i] << " ";
                cout << "\n";
            }
            return;
        }

        for(int x = 0; sum + (idx*x) <= k; x++){
            v[idx] = x;
            self(self, idx+1, sum + (idx*x));
        }
    };

    f(f,1,0);

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