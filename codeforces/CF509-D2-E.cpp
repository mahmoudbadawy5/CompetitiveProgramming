/*
We can calculate the answer for each vowel index independtly. Let's say for a length l it appeared in x segments of this length
that will add x/l to the total answer. How many times does a letter in position i appeared in a segment of length l?
it's min(l,n-l,i,n-i). We can split lengths to 3 parts. Ones with l<min(n-l,i,n-i) , ones with n-l < min(l,i,n-i)
and ones with min(i,n-i) <= min(l,n-l) and calculate them independtly
*/

#include <bits/stdc++.h>

using namespace std;

const int N=5e5+5;

double a[N],b[N];
int n;
string s;

int isv(char x)
{
	return (x=='A'||x=='E'||x=='I'||x=='O'||x=='U'||x=='Y');
}

int main()
{
	cin >> s;
	n=s.size();
	for(int i=1;i<=n;i++)
	{
		a[i]=1.0/i;
		a[i]+=a[i-1];
		b[i]=(n-i+1.0)/i;
		b[i]+=b[i-1];
	}
	double ans=0;
	for(int i=0;i<n;i++)
	{
		if(!isv(s[i])) continue;
		int mn=min(i+1,n-i);
		// min(len,mn,n-len)
		// len
		ans+=mn;
		// mn > n-len
		// len < n-mn
		ans+=b[n]-b[n-mn+1];
		ans+=mn*(a[n-mn+1]-a[mn]);
		//cout << mn << " " << b[n]-b[n-mn+1] << " " << a[n-mn+1]-a[mn] << endl;
	}
	cout << fixed << setprecision(10) << ans << endl;
}
