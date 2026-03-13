#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll dist(ll x1, ll y1, ll x2, ll y2){
    return ((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2));
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n; cin >> n;
    ll w, l, tx, ty; cin >> w >> l >> tx >> ty;
    vector<ll> teamA(n), teamR(n);
    
    for(int i = 0; i < n; i++){
        ll a, b; cin >> a >> b;
        teamA[i] = dist(a,b,tx,ty); 
    }

    for(int i = 0; i < n; i++){
        ll a, b; cin >> a >> b;
        teamR[i] = dist(a,b,tx,ty); 
    }

    sort(teamA.begin(),teamA.end());
    sort(teamR.begin(),teamR.end());

    int ans = 1;
    if(teamA[0] < teamR[0]){
        for(int i = 1; i < n; i++){
            if(teamA[i] < teamR[0]) ans++;
            else break;
        }
        cout << 'A' << ' ' << ans << endl;
    }
    else{
        for(int i = 1; i < n; i++){
            if(teamR[i] < teamA[0]) ans++;
            else break;
        }
        cout << 'R' << ' ' << ans << endl;
    }

    
}