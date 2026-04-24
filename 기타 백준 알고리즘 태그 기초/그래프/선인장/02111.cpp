// 2111(선인장) 문제 : https://www.acmicpc.net/problem/2111
// 알고리즘 태그 목록
/*
그래프 이론
임의 정밀도 / 큰 수 연산
이중 연결 요소
선인장
*/
#include <bits/stdc++.h>

using namespace std;

struct BigInt {
    vector<int> digits;
    BigInt(long long n = 0) {
        if (n == 0) digits.push_back(0);
        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
    }
    void multiply(int n) {
        if (n == 0) { digits = {0}; return; }
        int carry = 0;
        for (int i = 0; i < (int)digits.size(); i++) {
            long long value = (long long)digits[i] * n + carry;
            digits[i] = value % 10;
            carry = value / 10;
        }
        while (carry) {
            digits.push_back(carry % 10);
            carry /= 10;
        }
    }
    void print() {
        if (digits.empty()) { cout << 0 << "\n"; return; }
        for (int i = (int)digits.size() - 1; i >= 0; i--) cout << digits[i];
        cout << "\n";
    }
};

int n, m;
vector<int> graph[20001];
int discovery_time[20001], parent[20001], depth[20001];
int edge_use_count[20001];
int timer;
bool is_cactus = true;
vector<int> cycle_lengths;

void find_cycles(int current, int p, int d) {
    discovery_time[current] = ++timer;
    parent[current] = p;
    depth[current] = d;

    for (int next : graph[current]) {
        if (next == p) continue;
        if (discovery_time[next]) {
            if (discovery_time[next] < discovery_time[current]) {
                int length = 1;
                for (int temp = current; temp != next; temp = parent[temp]) {
                    length++;
                    edge_use_count[temp]++;
                    if (edge_use_count[temp] > 1) is_cactus = false;
                }
                cycle_lengths.push_back(length);
            }
        } else {
            find_cycles(next, current, d + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int k, u, v;
        cin >> k;
        if (k > 0) cin >> u;
        for (int j = 1; j < k; j++) {
            cin >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
            u = v;
        }
    }

    find_cycles(1, 0, 0);

    for (int i = 1; i <= n; i++) {
        if (!discovery_time[i]) {
            cout << 0 << "\n";
            return 0;
        }
    }

    if (!is_cactus) {
        cout << 0 << "\n";
    } else {
        BigInt result(1);
        for (int len : cycle_lengths) {
            result.multiply(len + 1);
        }
        result.print();
    }

    return 0;
}