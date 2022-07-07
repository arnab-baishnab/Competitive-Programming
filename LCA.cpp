#include<bits/stdc++.h>
using namespace std;
#define   MP             make_pair
#define   PB             push_back
#define   nn             '\n'
#define   endl           '\n'
#define   IOS            ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define   UNIQUE(vec)    vec.resize(distance(vec.begin(),unique(vec.begin(),vec.end()))) ;
#define   all(vec)       vec.begin(),vec.end()
#define   int            long long
#define   pii            pair<int,int>

typedef long long LL ;

const int MOD=1e9+7,Base=998244353 ;
const int N=1e6+7 ;
const int INF=1LL*1000*1000*1000*1000*1000*1000+7LL, INF2=(1LL<<62) ;
const double pie=acos(-1.0) ;
const double EPS=1e-9 ;

int n , test , anc[N][20] , d[N] ;

vector<int>adj[N] ;

/// lca used to solve https://codeforces.com/problemset/problem/1583/E

void dfs(int nd,int pa=-1,int c=0)
{
    d[nd]=c ;

    if(pa!=-1)
    {
        anc[nd][0]=pa ;
        for(int j=1,md; j<20; ++j)
            md=anc[nd][j-1], anc[nd][j]=anc[md][j-1] ;
    }
    for(int j=0,ch; j<adj[nd].size(); ++j)
    {
        ch=adj[nd][j] ;
        if(ch==pa)
            continue ;
        dfs(ch,nd,c+1) ;
    }
}

int lca(int u,int v)
{
    if(d[u]<d[v])
        swap(u,v) ;
    for(int j=19;j>=0 and d[u]>d[v] ;--j)  /// u niche ...
    {
        if(anc[u][j]==0)continue ;
        if(d[anc[u][j]]>=d[v])
            u=anc[u][j] ;
    }
    for(int j=19;j>=0 and u!=v; --j)
    {
        if(anc[u][j]!=anc[v][j])
            u=anc[u][j], v=anc[v][j] ;
        u=anc[u][0], v=anc[v][0] ;
    }
    return u ;
}

int32_t main()
{
    IOS

    cin>>n>>m ;

    dfs(1,-1,0) ;

    lca(u,v) ;

    return 0 ;
}
