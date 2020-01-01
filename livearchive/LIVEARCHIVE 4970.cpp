/*
Try all possible matchings using dp with bitmasks. I still can't figure how is the formula derived but it seems like a kind of pattern.
https://math.stackexchange.com/questions/3270282/chess-board-knight-distance
*/

#include <bits/stdc++.h>

using namespace std;

long long mem[(1<<15)];
int vis[(1<<15)];
long long a[15],b[15],x[15],y[15];
int n,tc;

long long dist(long long x,long long y)
{
	// I can't get why is this
	if(x+y==1) return 3;
	if(x==2&&y==2) return 4;
	long long md=max(max((x+1)/2,(y+1)/2),(x+y+2)/3);
	return md+((md+x+y)%2);
}

long long go(int mas)
{
	if(mas==(1<<n)-1) return 0;
	if(vis[mas]==tc)
		return mem[mas];
	vis[mas]=tc;
	int ind=__builtin_popcount(mas);
	mem[mas]=(1LL<<60);
	for(int i=0;i<n;i++)
	{
		if(mas&(1<<i)) continue;
		mem[mas]=min(mem[mas],go(mas|(1<<i))+dist(llabs(a[ind]-x[i]),llabs(b[ind]-y[i])));
	}
	return mem[mas];
}

int main()
{
	tc++;
	while(true)
	{
		scanf("%d",&n);
		if(!n) break;
		for(int i=0;i<n;i++)
			scanf("%lld %lld",&a[i],&b[i]);
		for(int i=0;i<n;i++)
			scanf("%lld %lld",&x[i],&y[i]);
		printf("%d. %lld\n",tc++,go(0));
	}
}
