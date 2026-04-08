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

const int INF = 1e9+5;

struct SegTree{
    int n;
    vll tree;
    ll neutro = INF;

    int left(int i) {return i<<1;}
    int right(int i) {return i<<1 | 1;}

    ll merge(ll a, ll b) {return min(a,b);}

    SegTree(const vll& a){
        n = sz(a);
        tree.assign(4*n, neutro);
        build(a, 1, 0, n-1);
    }

    void build(const vll& a, int i, int tl, int tr){
        if(tl==tr) tree[i] = a[tl];
        else{
            int tm = (tl+tr)/2;
            build(a, left(i), tl, tm);
            build(a, right(i), tm+1, tr);
            tree[i] = merge(tree[left(i)], tree[right(i)]);
        }
    }

    void update(int i, int tl, int tr, int p, ll v){
        if(tl == tr) tree[i] = v;
        else{
            int tm = (tl+tr)/2;
            if(p<=tm) update(left(i), tl, tm, p, v);
            else update(right(i), tm+1, tr, p, v);
            tree[i] = merge(tree[left(i)], tree[right(i)]);
        }
    }

    ll query(int i, int tl, int tr, int l, int r){
        if(l>r) return neutro;
        if(l == tl && r == tr) return tree[i];
        
        int tm = (tl+tr)/2;
        return merge(query(left(i),tl,tm,l,min(r,tm)), query(right(i),tm+1,tr,max(tm+1,l),r));
    }

    void update(int p, ll v){update(1,0,n-1, p, v);}
    ll query(int l, int r){ return query(1,0,n-1,l,r);}
};

void solve(){
    int n,m; cin >> n >> m;
    vll a(n);

    FOR(i,0,n) cin >> a[i];

    SegTree st(a);

    FOR(i,0,m){
        int x, y, z; cin >> x >> y >> z;
        if(x == 1) st.update(y,z);
        else{
            z--;
            cout << st.query(y, z) << "\n";
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}