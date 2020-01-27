/*
First we count the numer of sequences with dp[last][cur] where last is the last number in the sequence and cur is the remaining number
We can replace last and cur with their index in the divisors list of n as any divisor of a divisor of n is a divisor of n.

Then we can build the solution by trying to put some number and if the number of ways to put this number is larger than k
we subtract this number from k and proceed to the next possible number.

It seems like the test data is weak as my solution should fail on the case 963761198400 1
*/

#include <bits/stdc++.h>

using namespace std;

vector<long long> divi;
vector< pair<int,int> > v[7505];
long long n,k;
int mem[3505][3505];

void calc(int x)
{
	int l=0,r=divi.size()-1;
	long long cur=divi[x];
	for(;l<divi.size();l++)
	{
		while(r>=0&&divi[l]*divi[r]>divi[x]) r--;
		if(r<0) break;
		if(l>r) break;
		if(divi[l]*divi[r]==divi[x])
			v[x].push_back({l,r});
	}
	v[x].push_back({x,0});
}

long long go(int las,int cur)
{
	if(cur==0) return 1;
	if(divi[las]>divi[cur]) return 0;
	if(mem[las][cur]!=-1) return mem[las][cur];
	mem[las][cur]=0;
	int z=lower_bound(v[cur].begin(),v[cur].end(),make_pair(las,-1))-v[cur].begin();
	z=max(z,1);
	for(int i=z;i<v[cur].size();i++)
	{
		if(divi[v[cur][i].first]<divi[las]) continue;
		mem[las][cur]+=go(v[cur][i].first,v[cur][i].second);
	}
	return mem[las][cur];
}

vector<long long> ans;

void build(int las,int cur,long long k)
{
	if(cur==0) return;
	int z=lower_bound(v[cur].begin(),v[cur].end(),make_pair(las,-1))-v[cur].begin();
	z=max(z,1);
	for(int i=z;i<v[cur].size();i++)
	{
		if(k>=go(v[cur][i].first,v[cur][i].second))
		{
			k-=go(v[cur][i].first,v[cur][i].second);
		}
		else
		{
			ans.push_back(divi[v[cur][i].first]);
			build(v[cur][i].first,v[cur][i].second,k);
			return;
		}
	}
}

int main()
{
	freopen("desc.in","r",stdin); freopen("desc.out","w",stdout);
	cin >> n >> k;
	for(long long i=1;i*i<=n;i++)
	{
		if(n%i) continue;
		divi.push_back(i);
		if(n/i!=i) divi.push_back(n/i); 
	}
	sort(divi.begin(),divi.end());
	cout << divi.size() << endl;
	for(int i=1;i<divi.size();i++)
	{
		calc(i);
	}
	memset(mem,-1,sizeof mem);
	cout << go(0,divi.size()-1) << endl;
	build(0,divi.size()-1,k-1);
	for(auto i:ans)
		cout << i << " ";
	cout << endl;
}
