#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vc =vector<char>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    int n; cin >> n;
    vi v(n);
    map<int,int> freq;

    FOR(i,0,n) {
        cin >> v[i];
        freq[v[i]]++;
    }

    int menor = 1e9+5, idx = 0;
    FOR(i,0,n){
        if(freq[v[i]] < menor){
            menor = v[i];
            idx = i;
        }
    }

    // cout << "menor:" << menor << "\n";
    // cout << "idx:" << idx << "\n";

    set<int>s;
    FOR(i,0,n){
        if(v[i] == menor && i != idx) s.insert(i);
    }

    // for(auto v : s) cout << v << " ";
    // cout << "\n";

    if(sz(s) == n-1) cout << "NO" << "\n";
    else{
        cout << "YES" << endl;
        FOR(i,0,n){
            if(v[i] != menor){
                cout << idx+1 << " " << i+1 << "\n";
                if(sz(s) != 0){
                    auto it = s.begin();
                    cout << i+1 << " " << ((*it) + 1) << "\n";
                    s.erase(*it);
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}