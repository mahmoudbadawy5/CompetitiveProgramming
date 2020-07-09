/*
  -Same as: https://github.com/thecodingwizard/competitive-programming/blob/master/USACO/2019dec/pieaters.cpp
*/

#include <bits/stdc++.h>

using namespace std;

int n,m;
int mx[305][305][305];
int mem[305][305];

int go(int l,int r)
{
	if(r<l) return 0;
	if(mem[l][r]!=-1) return mem[l][r];
	int &ret=mem[l][r];
	ret=0;
	for(int i=l;i<r;i++)
		ret=max(ret,go(l,i)+go(i+1,r));
	for(int i=l;i<=r;i++)
	{
		if(mx[l][r][i]) ret=max(ret,go(l,i-1)+mx[l][r][i]+go(i+1,r));
	}
	return ret;
}

int main()
{
	freopen("pieaters.in","r",stdin); freopen("pieaters.out","w",stdout);
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int x,l,r;
		scanf("%d %d %d",&x,&l,&r);
		for(int j=l;j<=r;j++)
			mx[l][r][j]=max(mx[l][r][j],x);
	}
	for(int x=1;x<=n;x++)
	{
		for(int l=x;l>=1;l--)
		{
			for(int r=x;r<=n;r++)
			{
				mx[l-1][r][x]=max(mx[l][r][x],mx[l-1][r][x]);
				mx[l][r+1][x]=max(mx[l][r][x],mx[l][r+1][x]);
			}
		}
	}
	memset(mem,-1,sizeof mem);
	cout << go(1,n) << endl;
}
