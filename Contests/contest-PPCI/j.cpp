#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<ll>days(n);

    for(int i = 0; i < n; i++){
        int d, m, y; cin >> d >> m >> y;
        ll t_days = d + ((m-1)*(ll)30) + ((y-1)*(ll)360);
        days[i] = t_days;
    }

    ll minor = 1e18, biggest = 0;
    for(int i = 0; i < n-1; i++){
        minor = min(minor, (days[i+1] - days[i]));
        biggest = max(biggest, (days[i+1] - days[i]));
    }

    cout << minor << " " << biggest << endl;
}