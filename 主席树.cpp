#define _CRT_SECURE_NO_WARNINGS
//#include <intrin.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<iostream>
#include<cmath>
#include<random>
#include<algorithm>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<numeric>
#include<climits>
#include<string>
#include<stack>
#include<array>
#include<limits>
#define __builtin_popcount _mm_popcnt_u32
#define MAX_SIZE 910009
#define HASHMOD 47
#define HASH_SIZE 1000000
using pt = std::pair<int, int>;
typedef int64_t ll;
typedef int32_t ii;
#define MOOD 998244353
#define pair pt
const ll Inf = 0x3f3f3f3f3f3f3f3f;
#define int ll

template<typename type = int>
struct HistorySegTree {
    // 主席树版本线段树，从 1 开始，build(1,n) 返回第 0 个版本的根
    std::vector<type> arr;
    std::vector<type> sum;
    std::vector<type> add;
    std::vector<type> max;
    std::vector<type> min;
    std::vector<type> change;
    std::vector<type> update;
    std::vector<type> mul;
    std::vector<int> left;
    std::vector<int> right;
    int N;
    int cnt;
    HistorySegTree(const std::vector<type>& _arr) {
        init(_arr);
    }
    void init(const std::vector<type>& _arr) {
        N = _arr.size();
        cnt = 0;
        arr = std::vector<type>(N);
        for (int i = 1; i < N; i++)arr[i] = _arr[i];
        int sz = std::max((int)10, N * 80);
        sum = std::vector<type>(sz);
        add = std::vector<type>(sz);
        max = std::vector<type>(sz);
        min = std::vector<type>(sz);
        change = std::vector<type>(sz);
        update = std::vector<type>(sz);
        mul = std::vector<type>(sz, 1);
        left = std::vector<int>(sz);
        right = std::vector<int>(sz);
    }
    void check() {
        if (cnt + 5 >= (int)sum.size()) {
            int sz = sum.size() * 2 + 10;
            sum.resize(sz);
            add.resize(sz);
            max.resize(sz);
            min.resize(sz);
            change.resize(sz);
            update.resize(sz);
            mul.resize(sz, 1);
            left.resize(sz);
            right.resize(sz);
        }
    }
    void up(int i) {
        max[i] = std::max(max[left[i]], max[right[i]]);
        min[i] = std::min(min[left[i]], min[right[i]]);
        sum[i] = sum[left[i]] + sum[right[i]];
    }
    int clone(int i) {
        check();
        int rt = ++cnt;
        left[rt] = left[i];
        right[rt] = right[i];
        sum[rt] = sum[i];
        add[rt] = add[i];
        max[rt] = max[i];
        min[rt] = min[i];
        change[rt] = change[i];
        update[rt] = update[i];
        mul[rt] = mul[i];
        return rt;
    }
    void TagLazy(int i, type a, type b, int n) {
        type x = max[i] * a + b;
        type y = min[i] * a + b;
        max[i] = std::max(x, y);
        min[i] = std::min(x, y);
        sum[i] = sum[i] * a + b * n;
        mul[i] = mul[i] * a;
        add[i] = add[i] * a + b;
        if (update[i])change[i] = change[i] * a + b;
        if (a == 0) {
            update[i] = 1;
            change[i] = b;
        }
    }
    void MulLazy(int i, type v, int n) {
        TagLazy(i, v, 0, n);
    }
    void AddLazy(int i, type v, int n) {
        TagLazy(i, 1, v, n);
    }
    void UpdateLazy(int i, type v, int n) {
        TagLazy(i, 0, v, n);
    }
    void down(int i, int ln, int rn) {
        if (mul[i] != 1 || add[i] != 0) {
            left[i] = clone(left[i]);
            right[i] = clone(right[i]);
            TagLazy(left[i], mul[i], add[i], ln);
            TagLazy(right[i], mul[i], add[i], rn);
            mul[i] = 1;
            add[i] = 0;
            update[i] = 0;
            change[i] = 0;
        }
    }
    int build(int l, int r) {
        check();
        int rt = ++cnt;
        add[rt] = 0;
        mul[rt] = 1;
        update[rt] = 0;
        change[rt] = 0;
        if (l == r) {
            sum[rt] = max[rt] = min[rt] = arr[l];
        } else {
            int mid = (l + r) >> 1;
            left[rt] = build(l, mid);
            right[rt] = build(mid + 1, r);
            up(rt);
        }
        return rt;
    }
    type GetSum(int i, int n, type a, type b) {
        return sum[i] * a + b * n;
    }
    type GetMax(int i, type a, type b) {
        type x = max[i] * a + b;
        type y = min[i] * a + b;
        return std::max(x, y);
    }
    type GetMin(int i, type a, type b) {
        type x = max[i] * a + b;
        type y = min[i] * a + b;
        return std::min(x, y);
    }
    int Mul(int jobl, int jobr, type jobv, int l, int r, int i) {
        int rt = clone(i);
        if (jobl <= l && jobr >= r) {
            MulLazy(rt, jobv, r - l + 1);
        } else {
            int mid = (l + r) >> 1;
            down(rt, mid - l + 1, r - mid);
            if (jobl <= mid) {
                left[rt] = Mul(jobl, jobr, jobv, l, mid, left[rt]);
            }
            if (jobr > mid) {
                right[rt] = Mul(jobl, jobr, jobv, mid + 1, r, right[rt]);
            }
            up(rt);
        }
        return rt;
    }
    int Add(int jobl, int jobr, type jobv, int l, int r, int i) {
        int rt = clone(i);
        if (jobl <= l && jobr >= r) {
            AddLazy(rt, jobv, r - l + 1);
        } else {
            int mid = (l + r) >> 1;
            down(rt, mid - l + 1, r - mid);
            if (jobl <= mid) {
                left[rt] = Add(jobl, jobr, jobv, l, mid, left[rt]);
            }
            if (jobr > mid) {
                right[rt] = Add(jobl, jobr, jobv, mid + 1, r, right[rt]);
            }
            up(rt);
        }
        return rt;
    }
    int Update(int jobl, int jobr, type jobv, int l, int r, int i) {
        int rt = clone(i);
        if (jobl <= l && jobr >= r) {
            UpdateLazy(rt, jobv, r - l + 1);
        } else {
            int mid = (l + r) >> 1;
            down(rt, mid - l + 1, r - mid);
            if (jobl <= mid) {
                left[rt] = Update(jobl, jobr, jobv, l, mid, left[rt]);
            }
            if (jobr > mid) {
                right[rt] = Update(jobl, jobr, jobv, mid + 1, r, right[rt]);
            }
            up(rt);
        }
        return rt;
    }
    int aSUM(int jobl, int jobr, type jobv, int l, int r, int i) {
        return Add(jobl, jobr, jobv, l, r, i);
    }
    type qSUM(int jobl, int jobr, int l, int r, int i, type nowmul = 1, type nowadd = 0) {
        if (jobl <= l && jobr >= r) {
            return GetSum(i, r - l + 1, nowmul, nowadd);
        }
        int mid = (l + r) >> 1;
        type nmul = nowmul * mul[i];
        type nadd = nowadd + nowmul * add[i];
        type ans = 0;
        if (jobl <= mid) {
            ans += qSUM(jobl, jobr, l, mid, left[i], nmul, nadd);
        }
        if (jobr > mid) {
            ans += qSUM(jobl, jobr, mid + 1, r, right[i], nmul, nadd);
        }
        return ans;
    }
    type qMAX(int jobl, int jobr, int l, int r, int i, type nowmul = 1, type nowadd = 0) {
        if (jobl <= l && jobr >= r) {
            return GetMax(i, nowmul, nowadd);
        }
        int mid = (l + r) >> 1;
        type nmul = nowmul * mul[i];
        type nadd = nowadd + nowmul * add[i];
        type ans = std::numeric_limits<type>::lowest();
        if (jobl <= mid) {
            ans = std::max(ans, qMAX(jobl, jobr, l, mid, left[i], nmul, nadd));
        }
        if (jobr > mid) {
            ans = std::max(ans, qMAX(jobl, jobr, mid + 1, r, right[i], nmul, nadd));
        }
        return ans;
    }
    type qMIN(int jobl, int jobr, int l, int r, int i, type nowmul = 1, type nowadd = 0) {
        if (jobl <= l && jobr >= r) {
            return GetMin(i, nowmul, nowadd);
        }
        int mid = (l + r) >> 1;
        type nmul = nowmul * mul[i];
        type nadd = nowadd + nowmul * add[i];
        type ans = std::numeric_limits<type>::max();
        if (jobl <= mid) {
            ans = std::min(ans, qMIN(jobl, jobr, l, mid, left[i], nmul, nadd));
        }
        if (jobr > mid) {
            ans = std::min(ans, qMIN(jobl, jobr, mid + 1, r, right[i], nmul, nadd));
        }
        return ans;
    }
};
