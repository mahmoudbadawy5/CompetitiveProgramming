/*
same as : https://github.com/quangloc99/CompetitiveProgramming/blob/master/olympiad/COCI/2008/Periodni.cpp
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int MOD=1e9+7,N=505;

int n,k;
int arr[N];
vector<long long> mem[N][N];
long long fac[1000006],infac[1000006];

long long poww(long long x,int y)
{
	if(y==0) return 1;
	if(y&1) return (x*poww(x,y-1))%MOD;
	return poww((x*x)%MOD,y/2);
}

long long nCk(int x,int y)
{
	if(y>x) return 0;
	return (((fac[x]*infac[y])%MOD)*infac[x-y])%MOD;
}

void solve(int l,int r,int bs)
{
	if(l>r) return;
	vector< pair<int,int> > ch;
	int mn=(1<<30);
	for(int i=l;i<=r;i++)
		mn=min(mn,arr[i]);
	for(int i=l;i<=r;i++)
	{
		if(arr[i]>mn)
		{
			int j;
			for(j=i;j<=r;j++)
				if(arr[j]==mn) break;
			ch.push_back({i,j-1});
			i=j;
		}
	}
	mem[l][r]=vector<long long>(r-l+2);
	mem[l][r][0]=1;
	int h=r-l+1,w=mn-bs;
	vector<long long> v(h+1);
	for(auto x:ch)
	{
		solve(x.F,x.S,mn);
		for(int i=0;i<=h;i++)
		{
			for(int j=0;j<=x.S-x.F+1;j++)
			{
				if(i+j>h) continue;
				v[i+j]+=(mem[l][r][i]*mem[x.F][x.S][j])%MOD;
				v[i+j]%=MOD;
			}
		}
		for(int i=0;i<=h;i++)
		{
			mem[l][r][i]=v[i];
			v[i]=0;
		}
	}
	//cout << h << " " << w << endl;

	for(int i=0;i<=h;i++)
	{
		for(int j=0;j<=min(h,w);j++)
		{
			if(i+j>h) continue;
			long long now=nCk(h-i,j)*nCk(w,j);
			now%=MOD;
			now*=fac[j];
			now%=MOD;
			v[i+j]+=(now*mem[l][r][i])%MOD;
			//cout << i << " " << j << " " << nCk(h-i,j) << " " << nCk(w,j) << " " << mem[l][r][i+j] << endl;
			v[i+j]%=MOD;
		}
	}
	for(int i=0;i<=h;i++)
		mem[l][r][i]=v[i];
}

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	fac[0]=infac[0]=1;
	for(int i=1;i<1000006;i++)
	{
		fac[i]=(i*fac[i-1])%MOD;
		infac[i]=poww(fac[i],MOD-2);
	}
	solve(0,n-1,0);
	cout << mem[0][n-1][k] << endl;
}
