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
    PolyHash(const vi &s){
        n = sz(s) ;
 
        h1.assign (n +1 ,0) ;
        h2.assign (n +1 ,0) ;
        p1.assign (n +1 ,1) ;
        p2.assign (n +1 ,1) ;
 
        FOR (i ,0 , n ){
            int x = s[i] + 1;
 
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
    int n; cin >> n;
    vector<pii> v(n);
    FOR(i,0,n) cin >> v[i].first >> v[i].second;

    vi dist(n), ang(n);
    FOR(i,0,n){
        pii x = v[(n+i-1) % n];
        pii y = v[(i+1) % n];
        int ax = v[i].first - x.first;
        int ay = v[i].second - x.second;
        int bx = y.first - v[i].first;
        int by = y.second - v[i].second;
        int cross = ax*by - ay*bx;
        ang[i] = (cross > 0 ? 1 : 2);
        dist[i] = (v[i].first == y.first ? abs(v[i].second - y.second) : abs(v[i].first - y.first));
    }

    vi prefsum(n+1,0);
    FOR(i,0,n) prefsum[i+1] = prefsum[i] + dist[i];

    PolyHash h1(dist), h2(ang);

    int ans = 0;
    FOR(i,1,n){//cada ponto
        //achar o segmento unico indo ate a dir
        int parei = n;
        for(int k = i; k < n; k++){
            int tam = k-i, ok = 1;
            auto hsh1 = h1.get(i,k);
            auto hsh2 = h2.get(i,k+1);
            for(int j = 1; j < n - tam; j++){
                if(j == i) continue;
                auto hsh3 = h1.get(j, j+tam);
                auto hsh4 = h2.get(j, j+tam+1);
                if(hsh1 == hsh3 && hsh2 == hsh4){//esse segmento nao é valido
                    ok = 0;
                    break;
                }
            }
            if(ok){ 
                parei = k;
                break;
            }
        }
        //diferenca de dist
        int better = min(prefsum[i], prefsum[n]-prefsum[i]);
        int curr = min(prefsum[parei], prefsum[n]-prefsum[parei]);
        curr += prefsum[parei] - prefsum[i];
        int diff = abs(better-curr);
        ans = max(ans,diff);
    }

    cout << ans << "\n";
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