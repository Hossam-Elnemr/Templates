// NEUTRAL element
// Node: value, lazy, change()
// merge()
// propagate: values[x].lazy = operation identity

struct Node {
	int value = 0, lazy = 0;
	bool isLazy = 0;
	Node() {}
	Node(int v) : value(v) {}
	void change(int x, int l, int r) {
		value += x*(r-l);
		lazy += x;
		isLazy = true;
	}
};
class WakeMeUp {
public:
	Node NEUTRAL = {0};
	vector<Node> values;
	int sz;
	WakeMeUp(vector<int>& a) {
		sz = 1;
		int n = a.size();
		while(sz < n)
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
	void propagate(int x, int lx, int rx) {
		if(!values[x].isLazy || rx - lx == 1)
			return;
		int m = lx+rx>>1;
		values[2*x+1].change(values[x].lazy, lx, m);
		values[2*x+2].change(values[x].lazy, m, rx);
		values[x].isLazy = false;
		values[x].lazy = 0;
	}
	void build(vector<int>& a) {
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
	void set(int l, int r, int v) {
		set(l, r, v, 0, 0, sz);
	}
	void set(int l, int r, int v, int x, int lx, int rx) {
		propagate(x, lx, rx);
		if(lx>=r || rx<=l)
			return;
		if(lx>=l && rx<=r) {
			values[x].change(v, lx, rx);
			return;
		}
		int m = lx+rx>>1;
		set(l, r, v, x*2+1, lx, m);
		set(l, r, v, x*2+2, m, rx);
		values[x] = merge(values[x*2+1], values[x*2+2]);
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
		if(i<m)
			pointSet(i, v, x*2+1, lx, m);
		else
			pointSet(i, v, x*2+2, m, rx);
		values[x] = merge(values[2*x+1], values[2*x+2]);
	}
	Node get(int l, int r) {
		return get(l, r, 0, 0, sz);
	}
	Node get(int l, int r, int x, int lx, int rx) {
		propagate(x, lx, rx);
		if(lx>=r || rx<=l)
			return NEUTRAL;
		if(lx>=l && rx<=r)
			return values[x];
		int m = lx+rx>>1;
		Node leftPart = get(l, r, x*2+1, lx, m);
		Node rightPart = get(l, r, x*2+2, m ,rx);
		return merge(leftPart, rightPart);
	}
};
