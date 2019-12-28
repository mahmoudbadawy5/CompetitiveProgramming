/*
From a paper about greedy knapsack it says that the optimal solution would use a single element multiple times until the result is small.
We can compute dp till 10^6 then complete the rest with a single element.
We get the largest number <= 10^6 with mod ai = q_i mod ai
*/

#include <bits/stdc++.h>

using namespace std;

const int MOD=1e9+7+1e-8,MXQ=1e6;

long long dp[MXQ+1];
int n,c,m;
int a[105],b[105];

long long go(int w)
{
	if(w==0) return dp[w]=0;
	if(dp[w]!=-1) return dp[w];
	dp[w]=(1LL<<60);
	for(int i=0;i<n;i++)
	{
		if(w-a[i]>=0)
			dp[w]=min(dp[w],b[i]+go(w-a[i]));
	}
	return dp[w];
}

int main()
{
	cin >> n >> c >> m;
	for(int i=0;i<n;i++)
	{
		cin >> a[i] >> b[i];
	}
	memset(dp,-1,sizeof dp);
	for(int i=1;i<=MXQ;i++)
		go(i);
	while(m--)
	{
		long long x;
		scanf("%lld",&x);
		__int128 ans=2e36+15;
		// a*b + c
		// d*e + f
		if(x<=MXQ)
		{
			if(dp[x]<(1LL<<60))
				printf("%lld\n",dp[x]%MOD);
			else
				printf("-1\n");
		}
		else
		{
			for(int i=0;i<n;i++)
			{
				long long willget=MXQ/a[i]*a[i]-a[i]+x%a[i];
				if(dp[willget]>=(1LL<<60)) continue;
				__int128 cur=(x-willget)/a[i];
				cur=cur*b[i]+dp[willget];
				ans=min(ans,cur);
			}
			long long mans;
			if(ans>=2e36)
				mans=-1;
			else
				mans=ans%MOD;
			printf("%lld\n",mans);
		}
	}
}
