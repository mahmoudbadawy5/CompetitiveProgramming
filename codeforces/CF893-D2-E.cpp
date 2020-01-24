  /*
  We have some prime factors of x that needs to be distributed to y places. We can get the number of ways for each prime divisor
  independently then multiply the number of ways. The answer for one divisor can be calculated as stars and bars problem
  Let the power of this prime be p. We have p stars and y-1 bars. that's (p+y-1)C(p)
  We need to multiply the answer by 2^(p-1) as this is the number of ways to choose an even number of elements and make them negative.
  */
  
  #include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=2e6+6,MOD=1e9+7;

long long pw[N],fac[N],infac[N];
vector<pair<int,int> > pr[N];

long long poww(long long x,long long y)
{
	if(y==0) return 1;
	if(y&1) return (x*poww(x,y-1))%MOD;
	return poww((x*x)%MOD,y/2);
}

long long nCk(long long n,long long k)
{
	return (((fac[n]*infac[k])%MOD)*infac[n-k])%MOD;
}

int main()
{
	fac[0]=1;
	for(int i=1;i<N;i++)
		fac[i]=(i*fac[i-1])%MOD;
	infac[N-1]=poww(fac[N-1],MOD-2);
	for(int i=N-2;i>=0;i--)
		infac[i]=(infac[i+1]*(i+1))%MOD;
	pw[0]=1;
	for(int i=1;i<N;i++)
		pw[i]=(2*pw[i-1])%MOD;
	for(int i=2;i<N;i++)
	{
		//cout << i << endl;
		if(pr[i].size()==0)
		{
			for(int j=i;j<N;j+=i)
				pr[j].push_back({i,1});
			continue;
		}
		for(auto &x:pr[i])
		{
			int tmp=i;
			x.S=0;
			while(tmp%x.F==0)
			{
				x.S++;
				tmp/=x.F;
			}
		}
	}
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		long long ans=pw[y-1];
		for(auto i:pr[x])
		{
			ans*=nCk(y+i.S-1,i.S);
			ans%=MOD;
		}
		printf("%lld\n",ans);
	}
}
