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

struct prime{
    std::vector<int>isprime;
    std::vector<int>Prime;
    int n;
    prime(const int x){init(x);}
    void init(int x){
        isprime=std::vector<int>(x+91,1);
        n=x;
        isprime[1]=0;
        for(int i=2;i<=n;i++){
            if(isprime[i]){
                Prime.push_back(i);
            }
            int N=Prime.size();
            for(int j=0;j<N;j++){
                if(i*Prime[j]<=n)isprime[i*Prime[j]]=0;
                if(i%Prime[j]==0){
                    break;
                }
            }
        }
    }
    int q(int x){return isprime[x]==0?0:x;}
};



