/*
We know that the least occuring element will be the answer until it has the same count as the second one then they will increase
in altertaining order. We can binary search to know which elements will become equal after this query and then their count will
increase in the increasing order of their index. We can use ordered set to maintain their order by index.
*/

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

#include <bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

const int N=5e5+5;

pair<int,int> arr[N];
long long sum[N];
long long queries[N];
vector<pair<int,int> > qs[N];
int ans[N];
int n,m,q;

long long can(int x)
{
	return 1LL*arr[x].first*(x+1)-sum[x];
}

int main()
{
	scanf("%d %d %d",&n,&m,&q);
	for(int i=0;i<m;i++)
		arr[i].second=i+1;
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x); x--;
		arr[x].first++;
	}
	sort(arr,arr+m);
	for(int i=0;i<m;i++)
		sum[i]=arr[i].first+(i?sum[i-1]:0);
	for(int i=0;i<q;i++)
	{
		scanf("%lld",&queries[i]);
		queries[i]-=n;
		int st=0,en=m-1,ans=0;
		while(st<=en)
		{
			int mid=(st+en)/2;
			if(can(mid)<queries[i])
			{
				ans=mid; st=mid+1;
			}
			else en=mid-1;
		}
		queries[i]-=can(ans);
		queries[i]=(queries[i]-1+ans+1);
		queries[i]%=(ans+1);
		qs[ans].push_back({queries[i],i});
		//cout << ans << " " << can(ans) << endl;
	}
	ordered_set ss;
	for(int i=0;i<m;i++)
	{
		ss.insert(arr[i].second);
		for(auto j:qs[i])
		{
			ans[j.second]=(*ss.find_by_order(j.first));
		}
	}
	for(int i=0;i<q;i++)
		printf("%d\n",ans[i]);
}
