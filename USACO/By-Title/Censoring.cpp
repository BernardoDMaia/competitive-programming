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

const int HMOD1 = 1e9 + 7;
const int HMOD2 = 1e9 + 9;
const int HBASE = 911382323;
struct PolyHash{
    int n ;
    vi h1 , h2 , p1 , p2 ;
    PolyHash(const string &s){
        n = sz(s) ;

        h1.assign (n +1 ,0) ;
        h2.assign (n +1 ,0) ;
        p1.assign (n +1 ,1) ;
        p2.assign (n +1 ,1) ;

        FOR (i ,0 , n ){
            int x = (unsigned char) s [i] + 1;

            h1 [i +1] = (h1[i] * HBASE + x) % HMOD1 ;
            h2 [i +1] = (h2[i] * HBASE + x) % HMOD2 ;
            p1 [i +1] = p1 [i] * HBASE % HMOD1 ;
            p2 [i +1] = p2 [i] * HBASE % HMOD2 ;
        }
    }

    pair <int ,int > get ( int l , int r ) const {
        int x1 = (h1[r] - h1 [l] * p1 [r-l]) % HMOD1 ;
        int x2 = (h2[r] - h2 [l] * p2 [r-l]) % HMOD2 ;

        if(x1 < 0) x1 += HMOD1 ;
        if(x2 < 0) x2 += HMOD2 ;

        return {x1 , x2};
    }
};


void solve(){
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);
    string s, t; cin >> s >> t;
    PolyHash h1(t);
    int n = sz(s);
    int m = sz(t);

    string ans = "";
    int tam = 0;
    vi hDinamico(1,0);
    
    auto conta = [&](int h, int c) -> int {
        return (h * HBASE + c + HMOD1) % HMOD1;
    };
    auto getDin = [&](int l, int r) -> int {
        int res = (hDinamico[r] - hDinamico[l]*h1.p1[r-l]) % HMOD1;
        if(res < 0) res += HMOD1;
        return res;
    };

    FOR(i,0,n){
        ans += s[i];
        hDinamico.pb(conta(hDinamico.back(), (unsigned char)s[i] + 1));
        tam = sz(ans);
        if(tam < m) continue;
        if(h1.get(0,m).first == getDin(tam - m,tam)){
            ans.resize(tam-m);
            hDinamico.resize(tam-m+1);
        }
    }

    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--)
    solve();
    return 0;
}