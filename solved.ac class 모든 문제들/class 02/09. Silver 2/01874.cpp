// 1874(스택 수열) 문제 : https://www.acmicpc.net/problem/1874
// 알고리즘 태그 목록
/*
자료 구조
스택
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> stack;
    vector<char> result;
    
    result.reserve(2 * n); 
    
    int current = 1;
    bool possible = true;

    for (int i = 0; i < n; i++) {
        int target;
        cin >> target;

        while (current <= target) {
            stack.push_back(current++);
            result.push_back('+');
        }

        if (!stack.empty() && stack.back() == target) {
            stack.pop_back();
            result.push_back('-');
        } else {

            possible = false;
            break; 
        }
    }

    if (possible) {
        for (char c : result) {
            cout << c << "\n";
        }
    } else {
        cout << "NO\n";
    }

    return 0;
}