/*
This code gets 90 and I'm not sure how to optimize it further.
-https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2009/contest6_solutions
*/

#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define F first
#define S second

using namespace std;

const int N=2005,M=205;
const int INF=2e9+10;


int arr[N][M];
int sum[N][M],rsum[N][M];
int cst[N][2][N][2];
int vis[N*2][N*2];
int n,m,q;

pair<int,pair<int,int> > adj[N][2][4];
int sz[N][2];

int dist(int a,int b,int c,int d)
{
	int ans=INF;
	if(a==c) ans=sum[a][max(b,d)]-(min(b,d)?sum[a][min(b,d)-1]:0)-arr[a][b];
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			int aa=(i==0?sum[a][b]:rsum[a][b])-arr[a][b];
			int bb=(j==0?sum[c][d]:rsum[c][d])-(j==0?arr[c][0]:arr[c][m-1]);
			ans=min(ans,aa+bb+cst[a][i][c][j]);
		}
	}
	return ans;
}

void go(int x,int y)
{
	priority_queue< pair<int, int > > ss;
	for(int i=0;i<n;i++)
		for(int j=0;j<2;j++)
			cst[x][y][i][j]=INF;
	cst[x][y][x][y]=0;
	ss.push({0,x*2+y});
	int cz=x*2+y;
	while(ss.size())
	{
		auto cur=(ss.top());
		ss.pop();
		if(vis[cz][cur.S]) continue;
		vis[cz][cur.S]=1;
		int a=cur.S/2,b=cur.S&1;
		for(int i=0;i<sz[a][b];i++)
		{
			int nx=adj[a][b][i].S.F,ny=adj[a][b][i].S.S,c=adj[a][b][i].F;
			if(cst[x][y][a][b]+c<cst[x][y][nx][ny])
			{
				cst[x][y][nx][ny]=cst[x][y][a][b]+c;
				ss.push({-cst[x][y][nx][ny],{nx*2+ny}});
			}
		}
	}
}

int main()
{
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			scanf("%d",&arr[i][j]);
			sum[i][j]=(j?sum[i][j-1]:0)+arr[i][j];
		}
		for(int j=m-1;j>=0;j--)
			rsum[i][j]=rsum[i][j+1]+arr[i][j];
	}
	for(int i=0;i<n;i++)
	{
		if(i+1<n)
		{
			adj[i][0][sz[i][0]++]={arr[i+1][0],{i+1,0}};
			adj[i+1][0][sz[i+1][0]++]={arr[i][0],{i,0}};
			adj[i][1][sz[i][1]++]={arr[i+1][m-1],{i+1,1}};
			adj[i+1][1][sz[i+1][1]++]={arr[i][m-1],{i,1}};
		}
		adj[i][0][sz[i][0]++]={sum[i][m-1]-arr[i][0],{i,1}};
		adj[i][1][sz[i][1]++]={sum[i][m-1]-arr[i][m-1],{i,0}};
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<2;j++)
			go(i,j);
	int lx=0,ly=0;
	long long ans=arr[0][0];
	scanf("%d",&q);
	for(int i=0;i<q;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		x--; y--;
		ans+=dist(lx,ly,x,y);
		lx=x; ly=y;
	}
	cout << ans << endl;
}
