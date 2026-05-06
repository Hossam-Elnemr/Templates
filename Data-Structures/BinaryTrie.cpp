struct BinaryTrie {
    struct Node {
        int child[2];
        int pre, cnt;
        Node() {
            child[1] = child[0] = 0;
            pre = 0; // how many inserted numbers use that prefix path
            cnt = 0; // how many numbers end exactly at this node
        }
    };
    vector<Node> nodes;
 
    BinaryTrie() {
        nodes.push_back(Node());
    }
 
    void insert(int num) {
        int node = 0;
        for (int i = 30; i>=0; --i) {
            int bit = num >> i & 1;
            if (nodes[node].child[bit] == 0) {
                nodes.push_back(Node());
                nodes[node].child[bit] = (int)nodes.size() - 1;
            }
            node = nodes[node].child[bit];
            ++nodes[node].pre;
        }
        ++nodes[node].cnt;
    }
 
    void erase(int num) { // one occurence
        int prv = -1, node = 0;
        for (int i = 30; i>=0; --i) {
            int bit = num >> i & 1;
            prv = node;
            node = nodes[node].child[bit];
            --nodes[node].pre;
            if (nodes[node].pre == 0)
                nodes[prv].child[bit] = 0;
        }
        --nodes[node].cnt;
    }
 
    int get(int num) {
        int ans = 0, node = 0;
        for (int i = 30; i>=0; --i) {
            int target = num >> i & 1 ^ 1;
            if (nodes[node].child[target] != 0) {
                ans |= 1 << i;
                node = nodes[node].child[target];
            }
            else
                node = nodes[node].child[target ^ 1];
        }
 
        return ans;
    }
};
