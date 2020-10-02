/*
  Same as editorial: https://codeforces.com/blog/entry/23522
*/

#include <bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

int mem[205][205][1005];
int n,k;
int arr[205];

int go(int ind,int op,int bl)
{
	if(bl>k) return 0;
	if(ind>=n) return (op==0);
	int &ret=mem[ind][op][bl];
	if(ret!=-1) return ret;
	ret=0;
	int cbl=bl+op*(ind?arr[ind]-arr[ind-1]:0);
	ret+=go(ind+1,op+1,cbl);
	if(ret>=MOD) ret-=MOD;
	ret+=(1LL*go(ind+1,op,cbl)*(op+1))%MOD;
	if(ret>=MOD) ret-=MOD;
	if(op) ret+=(1LL*op*go(ind+1,op-1,cbl))%MOD;
	if(ret>=MOD) ret-=MOD;
	return ret;
}

int main()
{
	scanf("%d %d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	sort(arr,arr+n);
	memset(mem,-1,sizeof mem);
	cout << go(0,0,0) << endl;
}
