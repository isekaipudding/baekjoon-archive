// 35453(Goodbye, ChAOS!) 문제 : https://www.acmicpc.net/problem/35453
// 알고리즘 태그 목록
/*
구현
문자열
많은 조건 분기
해싱
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t; // 테스트 케이스 수 입력

    while (t--) {
        int n;
        cin >> n; // 한 케이스당 대회의 개수 입력

        long long hash_key = 1;
        for (int i = 0; i < n; i++) {
            string contest_name;
            cin >> contest_name; // 대회 이름 입력
            hash_key *= contest_name.length(); // 문자열 길이의 곱 계산
        }

        // Perfect Hash Function에 따른 연도 판정
        // 지문에 명시된 각 연도별 고유 해시값(길이의 곱)을 기준으로 분기합니다.
        if (hash_key == 232) {
            cout << 2017 << '\n';
        } else if (hash_key == 88) {
            cout << 2018 << '\n';
        } else if (hash_key == 754) {
            cout << 2019 << '\n';
        } else if (hash_key == 29) {
            cout << 2020 << '\n';
        } else if (hash_key == 28) {
            cout << 2021 << '\n';
        } else if (hash_key == 1015) {
            cout << 2022 << '\n';
        } else if (hash_key == 1295) {
            cout << 2023 << '\n';
        } else if (hash_key == 1073) {
            cout << 2024 << '\n';
        } else if (hash_key == 348) {
            cout << 2025 << '\n';
        } else {
            // 어느 해와도 일치하지 않는 경우
            cout << "Goodbye, ChAOS!" << '\n';
        }
    }

    return 0;
}