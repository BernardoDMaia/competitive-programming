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
    vi cards(7);
    FOR(i,1,7){
        cin >> cards[i];
    }

    ll ans = 0;
    int ok = 1;
    while(ok == 1){
        ok = 0;

        int rod_m = 1e9+5;
        FOR(i,1,7){
            int minimo = 1e9+5;
            if(cards[i] == 0) continue;
            minimo = min(minimo, cards[i]);
            if(i>1){
                if(cards[i-1] == 0){
                    if(minimo % 2 == 1){
                        if(minimo != 1) minimo /= 2;
                        rod_m = min(rod_m, ((minimo-1)*6)+i-1);
                    }
                    else{
                        minimo /= 2;
                        rod_m = min(rod_m, ((minimo-1)*6)+i);
                    }
                }
            }
        }

        FOR(i,1,7){
            cards[i] -= (rod_m-1)/6;
            if(rod_m%6 >= i) cards[i]--;
            if(cards[i] < 0) cards[i] = 0;
        }


        FOR(i,1,7){
            if(cards[i] > 0) ok = 1;
        }
    }

    cout << ans << endl;
    
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}