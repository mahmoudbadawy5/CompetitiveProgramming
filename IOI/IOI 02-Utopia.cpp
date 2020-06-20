/*
We will solve it independtly for each dimension. Let's have n sorted numbers and we want to assign them signs such that
sum(arr[i]) have the desired sign. Let the number of times the sign doesn't change be co. we can reserve the smallest
(x+1) elements for these times. Each time the sign change we can use the next large number with the desired sign. What if it
stays the same? we can use the next smaller number from the reserved ones.
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

int arr[100005];
int sgn[100005];
int n;
vector<int> v;

void print(int x)
{
	if(x>0)
		printf("+");
	printf("%d",x);
}

int getsgn(int x)
{
	return x<0?-1:1;
}

void solve(int x)
{
	int co=0;
	for(int i=x;i+1<x+n;i++)
	{
		co+=sgn[i+1]==sgn[i];
	}
	int l=co-1+x,r=co+1+x;
	arr[co+x]*=sgn[x];
	for(int i=l;i>=0;i--)
		arr[i]*=((l-i)%2==0?-1:1)*sgn[x];
	for(int i=r;i<x+n;i++)
		arr[i]*=((i-r)%2==0?-1:1)*sgn[x];
	v.push_back(arr[co+x]);
	for(int i=1+x;i<n+x;i++)
	{
		if(sgn[i]==sgn[i-1])
		{
			v.push_back(arr[l--]);
		}
		else
		{
			v.push_back(arr[r++]);
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<2*n;i++) scanf("%d",&arr[i]);
	sort(arr,arr+n); sort(arr+n,arr+2*n);
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		if(x==1) sgn[i]=sgn[i+n]=1;
		else if(x==2) sgn[i]=-1,sgn[i+n]=1;
		else if(x==3) sgn[i]=sgn[i+n]=-1;
		else sgn[i]=1,sgn[i+n]=-1;
	}
	solve(0); solve(n);
	int x=0,y=0;
	for(int i=0;i<n;i++)
	{
		print(v[i]); printf(" "); print(v[i+n]); puts("");
		x+=v[i]; y+=v[i+n];
		assert(getsgn(x)==sgn[i]);
		assert(getsgn(y)==sgn[i+n]);
	}
}
