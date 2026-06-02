#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)
#define all(x) x.begin(), x.end()

void solve(){
    int n,k,q; cin >> n >> k >> q;
    set<int> casa;
    FOR(i,0,n){
        casa.insert(i);
    }
    using T = tuple<int,int,int>;
    priority_queue<T,vector<T>, greater<T>> pq;
    vector<tuple<int,int,int, int>> a(q);
    FOR(i,0,q){
        int pessoa, l,r; cin >> pessoa >> l >> r;
        pessoa--;
        a[i] = {pessoa,l,r,i};
    }

    sort(all(a), [&](auto A, auto B){
        auto [pessoa,l,r, idx] = A;
        auto [ppessoa,lll,rr, id1] = B;
        return lll >  l;
    });

    vi ans(q);
    FOR(i,0,q){
        auto [pessoa,l,r,idx] = a[i];
        while(!pq.empty()){
            auto [x,y,z] = pq.top();
            if(x>l) break;
            pq.pop();
            if(casa.size()==0){
                ans[z] = 1;
            }
            casa.insert(y);
        }
        casa.erase(pessoa);
        pq.push({r,pessoa,idx});
    }

    while(!pq.empty()){
        auto [x,y,z] = pq.top();
        pq.pop();
        if(casa.size()==0){
            ans[z] = 1;
        }
        casa.insert(y);
    }

    int keys = k;
    priority_queue <int, vector<int> , greater<int>> chaves;
    FOR(i,0,q){
        auto [p,l,r,idx] = a[i];
        if(ans[idx]){
            while(!chaves.empty()){
                if(chaves.top() > l) break;
                chaves.pop();
                keys++;
            }
            keys--;
            chaves.push(r);
        }
        if(keys < 0){
            cout << "impossible\n";
            return;
        }
    }

    for(int v : ans) cout << v;
    cout << "\n";
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}