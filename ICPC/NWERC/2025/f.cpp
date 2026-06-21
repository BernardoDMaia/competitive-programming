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

struct DSU{
    vi f, siz;
    DSU(){}
    DSU(int n){
        init(n);
    }

    void init(int n){
        f.resize(n);
        iota(all(f),0);
        siz.assign(n,1);
    }

    int find(int x){
        while(x != f[x]) x = f[x] = f[f[x]];
        return x;
    }

    bool merge(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) return false;
        f[y] = x;
        return true;
    }
};

void solve(){
    int n, q; cin >> n >> q;
    vi v(n+1);
    vi curr(n+1,0);
    FOR(i,0,n) cin >> v[i];

    DSU dsu(n+1);
    vi ms(n+1,n);
    vector<pair<int,int>>stk;

    for(int i = n-1; i >= 0; i--){
        while(!stk.empty() && stk.back().first <= v[i]) stk.pop_back();
        if(!stk.empty()) ms[i] = stk.back().second;
        stk.push_back({v[i], i});
    }

    while(q--){
        char t; cin >> t;
        if(t == '+'){
            int x, y; cin >> x >> y;
            x--;
            while(curr[x] + y > v[x] && x != n){
                int encher = v[x] - curr[x];
                curr[x] += encher;
                y -= encher;
                dsu.merge(ms[x],x);
                x = dsu.find(x);
            }
            curr[x] += y;
        }
        else{
            int x; cin >> x;
            x--;
            cout << curr[x] << "\n";
        }
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