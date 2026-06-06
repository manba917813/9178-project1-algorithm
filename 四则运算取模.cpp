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
#define MOD 998244353
class inv {
public:
	int mul(int a, int b) {
		return 1ll * (a % MOD) * (b % MOD) % MOD;
	}
	int powll(int x, int n) {
		int ans = 1;
		while (n > 0) {
			if ((n & 1) == 1)ans = mul(ans, x);
			x = mul(x, x);
			n >>= 1;	
		}
		return ans;
	}
	int d(int p, int q) {
		return mul(p, powll(q, MOD - 2));
	}
	int plus(int a, int b) {
		a = (a % MOD + MOD) % MOD;
		b = (b % MOD + MOD) % MOD;
		return (a + b) % MOD;
	}

};