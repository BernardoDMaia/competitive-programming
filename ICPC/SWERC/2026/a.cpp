#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pll = pair<ll,ll>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";
#define pb push_back

void solve(){
    int n, k; cin >> n >> k;
    vi steps, freq(10*n, 0);
    FOR(i,0,n){
        int x; cin >> x;
        freq[x]++;
    }
    steps.pb(0);

    int curr = 0;
    FOR(i,0,(10*n) - 1){
        if(freq[i] <= k && curr != 0){
            steps.pb(curr);
            curr = 0;
        }
        else if(freq[i] > k){ 
            curr++;  
            freq[i+1] += freq[i]-1; 
        }
    }

    cout << *max_element(all(steps)) << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1; 
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}