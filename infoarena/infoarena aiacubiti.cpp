/*
Same as: https://github.com/zoooma13/Competitive-Programming/blob/master/aiacubiti.cpp
*/

#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
using namespace std;

const int N=1e5+5,M=(1<<20);

int arr[N];
int mem[M][5],co[M];
int n;

int main()
{
	freopen("aiacubiti.in","r",stdin); freopen("aiacubiti.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	long long ans=0;
	for(int i=0;i<M;i++)
		co[i]=__builtin_popcount(i);
	for(int i=0;i<n;i++)
	{
		int a=arr[i]>>10,b=arr[i]&((1<<10)-1);
		for(int i=0;i<(1<<10);i++)
		{
			int x=co[b^i];
			if(x>4) continue;
			ans+=mem[(a<<10)|i][4-x];
		}
		for(int i=0;i<(1<<10);i++)
		{
			int x=co[a^i];
			if(x>4) continue;
			mem[(i<<10)|b][x]++;
		}
	}
	printf("%lld\n",ans);
}
