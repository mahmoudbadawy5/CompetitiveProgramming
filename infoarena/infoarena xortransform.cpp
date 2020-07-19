/*
  -Same as: https://github.com/veljko02/CompetitiveProgramming/blob/master/Olympiad/infoarena/xortransform.cpp
*/

#include <bits/stdc++.h>

using namespace std;

const int MX=(1<<22);

int dp[(1<<22)];

int main()
{
	freopen("xortransform.in","r",stdin); freopen("xortransform.out","w",stdout);
	int n,m,q;
	scanf("%d %d %d",&n,&m,&q);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			int x;
			scanf("%d",&x);
			dp[i|j]^=x;
		}
	}
	for(int i=0;i<22;i++)
	{
		for(int j=MX-1;j>=0;j--)
		{
			if(j&(1<<i))
			{
				dp[j]^=dp[j^(1<<i)];
			}
		}
	}
	int las=0;
	while(q--)
	{
		int x;
		scanf("%d",&x);
		x^=las;
		x&=(MX-1);
		printf("%d\n",dp[x]);
		las=dp[x];
	}
}
