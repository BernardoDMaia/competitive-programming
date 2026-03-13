#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n; cin >> n;
    vector<ll>red(n);
    vector<ll>blue(n);
    for(int i = 0; i < n; i++) cin>>red[i];
    for(int i = 0; i < n; i++) cin>>blue[i];

    sort(red.begin(),red.end());
    sort(blue.begin(),blue.end());
    ll maximo = 0; ll minimo = 2e9+7;
    for(int i = 0; i < n; i++){
        ll p = (ll) blue[i] + red[n-i-1];
        maximo = max(maximo, p);
        minimo = min(minimo, p);
    }

    cout << maximo-minimo << endl;
}

 