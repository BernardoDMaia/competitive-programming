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
    int n; cin >> n;
    string s; cin >> s;
    vi v(1e8, -1);
    int mask = 0;
    v[mask] = 0;
    int ans = 1;

    FOR(i,0,n){
        int pos = s[i] - 'a';
        if(mask & (1 << pos)){
            mask &= ~(1 << pos);
            if(__builtin_popcount(mask) <= 1){
                if(v[mask] == -1) v[mask] = i+1;
                else ans = max(ans, i - v[mask]);
            }
        }
        else{
            mask|= (1 << pos);
            if(__builtin_popcount(mask) <= 1){
                if(v[mask] == -1) v[mask] = i+1;
                else ans = max(ans, i - v[mask]);
            }
        }
    }

    cout << ans << endl;

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}