#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define deb(x) cerr << #x << "=" <<  x << "\n";

template <typename T>
struct BIT{
    int n;
    vector<T> a;

    BIT(int n_ = 0){
        init(n_);
    }
    void init(int n_){
        n = n_;
        a.assign(n,T{});
    }

    void add(int x, const T &v){
        for(int i = x+1; i<=n; i+= i & -i){
            a[i-1] += v;
        }
    }

    T sum(int x){
        T ans{};
        for(int i = x;i>0; i-= i & -i){
            ans += a[i-1];
        }
        return ans;
    }

    T rangeSum(int l, int r){
        return sum(r)-sum(l);
    }
};

void solve(){
    int n,q; cin >> n >> q;
    vector<pair<int,int>> a(n);
    vi normal(n);
    FOR(i,0,n){
        cin >> a[i].first;
        a[i].second = i;
        normal[i] = a[i].first;
    }

    sort(all(a));
    vector<tuple<int,int,int, int>> queries;
    FOR(i,0,q){
        int l, pos,r; cin >> l >> pos >> r;
        queries.pb({pos,l,l+r,i});
    }

    sort(all(queries));
    reverse(all(queries));
    BIT<ll> bit(n);
    vi ans(q);
    vi vis(n,0);
    // cout << "vetor a: ";
    // for(auto[l,r] : a){
    //     cout << l << " " << r << "\n";
    // }
    for(auto[pos,l,r,idx] : queries){
        if(normal[l-1]>= pos){
            ans[idx] = 0;
            continue;
        }
        pair<int,int> curr = {pos,0};
        int start = lower_bound(all(a), curr) - a.begin();
        // cout << "start: " << start << "\n";
        FOR(i,start,n){
            // cout << "entrei no i: " << i << "\n";
            if(vis[a[i].second]) break; 
            else{
                vis[a[i].second] = 1;
                bit.add(a[i].second, 1);
            }
        }
        ans[idx] = bit.rangeSum(l,r);
    }
    
    for(int v : ans) cout << v << "\n";

        
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
} 