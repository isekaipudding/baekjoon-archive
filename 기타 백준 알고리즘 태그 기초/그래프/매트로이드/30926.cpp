// 30926(파티) 문제 : https://www.acmicpc.net/problem/30926
// 알고리즘 태그 목록
/*
구현
자료 구조
그래프 이론
그리디 알고리즘
세그먼트 트리
최대 유량
이분 매칭
이분 그래프
최대 유량 최소 컷 정리
홀의 결혼 정리
매트로이드
*/
#include <bits/stdc++.h>

using namespace std;

struct State {
    int small_count = 0;
    int big_count = 0;
    int mincut_f = 0;
    vector<int> per_personality_capacity;

    State(int n) {
        per_personality_capacity.assign(n, 0);
    }
};

void process_small(State& state, int personality) {
    if (state.per_personality_capacity[personality] < state.big_count) {
        state.per_personality_capacity[personality] = state.big_count;
    }
    state.per_personality_capacity[personality]++;
    state.small_count++;
}

bool process_big(State& state, int personality) {
    if (state.per_personality_capacity[personality] < state.big_count) {
        state.per_personality_capacity[personality] = state.big_count;
    }
    state.per_personality_capacity[personality]++;
    state.big_count++;
    state.mincut_f++;

    int threshold = state.small_count + state.big_count - state.per_personality_capacity[personality];
    
    if (state.mincut_f > threshold) {
        state.mincut_f = threshold;
        return false;
    }
    return true;
}

struct Item {
    int value;
    int tag;
    
    bool operator<(const Item& other) const {
        if (value != other.value) return value < other.value;
        return tag < other.tag;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int num_girls;
    long long limit_k;
    if (!(cin >> num_girls >> limit_k)) return 0;

    vector<Item> items;
    items.reserve(num_girls);

    for (int i = 0; i < num_girls; ++i) {
        int a, b;
        cin >> a >> b;
        int personality = a - 1;
        int happiness = b;

        if (happiness * 2 <= limit_k) {
            items.push_back({happiness, personality});
        } else {
            items.push_back({(int)(limit_k - happiness), personality + num_girls});
        }
    }

    sort(items.begin(), items.end());

    int write_index = 0;
    State state(num_girls);

    for (int i = 0; i < (int)items.size(); ++i) {
        int value = items[i].value;
        int tag = items[i].tag;

        if (tag < num_girls) {
            process_small(state, tag);
            items[write_index++] = items[i];
        } else {
            if (process_big(state, tag - num_girls)) {
                items[write_index++] = items[i];
            }
        }
    }
    items.resize(write_index);

    State final_state(num_girls);
    for (const auto& item : items) {
        if (item.tag < num_girls) {
            process_small(final_state, item.tag);
        } else {
            process_big(final_state, item.tag - num_girls);
        }
    }

    int majority_personality = -1;
    for (int c = 0; c < num_girls; ++c) {
        int remain_c = final_state.per_personality_capacity[c] - final_state.big_count;
        if (remain_c * 2 > (final_state.small_count - final_state.big_count)) {
            majority_personality = c;
            break;
        }
    }

    int need_to_remove = 0;
    if (majority_personality == -1) {
        need_to_remove = (final_state.small_count + final_state.big_count) & 1;
    } else {
        need_to_remove = (final_state.per_personality_capacity[majority_personality] - final_state.big_count) * 2 
                         - (final_state.small_count - final_state.big_count);
    }

    vector<long long> removable_values;
    State scan_state(num_girls);

    for (auto it = items.rbegin(); it != items.rend(); ++it) {
        int value = it->value;
        int tag = it->tag;

        if (tag < num_girls) {
            if (majority_personality == -1 || majority_personality == tag) {
                if (!process_big(scan_state, tag)) {
                    removable_values.push_back(value);
                }
            }
        } else {
            process_small(scan_state, tag - num_girls);
        }
    }

    long long remove_sum = 0;
    int limit_idx = min((size_t)need_to_remove, removable_values.size());
    
    for(int i = 0; i < limit_idx; ++i) {
        remove_sum += removable_values[removable_values.size() - 1 - i];
    }

    long long result_sum = 0;
    for (const auto& item : items) {
        if (item.tag < num_girls) {
            result_sum += item.value;
        } else {
            result_sum += (limit_k - item.value);
        }
    }
    result_sum -= remove_sum;

    cout << result_sum << "\n";

    return 0;
}