#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> v(n), aux(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
        aux[i] = v[i];
    }
    sort(aux.begin(),aux.end());
    
    while(q--){
        int k; cin >> k;
        vector<int>val(k);
        for(int i = 0; i < k; i++){
            int x; cin >> x;
            x--;
            val[i] = v[x];
        }
        sort(val.begin(), val.end());
        
        int ok = 0;
        for(int i = 0; i < k; i++){
            if(aux[i] < val[i]){
                cout << aux[i] << endl;
                ok = 1;
                break;
            }
        }
        if(ok == 0) cout << aux[k] << endl;
    }

}