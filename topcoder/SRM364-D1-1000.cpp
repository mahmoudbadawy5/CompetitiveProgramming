/*
It can be proved that every from the right will get the first present he didn't get. The last one can get his first present by swapping with the one who has it. The one before him won't try to get it as he knows that it will be taken from him that's why he will take the first present that's not taken by anyone in front of him. Now we need to find the lexcographically smallest moves that leads to this string. We can build the prefix a move by move and see if that prefix can lead to a result or not by seeing if the rest of swaps are sufficient to lead to the result or not.
*/

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


bool can(string seq,string ans)
{
	string cur="";
	int n=ans.size();
	int pos[26];
	for(int i=0;i<n;i++)
	{
		cur+='A'+i;
		pos[i]=i;
	}
	for(int i=0;i<seq.size();i++)
	{
		if(seq[i]=='-') continue;
		// i,seq[i]
		int to=seq[i]-'a';
		swap(cur[i],cur[to]);
		swap(pos[cur[i]-'A'],pos[cur[to]-'A']);
	}
	for(int i=seq.size();i<n;i++)
	{
		// I need to be ans[i]
		// If cur[i] != ans[i] I'll swap with the holder of ans[i]
		int goal=ans[i]-'A';
		if(cur[i]==ans[i]) continue;
		int to=pos[goal];
		swap(cur[i],cur[to]);
		swap(pos[cur[i]-'A'],pos[cur[to]-'A']);
	}
	return (cur==ans);
}

class YankeeSwap {
public:
	string sequenceOfSwaps(vector <string> pre) {
		string res="";
		int got[26]={0};
		int n=pre.size();
		for(int i=n-1;i>=0;i--)
		{
			for(int j=0;j<n;j++)
			{
				if(!got[pre[i][j]-'A'])
				{
					got[pre[i][j]-'A']=1;
					res+=pre[i][j];
					break;
				}
			}
		}
		reverse(res.begin(),res.end());
		//cout << res << endl;
		string ch="-";
		for(int i=0;i<n;i++) ch+='a'+i;
		string ans="";
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<ch.size();j++)
			{
				if(can(ans+ch[j],res))
				{
					ans+=ch[j]; break;
				}
			}
		}
		return ans;
	}
};


<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
