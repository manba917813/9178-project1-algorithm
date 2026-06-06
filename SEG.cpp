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
struct SEG {
    // size 大小 从 1 开始  
    std::vector<type> arr;
    std::vector<type> sum;
    std::vector<type> add;
    std::vector<type> max;
    std::vector<type> min;
    std::vector<type> change;
    std::vector<type> update;
    std::vector<type> mul; 
    type N;
    SEG(const std::vector<type> _arr) {
        init(_arr);
    }
    void init(const std::vector<type> _arr) {
        N = _arr.size()+91;
        arr = _arr;
        sum = std::vector<type>(4 * N);
        add = std::vector<type>(4 * N);
        max = std::vector<type>(4 * N);
        min = std::vector<type>(4 * N);
        update = std::vector<type>(4 * N);
        change = std::vector<type>(4 * N);
        mul = std::vector<type>(4 * N, 1); 
    }
    void up(int i) {
        max[i] = std::max(max[i << 1], max[i << 1 | 1]);
        min[i] = std::min(min[i << 1], min[i << 1 | 1]);
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
    void MulLazy(int i, type v, int n) {
        sum[i] *= v;
        mul[i] *= v;
        add[i] *= v; 
        max[i] *= v;
        min[i] *= v;
    }
    void AddLazy(int i, type v, int n) {
        sum[i] += v * n;
        add[i] += v;
        max[i] += v;
        min[i] += v;
    }
    void UpdateLazy(int i, type v, int n) {
        sum[i] = v * n;
        add[i] = 0;
        mul[i] = 1;    
        update[i] = 1;
        change[i] = v;
        max[i] = v;
        min[i] = v;
    }
    void Down(int i, int ln, int rn) {
		if (update[i]) {
			UpdateLazy(i << 1, change[i], ln);
			UpdateLazy(i << 1 | 1, change[i], rn);
			update[i] = 0;
		}
		if (mul[i] != 1) {
			MulLazy(i << 1, mul[i], ln);
			MulLazy(i << 1 | 1, mul[i], rn);
			mul[i] = 1;
		}
		if (add[i]) {
			AddLazy(i << 1, add[i], ln);
			AddLazy(i << 1 | 1, add[i], rn);
			add[i] = 0;
		}
    }
    void build(int l, int r, int i) {
		if (l == r) {
			mul[i]=min[i]=max[i]=sum[i]=arr[l];
        } else {
			int mid = (l + r) >> 1;
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);
            up(i);
        }
		update[i] = 0;
		change[i] = 0;
		add[i] = 0;
		mul[i] = 1;
    }
    void Mul(int jobl, int jobr, type jobv, int l, int r, int i) {
        if (jobl <= l && jobr >= r) {
            MulLazy(i, jobv, r - l + 1);
        } else {
            int mid = (l + r) >> 1;
            Down(i, mid - l + 1, r - mid);
            if (jobl <= mid) {
                Mul(jobl, jobr, jobv, l, mid, i << 1);
            }
            if (jobr > mid) {
                Mul(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }
            up(i);
        }
    }
    void Add(int jobl, int jobr, type jobv, int l, int r, int i) {
        if (jobl <= l && jobr >= r) {
            AddLazy(i, jobv, r - l + 1);
        } else {
            int mid = (l + r) >> 1;
            Down(i, mid - l + 1, r - mid);
            if (jobl <= mid) {
                Add(jobl, jobr, jobv, l, mid, i << 1);
            }
            if (jobr > mid) {
                Add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }
            up(i);
        }
    }
    void Update(int jobl, int jobr, type jobv, int l, int r, int i) {
        if (jobl <= l && jobr >= r) {
            UpdateLazy(i, jobv, r - l + 1);
        } else {
            int mid = (l + r) >> 1;
            Down(i, mid - l + 1, r - mid);
            if (jobl <= mid) {
                Update(jobl, jobr, jobv, l, mid, i << 1);
            }
            if (jobr > mid) {
                Update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }
            up(i);
        }
    }
    type qMAX(int jobl, int jobr, int l, int r, int i) {
        if (jobl <= l && jobr >= r) {
            return max[i];
        }
        int mid = (l + r) >> 1;
        Down(i, mid - l + 1, r - mid);
        type ans = typeid(INT_MIN) == typeid(type) ? INT_MIN : LLONG_MIN;
        if (jobr <= mid) {
            ans = qMAX(jobl, jobr, l, mid, i << 1);
        } else if (jobl > mid) {
            ans = qMAX(jobl, jobr, mid + 1, r, i << 1 | 1);
        } else {
            ans = std::max(qMAX(jobl, jobr, l, mid, i << 1), qMAX(jobl, jobr, mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
    type qSUM(int jobl, int jobr, int l, int r, int i) {
        if (jobl <= l && jobr >= r) {
            return sum[i];
        }
        int mid = (l + r) >> 1;
        Down(i, mid - l + 1, r - mid);
        type ans = 0;
        if (jobl <= mid) {
            ans += qSUM(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            ans += qSUM(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
    type qMIN(int jobl, int jobr, int l, int r, int i) {
        if (jobl <= l && jobr >= r) {
            return min[i];
        }
        int mid = (l + r) >> 1;
        Down(i, mid - l + 1, r - mid);
        type ans = typeid(INT_MAX) == typeid(type) ? INT_MAX : LLONG_MAX;
        if (jobr <= mid) {
            ans = qMIN(jobl, jobr, l, mid, i << 1);
        } else if (jobl > mid) {
            ans = qMIN(jobl, jobr, mid + 1, r, i << 1 | 1);
        } else {
            ans = std::min(qMIN(jobl, jobr, l, mid, i << 1), qMIN(jobl, jobr, mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
};