#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1e8;
vector<bool>primos(MAXN, true);

void crivo(){
    primos[0] = false;
    primos[1] = false;

    for(int i = 2; (ll)i*i <= MAXN; i++){
        if(primos[i] == true){
            for(int j = i+i; (ll)j*j <= MAXN; j+=i){
                primos[j] = false;
            }
        }
    }
}

bool ehprimo(ll n){
    if(n == 0) return false;
    if(n == 1) return false;
    for(int i = 2; (ll)i*i < n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    crivo();
    int n; cin >> n;
    vector<ll>ans;
    while(n--){
        int m; cin >> m;
        ll sum = 0;
        for(int i = 1; i <= m; i++){
            int x; cin >> x;
            if(primos[i]){
                sum += x;
            }
        }
        if(ehprimo(sum)) ans.push_back(sum);
    }

    if(ans.size() == 0) cout << "ITS OVER SOBROU NADA PRO BETINHA" << endl;
    else{
        cout << ans.size() << endl;
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << endl;
    }
}