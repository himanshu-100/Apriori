/*
	Author: @himkha_100
	Himanshu Khandelwal, NITW
*/
#include<bits/stdc++.h>
#define MOD 1000000007
#define ll long long int
#define s(t) scanf("%d",&t)
#define p(t) printf("%d\n",t)
#define pb push_back
#define f(t) for(int i=0;i<t;i++)
#define fi first
#define se second
#define all(t) t.begin(),t.end()
#define ci(t) cin>>t
#define co(t) cout<<t
#define mii map<int,int>
#define pii pair<int,int>
using namespace std;
struct node{
	int val;
	int pos;
};
bool ac(int x,int y)
{
	return x>y;
}
int main()
{
	srand(time(0));
	ofstream out;
	out.open("transaction.txt");
	int st=rand()%10+150;
	int size=rand()%10+75;
	for(int i=st;i<=st+size;i++)
	{
		out<<i<<" ";
		vector<int> r;
		ll num=rand();
		for(int j=0;j<18;j++)
		{
			if(num&(1ll<<j))
			{
				r.pb(j+1);
			}
		}
		f(r.size())
		{
			out<<r[i]<<" ";
		}out<<endl;
	}
	out.close();
	return 0;
}


