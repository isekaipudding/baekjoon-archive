// 10814(나이순 정렬) 문제 : https://www.acmicpc.net/problem/10814
// 알고리즘 태그 목록
/*
정렬
집합과 맵
*/
#include <bits/stdc++.h>

using namespace std;

struct Member {
    int age;
    string name;
};

bool compare(const Member& a, const Member& b) {
    return a.age < b.age;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Member> members(n);

    for(int i = 0; i < n; i++) cin >> members[i].age >> members[i].name;

    stable_sort(members.begin(), members.end(), compare);

    for(int i = 0; i < n; i++)
        cout << members[i].age << " " << members[i].name << "\n";

    return 0;
}