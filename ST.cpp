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
struct ST {

	int n;
	int B;
	const type& (*cmp)(const type&, const type&);
	std::vector<int>Lg;
	std::vector<std::vector<type>>st;

	ST(const std::vector<type>& _vec, const type& (*_cmp)(const type&, const type&)) {
		init(_vec, _cmp);
	}

	void init(const std::vector<type>& _vec, const type& (*_cmp)(const type&, const type&)) {
		n = _vec.size();
		cmp = _cmp;
		Lg = std::vector<int>(n + 1);

		for (int i = 1; i <= n; ++i)Lg[i] = log2(i);
		B = Lg[n] + 1;
		st = std::vector<std::vector<type>>(n, std::vector<type>(B));
		for (int i = 0; i < n; ++i)st[i][0] = _vec[i];


		for (int k = 1; k < B; ++k) {
			for (int i = 0; i < n; ++i) {
				st[i][k] = cmp(st[i][k - 1], st[std::min(i + (1 << k - 1), n - 1)][k - 1]);
			}
		}
		
	}
	type query(int l, int r) {
		int k = Lg[r - l + 1];
		return cmp(st[l][k], st[r - (1 << k) + 1][k]);
	}
};