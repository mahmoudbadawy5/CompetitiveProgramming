/*
N*K <= 3*10^4 means min(n,k)<=sqrt(3*10^4)

We can solve it in two cases:
-if n is small enough we can do n^2*k check by iterating over all two strings and check if they differ in atmost two places.
-otherwise k will be small and we can try all possible two characters and check if there's a string with the same charachters
except these two. This can be done in O(n*k^2) using hashing.

The problem has a very tight TL. You need to optimize very well. Hashing using modulo won't pass you can make your modulo = 2^64
by using unsigned long long and let it overflow.
*/

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

const int SQ=170,N=2e4+1;
const int M1=1e9+9,M2=1e9+7,B=131;

string arr[N];
char tmp[N];
int n,k;

void n2k()
{
    for(int i=0;i<n;i++)
    {
        int cur=0;
        for(int j=0;j<n;j++)
        {
            if(i==j) continue;
            int dif=0;
            for(int l=0;l<k;l++)
                dif+=arr[i][l]!=arr[j][l];
            cur|=(dif<=2);
        }
        putchar(cur+'0');
    }
    puts("");
}

int ans[N];
unsigned long long pw[N],hsh[N];

void nk2()
{
   // vector<int> hs[N];
    pw[0]=1;
    for(int i=1;i<=k;i++)
        pw[i]=B*pw[i-1];
    for(int i=0;i<n;i++) ans[i]=0;
    for(int i=0;i<n;i++)
    {
        long long curh=0;
        for(int j=0;j<k;j++)
        {
            curh*=B; curh+=arr[i][j];
            //curh%=M1;
        }
        hsh[i]=curh;
    }
    
    for(int x=0;x<k;x++)
    {
        for(int y=x+1;y<k;y++)
        {
            unordered_map< unsigned long long , int > mp;
            for(int i=0;i<n;i++)
            {
                unsigned long long h1=hsh[i]-arr[i][x]*pw[k-x-1]-arr[i][y]*pw[k-y-1];
                int &cur=mp[h1];
                if(cur)
                    ans[i]=ans[cur-1]=1;
                cur=i+1;
            }
        }
    }
    for(int i=0;i<n;i++)
        putchar(ans[i]+'0');
    putchar('\n');
}

int main() {
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&k);
        for(int i=0;i<n;i++)
        {
            scanf("%s",tmp);
            arr[i]=tmp;
        }
        if(k<=2)
            puts(string('1',n).c_str());
        else if(n<=SQ) n2k();
        else nk2();
    }
    return 0;
}
