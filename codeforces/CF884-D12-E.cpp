/*
  Same as editorial: https://codeforces.com/blog/entry/55470
*/

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx")

#include <bits/stdc++.h>

using namespace std;

int n,m;
pair<int,int> uni[2][(1<<14)+5];
char cur[2][(1<<14)+5];

inline int get(char x,int j)
{
	j%=4;
	j=3-j;
	if('0'<=x&&x<='9') return ((x-'0')&(1<<j))!=0;
	x-='A';
	x+=10;
	return (x&(1<<j))!=0;
}

pair<int,int> uni_find(int x,int y)
{
	if(uni[x&1][y]==make_pair(x,y)) return {x,y};
	return uni[x&1][y]=uni_find(uni[x&1][y].first,uni[x&1][y].second);
}

int unio(int a,int b,int c,int d)
{
	pair<int,int> aa=uni_find(a,b),bb=uni_find(c,d);
	if(aa==bb) return 0;
	uni[aa.first&1][aa.second]=bb;
	return 1;
}

int main()
{
	scanf("%d %d",&n,&m);
	int ans=0;
	for(int i=0;i<n;i++)
	{
		scanf("%s",cur[i&1]);
		for(int j=0;j<m;j++)
			uni[i&1][j]={i,j};
		for(int j=0;j<m;j++)
		{
			int cb=get(cur[i&1][j/4],j);
			//cout << cb; 
			ans+=cb!=0;
			if(!cb) continue;
			if(j)
			{
				int lb=get(cur[i&1][(j-1)/4],j-1);
				if(lb) ans-=unio(i,j-1,i,j);
			}
			if(i)
			{
				int lb=get(cur[(i-1)&1][j/4],j);
				if(lb) ans-=unio(i-1,j,i,j);
			}
		}
		//cout << endl;
		for(int j=0;j<m;j++) uni_find(i,j);
	}
	printf("%d\n",ans);
}
