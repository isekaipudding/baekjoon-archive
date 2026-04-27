// 2295(세 수의 합) 문제 : https://www.acmicpc.net/problem/2295
// 알고리즘 태그 목록
/*
자료 구조
이분 탐색
집합과 맵
해시를 사용한 집합과 맵
중간에서 만나기
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 1. 입출력 최적화
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 이분 탐색과 순차 탐색을 위해 정렬
    sort(a.begin(), a.end());

    // 2. 두 수의 합(a + b)을 모두 구해서 저장 (O(N^2))
    vector<int> two_sum;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            two_sum.push_back(a[i] + a[j]);
        }
    }
    sort(two_sum.begin(), two_sum.end());

    // 3. d - c가 two_sum에 있는지 확인 (O(N^2 * log(N^2)))
    // 가장 큰 d를 찾아야 하므로 역순으로 탐색
    for (int i = n - 1; i >= 0; --i) { // d 후보
        for (int j = 0; j < i; ++j) {  // c 후보
            int diff = a[i] - a[j];
            
            // binary_search를 이용해 diff가 two_sum에 있는지 확인
            if (binary_search(two_sum.begin(), two_sum.end(), diff)) {
                cout << a[i] << "\n";
                return 0; // 가장 큰 d를 찾으면 즉시 종료
            }
        }
    }

    return 0;
}