#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i, a, b) for(int i = a; i < b; i++)
#define all(x) x.begin() , x.end()
#define pb push_back

void solve(){
    ll a, n; cin >> a >> n;
    vi d(10,0), dmen(10,0), dmai(10,0);
    int menord = 9, maiord = 0;

    FOR(i,0,n){
        int x; cin >> x;
        d[x] = 1;
        dmen[x] = 1;
        dmai[x] = 1;
        menord = min(x,menord);
        maiord = max(x,maiord);
    }

    string maid = to_string(maiord);
    string mend = to_string(menord);

    for(int i = 8; i >= 0; i--) dmai[i] += dmai[i+1];
    FOR(i,1,10) dmen[i] += dmen[i-1];

    string s = to_string(a), menor = "", maior = "";

    if(n == 1 && d[0]){
        cout << a << "\n";
        return;
    }
    
    //menor
    int ok = 1, jamenor = 0;
    FOR(i,0,s.size()){
        int x = s[i] - '0';
        if(jamenor) menor += maid;
        else if(dmen[x]){
            for(int j = x; j >= 0; j--){
                if(i == 0 && j == 0) ok = 0;
                if(j < x) jamenor = 1;
                if(d[j]){
                    //  cout << "entrei, j:" << j << "\n";
                    string aux = to_string(j);
                    menor += aux;
                    break;
                }
            }
        }
        else ok = 0;
    }

    if(!ok){
        menor = "";
        FOR(i,0,s.size()-1) menor += maid;
    }

    //maior
    int jamaior = 0; ok = 1;
    FOR(i,0,s.size()){
        int x = s[i] - '0';
        if(jamaior) maior += mend;
        else if(dmai[x]){
            FOR(j,x,10){
                if(j > x) jamaior = 1;
                if(d[j]){
                    string aux = to_string(j);
                    maior += aux;
                    break;
                }
            }
        }
        else ok = 0;
    }

    if(!ok){
        maior = "";
        if(menord == 0){
            FOR(i,1,10) if(d[i]) maior += to_string(i);
            if(maior != "") FOR(i,0,s.size()) maior += mend;
        }
        else FOR(i,0,s.size()+1) maior += mend;
    }

    ll ans;
    if(maior == ""){
        ll b2 = stoll(menor);
        ans = a - b2;
    }
    else if(menor == ""){
        ll b1 = stoll(maior);
        ans = b1 - a;
    }
    else{
        ll b1 = stoll(maior);
        ll b2 = stoll(menor);
        ans = min(a-b2, b1-a);
    }

    cout << ans << "\n";
    
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}