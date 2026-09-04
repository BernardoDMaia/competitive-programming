#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<b;i++)
#define all(x) x.begin(), x.end()
using pii = pair<int,int>;
#define pb push_back
#define sz(x) x.size()
#define deb(x) cerr << #x << "= " << x << "\n";
#define deb2(x,y) cerr << #x << "= " << x << ", "<< #y << "= " << y << "\n";
//ctrl+alt+a p/ accepted

void solve(){
    int n, c; cin >> n >> c;
    vi a(n);
    FOR(i,0,n) cin >> a[i];
    
    vi firstPick(n), bestCost(n);
    vector<pii> bestPick(n);
    FOR(i,0,n){
        firstPick[i] = i+1+a[i];
        bestPick[i] = {min(i+1, n-i)+a[i], i};
        bestCost[i] = min(i+1, n-i)+a[i];
    }

    sort(all(bestPick));
    vi prefBest(n+1, 0), idx(n); 
    FOR(i,1,n+1) prefBest[i] = prefBest[i-1] + bestPick[i-1].first;
    FOR(i,0,n) idx[bestPick[i].second] = i;

    auto canGet = [&](int tam, int i) -> bool{
        int cost = firstPick[i];
        if(idx[i] < tam){//está nos primeiros
            cost += prefBest[tam+1] - bestCost[i];
        }
        else cost += prefBest[tam];

        return cost <= c;
    };  

    //se eu escolher i, quantos eu consigo?
    int ans = 0;
    FOR(i,0,n){
        int maxTelep = 0;
        int l = 0, r = n-1; //qtd de telep
        while(l <= r){
            int mid = (l+r)/2;
            if(canGet(mid, i)){ //posso usar mid+1 teleportes
                maxTelep = mid+1;
                l = mid+1;
            }
            else r = mid-1;
        }
        ans = max(ans,maxTelep);
    }

    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--)
    solve();
    return 0;
}