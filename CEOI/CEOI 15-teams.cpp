/*
We will consider the form of the team a number and will use dp on digits to calculate the number of forms less than our form
The condition on these numbers is that the first occurence of x must be after the first occurence of y if x>y.
We can have an additional dimension in the DP which represents the maximum digit that appeared

consider dp[index][limit][smaller] as the number of forms starting from index with the current maximum digit is limit,
smaller is a boolean to tell if the current number is already smaller than the initial number

That's O(n^2) in time and needs memory reduction to pass the last subtask
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e4+5,MOD=1e6+7;

long long mem[2][N][2];
int arr[N];
int n;

inline int add(int x,int y)
{
	x=x+y;
	//x%=MOD;
	if(x<0) return x+MOD;
	if(x>=MOD) return x-MOD;
	return x;
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(int i=1;i<=n+1;i++)
		mem[n%2][i][0]=mem[n%2][i][1]=1;
	for(int i=n-1;i>=0;i--)
	{
		for(int l=1;l<=i+1;l++)
		{
			// s=0
			// go with the same digit
			int x=i&1; int y=x^1;
			mem[x][l][0]=mem[y][max(l,arr[i])][0];
			// go with smaller digit
			mem[x][l][0]=add(mem[x][l][0],(1LL*(arr[i]-1)*mem[y][l][1])%MOD);
			//if(l<arr[i]) mem[x][l][0]=0;
			// s=1
			// increase l
			mem[x][l][1]=mem[y][l+1][1];
			// same l
			mem[x][l][1]=add(mem[x][l][1],(1LL*l*mem[y][l][1])%MOD);
			//cout << i << " " << l << " " << mem[x][l][0] << " " << mem[x][l][1] << endl;
		}
	}
	printf("%lld\n",mem[0][1][0]);
}
