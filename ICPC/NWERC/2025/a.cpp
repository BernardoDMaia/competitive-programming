#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";
#define sz(x) x.size()
#define pb push_back

void solve(){
    int n; cin >> n;
    cin.ignore();
    vector<pair<string,string>> v;
    FOR(j,0,n){
        string s, ss;
        getline(cin, s);
        FOR(i,0,s.size()){
            if(s[i] >= 'A' && s[i] <= 'Z') {
                ss = s.substr(i);
                v.pb({ss,s});
                break;
            }
        }
    }
    sort(all(v));
    for(auto[l,r] : v) cout << r << "\n";


    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();    
    }
    return 0;
}