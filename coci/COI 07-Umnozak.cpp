/*
 - https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2008/olympiad_solutions/solutions.pdf
 */
 
 #include <bits/stdc++.h>

using namespace std;

const int N=1e9;

unordered_map<int,int> cmp;
long long mem[18][6005][2];
int vis[18][6005][2],visid;
long long pw9[19];
string s;
long long a,b;
vector<int> v;

long long poww(long long b,int x)
{
	long long ans=1;
	for(int i=0;i<x;i++)
		ans*=b;
	return ans;
}

void init(long long x,int ind)
{
	s="";
	while(x)
	{
		s+=x%10+'0';
		x/=10;
	}
	reverse(s.begin(),s.end());
	visid++;
}

long long go(int ind,int p,int is)
{
	//cout << ind << " " << p << " " << is << endl;
	if(ind>=s.size())
		return p==1;
	if(p>pw9[s.size()-ind]) return 0;
	int c=cmp[p];
	long long &ret=mem[ind][c][is];
	if(vis[ind][c][is]==visid) return ret;
	vis[ind][c][is]=visid;
	ret=0;
	for(int i=1;i<=(is?9:s[ind]-'0');i++)
	{
		if(p%i) continue;
		ret+=go(ind+1,p/i,is|(i<s[ind]-'0'));
	}
	return ret;
}

int main()
{
	cin >> a >> b;
	for(int a2=0;a2<=30;a2++)
	{
		for(int a3=0;a3<=19;a3++)
		{
			for(int a5=0;a5<=13;a5++)
			{
				for(int a7=0;a7<=11;a7++)
				{
					long long cur=poww(2,a2);
					if(cur>N) continue;
					cur*=poww(3,a3);
					if(cur>N) continue;
					cur*=poww(5,a5);
					if(cur>N) continue;
					cur*=poww(7,a7);
					if(cur>N) continue;
					v.push_back(cur);
				}
			}
		}
	}
	pw9[0]=1;
	for(int i=1;i<19;i++) pw9[i]=pw9[i-1]*9;
	sort(v.begin(),v.end());
	for(int i=0;i<v.size();i++)
		cmp[v[i]]=i;
	long long ans=0;
	for(int i=0;i<v.size();i++)
	{
		if(b/v[i]>0){
			init(b/v[i],i);
			for(int j=0;j<s.size();j++) ans+=go(j,v[i],(j!=0));
		}
		if(a/v[i]-(a%v[i]==0)>0){
			init(a/v[i]-(a%v[i]==0),i);
			for(int j=0;j<s.size();j++) ans-=go(j,v[i],(j!=0));
		}
	}
	cout << ans << endl;
}
