#define  _CRT_SECURE_NO_WARNINGS
#if 0
#include<iostream>
#include<fstream>
using namespace std;
void test(){
	ifstream file("test.txt", ios::binary);
	char p[100];
	file.read(p, 10);
	for (auto& e : p)
		cout << e;
	cout << endl;
	//cout << file.gcount();
	ifstream f0("test.txt", ios::out);
	char* ch = "0x123456";
	cout.write( ch, 5);

}

int main(){
	test();
	return 0;
}
#endif
#include<iostream>
#include<map>
using namespace std;
struct LCA{
	// 用哈希表记录下任意两个节点的最近公共祖先
	map<int, map<int, int>>mp;
	// 初始化，每个节点都成为这个map的一个键
	void initMap(int root, int* lc, int* rc)
	{
		if (!root) return;
		map<int, int>map_;
		mp.insert(make_pair(root, map_));
		initMap(lc[root], lc, rc);
		initMap(rc[root], lc, rc);
	}
	// 填完整这张表
	void setMap(int root, int* lc, int* rc)
	{
		if (!root) return;
		// 任意节点h和它的后代节点的LCA是h
		headRecord(lc[root], root, lc, rc);
		headRecord(rc[root], root, lc, rc);
		// h的左子树的每个节点和h右子树的每个节点的LCA是h
		subRecord(root, lc, rc);
		// 对每个结点均按此要求来填表
		setMap(lc[root], lc, rc);
		setMap(rc[root], lc, rc);
	}
	void headRecord(int n, int h, int* lc, int* rc)
	{
		if (!n) return;
		mp[n].insert(make_pair(h, h));
		headRecord(lc[n], h, lc, rc);
		headRecord(rc[n], h, lc, rc);
	}
	void subRecord(int h, int* lc, int* rc)
	{
		if (!h) return;
		preLeft(lc[h], rc[h], h, lc, rc);
		subRecord(lc[h], lc, rc);
		subRecord(rc[h], lc, rc);
	}
	void preLeft(int l, int r, int h, int* lc, int* rc)
	{
		if (!l) return;
		preRight(l, r, h, lc, rc);
		preLeft(lc[l], r, h, lc, rc);
		preLeft(rc[l], r, h, lc, rc);
	}
	void preRight(int l, int r, int h, int* lc, int* rc)
	{
		if (!r) return;
		mp[l].insert(make_pair(r, h));
		preRight(l, lc[r], h, lc, rc);
		preRight(l, rc[r], h, lc, rc);
	}
	int query(int a, int b)
	{

		if (mp[a].find(b) != mp[a].end())
			return mp[a][b];
		if (mp[b].find(a) != mp[b].end())
			return mp[b][a];
	}
};
int main()
{
	int n, root;
	//cin>>n>>root;
	scanf("%d %d", &n, &root);
	int p;
	int* lc = new int[n + 1];
	int* rc = new int[n + 1];
	for (int i = 0; i<n; ++i)
	{
		scanf("%d", &p);
		scanf("%d %d", &lc[p], &rc[p]);
	}
	LCA* lca = new LCA();
	lca->initMap(root, lc, rc);
	lca->setMap(root, lc, rc);
	int m;
	//cin>>m;
	scanf("%d", &m);
	int a, b;
	while (m--)
	{
		//cin>>a>>b;
		//cout<<LCA(root,lc,rc,a,b)<<endl;
		scanf("%d %d", &a, &b);
		printf("%d\n", lca->query(a, b));
	}
	return 0;
}