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

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    map<string,int> aura;

    aura["picoton"] = 6900;
    aura["fcw"] = 9999;
    aura["ifuaslaeRL"] = 6767;
    aura["pagesh"] = 5049;
    aura["loadz"] = 3852;
    aura["junje"] = 5678;
    aura["MAML_8"] = 9998;
    aura["El_medonho"] = 8000;
    aura["bemagno"] = 2025;
    aura["Luwai"] = 7999;

    string s; cin >> s;
    cout << aura[s] << endl;
}