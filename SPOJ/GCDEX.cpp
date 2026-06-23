#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pll = pair<ll,ll>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";
#define sz(x) x.size()
#define pb push_back

const int MAXN = 1e6+5;

int phi_sieve[MAXN];
vector<int>pr;
bool is_not_p[MAXN];

void linear_phi(){
    phi_sieve[1] = 1;
    FOR(i,2,MAXN){
        if(!is_not_p[i]){
            pr.push_back(i);
            phi_sieve[i] = i - 1;
        }
        for(int p : pr){
            if(i * p >= MAXN) break;
            is_not_p[i*p] = true;
            if(i % p == 0){
                phi_sieve[i*p] = phi_sieve[i] * p;
                break;
            }
            else{
                phi_sieve[i*p] = phi_sieve[i] * (p-1);
            }
        }
    }
}

void solve(){
    linear_phi();
    vll pref_sum(MAXN);
    FOR(i,2,MAXN) pref_sum[i] = pref_sum[i-1] + (ll)phi_sieve[i];

    //achando != 1
    vll f(MAXN);
    FOR(i,2,MAXN){
        for(int j = i; j < MAXN; j += i) f[j] += (ll)(i*(ll)phi_sieve[j/i]);
    }

    vll pref2_sum(MAXN);
    FOR(i,2,MAXN) pref2_sum[i] = pref2_sum[i-1] + f[i] - i;

    while(true){
        int n; cin >> n;
        if(n == 0) return;
        ll ans = pref_sum[n] + pref2_sum[n];
        cout << ans << "\n";
    }
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