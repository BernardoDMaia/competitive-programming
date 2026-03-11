#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> p(m);
    int ans = 0;

    for(int i = 0; i < m; i++){
        cin >> p[i];
    }

    for(int i = 0; i < n; i++){
        int b, a; cin >> b >> a;
        b--;
        if(p[b] > 0){
            if(p[b] > a){
                ans += a;
                p[b] -= a;
            }
            else{
                ans += p[b];
                p[b] = 0;
            }
        }
       // cout << ans << endl;
    }

    cout << ans << endl;

}