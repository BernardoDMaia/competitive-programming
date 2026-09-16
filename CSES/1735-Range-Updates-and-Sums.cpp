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
//ctrl+alt+a p/ accepted

enum QueryType { UPDATE, SET, NONE };

struct Tag{
    QueryType type = NONE;
    int val = 0;

    void apply(const Tag& t){
        if(t.type == SET){
            type = SET;
            val = t.val;
        }else if(t.type == UPDATE){
            if(type == NONE){
                type = UPDATE;
                val = t.val;
            }else val += t.val;
        }
    }
};

struct Info{
    int val = 0;

    void apply(const Tag& t, int l, int r){
        if(t.type == UPDATE) val += t.val * (r - l + 1);
        else if(t.type == SET) val = t.val * (r - l + 1);
    }
};

Info operator+(const Info& a, const Info& b){
    return {a.val + b.val};
}

template<class Info, class Tag>
struct LazySegtree{
    int n;
    vector<Info> tree;
    vector<Tag> lazy;

    LazySegtree(int n) : n(n){
        tree.assign(4*n, Info());
        lazy.assign(4*n, Tag());
    }

    LazySegtree(const vector<Info>& a) : n(sz(a)){
        tree.assign(4*n, Info());
        lazy.assign(4*n, Tag());
        build(1, 0, n-1, a);
    }

    void build(int v, int l, int r, const vector<Info>& a){
        if(l == r){ tree[v] = a[l]; return; }
        int m = (l+r)/2;
        build(2*v, l, m, a);
        build(2*v+1, m+1, r, a);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    void apply(int v, int l, int r, const Tag& x){
        tree[v].apply(x, l, r);
        lazy[v].apply(x);
    }

    void push(int v, int l, int r){
        if(lazy[v].type == NONE || l == r) return;
        int m = (l+r)/2;
        apply(2*v, l, m, lazy[v]);
        apply(2*v+1, m+1, r, lazy[v]);
        lazy[v] = Tag();
    }

    void update(int v, int l, int r, int ql, int qr, const Tag& x){
        if(qr < l || r < ql) return;
        if(ql <= l && r <= qr){ apply(v, l, r, x); return; }
        push(v, l, r);
        int m = (l+r)/2;
        update(2*v, l, m, ql, qr, x);
        update(2*v+1, m+1, r, ql, qr, x);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    Info query(int v, int l, int r, int ql, int qr){
        if(qr < l || r < ql) return Info();
        if(ql <= l && r <= qr) return tree[v];
        push(v, l, r);
        int m = (l+r)/2;
        return query(2*v, l, m, ql, qr) + query(2*v+1, m+1, r, ql, qr);
    }

    void update(int ql, int qr, const Tag& x){ update(1, 0, n-1, ql, qr, x); }
    Info query(int ql, int qr){ return query(1, 0, n-1, ql, qr); }
};

void solve(){
    int n, q; cin >> n >> q;
    vector<Info>base(n);
    FOR(i,0,n){
        int x; cin >> x;
        base[i] = {x};
    }

    LazySegtree<Info, Tag> lst(base);

    while(q--){
        int type, l, r; cin >> type >> l >> r;
        l--;r--;
        if(type == 1){
            int x; cin >> x;
            lst.update(l,r, {UPDATE,x});
        }
        else if(type == 2){
            int x; cin >> x;
            lst.update(l,r, {SET, x});
        }
        else cout << lst.query(l,r).val << "\n";
    }
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