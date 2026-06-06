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
#include<algorithm>//sort
#include<queue>//deque
#include<vector>
#include<set>//set,multiset
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

template<typename type = int>
struct BIT {
	//   ± 1  ʼ      ״    
	std::vector<type>arr;
	std::vector<type>tree;
	int n;
	BIT(const type _n) {
		init(_n);
	}
	void init(const type _n) {
		n = _n - 1;
		tree = std::vector<type>(_n);
	}
	int lowbit(int i) { return i & (-i); }
	void Add(int i, type v) {
		while (i <= n) {
			tree[i] += v;
			i += lowbit(i);
		}
	}
	type query(int i) {
		type ans = 0;
		while (i > 0) {
			ans += tree[i];
			i -= lowbit(i);
		}
		return ans;
	}
};