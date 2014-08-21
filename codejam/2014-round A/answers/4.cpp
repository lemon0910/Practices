#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<iostream>
#include<algorithm>
#include<memory>
#include<map>
#include<queue>
#include <set>
using namespace std;
typedef pair<int,int> PII;
void adjust(PII &A){
	if (A.first > A.second)
		swap(A.first, A.second);
}
int main(){
	int tt;
	int N, M;
	cin >> tt;
	for (int tcas = 1; tcas <= tt; ++tcas){
		cin >> N >> M;
		multiset<PII> se;
		vector<int> goods;
		goods.resize(N);
		for (int i = 0; i < N; i++)
			scanf("%d",&goods[i]);
		sort(goods.begin(), goods.end(), std::greater<int>());
		int result = 0;
		for (int i = 0; i < N; i++){
			int cur = goods[i];
			int board = (1<<cur);
			auto ptr = se.lower_bound(PII(1<<cur, 1<<cur));
			PII box;
			if (ptr == se.end()){
				//need a new one;
				box = PII(M, M);
				result ++;
			}else {
				box = *ptr;
				se.erase(ptr);
			}
			PII box1, box2;
			box1.first = box.first;
			box1.second = box.second - board;
			box2.first = box.first - board;
			box2.second = board;
			adjust(box1);
			adjust(box2);
			se.insert(box1);
			se.insert(box2);
		}
		printf("Case #%d: ", tcas);
		cout << result <<endl;
	}
}