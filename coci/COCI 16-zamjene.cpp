/*
We can simulate the queries using a DSU. To keep which numbers is missing or extra for each cloud we can use hashing.
Here the hash is sum(BASE^(p[i])) - sum(BASE^(q[i]).
To add two clouds and make them good we need hash1+hash2=0 so we can find for each cloud the number of other clouds with -hash
I used double hash here but sime solutions passed with a single hash.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e6+6,H=2,BASE=N;
const int MOD[H]={88199200,102345521};
int pw[N][H];
map< pair<int,int>, int > mp;
long long ans4,bad;
int arr[N],sor[N];

inline int neg(int x,int i)
{
	x=MOD[i]-x;
	if(x>=MOD[i]) return x-MOD[i];
	return x;
}

struct DSU{
	int pa[N],sz[N];
	int hsh[N][H];	void init(int n)
	{
		iota(pa,pa+n,0);
		fill(sz,sz+n,1);
	}
	int operator() (int x)
	{
		if(pa[x]==x) return x;
		return pa[x]=(*this)(pa[x]);
	}
	void updAns(int x,int p)
	{
		if(hsh[x][0]||hsh[x][1]) {bad+=p; ans4+=1LL*p*mp[{neg(hsh[x][0],0),neg(hsh[x][1],1)}]*sz[x];}

	}
	void operator() (int x,int y)
	{
		x=(*this)(x); y=(*this)(y);
		if(x==y) return;
		if(sz[x]>sz[y]) swap(x,y);
		if(hsh[x][0]||hsh[x][1]) mp[{hsh[x][0],hsh[x][1]}]-=sz[x];
		updAns(x,-1);
		updAns(y,-1);
		if(hsh[y][0]||hsh[y][1]) mp[{hsh[y][0],hsh[y][1]}]-=sz[y];
		for(int i=0;i<H;i++)
		{
			hsh[y][i]+=hsh[x][i];
			hsh[y][i]%=MOD[i];
			hsh[y][i]+=MOD[i];
			while(hsh[y][i]>=MOD[i]) hsh[y][i]-=MOD[i];
		}
		pa[x]=y; sz[y]+=sz[x]; sz[x]=0;
		if(hsh[y][0]||hsh[y][1]) mp[{hsh[y][0],hsh[y][1]}]+=sz[y];
		updAns(y,1);
	}
	void mod(int x,int y,int z)
	{
		x=(*this)(x);
		if(hsh[x][0]||hsh[x][1]) mp[{hsh[x][0],hsh[x][1]}]-=sz[x];
		updAns(x,-1);
		for(int i=0;i<H;i++)
		{
			hsh[x][i]+=pw[y][i];
			hsh[x][i]-=pw[z][i];
			hsh[x][i]%=MOD[i];
			hsh[x][i]+=MOD[i];
			while(hsh[x][i]>=MOD[i]) hsh[x][i]-=MOD[i];
		}
		updAns(x,1);
		if(hsh[x][0]||hsh[x][1]) mp[{hsh[x][0],hsh[x][1]}]+=sz[x];
	}
} dsu;

void print()
{
	return;
	cout << "ARR: ";
	for(int i=0;i<4;i++)
		cout << arr[i] << " ";
	cout << endl;
	cout << "DATA: " << endl;
	for(int i=0;i<4;i++)
	{
		cout << dsu(i) << endl;
		cout << dsu.hsh[i][0] << " " << dsu.hsh[i][1] << endl;
		cout << dsu.sz[i] << " " << mp[{neg(dsu.hsh[i][0],0),neg(dsu.hsh[i][1],1)}] << endl;
	}
}

int main()
{
	pw[0][0]=pw[0][1]=1;
	for(int i=1;i<N;i++)
	{
		for(int j=0;j<H;j++)
			pw[i][j]=(1LL*BASE*pw[i-1][j])%MOD[j];
	}
	int n,q;
	scanf("%d %d",&n,&q);
	dsu.init(n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
		sor[i]=arr[i];
	}
	sort(sor,sor+n);
	for(int i=0;i<n;i++)
	{
		dsu.mod(i,arr[i],sor[i]);
	}
	while(q--)
	{
		print();
		int t;
		scanf("%d",&t);
		if(t==2)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			x--; y--;
			dsu(x,y);
		}
		else if(t==1)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			x--; y--;
			int ox=x,oy=y;
			swap(arr[x],arr[y]);
			x=dsu(x); y=dsu(y);
			if(x==y) continue;
			dsu.mod(x,arr[ox],arr[oy]);
			dsu.mod(y,arr[oy],arr[ox]);
		}
		else if(t==3)
		{
			//cout << bad << endl;
			printf("%s\n",(bad==0?"DA":"NE"));
		}
		else
		{
			printf("%lld\n",ans4);
		}
	}
}
