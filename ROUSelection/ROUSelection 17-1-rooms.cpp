/*
Same as editorial in csacademy
*/

#include <bits/stdc++.h>

using namespace std;

const int N=2005;

int ids[N][N],id;
pair<int,int> st[N*N];
int sum[N][N];
string gr[N];
int n,m,q;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};

int ok(int x,int y)
{
	return (0<=x&&x<n&&0<=y&&y<m);
}

void go(int x,int y,int cur)
{
	if(ids[x][y]) return;
	ids[x][y]=cur;
	for(int i=0;i<4;i++)
	{
		int nx=x+dx[i],ny=y+dy[i];
		if(!ok(nx,ny) || gr[x][y]!=gr[nx][ny]) continue;
		go(nx,ny,cur);
	}
}

int getsum(int a,int b,int c,int d)
{
	int ans=sum[c][d];
	if(b) ans-=sum[c][b-1];
	if(a) ans-=sum[a-1][d];
	if(a&&b) ans+=sum[a-1][b-1];
	return ans;
}

int in(pair<int,int> x,int a,int b,int c,int d)
{
	return (a<=x.first&&x.first<=c)&&(b<=x.second&&x.second<=d);
}

int main()
{
	cin >> n >> m;
	for(int i=0;i<n;i++)
		cin >> gr[i];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(!ids[i][j])
			{
				st[++id]={i,j};
				sum[i][j]=1;
				go(i,j,id);
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(i) sum[i][j]+=sum[i-1][j];
			if(j) sum[i][j]+=sum[i][j-1];
			if(i&&j) sum[i][j]-=sum[i-1][j-1];
		}
	}
	scanf("%d",&q);
	while(q--)
	{
		int a,b,c,d;
		scanf("%d %d %d %d",&a,&b,&c,&d);
		a--; b--; c--; d--;
		int z=getsum(a,b,c,d);
		set<int> ss;
		for(int i=a;i<=c;i++)
		{
			int cid=ids[i][b];
			if(ss.find(cid)==ss.end())
			{
				ss.insert(cid);
				if(!in(st[cid] , a,b,c,d)) z++;
			}
			cid=ids[i][d];
			if(ss.find(cid)==ss.end())
			{
				ss.insert(cid);
				if(!in(st[cid] , a,b,c,d)) z++;
			}
		}
		for(int i=b;i<=d;i++)
		{
			int cid=ids[a][i];
			if(ss.find(cid)==ss.end())
			{
				ss.insert(cid);
				if(!in(st[cid] , a,b,c,d)) z++;
			}
			cid=ids[c][i];
			if(ss.find(cid)==ss.end())
			{
				ss.insert(cid);
				if(!in(st[cid] , a,b,c,d)) z++;
			}
		}
		printf("%d\n",z);
	}

}
