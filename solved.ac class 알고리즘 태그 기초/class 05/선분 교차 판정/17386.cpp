// 17386(선분 교차 1) 문제 : https://www.acmicpc.net/problem/17386
// 알고리즘 태그 목록
/*
기하학
선분 교차 판정
*/
#include <iostream>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
};

// CCW 함수 : 세 점의 방향성을 판별
// 1(반시계), -1(시계), 0(일직선)
int ccw(Point p1, Point p2, Point p3) {
    ll result = (p1.x * p2.y + p2.x * p3.y + p3.x * p1.y) - 
                 (p1.y * p2.x + p2.y * p3.x + p3.y * p1.x);
    
    if (result > 0) return 1;
    if (result < 0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Point A, B, C, D;
    
    // 선분 1 입력
    cin >> A.x >> A.y >> B.x >> B.y;
    // 선분 2 입력
    cin >> C.x >> C.y >> D.x >> D.y;

    // 선분 AB를 기준으로 C, D의 방향 확인
    int abc = ccw(A, B, C);
    int abd = ccw(A, B, D);
    
    // 선분 CD를 기준으로 A, B의 방향 확인
    int cda = ccw(C, D, A);
    int cdb = ccw(C, D, B);

    // 두 조건이 모두 서로 다른 방향(곱이 음수)이어야 교차함
    if (abc * abd < 0 && cda * cdb < 0) {
        cout << 1 << "\n";
    } else {
        cout << 0 << "\n";
    }

    return 0;
}