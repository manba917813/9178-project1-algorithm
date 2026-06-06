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
#define MAX_SIZE 2000009
#define HASHMOD 47
#define HASH_SIZE 1000000
typedef long long ll;
typedef int ii;
#define MOOD 998244353
#define pair pt
// const ll Inf = 0x3f3f3f3f3f3f3f3f;
#define int ll
//。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。//
//     。         .          .         .          .
//    。。       . .        . .       . .        .
//   。  。     。  .      .   .     .   .      .
//  。    。   。    .    .     .   .     .    .
// 。      。 。      .  . . . . . .       .  .
//。        。         .          .         .
//。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。//
#define MAXN 9100091
// #define MOD 998244353
// int cnt=1;

int head[MAXN];
int to[MAXN];
int cnt=1;
int next[MAXN];
void addedge(int u,int v){
    next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}
int siz[MAXN];
int sum[MAXN];
void dfs1(int u,int f){
    siz[u]=1;
    for(int e=head[u];e>0;e=next[e]){
        int v=to[e];
        if(v!=f){
            dfs1(v,u);
            siz[u]+=siz[v];
            sum[u]+=sum[v];
        }
    }
    sum[u]+=siz[u];
}
int N;
int dp[MAXN];
void dfs2(int u,int f){
    int cur=sum[u]-siz[u]+N;
    int cur1=dp[f]-siz[u]-sum[u];
    dp[u]=cur+cur1;
    for(int e=head[u];e>0;e=next[e]){
        int v=to[e];
        if(v!=f){
            dfs2(v,u);
        }
    }
}

void sovle() {
    int n;std::cin>>n;N=n;
    for(int i=0;i<n-1;i++){
        int u,v;std::cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,1);
    dp[1]=sum[1];
    for(int e=head[1];e>0;e=next[e]){
        int v=to[e];
        dfs2(v,1);
    }
    int max=INT_MIN;
    for(int i=1;i<=n;i++)max=std::max(max,dp[i]);
    std::cout<<max<<"\n";
    // std::cout<<"看我代码的是gay，被我抓到了小宝贝";
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // int T;std::cin>>T;while(T--)sovle();
    sovle();
    return 0;
}
