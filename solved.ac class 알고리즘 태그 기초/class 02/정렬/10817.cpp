// 10817(세 수) 문제 : https://www.acmicpc.net/problem/10817
// 알고리즘 태그 목록
/*
구현
정렬
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1. 데이터를 담을 vector 선언
    vector<int> v(3);

    // 2. 세 수 입력
    for (int i = 0; i < 3; i++) {
        cin >> v[i];
    }

    // 3. v.begin(), v.end() 형식을 사용하여 정렬
    // 오름차순으로 정렬됩니다.
    sort(v.begin(), v.end());

    // 4. 두 번째로 큰 수(인덱스 1) 출력
    cout << v[1] << '\n';

    return 0;
}