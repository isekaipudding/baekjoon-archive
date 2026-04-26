// 18440(LCS 7) 문제 : https://www.acmicpc.net/problem/18440
// 알고리즘 태그 목록
/*
다이나믹 프로그래밍
문자열
분할 정복
비트 집합
최장 공통 부분 수열 문제
비트 집합을 이용한 최장 공통 부분 수열 최적화
히르쉬버그
*/
#include <bits/stdc++.h>

using namespace std;

using U64 = unsigned long long;

static string A, B;

static vector<array<U64, 1>> _dummy;
static vector<vector<U64>> masks, masks_rev;
static vector<U64> S, Xbuf, Sh1, Sub, Mtmp;
static vector<int> Lrow, Rrow;

static inline int popcount_vector(const vector<U64>& v, int W){
    int result = 0;
    for (int i = 0; i < W; ++i) result += __builtin_popcountll(v[i]);
    return result;
}

static inline void shl1_or1(const vector<U64>& src, vector<U64>& distance, int W, int tail_bits){
    U64 carry = 0;
    for (int i = 0; i < W; ++i){
        U64 nc = src[i] >> 63;
        distance[i] = (src[i] << 1) | carry;
        carry = nc;
    }
    distance[0] |= 1ULL;
    if (tail_bits){
        U64 mask = (tail_bits == 64) ? ~0ULL : ((1ULL << tail_bits) - 1ULL);
        distance[W-1] &= mask;
    }
}

static inline void sub_vector(const vector<U64>& a, 
                              const vector<U64>& b,
                              vector<U64>& distance, int W)
{
    U64 borrow = 0;
    for (int i = 0; i < W; ++i) {
        U64 ai = a[i], bi = b[i];
        U64 t = ai - borrow;
        U64 b1 = (ai < borrow);
        U64 d = t - bi;
        U64 b2 = (t < bi);
        distance[i] = d;
        borrow = (b1 | b2);
    }
}

static inline void or_vector (const vector<U64>& a, const vector<U64>& b, vector<U64>& distance, int W){
    for (int i = 0; i < W; ++i) distance[i] = a[i] | b[i];
}
static inline void and_vector(const vector<U64>& a, const vector<U64>& b, vector<U64>& distance, int W){
    for (int i = 0; i < W; ++i) distance[i] = a[i] & b[i];
}
static inline void not_into(const vector<U64>& a, vector<U64>& distance, int W){
    for (int i = 0; i < W; ++i) distance[i] = ~a[i];
}

static inline void extract_mask_from(const vector<vector<U64>>& table,
                                     unsigned char c,
                                     int xl, int n,
                                     int Wfull, int Wsub, int tail_bits)
{
    const vector<U64>& full = table[c];
    int off = xl & 63;
    int ws = xl >> 6;
    for (int t = 0; t < Wsub; ++t) {
        U64 lo = (ws + t < Wfull) ? (full[ws + t] >> off) : 0ULL;
        U64 hi = 0ULL;
        if (off && ws + t + 1 < Wfull) hi = full[ws + t + 1] << (64 - off);
        Mtmp[t] = lo | hi;
    }
    if (tail_bits) {
        U64 mask = (tail_bits == 64) ? ~0ULL : ((1ULL << tail_bits) - 1ULL);
        Mtmp[Wsub - 1] &= mask;
    }
}

static void lcs_prefix_bitrow(int xl, int xr, int yl, int yr,
                              int Wfull, vector<int>& out)
{
    const int n = xr - xl + 1;
    const int m = yr - yl + 1;
    const int Wsub = (n + 63) >> 6;
    const int tail_bits = (n == 0) ? 0 : ((n - 1) % 64 + 1);

    S.assign(Wsub, 0ULL);
    out[0] = 0;

    for (int j = 1; j <= m; ++j) {
        unsigned char ch = (unsigned char)B[yl + j - 1];
        extract_mask_from(masks, ch, xl, n, Wfull, Wsub, tail_bits);
        or_vector(S, Mtmp, Xbuf, Wsub);
        shl1_or1(S, Sh1, Wsub, tail_bits);
        sub_vector(Xbuf, Sh1, Sub, Wsub);
        not_into(Sub, S, Wsub);
        and_vector(Xbuf, S, S, Wsub);
        out[j] = popcount_vector(S, Wsub);
    }
}

static void lcs_suffix_bitrow(int xl, int xr, int yl, int yr,
                              int Wfull, vector<int>& out)
{
    const int n = xr - xl + 1;
    const int m = yr - yl + 1;
    const int Wsub = (n + 63) >> 6;
    const int tail_bits = (n == 0) ? 0 : ((n - 1) % 64 + 1);
    const int NA = (int)A.size();
    const int rev_xl = (NA - 1 - xr);

    S.assign(Wsub, 0ULL);
    out[m] = 0;

    for (int t = 1; t <= m; ++t) {
        unsigned char ch = (unsigned char)B[yr - (t - 1)];
        extract_mask_from(masks_rev, ch, rev_xl, n, Wfull, Wsub, tail_bits);
        or_vector(S, Mtmp, Xbuf, Wsub);
        shl1_or1(S, Sh1, Wsub, tail_bits);
        sub_vector(Xbuf, Sh1, Sub, Wsub);
        not_into(Sub, S, Wsub);
        and_vector(Xbuf, S, S, Wsub);
        out[m - t] = popcount_vector(S, Wsub);
    }
}

static string hirschberg(int xl, int xr, int yl, int yr, int Wfull)
{
    if (xl > xr || yl > yr) return "";
    int n = xr - xl + 1;
    int m = yr - yl + 1;

    if (n == 1){
        char c = A[xl];
        for (int j = yl; j <= yr; ++j)
            if (B[j] == c) return string(1, c);
        return "";
    }

    int mid = (xl + xr) >> 1;

    lcs_prefix_bitrow(xl, mid, yl, yr, Wfull, Lrow);
    lcs_suffix_bitrow(mid + 1, xr, yl, yr, Wfull, Rrow);

    int k = 0, best = Lrow[0] + Rrow[0];
    for (int j = 1; j <= m; ++j){
        int v = Lrow[j] + Rrow[j];
        if (v > best){ best = v; k = j; }
    }

    string left  = hirschberg(xl, mid, yl, yl + k - 1, Wfull);
    string right = hirschberg(mid + 1, xr, yl + k, yr, Wfull);
    return left + right;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> A >> B;
    const int NA = (int)A.size();
    const int NB = (int)B.size();

    const int Wfull = (NA + 63) >> 6;
    masks.assign(256, vector<U64>(Wfull, 0ULL));
    masks_rev.assign(256, vector<U64>(Wfull, 0ULL));

    for (int i = 0; i < NA; ++i){
        unsigned char c = static_cast<unsigned char>(A[i]);
        masks[c][i >> 6] |= (1ULL << (i & 63));

        int ir = NA - 1 - i;
        masks_rev[c][ir >> 6] |= (1ULL << (ir & 63));
    }

    S.assign(Wfull, 0ULL);
    Xbuf.assign(Wfull, 0ULL);
    Sh1.assign(Wfull, 0ULL);
    Sub.assign(Wfull, 0ULL);
    Mtmp.assign(Wfull, 0ULL);

    Lrow.assign(NB + 1, 0);
    Rrow.assign(NB + 1, 0);

    string lcs = hirschberg(0, NA - 1, 0, NB - 1, Wfull);
    cout << lcs.size() << '\n' << lcs << '\n';
    return 0;
}