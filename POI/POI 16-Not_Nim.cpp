/*
  Same as: https://github.com/thecodingwizard/competitive-programming/blob/master/POI/POI16-Not_Nim.cpp
*/

#include <bits/stdc++.h>

using namespace std;

const int N=5e5+5;

int n;
int arr[N];

int lg(int x)
{
	int ans=0;
	while(x){ans++; x/=2;}
	return ans-1;
}

int ldo(int x)
{
	int cur=0;
	for(int i=30;i>=0;i--)
	{
		if(x&(1<<i))
		{
			cur++;
		}
		else if(cur) return cur;
	}
}

int main()
{
	cin >> n;
	int ans=-1;
	for(int i=0;i<n;i++)
	{
		cin >> arr[i];
		ans+=2*lg(arr[i])+4;
	}
	priority_queue<int> q;
	for(int i=0;i<n;i++)
	{
		q.push(ldo(arr[i]));
	}
	q.pop();
	while(q.size())
	{
		int x=q.top(); q.pop();
		if(x==1)
		{
			ans-=2;
		}
		else
		{
			q.push(x-1);
			q.pop();
		}
	}
	cout << ans << endl;
}
