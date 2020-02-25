/*
Same as: https://github.com/nikolapesic2802/Programming-Practice/blob/master/Flood/main.cpp
*/
#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=1e5+5;

int n,m;
pair<int,int> arr[N];
int sorted[N],vis[N];
pair<int,int> adj[N][4];
vector<int> ans;

bool cmp(int x,int y)
{
	return arr[x]<arr[y];
}

int go(int x,int d)
{
	if(vis[x]) return x;
	vis[x]=1;
	for(int i=0;i<4;i++)
	{
		int tod=(d-i+1+4)%4;
		int to=adj[x][tod].F;
		if(to==-1) continue;
		int ed=adj[x][tod].S;
		adj[x][tod]={-1,-1};
		adj[to][(tod+2)%4]={-1,-1};
		int y=go(to,tod);
		if(y==-1)
		{
			ans.push_back(ed);
			continue;
		}
		if(y!=x)
		{
			vis[x]=0;
			return y;
		}
	}
	vis[x]=0;
	return -1;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		sorted[i]=i;
		scanf("%d %d",&arr[i].F,&arr[i].S);
		for(int j=0;j<4;j++)
			adj[i][j]={-1,-1};
	}
	sort(sorted,sorted+n,cmp);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y); x--; y--;
		if(arr[x].F==arr[y].F)
		{
			if(arr[x].S>arr[y].S) swap(x,y);
			adj[x][0]={y,i};
			adj[y][2]={x,i};
		}
		else
		{
			if(arr[x].F>arr[y].F) swap(x,y);
			adj[x][1]={y,i};
			adj[y][3]={x,i};
		}
	}
	for(int i=0;i<n;i++)
	{
		go(sorted[i],0);
	}
	cout << ans.size() << endl;
	for(int i:ans)
		cout << i << endl;
}
