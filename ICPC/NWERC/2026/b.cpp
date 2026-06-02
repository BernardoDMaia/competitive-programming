#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)
#define all(x) x.begin(), x.end()

void solve(){
    int n; cin >> n;
    vi np = {4, 40, 44, 400,404, 440,444,  1000};
    int aux = n;
    while(aux>1000){
        aux-=1000;
    }
    FOR(i,0, np.size()){
        if (aux== np[i]) {
            cout << "splittable\n";
            // return;
        }
    }

    aux = n;

    vi coins = {1, 2, 5, 10, 20, 50, 100, 200, 500};
    reverse(coins.begin(), coins.end());
    vi ans;

    FOR(i,0,coins.size()){
        while(coins[i]<= aux){
            ans.push_back(coins[i]);
            aux-= coins[i];
        }
        if(aux==0) break;
    }
    cout << ans.size() << "\n";
    for(int x : ans) cout<< x << " ";
    cout << "\n";




}

int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    int t; cin >> t;
    while(t--)
    solve();

    return 0;
}