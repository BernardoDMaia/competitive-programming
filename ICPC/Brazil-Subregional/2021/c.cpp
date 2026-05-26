#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define deb(x) cerr << #x << "=" <<  x << "\n";

const int MAXN = 1e5+5;

void solve(){
    int b, l; cin >> b >> l;
    vi digitos(l);
    int MOD = b+1;
    for(int i = l-1; i >= 0; i--){
        int d; cin >> d;
        digitos[i] = d;
    }

    ll soma = 0;
    FOR(i,0, l){
        ll add;
        if(i%2 ==0 ){
            add=digitos[i];
        } 
        else {
            add =(ll)b*digitos[i];
        }
        soma+= add;
        // deb(add);
    }

    ll reduzir = soma %MOD;
    // deb(reduzir);

    if(reduzir ==0){
        cout << "0 0\n";
        return;
    }
    ll alvo = -1;
    FOR(i,0, b+1){
        if((reduzir+MOD*i)% b == 0){
            alvo = reduzir+MOD*i;
            break;
        }
    }
    ll ans =-1 ;
    int idx = -1;
    for(int i = l-1; i >= 0; i--){
        // 1
        if(i%2 ==0 ){
            if(digitos[i] >= reduzir){
                idx = l-i;
                ans = digitos[i] - reduzir;
                break;
            }
        }
        else{
            if(digitos[i] *b >= alvo){
                idx = l-i;
                ans = (digitos[i]*b - alvo)/b;
                break;
            }
        }
    }
    cout << idx  << " "<< ans << "\n";

        
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
} 