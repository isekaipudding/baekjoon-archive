// 1840(스도쿠) 문제 : https://www.acmicpc.net/problem/1840
// 알고리즘 태그 목록
/*
백트래킹
춤추는 링크
크누스 x
*/
#include <bits/stdc++.h>

using namespace std;

const int SIZE = 9;
const int SQR_SIZE = 81;
const int COLS = 324; // 4가지 조건 * 81
const int ROWS = 729; // 9행 * 9열 * 9숫자

struct DancingLinks {
    struct Node {
        int id;
        int size;
        Node *head, *up, *down, *left, *right;
    };

    Node root;
    vector<Node> col_nodes;
    vector<vector<Node>> row_nodes;
    bool found;

    DancingLinks() {
        col_nodes.resize(COLS);
        row_nodes.reserve(ROWS);
        init_matrix();
    }

    void init_matrix() {
        root.right = &col_nodes[0];
        root.left = &col_nodes[COLS - 1];
        for (int i = 0; i < COLS; i++) {
            col_nodes[i].id = i;
            col_nodes[i].size = 0;
            col_nodes[i].head = &col_nodes[i];
            col_nodes[i].up = col_nodes[i].down = &col_nodes[i];

            col_nodes[i].left = (i == 0) ? &root : &col_nodes[i - 1];
            col_nodes[i].right = (i == COLS - 1) ? &root : &col_nodes[i + 1];
        }

        for (int i = 0; i < ROWS; i++) {
            int y = i / SQR_SIZE;
            int x = (i / SIZE) % SIZE;
            int v = i % SIZE;

            int c_ids[4] = {
                y * SIZE + x,
                (y / 3 * 3 + x / 3) * SIZE + v + SQR_SIZE,
                y * SIZE + v + SQR_SIZE * 2,
                x * SIZE + v + SQR_SIZE * 3
            };
            add_row(i, c_ids);
        }
    }

    void add_row(int row_id, int c_ids[4]) {
        row_nodes.emplace_back();
        vector<Node>& nodes = row_nodes.back();
        
        nodes.resize(4);
        
        for (int i = 0; i < 4; i++) {
            int c_id = c_ids[i];
            Node* col = &col_nodes[c_id];
            Node* node = &nodes[i];
            
            if (col->down == col) col->down = node;
            col->size++;
            
            node->id = row_id;
            col->up->down = node;
            node->up = col->up;
            col->up = node;
            node->head = node->down = col;
        }

        int l_index[] = {3, 0, 1, 2};
        int r_index[] = {1, 2, 3, 0};
        for (int i = 0; i < 4; i++) {
            nodes[i].left = &nodes[l_index[i]];
            nodes[i].right = &nodes[r_index[i]];
        }
    }

    void cover(Node* col) {
        col->left->right = col->right;
        col->right->left = col->left;
        
        for (Node* row = col->down; row != col; row = row->down) {
            for (Node* node = row->right; node != row; node = node->right) {
                node->up->down = node->down;
                node->down->up = node->up;
                node->head->size--;
            }
        }
    }

    void uncover(Node* col) {
        for (Node* row = col->up; row != col; row = row->up) {
            for (Node* node = row->left; node != row; node = node->left) {
                node->head->size++;
                node->up->down = node;
                node->down->up = node;
            }
        }
        col->left->right = col;
        col->right->left = col;
    }

    Node* get_min_column() {
        int min_size = 1e9;
        Node* min_col = nullptr;
        for (Node* col = root.right; col != &root; col = col->right) {
            if (min_size > col->size) {
                min_size = col->size;
                min_col = col;
            }
        }
        return min_col;
    }

    bool is_active(int id) {
        for (Node* col = root.right; col != &root; col = col->right) {
            if (col->id == id) return true;
        }
        return false;
    }

    void search() {
        if (root.right == &root) {
            found = true;
            return;
        }

        Node* min_col = get_min_column();
        if (!min_col) return;

        cover(min_col);
        for (Node* n1 = min_col->down; !found && n1 != min_col; n1 = n1->down) {
            for (Node* n2 = n1->right; n2 != n1; n2 = n2->right) cover(n2->head);
            
            search();
            
            for (Node* n2 = n1->left; n2 != n1; n2 = n2->left) uncover(n2->head);
        }
        uncover(min_col);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    DancingLinks dlx;

    for (int i = 1; i <= 81; i++) {
        int y, x, v;
        cin >> y >> x >> v;
        y--; x--; v--;
        
        int row_id = y * SQR_SIZE + x * SIZE + v;

        for (auto& node : dlx.row_nodes[row_id]) {
            DancingLinks::Node* col = node.head;
            
            if (!dlx.is_active(col->id)) {
                cout << i << "\n";
                return 0;
            }
            dlx.cover(col);
        }

        dlx.found = false;
        dlx.search();

        if (!dlx.found) {
            cout << i << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";

    return 0;
}