/*
The same as : https://github.com/OmarHashim/Competitive-Programming/blob/master/SPOJ/EASYFACT.cpp
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e8+1;

//bitset<N> bt;
vector<int> primes;
int pr[N];

void sieve()
{
	for(int i=2;i<N;i++)
	{
		if(!pr[i])
		{
			pr[i]=i;
			primes.push_back(i);
		}
		for(int j=0;j<primes.size()&&primes[j]<=pr[i]&&i*primes[j]<N;j++)
		{
			pr[primes[j]*i]=primes[j];
		}
	}
}

int cnt(int x,int y)
{
	//cout << x << " " << y << endl;
	int ans=0;
	while(x>=y)
	{
		ans+=x/y;
		x/=y;
	}
	return ans;
}
int m;

long long poww(long long x,int p)
{
	if(p==0) return 1;
	if(p&1) return (poww(x,p-1)*x)%m;
	return poww((x*x)%m,p/2);
}

int SQ=1e4;

int main()
{
	sieve();
	//cout << "OK" << endl; return 0;
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d%d",&n,&m);
		long long ans=1;
		for(int i=1;i<SQ;i++)
		{
			ans*=1+cnt(n,primes[i]);
			ans%=m;
		}
		//cout << ans << "OK" << endl;
		int cur=SQ;
		while(cur<primes.size())
		{
			int x=cnt(n,primes[cur]);
			int st=cur,en=primes.size()-1,ansid=cur;
			while(st<=en)
			{
				int mid=(st+en)>>1;
				if(cnt(n,primes[mid])==x)
				{
					ansid=mid; st=mid+1;
				}
				else en=mid-1;
			}
			ans*=poww(x+1,ansid-cur+1);
			ans%=m;
			cur=ansid+1;
		}
		printf("%lld\n",(ans+m-1)%m);
	}
}
