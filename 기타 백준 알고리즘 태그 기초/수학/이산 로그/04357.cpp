// 4357(이산 로그) 문제 : https://www.acmicpc.net/problem/4357
// 알고리즘 태그 목록
/*
수학
정수론
중간에서 만나기
페르마의 소정리
이산 로그
*/
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll power(ll base, ll exponent, ll modular) {
    ll result = 1;
    base %= modular;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % modular;
        base = (base * base) % modular;
        exponent /= 2;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll P, B, N;
    
    while (cin >> P >> B >> N) {
        B %= P;
        N %= P;

        ll m = ceil(sqrt(P));
        
        vector<pair<ll, int>> baby;
        baby.reserve(m);

        ll current = 1;
        for (int j = 0; j < m; ++j) {
            baby.push_back({current, j});
            current = (current * B) % P;
        }

        sort(baby.begin(), baby.end());

        ll invB = power(B, P - 2, P);
        ll invBm = power(invB, m, P);

        ll result = -1;
        current = N;
        
        for (ll i = 0; i <= m; ++i) {
            auto it = lower_bound(baby.begin(), baby.end(), make_pair(current, -1));
            
            if (it != baby.end() && it->first == current) {
                result = i * m + it->second;
                break;
            }
            
            current = (current * invBm) % P;
        }

        if (result == -1) {
            cout << "no solution\n";
        } else {
            cout << result << "\n";
        }
    }

    return 0;
}