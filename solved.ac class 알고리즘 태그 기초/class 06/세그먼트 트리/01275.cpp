// 1275(커피숍2) 문제 : https://www.acmicpc.net/problem/1275
// 알고리즘 태그 목록
/*
자료 구조
세그먼트 트리
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

// 전역 변수로 데이터 배열과 트리 벡터 선언
vector<ll> L;
vector<ll> tree;

// 1. 트리 초기화 함수
ll init(int node, int start, int end) {
    if (start == end) {
        return tree[node] = L[start];
    }
    int mid = (start + end) / 2;
    // 왼쪽 자식과 오른쪽 자식의 합을 현재 노드에 저장
    return tree[node] = init(node * 2, start, mid) + init(node * 2 + 1, mid + 1, end);
}

// 2. 구간 합 쿼리 함수
ll query(int node, int start, int end, int left, int right) {
    // 범위를 완전히 벗어난 경우 0 반환
    if (left > end || right < start) return 0;
    
    // 범위에 완전히 포함되는 경우 현재 노드의 값 반환
    if (left <= start && end <= right) return tree[node];
    
    // 걸쳐 있는 경우 자식 노드들로 분할해서 탐색
    int mid = (start + end) / 2;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

// 3. 단일 노드 업데이트 함수
void update(int node, int start, int end, int index, ll diff) {
    // 업데이트할 인덱스가 범위를 벗어나면 종료
    if (index < start || index > end) return;
    
    // 범위 안에 있다면 현재 노드 값에 차이(diff)만큼 더함
    tree[node] += diff;
    
    // 리프 노드가 아니라면 자식 노드들도 업데이트
    if (start != end) {
        int mid = (start + end) / 2;
        update(node * 2, start, mid, index, diff);
        update(node * 2 + 1, mid + 1, end, index, diff);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    // 1-based index를 위해 N + 1 사이즈 할당
    L.resize(N + 1);
    // 세그먼트 트리의 크기는 대략 N의 4배로 할당하면 안전함
    tree.resize(N * 4);

    for (int i = 1; i <= N; i++) {
        cin >> L[i];
    }

    // 트리 생성 (1번 노드부터 시작, 범위는 1 ~ N)
    init(1, 1, N);

    for (int i = 0; i < Q; i++) {
        int x, y, a;
        ll b;
        cin >> x >> y >> a >> b;

        // [함정 1] x가 y보다 클 경우 스왑
        if (x > y) swap(x, y);

        // x부터 y까지의 구간 합 출력
        cout << query(1, 1, N, x, y) << "\n";

        // [함정 2] a번째 값을 b로 변경하기 위한 차이(diff) 계산
        ll diff = b - L[a];
        L[a] = b; // 원본 배열 업데이트

        // 세그먼트 트리에 변경된 차이 적용
        update(1, 1, N, a, diff);
    }

    return 0;
}