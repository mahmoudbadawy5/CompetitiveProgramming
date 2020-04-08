/*
Let's solve it using dp[used][last] where used is the number of used drills and last is the last drilled column. We can 
observe that if you drilled a hole in a column i then all components that starts before i and ends after i are included.

So if we drilled a hole in column j and the last column is i we get all components with (l,r) i<l<=j , j<=r. So we can precalculate
every answer for (i,j) using 2d prefix sum. This is O(n^3) dp but we can notice that the optimal last hole is increasing while
increasing the current hole so we can make a divide and conqure dp.
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=2005;

char gr[N][N];
int n,m,idc;
int mn[N*N],mx[N*N],sum[N*N];
int id[N][N];
int sm[N][N];
int dp[N][N];

int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

void go(int x,int y)
{
	if(x<0||x>=n||y<0||y>=m) return;
	if(gr[x][y]=='.') return;
	if(id[x][y]) return;
	id[x][y]=idc;
	sum[idc]+=gr[x][y]-'0';
	mn[idc]=min(mn[idc],y);
	mx[idc]=max(mx[idc],y);
	for(int i=0;i<4;i++)
		go(x+dx[i],y+dy[i]);
}

int get(int l,int r)
{
	// [l,r] , [r,m-1];
	int ans=sm[r][m-1];
	if(l) ans-=sm[l-1][m-1];
	if(r) ans-=sm[r][r-1];
	if(l&&r) ans+=sm[l-1][r-1];
	return ans;
}

void solve(int cur,int l,int r,int lo,int ro)
{
	if(r<l) return;
	int mid=(l+r)/2;
	int opt=lo;
	// mid is the point to drill
	for(int i=lo;i<=min(ro,mid);i++)
	{
		// i-1 is the last drilled hole
		int curans=(i?dp[cur-1][i-1]:0)+get(i,mid);
		if(curans>dp[cur][mid])
		{
			dp[cur][mid]=curans;
			opt=i;
		}
	}
	solve(cur,l,mid-1,lo,opt);
	solve(cur,mid+1,r,opt,ro);
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%s",gr[i]);
	memset(mn,'?',sizeof mn);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(!id[i][j] && gr[i][j]!='.')
			{
				idc++;
				go(i,j);
			}
		}
	}
	for(int i=1;i<=idc;i++)
	{
		sm[mn[i]][mx[i]]+=sum[i];
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(i) sm[i][j]+=sm[i-1][j];
			if(j) sm[i][j]+=sm[i][j-1];
			if(i&&j) sm[i][j]-=sm[i-1][j-1];
		}
	}
	// sm[i][j] is the sum of components with l<=i ,r<=j
	for(int i=1;i<=m;i++)
	{
		solve(i,0,m-1,0,m-1);
		int ans=0;
		for(int j=0;j<m;j++) ans=max(ans,dp[i][j]);
		printf("%d\n",ans);
	}
}
