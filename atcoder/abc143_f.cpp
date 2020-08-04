/*
  -Same as editorial: https://img.atcoder.jp/abc143/editorial.pdf
*/

#include <bits/stdc++.h>

using namespace std;

const int N=3e5+5;

int co[N],ans[N];
int n;

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		co[x]++;
	}
	sort(co+1,co+n+1);
	int l=1,curs=0;
	for(int i=1;i<=n;i++)
	{
		while(l<=n&&co[l]<i) curs+=co[l++];
		ans[i]=(curs+(n-l+1)*i)/i;
	}
	ans[0]=(1<<30);
	l=n;
	for(int i=1;i<=n;i++)
	{
		while(ans[l]<i) l--;
		printf("%d\n",l);
	}
}
