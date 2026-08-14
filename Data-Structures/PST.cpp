// Persistent Segment Tree
// pointSet: O(log N) new nodes per update
// get:      O(log N) point query / O(log N) or O(log N + k) range query depending on overlap
// Memory:   O(N + Q log N)
//
// Usage:
// WakeMeUp pst(a);
//
// pst.pointSet(i, v, ver);       // creates a NEW version based on version ver
// pst.pointSet(i, v);            // creates a NEW version based on latest version
//
// pst.get(l, r, ver).value;      // query [l, r) in version ver
// pst.get(i, ver).value;         // value at index i in version ver
//
// int latest = pst.roots.size() - 1;


// CHANGE: Node data + single() + merge() depending on the problem
struct Node {
	int value = 0;
	int left = 0, right = 0;

	Node() {}
	Node(int v) : value(v) {}
};

class WakeMeUp {
public:
	Node NEUTRAL = {0};

	vector<Node> values;
	vector<int> roots;

	int sz;

	WakeMeUp(vector<int>& a) {
		sz = 1;
		while(sz < a.size())
			sz <<= 1;

		values.reserve(2*sz + 40*a.size());
		roots.push_back(build(a, 0, sz));
	}

	Node single(int v) {
		return {v};
	}

	Node merge(Node a, Node b) {
		return {a.value + b.value}; // CHANGE
	}

	int newNode(Node v) {
		values.push_back(v);
		return values.size() - 1;
	}

	int build(vector<int>& a, int lx, int rx) {
		if(rx - lx == 1) {
			if(lx < a.size())
				return newNode(single(a[lx]));

			return newNode(NEUTRAL);
		}

		int m = lx+rx>>1;

		int left = build(a, lx, m);
		int right = build(a, m, rx);

		Node cur = merge(values[left], values[right]);
		cur.left = left;
		cur.right = right;

		return newNode(cur);
	}

	void pointSet(int i, int v) {
		pointSet(i, v, roots.size() - 1);
	}

	void pointSet(int i, int v, int ver) {
		roots.push_back(pointSet(i, v, roots[ver], 0, sz));
	}

	int pointSet(int i, int v, int x, int lx, int rx) {
		if(rx - lx == 1)
			return newNode(single(v));

		int m = lx+rx>>1;

		int left = values[x].left;
		int right = values[x].right;

		if(i < m)
			left = pointSet(i, v, left, lx, m);
		else
			right = pointSet(i, v, right, m, rx);

		Node cur = merge(values[left], values[right]);
		cur.left = left;
		cur.right = right;

		return newNode(cur);
	}

	Node get(int l, int r, int ver) {
		return get(l, r, roots[ver], 0, sz);
	}

	Node get(int l, int r, int x, int lx, int rx) {
		if(lx >= r || rx <= l)
			return NEUTRAL;

		if(lx >= l && rx <= r)
			return values[x];

		int m = lx+rx>>1;

		Node leftPart = get(l, r, values[x].left, lx, m);
		Node rightPart = get(l, r, values[x].right, m, rx);

		return merge(leftPart, rightPart);
	}

	Node get(int i, int ver) {
		return get(i, i+1, ver);
	}

	int kth(int l, int r, int k) {
		return kth(roots[l], roots[r + 1], k, 0, sz);
	}

	int kth(int leftRoot, int rightRoot, int k, int lx, int rx) {
		if(rx - lx == 1)
			return comp[lx];

		int leftCount =
			values[values[rightRoot].left].value -
			values[values[leftRoot].left].value;

		int m = lx + rx >> 1;

		if(k <= leftCount)
			return kth(
				values[leftRoot].left,
				values[rightRoot].left,
				k,
				lx,
				m
			);

		return kth(
			values[leftRoot].right,
			values[rightRoot].right,
			k - leftCount,
			m,
			rx
		);
	}
};
