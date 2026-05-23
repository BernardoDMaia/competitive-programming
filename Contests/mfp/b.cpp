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
    string sa, sp; cin >> sa >> sp;
    vll freqA(26, 0), freqP(26,0);

    FOR(i,0,sa.size()) freqA[sa[i] - 'a']++;
    FOR(i,0,sp.size()) freqP[sp[i] - 'a']++;

    int q; cin >> q;
    while(q--){
        int tp; cin >> tp;
        if(tp == 1){
            ll k; cin >> k;
            string s; cin >> s;
            FOR(i,0,s.size()) freqA[s[i]-'a'] += k;
        }
        else if(tp == 2){
            ll k; cin >> k;
            string s; cin >> s;
            FOR(i,0,s.size()) freqP[s[i]-'a'] += k;
        }
        else{
            int ok = 1;
            FOR(i,0,26){
                if(freqA[i] > freqP[i]){
                    int ok1 = 1;
                    ok = 0;
                    FOR(j,i+1,26){
                        if(freqP[j] > 0){
                            ok1 = 0;
                            cout << "ADA\n";
                            break;
                        }
                    }
                    if(ok1)cout << "PY\n";
                    break;
                }
                if(freqA[i] < freqP[i]){
                    int ok1 = 1;
                    ok = 0;
                    FOR(j,i+1,26){
                        if(freqA[j] > 0){
                            ok1 = 0;
                            cout << "PY\n";
                            break;
                        }
                    }
                    if(ok1)cout << "ADA\n";
                    break;
                }
            }
            if(ok) cout << "EMPATE\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; 
    //cin >> t;
    while(t--){
        solve();
    }
}