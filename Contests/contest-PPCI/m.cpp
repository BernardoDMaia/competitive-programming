#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n,b,v; cin >> n >> b >> v;
    if((b-v)%n == 0) cout << (b-v)/n << endl;
    else cout << -1 << endl;
}