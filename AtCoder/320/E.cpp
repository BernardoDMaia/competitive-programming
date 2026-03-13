#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAX = 2e5 + 5;


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n,m; cin >> n >> m;
    set<ll>fila;
    vector<ll>ans(n);
    using T = pair<ll,ll>;
    priority_queue<T, vector<T>,greater<T>>pq;

    for(int i = 0; i<n; i++){
        fila.insert(i+1);
    }

    for(int i = 0; i < m; i++){
        int t, w, s; cin >> t >> w >> s;
        while(!pq.empty() && pq.top().first <= t){
            fila.insert(pq.top().second);
            pq.pop();
        }

        if(!fila.empty()){
            ans[*fila.begin()-1] += w;
            pq.push({(ll)t+s, *fila.begin()});
            fila.erase(fila.begin());
        }
    }

    for(int i = 0; i < n; i++){
        cout << ans[i] << endl;
    }

}