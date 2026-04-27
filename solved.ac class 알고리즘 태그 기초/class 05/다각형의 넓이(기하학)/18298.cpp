// 18298(Icebergs) 문제 : https://www.acmicpc.net/problem/18298
// 알고리즘 태그 목록
/*
기하학
다각형의 넓이
*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using ll = long long;

// 다각형의 넓이(신발끈 공식) 사용하는 함수
ll get_double_area() {
    int p;
    cin >> p;
    vector<pair<ll, ll>> points(p);
    for (int i = 0; i < p; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    ll sum = 0;
    for (int i = 0; i < p; ++i) {
        int next = (i + 1) % p;
        sum += (points[i].first * points[next].second);
        sum -= (points[next].first * points[i].second);
    }

    return abs(sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    ll total_area = 0;
    for (int i = 0; i < n; ++i) {
        total_area += get_double_area();
    }

    // 최종 넓이 = total_area / 2
    // 문제에서 정수 부분을 요구하므로 2로 나눈 몫을 바로 출력
    cout << total_area / 2 << "\n";

    return 0;
}