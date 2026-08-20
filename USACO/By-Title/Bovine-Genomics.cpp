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
    int n, m; cin >> n >> m;
    vector<vi> hshS(n, vi(m+1)), hshP(n, vi(m+1));
    string b = "";
    FOR(i,0,m) b += "a";
    PolyHash base(b);

    FOR(i,0,n){
        string s; cin >> s;
        PolyHash h(s);
        hshS[i] = (h.h1);
    }

    FOR(i,0,n){
        string s; cin >> s;
        PolyHash h(s);
        hshP[i] = (h.h1);
    }

    auto get = [&](int l, int r, vi &h) -> int {
        int ret = (h[r] - h[l] * base.p1[r-l]) % HMOD1;
        if(ret < 0) ret += HMOD1;
        return ret;
    };

    auto check = [&](int len) -> bool {
        for(int k = 0; k <= m-len; k++){//blocos
            int ok = 1;
            unordered_set<int> s;
            FOR(i,0,n){//percorro as spotties
                s.insert(get(k,k+len,hshS[i])); //coloco todos os hsh em um set
            }
            FOR(j,0,n){//percorro as plains
                int x = get(k,k+len,hshP[j]);
                if(s.count(x)){//ha uma plain que tem mesmo hashing, logo nao da pra diferenciar
                    ok = 0; //k nao é uma posicao
                    break;
                } 
            }
            if(ok) return true;
        }
        return false; //len nao serve
    };

    int l = 1, r = m, ans;
    while(l <= r){
        int mid = (l+r)/2;
        if(check(mid)){
            r = mid-1;
            ans = mid;
        }
        else l = mid+1;
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