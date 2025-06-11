struct Node{
	int value;
};
class WakeMeUp {
public:
	vector<Node> values;
	int sz;
	Node NEUTRAL = {0};
	WakeMeUp(vector<int>&a) {
		sz = 1;
		int n = a.size();
		while(sz<n)
			sz <<= 1;
		values.resize(2*sz+1);
		build(a);
	}
	Node single(int v) {
		return {v};
	}
	Node merge(Node a, Node b) {
		return {a.value + b.value};
	}
	void build(vector<int> &a) {
		build(a, 0, 0, sz);
	}
	void build(vector<int>& a, int x, int lx, int rx) {
		if(rx - lx == 1) {
			if(lx < a.size())
				values[x] = single(a[lx]);
			return;
		}
		int m = lx+rx>>1;
		build(a, 2*x+1, lx, m);
		build(a, 2*x+2, m, rx);
		values[x] = merge(values[2*x+1], values[2*x+2]);
	}
	void pointSet(int i, int v) {
		pointSet(i, v, 0, 0, sz);
	}
	void pointSet(int i, int v, int x, int lx, int rx) {
		if(rx - lx == 1) {
			values[x] = single(v);
			return;
		}
		int m = lx+rx>>1;
		if(i < m)
			pointSet(i, v, 2*x+1, lx, m);
		else
			pointSet(i, v, 2*x+2, m, rx);
		values[x] = merge(values[2*x+1], values[2*x+2]);
	}
	Node get(int l, int r) {
		return get(l, r, 0, 0, sz);
	}
	Node get(int l, int r, int x, int lx, int rx) {
		if(lx>=r || rx <= l)
			return NEUTRAL;
		if(lx>=l && rx<=r)
			return values[x];
		int m = lx+rx>>1;
		Node leftPart = get(l, r, 2*x+1, lx, m);
		Node rightPart= get(l, r, 2*x+2, m, rx);
		return merge(leftPart, rightPart);
	}
};
