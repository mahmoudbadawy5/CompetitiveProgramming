/*
Let's assume that we know the number of permutations with (n-1) elements and starts with all possible numbers and the next number
in it is smaller than the first. We can put a number that's smaller than the first number and it will be a valid permutation.
When we add a number x at the beginning of the permutation we need to add one to all numbers >=x as we inserted this number
and we considered the old permutation to be in a relative order.

We can cnstruct the solution using a recursive function that tries to put numbers one by one and subtract the number of ways from C
*/

#include <bits/stdc++.h>

using namespace std;

long long mem[22][22][2];
int got[22];
vector<int> ans;

long long go(int n,int st,int nx)
{
	if(n==1) return (st==0);
	long long &ret=mem[n][st][nx];
	if(ret!=-1) return ret;
	ret=0;
	for(int i=0;nx==0&&i<st;i++)
	{
		ret+=go(n-1,i,1);
	}
	for(int i=st;nx==1&&i<n-1;i++)
	{
		ret+=go(n-1,i,0);
	}
	return ret;
}

void solve(int n,int st,int nx,long long k,int nn)
{
	for(int i=0,cur=0;i<nn;i++)
	{
		if(got[i]) continue;
		if(cur==st)
		{
			ans.push_back(i);
			got[i]=1;
			break;
		}
		cur++;
	}
	if(n==1) return;
	for(int i=0;nx==0&&i<st;i++)
	{
		if(k>=go(n-1,i,1))
			k-=go(n-1,i,1);
		else
			return solve(n-1,i,1,k,nn);
	}
	for(int i=st;nx==1&&i<n-1;i++)
	{
		if(k>=go(n-1,i,0))
			k-=go(n-1,i,0);
		else
			return solve(n-1,i,0,k,nn);
	}
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n; long long k;
		cin >> n >> k;
		memset(mem,-1,sizeof mem);
		memset(got,0,sizeof got);
		ans.clear();
		k--; int got=0;
		for(int i=0;i<n&&got==0;i++)
		{
			for(int j=0;j<2;j++)
			{
				if(k>=go(n,i,j))
					k-=go(n,i,j);
				else
				{
					got=1;
					solve(n,i,j,k,n);
					break;
				}
			}
		}
		assert(ans.size()==n);
		for(int i=0;i<n;i++)
			cout << ans[i]+1 << " \n"[i==n-1];
	}
}
