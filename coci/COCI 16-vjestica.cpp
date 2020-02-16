/*
Let's solve it using bitmasks dp. For a mask x let's assume that a and b are submasks from it and a|b = x, dp[a] and dp[b]
are the minimum number of nodes to cover the words in these masks. Now to merge the subtrees we can get the common letters at the
beginnig and subtract them from the total cost.

so dp[x]=min(dp[a]+dp[b]-cost[x]) where cost[x] is the number of common letters in all words in x.

Now to iterate on the submasks quicly we can use the trick here: https://codeforces.com/blog/entry/45223
*/

#include <bits/stdc++.h>

using namespace std;

const int N=16;

int mem[(1<<N)];
int cost[(1<<N)];
int co[N][26];
int n;
string arr[N];

int main()
{
	cin >> n;
	for(int i=0;i<n;i++)
	{
		cin >> arr[i];
		for(int j=0;j<arr[i].size();j++)
			co[i][arr[i][j]-'a']++;
	}
	for(int i=1;i<(1<<n);i++)
	{
		int cur[26];
		memset(cur,'?',sizeof cur);
		for(int j=0;j<n;j++)
		{
			if(i&(1<<j))
			{
				for(int k=0;k<26;k++)
				{
					cur[k]=min(cur[k],co[j][k]);
					mem[i]+=co[j][k];
				}
			}
		}
		for(int j=0;j<26;j++) cost[i]+=cur[j];
	}
	for(int i=1;i<(1<<n);i++)
	{
		for(int j=i;j>0;j=(j-1)&i)
		{
			if(j==i) continue;
			mem[i]=min(mem[i],mem[j]+mem[i^j]-cost[i]);
		}
	}
	cout << mem[(1<<n)-1]+1 << endl;
}
