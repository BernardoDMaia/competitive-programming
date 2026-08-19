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
    string s, t; cin >> s >> t;
    PolyHash h(t);

    int qtd0 = 0, qtd1 = 0;
    FOR(i,0,sz(s)){
        if(s[i] == '0') qtd0++;
        else qtd1++;
    }

    int tam = sz(t);
    int ans = 0;
    FOR(i,1,tam){//i é o tam de r0
        if((tam - (i*qtd0)) % qtd1 != 0) continue;
        if(i*qtd0 >= tam) break;
        
        int tr0 = i;
        int tr1 = (tam - (i*qtd0)) / qtd1;
        pii nulo = {-1, -1};
        pii hshR0 = nulo;
        pii hshR1 = nulo;
        int idx = 0, ok = 1;

        FOR(i,0,sz(s)){
            // deb(idx);
            // deb2(tr0,tr1);
            if(s[i] == '0'){
                if(hshR0 == nulo) hshR0 = h.get(idx, idx+tr0);
                else if(hshR0 != h.get(idx, idx+tr0)) {ok = 0;break;}
                idx += tr0;
            }
            else{
                if(hshR1 == nulo) hshR1 = h.get(idx, idx+tr1);
                else if(hshR1 != h.get(idx, idx+tr1)) {ok = 0;break;}
                idx += tr1;
            }
        }

        if(ok && hshR0 != hshR1) ans++;
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