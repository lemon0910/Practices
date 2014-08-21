#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<iostream>
#include<algorithm>
#include<memory>
#include<map>
#include<queue>
using namespace std;
#define maxn 30
int N,mp[maxn][maxn],outs[maxn][maxn];
char dir[10];
int main(){
	int tt;
	int i,j,k;
	cin >> tt;
	for (int tcas = 1; tcas <= tt; ++tcas){
		memset(mp,0,sizeof(mp));
		memset(outs,0,sizeof(outs));
		scanf("%d%s",&N,dir);
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				scanf("%d",&mp[i][j]);
			}
		}
		if(dir[0]=='u'){
			for(i=0;i<N-1;i++){
				for(j=0;j<N;j++){
					if(mp[i][j]==0)continue;
					k=i+1;
					while(k<N&&mp[k][j]==0)k++;
					if(mp[i][j]==mp[k][j]){
						mp[i][j]*=2;
						mp[k][j]=0;
					}
				}
			}
			for(j=0;j<N;j++){
				k=0;
				for(i=0;i<N;i++){
					if(mp[i][j])outs[k++][j]=mp[i][j];
				}
			}
		}
		if(dir[0]=='r'){
			for(j=N-1;j>0;j--){
				for(i=0;i<N;i++){
					if(mp[i][j]==0)continue;
					k=j-1;
					while(k>=0&&mp[i][k]==0)k--;
					if(k>=0&&mp[i][j]==mp[i][k]){
						mp[i][j]*=2;
						mp[i][k]=0;
					}
				}
			}
			for(i=0;i<N;i++){
				k=N-1;
				for(j=N-1;j>=0;j--){
					if(mp[i][j])outs[i][k--]=mp[i][j];
				}
			}
		}
		if(dir[0]=='d'){
			for(i=N-1;i>0;i--){
				for(j=0;j<N;j++){
					if(mp[i][j]==0)continue;
					k=i-1;
					while(k>=0&&mp[k][j]==0)k--;
					if(k>=0&&mp[i][j]==mp[k][j]){
						mp[i][j]*=2;
						mp[k][j]=0;
					}
				}
			}
			for(j=0;j<N;j++){
				k=N-1;
				for(i=N-1;i>=0;i--){
					if(mp[i][j])outs[k--][j]=mp[i][j];
				}
			}
		}
		if(dir[0]=='l'){
			for(j=0;j<N-1;j++){
				for(i=0;i<N;i++){
					if(mp[i][j]==0)continue;
					k=j+1;
					while(k<=N&&mp[i][k]==0)k++;
					if(mp[i][j]==mp[i][k]){
						mp[i][j]*=2;
						mp[i][k]=0;
					}
				}
			}
			for(i=0;i<N;i++){
				k=0;
				for(j=0;j<N;j++){
					if(mp[i][j])outs[i][k++]=mp[i][j];
				}
			}
		}
		printf("Case #%d:\n", tcas);
		for(i=0;i<N;i++){
			for(j=0;j<N-1;j++){
				printf("%d ",outs[i][j]);
			}
			printf("%d\n",outs[i][N-1]);
		}
		
	}
	return 0;
}