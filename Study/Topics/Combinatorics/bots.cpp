#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)(x).size()
#define deb(x) cerr << #x << " = " << x << "\n";
#define deb2(x,y) cerr << #x << "=" << x << ", " << #y << "=" << y << "\n";
#define deb3(x,y,z) cerr << #x << "=" << x << ", " << #y << "=" << y << ", " << #z << "=" << z << "\n";
const int MOD = 1e9 + 7;
const int MAXN = 3e6 + 7;

int fat[MAXN], invFat[MAXN];

int fexp(int b, int e){
    int res = 1;
    while(e){
        if(e & 1) res = (res*b) % MOD;
        b = (b*b)%MOD;
        e /= 2;
    }
    return res;
}

int inv(int x){
    return fexp(x, MOD-2);
}

void build_fat(){
    fat[0] = 1;
    FOR(i,1,MAXN) fat[i] = (fat[i-1] * i) % MOD;

    invFat[MAXN-1] = inv(fat[MAXN-1]);
    for(int i = MAXN-2; i >= 0; i--){
        invFat[i] = (invFat[i+1] * (i+1)) % MOD;
    }
}

int nCr(int n, int k){
    if(k < 0 || k > n) return 0;
    return fat[n]*invFat[k] % MOD * invFat[n-k] % MOD;
}

void solve(){
    int n; cin >> n;
    int completos = 0, ans = 1, curr = 1;
    FOR(i,1,(2*n + 1)){
        if(i > n){//ja completou
            completos = (2 * nCr(i-1, n)) % MOD;
            curr = ((((curr-completos+MOD)*2) % MOD) + completos) % MOD;
        }
        else curr = (curr * 2) % MOD;
        ans = (ans + curr) % MOD;
    }

    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    build_fat();
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}