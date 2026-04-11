#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vc =vector<char>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

struct DSU{
    vi e;
    void init(int n){
        e = vi(n,-1);
    }

    int get(int x){
        return e[x] < 0 ? x : e[x] = get(e[x]);
    }

    bool sameSet(int a, int b){
        return get(a) == get(b);
    }
    int size(int x){
        return -e[get(x)];
    }
    bool unite(int x, int y){
        x = get(x), y = get(y);
        if(x==y) return 0;
        if(e[x]>e[y]) swap(x,y);
        e[x] += e[y];
        e[y] = x;
        return 1;
    }
};

void solve(){
    int n,m; cin >> n >> m;
    DSU dsu;
    dsu.init(n);
    
    int mx = 0;
    int comp = n;
    FOR(i,0,m){
        int x, y; cin >> x >> y;
        x--; y--;

        if(!dsu.sameSet(x,y)){
            comp--;
            dsu.unite(x,y);
        }
        mx = max(mx, dsu.size(x));

        cout << comp << " " << mx << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    // int t = 1;
    // cin >> t;
//    while(t--){
        solve();
  //  }
}