/*
http://usaco.org/current/data/sol_sort_gold_open18.html
*/
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int bit[N];
pair<int,int> arr[N];
int n;

void upd(int x)
{
	for(;x<N;x+=x&(-x))
		bit[x]++;
}

int query(int x)
{
	int ans=0;
	for(;x>0;x-=x&(-x))
		ans+=bit[x];
	return ans;
}

int main()
{
	freopen("sort.in","r",stdin); freopen("sort.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i].first);
		arr[i].second=i+1; 
	}
	sort(arr,arr+n);
	int ans=1;
	for(int i=0;i<n;i++)
	{
		upd(arr[i].second);
		//cout << i+1 << " " << query(i+1) << endl;
		ans=max(ans,i+1-query(i+1));
	}
	cout << ans << endl;
}
