#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct State{
    int beg;
    int end;
    int happy;
};

int main (){
    cin.tie(0), ios_base::sync_with_stdio(false);
    int A,T;
    int total = 0;
    cin >> A >> T;
    vector<State> v;

    for (int i = 0; i < A; i++){
        int h,d,t;
        cin >> h >> d >> t;
        total +=t;
        for (int j =0; j < t; j++){
            int tj;
            cin >> tj;
            State s;
            s.beg = tj;
            s.end = tj+ d;
            s.happy = h;
            v.push_back(s);
        }
    }
    auto f = [](State a, State b){
        if(a.end != b.end) return a.end < b.end;
        return a.beg < b.beg;
    };
    sort(v.begin(),v.end(),f);

    vector<int> dp(total);
    dp[0] = v[0].happy;

    vector<int> vfim(total);
    for (int i = 0; i < total; i++){
        vfim[i] = v[i].end;
    }

    for (int i = 1; i < total; i++){
        int Bla= v[i].happy;
        int k = (upper_bound(vfim.begin(),vfim.end(),v[i].beg) - vfim.begin())-1;
        if (k >= 0) {
            Bla += dp[k];
        }
        dp[i] = max(dp[i-1],Bla);
    }

    cout << dp[total-1];
}

   