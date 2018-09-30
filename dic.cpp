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
struct itemset{
	vector<int> items;
	int count;
	int start;
	int travc;
};
bool ac(int x,int y)
{
	return x>y;
}
vector<itemset> sc;			
vector<itemset> dc;
vector<itemset> ss;
vector<itemset> ds;
int cnum(string s)
{
	int num=0;
	f(s.length())
	{
		num=10*num+(s[i]-48);
	}
	return num;
}
vector<int> extract_items(string s)
{
	vector<int> temp;
	int ind=-1;
	f(s.length()){
		if(s[i]==' '){
			ind=i;break;
		}
	}
	int st=ind+1;
	for(int i=ind+1;i<s.length();i++){
		if(s[i]==' '){
			temp.pb(cnum(s.substr(st,i-st)));
			st=i+1;
		}
	}
	return temp;
}
bool contains(vector<int> its, itemset x)
{
	bool flag=0;
	f(x.items.size())
	{
		int cnt=0;
		for(int j=0;j<its.size();j++)
		{
			if(x.items[i]==its[j])
			{
				cnt++;
			}
		}
		if(cnt==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==0) return true;
	else return false;
}
vector< vector<int> > generate_superset(itemset its)
{
	set<int> se;
	for(int i=1;i<=15;i++)
	{
		se.insert(i);
	}
	f(its.items.size())
	{
		se.erase(its.items[i]);
	}
	vector< vector<int> > ans;
	set<int>::iterator it;
	for(it=se.begin();it!=se.end();it++)
	{
		vector<int> d=its.items;
		d.pb(*it);
		sort(all(d));
		ans.pb(d);
	}
	return ans;
}
vector< vector<int> > generate_subset(vector<int> v)
{
	ll size=v.size();
	size=1ll<<size;
	vector< vector<int> > ans;
	for(ll z=1;z<size;z++)
	{
		vector<int> temp;
		for(int j=0;j<v.size()-1;j++)
		{
			if(z&(1ll<<j))
			{
				temp.pb(v[j]);
			}
		}
		ans.pb(temp);
	}
	return ans;
}
bool freq(vector<int> d)
{
	int fl=0;
	f(ds.size())
	{
		if(ds[i].items==d)
		{
			fl=1;
			break;
		}
	}
	f(ss.size())
	{
		if(ss[i].items==d)
		{
			fl=1;
			break;
		}
	}
	if(fl==0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool have(vector<int> d)
{
	int fl=0;
	f(ds.size())
	{
		if(ds[i].items==d)
		{
			fl=1;
			break;
		}
	}
	f(ss.size())
	{
		if(ss[i].items==d)
		{
			fl=1;
			break;
		}
	}
	f(dc.size())
	{
		if(dc[i].items==d)
		{
			fl=1;
			break;
		}
	}
	f(sc.size())
	{
		if(sc[i].items==d)
		{
			fl=1;
			break;
		}
	}
	if(fl==0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
int main()
{
	ifstream in;
	in.open("transaction.txt");
	ofstream out;
	out.open("ans.txt");
	string s;
	int ctxn=0;
	set<int> its1;
	int thres=8;
	while(getline(in,s))
	{
		vector<int> txn=extract_items(s);
		f(txn.size())
		{
			its1.insert(txn[i]);
		}
		ctxn++;
	}
	set<int>::iterator it;
	for(it=its1.begin();it!=its1.end();it++)
	{
		itemset temp;
		temp.items.pb(*it);
		temp.count=0;
		temp.start=0;
		temp.travc=0;
		dc.pb(temp);
	}
	int m=13;
	int r=0;
	int cpart=ctxn/m;
	itemset nul;
	nul.count=ctxn;
	nul.start=0;
	ss.pb(nul);
	int e=1;
	in.close();
	while(dc.size()>0||ds.size()>0)
	{
		in.open("transaction.txt");
		int lno=0;
		while(getline(in,s))
		{
			vector<int> its=extract_items(s);
			f(dc.size())
			{
				if(contains(its,dc[i]))
				{
					dc[i].count++;
				}
			}
			f(ds.size())
			{
				if(contains(its,ds[i]))
				{
					ds[i].count++;
				}
			}
			lno++;
			if(lno%m==0)
			{
				vector<int> pos;
				f(dc.size())
				{
					if(dc[i].count>=thres)
					{
						pos.pb(i);
						ds.pb(dc[i]);
						vector< vector<int> >superset=generate_superset(dc[i]);
						for(int j=0;j<superset.size();j++)
						{
							if(!have(superset[j]))
							{
								vector< vector<int> > subset=generate_subset(superset[j]);
								int flag=0;
								for(int k=0;k<subset.size();k++)
								{
									if(!freq(subset[k]))
									{
										flag=1;
										break;
									}
								}
								if(flag==0)
								{
									itemset temp;
									temp.count=0;
									temp.start=lno/m;
									temp.items=superset[j];
									temp.travc=e;
									dc.pb(temp);
								}
							}	
						}
					}
				}
				int eh=0;
				f(pos.size())
				{
					dc.erase(dc.begin()+pos[i]-eh);
					eh++;
				}
				vector<int> fill;
				f(dc.size())
				{
					if((dc[i].start==((lno/m)-1+m)%m&&dc[i].travc==e-1)||(dc[i].travc<=e-2))
					{
						fill.pb(i);
						sc.pb(dc[i]);
					}
				}
				eh=0;
				f(fill.size())
				{
					dc.erase(dc.begin()+fill[i]-eh);
					eh++;
				}
				fill.clear();
				f(ds.size())
				{
					if((ds[i].start==((lno/m)-1+m)%m&&ds[i].travc==e-1)||(ds[i].travc<=e-2))
					{
						fill.pb(i);
						ss.pb(ds[i]);
					}
				}
				eh=0;
				f(fill.size())
				{
					ds.erase(ds.begin()+fill[i]-eh);
					eh++;
				}
			}
		}
		e++;
		in.close();
	}
	out<<"Frequent itemsets are- \n";
	f(ss.size())
	{
		for(int j=0;j<ss[i].items.size();j++)
		{
			out<<ss[i].items[j]<<" ";	
		}out<<endl;
	}
	out.close();
	return 0;
}


