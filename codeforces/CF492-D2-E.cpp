/*
gcd(n,dx) =1 means that the length of the cycle the mod makes is exactly n. That gives us the option to choose a shifthing in a coordinate then a cycle of length n will happen between the two coordinates. So we can calculate the shfting we needs for every tree and find the shifthing that will pass through the most number of trees.
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e6+6;

vector<int> x,y;
int px[N],py[N];
int arr[N][2];
int n,m,dx,dy;
int sh[N];

int main()
{
	scanf("%d %d %d %d",&n,&m,&dx,&dy);
	int cx=0,cy=0;
	for(int i=0;i<n;i++)
	{
		x.push_back(cx); y.push_back(cy);
		px[cx]=i; py[cy]=i;
		cx=(cx+dx)%n; cy=(cy+dy)%n;
	}
	for(int i=0;i<m;i++)
	{
		scanf("%d %d",&arr[i][0],&arr[i][1]);
		int csh=px[arr[i][0]]-py[arr[i][1]];
		if(csh<0) csh+=n;
		//cout << csh << endl;
		sh[csh]++;
	}
	int mxans=0,mxsh=0;
	for(int i=0;i<n;i++)
	{
		if(sh[i]>mxans)
		{
			mxans=sh[i];
			mxsh=i;
		}
	}
	for(int i=0;i<m;i++)
	{
		int csh=px[arr[i][0]]-py[arr[i][1]];
		if(csh<0) csh+=n;
		if(csh==mxsh)
		{
			cout << arr[i][0] << " " << arr[i][1] << endl;
			/*for(int j=0;j<n;j++)
			{
				arr[i][0]+=dx; arr[i][1]+=dy;
				arr[i][0]%=n; arr[i][1]%=n;
				cout << arr[i][0] << " " << arr[i][1] << endl;
			}*/
			return 0;
		}
	}
}
