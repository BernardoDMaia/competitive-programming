#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)

const int MAXN = 1e5+5;

int phi_sieve[MAXN];
vector<int>pr;
bool is_not_p[MAXN];

void linear_phi(){
    phi_sieve[1] = 1;
    FOR(i,2,MAXN){
        if(!is_not_p[i]){
            pr.push_back(i);
            phi_sieve[i] = i - 1;
        }
        for(int p : pr){
            if(i * p >= MAXN) break;
            is_not_p[i*p] = true;
            if(i % p == 0){
                phi_sieve[i*p] = phi_sieve[i] * p;
                break;
            }
            else{
                phi_sieve[i*p] = phi_sieve[i] * (p-1);
            }
        }
    }
}

int prefix_sum[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    linear_phi();
    prefix_sum[1] = 0;
    FOR(i,2,MAXN){
        prefix_sum[i] = prefix_sum[i-1] + (i-phi_sieve[i]);
    }

    int t; cin >> t;
    int a = t;
    while(t--){
        int n; cin >> n;
        cout << "Case " << a-t << ": ";
        cout << prefix_sum[n] << "\n";
    }

    return 0;
}