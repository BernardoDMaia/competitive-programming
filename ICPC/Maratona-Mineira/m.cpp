#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    int q, n, t; cin >> q >> n >> t;
    vpii a(q);
    vi v(n), ans(n);
    vpii aux(n);

    FOR(i,0,q){
        int x,y; cin >> x >> y;
        a[i] = {x,y};
    }

    FOR(i,0,n){
        cin >> v[i];
        aux[i] = {v[i], i}; 
    }

    sort(all(aux));
    sort(all(a));

    priority_queue<int>pq;
    ll soma = 0; int j = 0;

    FOR(i,0,n){
        while(a[j].first <= aux[i].first && j<q){
            pq.push(a[j].second);
            soma += (ll)a[j].second;
            j++;
        }

        while(soma > t){
            soma -= (ll)pq.top();
            pq.pop();
        }

        ans[aux[i].second] = sz(pq);
    }

    FOR(i,0,n) cout << ans[i] << endl;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}