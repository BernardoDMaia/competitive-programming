#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
using pii = pair<int,int>;
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
    int n; cin >> n;
    vector<string> ent(n), v;
    FOR(i,0,n) cin >> ent[i];
    sort(all(ent));
    ent.erase(unique(all(ent)), ent.end());
    n = sz(ent);
    
    //curiosidade
    //existe isSubstring(string1, string2) que diz de s1 é substr de s2 
    FOR(i,0,n){
        int ok = 0;
        FOR(j,0,n){
            if(i == j) continue;
            string s = ent[i], t = ent[j];
            int t1 = sz(s), t2 = sz(t);
            if(t1 > t2) continue;
            //ver se t1 é substr de t2
            PolyHash h1(s), h2(t);
            for(int k = 0; k <= t2-t1; k++){
                if(h1.get(0,t1) == h2.get(k, k+t1)) ok = 1;
            }
        }
        //se t1 é substr de qualquer j, nao deve estar
        if(ok) continue;
        v.pb(ent[i]); 
    }
    
    int tam = sz(v);
    if(tam == 1){
        cout << v[0].size() << "\n";
        return;
    }
    
    vector<vi> res(tam, vi(tam)); //res[i][j] guarda qts letras precisam continuar se juntarmos S(i)S(j)
    FOR(i,0,tam){
        string s = v[i];
        FOR(j,0,tam){
            if(i==j){
                res[i][j] = sz(s);
                continue;
            }
            string t = v[j];

            //colocar j na frente de i -> maior suf de i que tambem é pref de j
            int hshI = 0, hshJ = 0, pw = 1, curr = 0;
            int t1 = sz(t), t2 = sz(s);
            FOR(r,0,t1){
                if(t2-r-1 < 0) break;
                int x = (unsigned char)t[r] + 1;
                int y = (unsigned char)s[t2-r-1] + 1;

                hshJ = (hshJ*HBASE + x) % HMOD1;
                hshI = (hshI + pw*y) % HMOD1;
                if(hshI==hshJ) curr = r+1;

                pw = (pw*HBASE)%HMOD1;
            }
            res[i][j] = t1 - curr;
        }
    }

    vi a(sz(v));
    iota(all(a), 0);
    int ans = 1e9;
    
    while(true){
        int curr = 0;
        FOR(i,0,sz(a)-1){
            //a[i] é a string i
            //preciso do tam da primeira, ja a segunda é res[i][j]
            if(i == 0) curr += res[a[i]][a[i]];
            curr += res[a[i]][a[i+1]];
        }
        ans = min(ans,curr);
        if(!next_permutation(all(a))) break;
    }

    //outra opcao -> bitmask dp
    /*
    const int INF = 4e18;
    vector<vi> dp((1 << tam), vi(tam, INF)); //guarda a transição entre dp[mask][last]
    FOR(i,0,tam){
        dp[1 << i][i] = sz(v[i]); //casos base
    }
    
    FOR(mask,0,(1 << tam)){
        FOR(last,0,tam){
            if(!((mask >> last) & 1)) continue; //last nao esta na mask
            if(dp[mask][last] == INF) continue; //estado impossivel
            //prox masks
            FOR(i,0,tam){
                if((mask >> i) & 1) continue; //ja esta ligado
                int newMask = mask | (1 << i);
                dp[newMask][i] = min(dp[mask][last] + res[last][i], dp[newMask][i]);
            }
        }
    }

    int ans = INF;
    int lst = (1 << tam) - 1;
    FOR(i,0,tam){
        ans = min(ans, dp[lst][i]);
    }
    */

    cout << ans << "\n";
}

signed main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--)
    solve();
    return 0;
}