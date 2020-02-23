/*
Same as: https://github.com/stefdasca/CompetitiveProgramming/blob/master/CEOI/CEOI%2016-Kangaroo.cpp
*/

#include <bits/stdc++.h>

using namespace std;

const int N=2005,MOD=1e9+7;

long long mem[N][N];
int n,a,b;

int main()
{
	cin >> n >> a >> b;
	mem[1][1]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			if(i==a||i==b)
			{
				mem[i][j]=mem[i-1][j]+mem[i-1][j-1];
				if(mem[i][j]>=MOD) mem[i][j]-=MOD;
				continue;
			}
			mem[i][j]=mem[i-1][j-1]*(j-((i>a)+(i>b))); // add a new component
			mem[i][j]%=MOD;
			mem[i][j]+=mem[i-1][j+1]*j; // combine two existing components;
			mem[i][j]%=MOD;
		}
	}
	cout << mem[n][1] << endl;
}
