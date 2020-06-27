/*
  -Same as: https://github.com/stefdasca/CompetitiveProgramming/blob/master/COCI/COCI%2015-Endor.cpp
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

struct data{
	int pos,col;
	char type;
};

data arr[N];
int n,k,l;
long long sum[44][2],pos[44][2],cnt[44][2];
long long ans[44];

int main()
{
	scanf("%d %d %d",&n,&k,&l);
	for(int i=0;i<n;i++)
	{
		cin >> arr[i].pos >> arr[i].col >> arr[i].type;
	}
	for(int i=n-1;i>=0;i--)
	{
		if(arr[i].type=='L')
		{
			sum[arr[i].col][0]+=arr[i].pos;
			pos[arr[i].col][0]+=arr[i].pos*2;
			cnt[arr[i].col][0]++;
		}
		else
		{
			ans[arr[i].col]+=(l-arr[i].pos)*2;
			for(int c=0;c<k;c++)
			{
				long long inter=cnt[c][0]*arr[i].pos+sum[c][0];
				ans[c]+=pos[c][0]-inter;
				int nc=(c+arr[i].col)%k;
				sum[nc][1]=sum[c][0];
				cnt[nc][1]=cnt[c][0];
				pos[nc][1]=inter;
			}
			for(int c=0;c<k;c++)
			{
				sum[c][0]=sum[c][1]; cnt[c][0]=cnt[c][1]; pos[c][0]=pos[c][1];
			}
		}
	}
	for(int c=0;c<k;c++)
		ans[c]+=pos[c][0];
	for(int c=0;c<k;c++)
	{
		printf("%.1lf\n",ans[c]/2.0);
	}
}
