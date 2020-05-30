/*
 Same as: https://github.com/stefdasca/CompetitiveProgramming/blob/master/COI/COI%2015-zarulje.cpp
*/
#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5,MOD=1e9+7;

int n,k;
int arr[N],ans[N];
int l[N],r[N];
stack<int> ll,rr;
vector<int> del[N];
long long fac[N],infac[N],anss;

long long poww(long long x,long long y)
{
	if(y==0) return 1;
	if(y&1) return (poww(x,y-1)*x)%MOD;
	return poww((x*x)%MOD,y/2);
}

long long nCk(int n,int k)
{
	return (((fac[n]*infac[k])%MOD)*infac[n-k])%MOD;
}

void add(int x,int dl,int dr)
{
	//cout << l[x]+r[x] << " " << l[x] << " " << poww(nCk(l[x]+r[x],l[x]),MOD-2) << endl;
	anss=(anss*poww(nCk(l[x]+r[x],l[x]),MOD-2))%MOD;
	l[x]+=dl; r[x]+=dr;
	//cout << l[x]+r[x] << " " << l[x] << " " << nCk(l[x]+r[x],l[x]) << endl;
	anss=(anss*nCk(l[x]+r[x],l[x]))%MOD;
}

int main()
{
	fac[0]=infac[0]=1; anss=1;
	for(int i=1;i<N;i++) {fac[i]=(i*fac[i-1])%MOD; infac[i]=poww(fac[i],MOD-2);}
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(int i=n-1;i>0;i--)
	{
		r[arr[i]]++;
		while(rr.size() && rr.top()>arr[i])
		{
			del[i].push_back(rr.top());
			r[rr.top()]--;
			rr.pop();
		}
		rr.push(arr[i]);
	}
	ans[0]=1;
	for(int i=1;i<n;i++)
	{
		while(ll.size() && ll.top()>arr[i-1])
		{
			add(ll.top(),-1,0);
			ll.pop();
		}
		ll.push(arr[i-1]);
		add(arr[i-1],1,0);
		add(rr.top(),0,-1);
		rr.pop();
		for(int j=del[i].size()-1;j>=0;j--)
		{
			rr.push(del[i][j]);
			add(del[i][j],0,1);
		}
		ans[i]=anss;
	}
	while(k--)
	{
		int x;
		scanf("%d",&x);
		x--;
		printf("%d\n",ans[x]);
	}
}
