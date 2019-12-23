/*
Cosider that the first class for each group is a[i] , second class is b[i]. We will consider a as a non decrasing sequence and we can get it using X.
We will multiply the answer by the number of different permutations possible at the end (n!/x[0]!x[1]!...). now how to calculate the number of possible b[i]? 
We will use DP[index][rem] where index is the current class and rem is the number of remaining people. 
If we know that the first A people can be assigned to class index, we already assigned n-rem people, we will assign val people to it then the number of ways is (A-(n-rem))C(val). 
Then we can go to the next state. The total complexty is O(n^2).
*/

#include <bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

long long dp[105][1005];
long long nck[1005][1005],fac[1005],infac[1005];
int x[1005],y[1005];
int a[1005],las[1005];
int m,n;

long long go(int ind,int rem)
{
	if(rem==0) return 1;
	if(ind>=m) return 0;
	long long &ret=dp[ind][rem];
	if(ret!=-1) return ret;
	// [0,n-rem] -> got by higher classes
	// val -> what will I take
	ret=go(ind+1,rem);
	for(int val=1;val<=min(rem,y[ind]);val++)
	{
		if(x[n-rem+val-1]>ind) break;
		int got=n-rem;
		ret+=nck[las[ind]-got][val]*go(ind+1,rem-val);
		//cout << ind << " " << val << " " << rem <<" " << las[ind] << " " << las[ind]-got << endl;
		ret%=MOD;
	}
	return ret;
}

long long poww(long long x,int p)
{
	if(p==0) return 1;
	if(p&1) return (x*poww(x,p-1))%MOD;
	return poww((x*x)%MOD,p/2);
}

int main()
{
	nck[0][0]=1;
	for(int i=1;i<=1000;i++)
	{
		nck[i][0]=nck[i][i]=1;
		for(int j=1;j<i;j++)
		{
			nck[i][j]=(nck[i-1][j-1]+nck[i-1][j])%MOD;
		}
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%d",&a[i]);
		for(int j=n;j<n+a[i];j++)
			x[j]=i;
		las[i]=n+a[i];
		n+=a[i];
	}
	for(int i=0;i<m;i++)
		scanf("%d",&y[i]);
	memset(dp,-1,sizeof dp);
	long long ans=go(0,n);
	fac[0]=1;
	for(int i=1;i<=n;i++)
	{
		fac[i]=(i*fac[i-1])%MOD;
		infac[i]=poww(fac[i],MOD-2);
		ans=(ans*i)%MOD;
	}
	for(int i=0;i<m;i++)
	{
		ans=(ans*infac[a[i]])%MOD;
	}
	cout << ans << endl;
}
