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
using pt = std::pair<int, int>;
#define MAX_SIZE 200009
#define HASHMOD 47
#define HASH_SIZE 1000000
typedef int64_t ll;
typedef int32_t ii;
#define MOOD 998244353
#define pair pt
const ll Inf = 0x3f3f3f3f3f3f3f3f;
#define MAXP 21


struct dsuman{
    //n是1下表做起点
    std::vector<int>fa,siz;
    std::vector<std::vector<int>>sta;
    int top;int n;
    dsuman(int _n){
        init(_n);
    }
    void init(int n){
        sta=std::vector<std::vector<int>>(917891,std::vector<int>(2));
        fa=std::vector<int>(n);
        siz=std::vector<int>(n);
        for(int i=1;i<=n;i++){
            fa[i]=i;
            siz[i]=1;
        }
    }
    int find(int x){
        while(x!=fa[x])x=fa[x];
        return x;
    }
    void U(int x,int y){
        int a=find(x),b=find(y);
        if(siz[a]<siz[b]){
            int tmp=a;
            a=b;
            b=tmp;
        }
        if(a!=b){
            fa[b]=a;
            siz[a]+=siz[b];
            sta[++top][0]=a;
            sta[top][1]=b;
        }
    }
    void re(){
        int x=sta[top][0];
        int y=sta[top--][1];
        fa[y]=y;
        siz[x]-=siz[y];
    }
};





int main(){
    return 0;
}
