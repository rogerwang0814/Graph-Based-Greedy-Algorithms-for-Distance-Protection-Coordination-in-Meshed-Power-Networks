#include <bits/stdc++.h>
using namespace std;

struct dedge{
	int l,r;
	double val;
} es[200010],es2[200010];

vector<int> e[20010];
int vis[200010],chs[200010];

void dfsv(int pos,double vl,int from){
	if (vl<0.6) return;
	vis[pos]=1;
	//cout<<pos<<"\n";
	for (auto x:e[pos]){
		if (es[x].val!=0) continue;
		bool got=0;
		if (!vis[es[x].r] && (from==-1 || x-1!=((from-1)^1))){
			es[x].val=vl;got=1;
		}
		else if (vis[es[x].r]){
			es[x].val=vl;
		}
		if (!vis[es[x].r] && (from==-1 || x-1!=((from-1)^1)) && got) dfsv(es[x].r,vl-0.2,x);
	}
}

signed main(){
	int n,m;cin>>n>>m;
	for (int i=1;i<=m;i++){
		int a,b;cin>>a>>b;
		e[a].push_back(i*2-1);e[b].push_back(i*2);
		es[i*2-1].l=a;es[i*2-1].r=b;es[i*2-1].val=0;
		es[i*2].r=a;es[i*2].l=b;es[i*2].val=0;
	}
	srand(time(NULL));
	int ans[3]={};
	for (int z=1;z<=n*n*n;z++){
		for (int i=1;i<=n;i++){
			chs[i]=0;
		}
		for (int i=1;i<=m*2;i++) es[i].val=0;
		for (int i=1;i<=n;i++){
			int k=rand()%(n-i+1)+1;
			int ct=0,ind=0;
			for (int j=1;j<=n;j++){
				if (chs[j]==0) ct++;
				if (ct==k){
					chs[j]=1;
					ind=j;break;
				}
			}
			//cout<<ind<<' ';
			for (int j=1;j<=n;j++) vis[j]=0;
			//cout<<"s "<<ind<<"\n";
			dfsv(ind,1.8,-1);
		}
		int now[3]={};
		for (int i=1;i<=m*2;i++){
			bool t0=0,t1=1;
			for (int j=1;j<=m*2;j++){
				if (es[j].r==es[i].l && es[j].l!=es[i].r){
					if (es[j].val>=es[i].val+0.2) t0=1;
					else t1=0;
				}
			}
			if (t0==1 && t1==1) now[0]++;
			else if (t0==1 && t1==0) now[1]++;
			else now[2]++;
		}
		if (now[0]>ans[0] || (now[0]==ans[0] && now[1]>ans[1])){
			ans[0]=now[0];ans[1]=now[1];ans[2]=now[2];
			for (int i=1;i<=m*2;i++){
				es2[i]=es[i];
			}
		}
		//cout<<"\n";
	}
	cout<<ans[0]<<' '<<ans[1]<<' '<<ans[2]<<"\n";
	double mn=1e9;
	for (int j=1;j<=m*2;j++){
		mn=min(es[j].val,mn);
	}
	mn-=0.6;mn=max(0.0,mn);
	for (int i=1;i<=m*2;i++){
		es[i].val-=mn;
		cout<<es[i].l<<' '<<es[i].r<<' '<<es[i].val<<"\n";
	}
}