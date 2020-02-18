/*
https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2008/contest6_solutions/solutions.pdf
*/

#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int a[N],b[N];
long long mem[N];
int n;

long long go(int x)
{
	if(x==n) return 0;
	if(mem[x]!=-1) return mem[x];
	int arr[3];
	mem[x]=(1LL<<60);
	for(int l=1;l<=min(3,n-x);l++)
	{
		for(int j=0;j<l;j++)
			arr[j]=a[j+x];
		do{
			bool ok=1;
			for(int j=0;j<l;j++)
				ok&=arr[j]!=b[j+x];
			if(!ok) continue;
			long long cur=0;
			for(int j=0;j<l;j++) cur+=abs(arr[j]-b[j+x]);
			mem[x]=min(mem[x],cur+go(x+l));
		} while(next_permutation(arr,arr+l));
	}
	return mem[x];
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d %d",&a[i],&b[i]);
	sort(a,a+n); sort(b,b+n);
	memset(mem,-1,sizeof mem);
	cout << go(0) << endl;
}
