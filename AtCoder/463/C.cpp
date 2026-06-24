#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";

void solve(){
    int n; cin >> n;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    multiset<int> h;

    FOR(i,0,n){
        int a, b; cin >> a >> b;
        h.insert(a);
        pq.push({b,a});
    }

    int q; cin >> q;
    vector<pii>queries;
    FOR(i,0,q){
        int time; cin >> time;
        queries.push_back({time,i});
    }
    sort(all(queries));

    vi ans(q);
    FOR(i,0,q){
        int time = queries[i].first;
        while(!pq.empty()){
            auto [l,r] = pq.top();
            if(l <= time){ 
                pq.pop();
                h.erase(r);
            }
            else break;
        }
        auto it = h.end();
        it--;
        ans[queries[i].second] = *it;
    }

    for(int v :ans) cout << v << "\n";
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