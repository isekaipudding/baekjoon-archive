// 해당 알고리즘이 필요한 백준 문제가 없으므로 직접 소스 코드를 만듭니다.
#include <bits/stdc++.h>

using namespace std;

// 좌표 구조체
struct Node {
    int x, y;
    int g, h, f;
    Node* parent;

    Node(int x, int y, Node* parent = nullptr) : x(x), y(y), parent(parent), g(0), h(0), f(0) {}

    // 우선순위 큐를 위한 비교 연산자 (f값이 작을수록 우선순위 높음)
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

// 맨해튼 거리 계산 (휴리스틱 h)
int calculateH(int x, int y, int tx, int ty) {
    return abs(x - tx) + abs(y - ty);
}

// 경로 출력 함수
void printPath(Node* current) {
    if (current == nullptr) return;
    printPath(current->parent);
    cout << "(" << current->x << ", " << current->y << ") -> ";
}

void aStar(int startX, int startY, int targetX, int targetY, vector<vector<int>>& map) {
    int n = map.size();
    int m = map[0].size();

    // 상하좌우 이동
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    priority_queue<Node, vector<Node>, greater<Node>> openList;
    vector<vector<bool>> closedList(n, vector<bool>(m, false));

    Node* startNode = new Node(startX, startY);
    startNode->h = calculateH(startX, startY, targetX, targetY);
    startNode->f = startNode->g + startNode->h;
    
    openList.push(*startNode);

    while (!openList.empty()) {
        Node* current = new Node(openList.top());
        openList.pop();

        if (current->x == targetX && current->y == targetY) {
            cout << "Path Found: ";
            printPath(current);
            cout << "End" << endl;
            return;
        }

        closedList[current->x][current->y] = true;

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            // 맵 범위 내이고, 벽(1)이 아니며, 방문하지 않은 곳
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && map[nx][ny] == 0 && !closedList[nx][ny]) {
                Node* nextNode = new Node(nx, ny, current);
                nextNode->g = current->g + 1;
                nextNode->h = calculateH(nx, ny, targetX, targetY);
                nextNode->f = nextNode->g + nextNode->h;

                openList.push(*nextNode);
            }
        }
    }
    cout << "Path not found." << endl;
}

int main() {
    // 0 : 갈 수 있는 길, 1 : 벽
    vector<vector<int>> map = {
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0}
    };

    aStar(0, 0, 4, 4, map);

    return 0;
}