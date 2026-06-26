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

const int MOD = 1e9+7;

ll fexp(ll b, ll e, ll m){
    ll res = 1;
    while(e){
        if(e & 1) res = (res*b)%m;
        b = (b*b)%m;
        e /= 2;
    }
    return res;
}

ll inv(ll x, ll m){
    return fexp(x, m-2, m);
}

void solve(){
    int n; cin >> n;
    ll number = 1, sumdiv = 1, numdiv = 1, numdiv2 = 1, proddiv = 1;
    FOR(i,0,n){
        ll x,y; cin >> x >> y;
        number = (number*fexp(x,y, MOD))%MOD;
        ll num = (fexp(x,(y+1),MOD)-1+MOD)%MOD;
        ll div = inv(x-1,MOD);
        ll pg = (num*div)%MOD;
        sumdiv = (sumdiv*pg)%MOD;
        numdiv = (numdiv*(y+1))%(MOD);
        //novo proddiv
        proddiv = fexp(proddiv,(y+1),MOD);
        //contribuicao do novo primo
        ll pot = (((y)*(y+1))/2)%(MOD-1);
        pot = (pot*numdiv2)%(MOD-1);
        ll newprime = fexp(x,pot,MOD);
        //final
        proddiv = (proddiv*newprime)%MOD;
        //atualiza depois pq pega os anteriores
        numdiv2 = (numdiv2*(y+1))%(MOD-1);
    }


    cout << numdiv%MOD << " " << sumdiv%MOD << " " << proddiv%MOD << "\n";
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