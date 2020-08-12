/*
Each word must be one or more blocks of good subwords. the good subword is a word starting with zero or more letters with indices <= n/2 then one letter with index >= n/2.
We can notice that the length of each good subword can't exceed log(n) as each character is at least double the last character. We can count the number of good words
using dp[index][cur_letter] and by using prefix sums we can caclulate it in O(nlogn) then using another dp to construct words from subwords.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=5e5+5,MOD=1e8+7;

int n,m;
long long mem[N];
long long mem2[20][N];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			if(2*i>n)
				mem2[0][i]=1;
			else mem2[0][i]=0;
			mem2[0][i]+=mem2[0][i-1];
		}
		for(int i=1;i<20;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(2*j>n) mem2[i][j]=0;
				else
				{
					int x=2*j;
					// next -> [2*j,n]
					mem2[i][j]=mem2[i-1][n]-mem2[i-1][x-1];
					mem2[i][j]+=MOD;
					if(mem2[i][j]>=MOD) mem2[i][j]-=MOD;
				}
				mem2[i][j]+=mem2[i][j-1];
				if(mem2[i][j]>=MOD) mem2[i][j]-=MOD;
			}
		}
		mem[m]=1;
		for(int i=m-1;i>=0;i--)
		{
			mem[i]=0;
			for(int j=0;j<20;j++)
			{
				if(i+j>=m) break;
				mem[i]+=mem2[j][n]*mem[i+j+1];
				mem[i]%=MOD;
			}
		}
		printf("%lld\n",mem[0]);
	}
}
