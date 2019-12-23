/*
rotate the points 45 degree (x,y) - > (x+y,x-y). Now the distance becomes a normal manhattan distance but each two steps in the new version is one step in the original problem. The distance now can be calculated using sorting + cumulative sum.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
long long x[N],y[N];
long long xs[N],ys[N],xsum[N],ysum[N];

int main()
{
	cin >> n;
	for(int i=0;i<n;i++)
	{
		long long a,b;
		cin >> a >> b;
		// rotate by 45 degrees
		x[i]=a+b; y[i]=a-b;
		xs[i]=x[i];
		ys[i]=y[i];
	}
	sort(xs,xs+n);
	sort(ys,ys+n);
	for(int i=0;i<n;i++)
	{
		xsum[i+1]=xs[i]+xsum[i];
		ysum[i+1]=ys[i]+ysum[i];
	}
	long long ans=(1LL<<60);
	for(int i=0;i<n;i++)
	{
		int p1=lower_bound(xs,xs+n,x[i])-xs,p2=lower_bound(ys,ys+n,y[i])-ys;
		p1++; p2++;
		long long cur=x[i]*p1-xsum[p1]+(xsum[n]-xsum[p1])-(n-p1)*x[i];
		cur+=y[i]*p2-ysum[p2]+(ysum[n]-ysum[p2])-(n-p2)*y[i];
		//cout << xsum[p1] << " " << xsum[n]-xsum[p2] << " " << ysum[p1] << " " << ysum[n]-ysum[p2] << endl;
		//cout << cur/2 << " ";
		ans=min(ans,cur);
	}
	cout << ans/2 << endl;
}
