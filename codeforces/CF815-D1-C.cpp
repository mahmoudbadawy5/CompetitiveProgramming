/*
Solve it using DP where dp[i][j][1] means you are required to buy j items from the subtree of j and you can use a copon while dp[i][h][0] is the same but you can't use a copun. How to distribute j items between your siblings? You can use sibling DP trick.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=5e3+3;

long long dp[N][N][2];
long long c[N],d[N],sz[N];
vector<int> adj[N];
int n,b;

bool cmp(int x,int y)
{
	return sz[x]>sz[y];
}

void dfs(int x)
{
	sz[x]=1;
	for(int i=1;i<=n;i++)
		dp[x][i][0]=dp[x][i][1]=(1LL<<60);
	dp[x][1][0]=c[x];
	dp[x][1][1]=c[x]-d[x];
	dp[x][0][1]=(1LL<<60);
	for(int to:adj[x])
	{
		dfs(to);
	}
	sort(adj[x].begin(),adj[x].end(),cmp);
	for(int to:adj[x])
	{
		for(int i=sz[x];i>=0;i--)
		{
			for(int j=1;j<=sz[to];j++)
			{
				dp[x][i+j][0]=min(dp[x][i+j][0],dp[x][i][0]+dp[to][j][0]);
				dp[x][i+j][1]=min(dp[x][i+j][1],dp[x][i][1]+min(dp[to][j][0],dp[to][j][1]));
			}
		}
		sz[x]+=sz[to];
	}
}

int main()
{
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld %lld",&c[i],&d[i]);
		if(i>1)
		{
			int x;
			scanf("%d",&x);
			adj[x].push_back(i);
		}
	}
	dfs(1);
	int ans=0;
	for(int i=1;i<=n;i++)
		if(min(dp[1][i][0],dp[1][i][1])<=b) ans=i;
	cout << ans << endl;
}
