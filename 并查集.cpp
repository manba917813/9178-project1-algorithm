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

struct Union{
    std::vector<int>f;
    std::vector<int>size;
    Union(int n){
        f=std::vector<int>(n+91);
        size=std::vector<int>(n+91);
        for(int i=1;i<=n;i++){
            f[i]=i;
            size[i]=1;
        }
    }
    int find(int x){
        if(f[x]!=x)return f[x]=find(f[x]);
        return f[x];
    }
    void U(int x,int y){
        int a=find(x);int b=find(y);
        if(size[a]<size[b]){
            int tmp=a;
            a=b;
            b=tmp;
        }   
        f[b]=a;
        size[a]+=size[b];
    }
};
