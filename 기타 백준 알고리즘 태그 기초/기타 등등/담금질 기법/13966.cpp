// 13966(Risky Lottery) 문제 : https://www.acmicpc.net/problem/13966
// 알고리즘 태그 목록
/*
다이나믹 프로그래밍
비트마스킹
비트필드를 이용한 다이나믹 프로그래밍
런타임 전의 전처리
담금질 기법
*/
#include <bits/stdc++.h>

using namespace std;

int N, M;
double p[10];
double W[10];
long long fact[10];
double p_pow[10][10];

struct State {
    double multinomial_coeff;
    vector<pair<int, int>> non_zero_counts;
    vector<int> winning_k;
};

vector<State> all_states;

void generate_states(int index, int remaining, vector<int>& current) {
    if (index == M) {
        if (remaining == 0) {
            double coeff = fact[N - 1];
            vector<pair<int, int>> nz;
            for (int i = 0; i < M; ++i) {
                coeff /= fact[current[i]];
                if (current[i] > 0) nz.push_back({i, current[i]});
            }
            
            vector<int> win_k;

            for (int k = 0; k < M; ++k) {
                if (current[k] == 0) {
                    bool lower_unique = false;
                    for (int j = 0; j < k; ++j) {
                        if (current[j] == 1) {
                            lower_unique = true;
                            break;
                        }
                    }
                    if (!lower_unique) win_k.push_back(k);
                }
            }
            if (!win_k.empty()) {
                all_states.push_back({coeff, nz, win_k});
            }
        }
        return;
    }
    for (int i = 0; i <= remaining; ++i) {
        current.push_back(i);
        generate_states(index + 1, remaining - i, current);
        current.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    fact[0] = 1;
    for (int i = 1; i <= 9; ++i) fact[i] = fact[i - 1] * i;

    vector<int> current;
    generate_states(0, N - 1, current);

    for (int i = 0; i < M; ++i) p[i] = 1.0 / M;

    for (int iter = 0; iter < 100000; ++iter) {
        for (int i = 0; i < M; ++i) {
            p_pow[i][0] = 1.0;
            for (int c = 1; c <= N; ++c) {
                p_pow[i][c] = p_pow[i][c - 1] * p[i];
            }
        }

        for (int i = 0; i < M; ++i) W[i] = 0;

        for (const auto& state : all_states) {
            double prob_product = state.multinomial_coeff;
            for (const auto& nz : state.non_zero_counts) {
                prob_product *= p_pow[nz.first][nz.second];
            }

            for (int k : state.winning_k) {
                W[k] += prob_product;
            }
        }

        double next_p[10];
        double sum_next = 0;
        for (int i = 0; i < M; ++i) {
            next_p[i] = p[i] * W[i];
            sum_next += next_p[i];
        }

        if (sum_next > 1e-18) {
            for (int i = 0; i < M; ++i) {
                double target_p = next_p[i] / sum_next;
                p[i] = p[i] * 0.95 + target_p * 0.05; 
            }
        } else {
            break;
        }
    }

    cout << fixed << setprecision(5);
    for (int i = 0; i < M; ++i) {
        cout << p[i] << "\n";
    }

    return 0;
}