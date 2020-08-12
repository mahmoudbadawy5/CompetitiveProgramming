/*
We can solve it using meet in the middle. If for some subset x in the first middle we could split it into two subsets and the sifference in sum between them was d then
any subset in the other half that can be split with difference = -d can be paired with it to make a good subset. So we can just loop over all subsets of each half and
try to match them. Optimizations needed to pass this problem as O(2^(n/2)*3^(n/2) * log(3^(n/2)) didn't pass and passed without the log.
*/

#include <bits/stdc++.h>

using namespace std;

int n;
int arr[22];
int sum[(1<<20)];
vector<int> got[(1<<20)];
//unordered_map<int,int> got[(1<<20)];

int main()
{
	cin >> n;
	for(int i=0;i<n;i++) cin >> arr[i];
	for(int i=1;i<(1<<n);i++)
	{
		for(int j=0;j<n;j++)
			if(i&(1<<j)) sum[i]+=arr[j];
	}
	int ans=0;
	for(int i=1;i<(1<<(n/2+n%2));i++)
	{
		int isok=0;
		for(int j=i;j;j=(j-1)&i)
		{
			isok|=(sum[j]==sum[i^j]);
			got[i].push_back(sum[j]-sum[i^j]);
		}
		got[i].push_back(-sum[i]);
		sort(got[i].begin(),got[i].end());
		ans+=isok;
	}
	for(int t=1;t<(1<<(n/2));t++)
	{
		int i=t<<(n/2+n%2);
		int isok=0;
		vector<int> ds;
		for(int j=i;j;j=(j-1)&i)
		{
			ds.push_back(sum[i^j]-sum[j]);
			isok|=(sum[i^j]==sum[j]);
		}
		sort(ds.begin(),ds.end());
		for(int k=1;k<(1<<(n/2+n%2));k++)
		{
			int x=0;
			for(int j:ds)
			{
				while(x<got[k].size()&&got[k][x]<j) x++;
				if(x<got[k].size() && got[k][x]==j) {ans++; break;}
			}
		}
		ans+=isok;
	}
	cout << ans << endl;
}
