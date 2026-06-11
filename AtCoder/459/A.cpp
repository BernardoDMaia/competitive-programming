#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define fastio cin.tie(0)->sync_with_stdio(0);
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define deb(k) cerr << #k << ":" << k << "\n";
#define pb push_back
using ll = long long ;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void solve(){
    int n, q; cin >> n >> q;
    ordered_set s;
    vi v(n,0);
    FOR(i,0,n) s.insert({0,i});
    int rem = 0;

    while(q--){
        int tp,x; cin >> tp >> x;
        if(tp == 1){
            x--;
            int ant = v[x];
            v[x]++;
            s.erase({ant,x});
            s.insert({ant+1,x});
            if(s.begin()->first > rem) rem++;
        }
        else{
            int idx = s.order_of_key({x+rem,0});
            cout << n-idx << "\n";
        }
    }
}

int main(){
    fastio
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
