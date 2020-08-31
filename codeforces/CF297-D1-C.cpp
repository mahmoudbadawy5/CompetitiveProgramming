/*
  Same as editorial: https://codeforces.com/blog/entry/7437
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int N=1e5+5;

pair<int,int> arr[N];
set<int> a,b;
int aa[N],bb[N],used[N];
int n;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i].F);
		arr[i].S=i;
	}
	sort(arr,arr+n);
	int cur=0;
	for(int i=0;i<n/3;i++)
	{
		aa[arr[i].S]=i; bb[arr[i].S]=arr[i].F-aa[arr[i].S];
		a.insert(arr[i].F); b.insert(0);
	}
	for(int i=n/3;i<2*n/3;i++)
	{
		bb[arr[i].S]=i; aa[arr[i].S]=arr[i].F-bb[arr[i].S];
		b.insert(arr[i].F); a.insert(0);
	}
	int x=arr[n/3].F;
	for(int i=2*n/3;i<n;i++)
	{
		bb[arr[i].S]=n-i-1; aa[arr[i].S]=arr[i].F-bb[arr[i].S];
		a.insert(aa[arr[i].S]);
		b.insert(bb[arr[i].S]);
	}
	cout << "YES" << endl;
	//assert(n-a.size()<=(n+2)/3 && n-b.size()<=(n+2)/3);
	for(int i=0;i<n;i++)
		printf("%d ",aa[i]);
	puts("");
	for(int i=0;i<n;i++)
		printf("%d ",bb[i]);
	puts("");
}
