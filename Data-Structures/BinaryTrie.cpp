struct Node {
    Node* links[2];
    int countPrefix = 0;
    bool containsKey(int bit) {
        return links[bit] != nullptr;
    }
    Node* get(int bit) {
        return links[bit];
    }
    void put(int bit, Node* node) {
        links[bit] = node;
    }
    void increasePrefix() {
        ++countPrefix;
    }
    void decreasePrefix() {
        --countPrefix;
    }
    int getPrefxix() {
        return countPrefix;
    }
};
class BinaryTrie {
    Node *root;
public:
    BinaryTrie() {
        root = new Node();
    }
    void insert(int num) {
        Node *node = root;
        for (int i = 31; i>=0; --i) {
            int bit = num>>i & 1;
            if (!node->containsKey(bit))
                node->put(bit, new Node());
            node = node->get(bit);
            node->increasePrefix();
        }
    }
    void erase(int num) {
        Node *node = root;
        for (int i = 31; i>=0; --i) {
            int bit = num>>i & 1;
            node = node->get(bit);
            node->decreasePrefix();
        }
    }
    int getMaxXor(int num) {
        Node *node = root;
        int ans = 0;
        for (int i = 31; i>=0; --i) {
            int bit = num>>i & 1;
            Node* desiredNode = node->get(bit ^ 1);
            if (node->containsKey(bit ^ 1) && desiredNode->getPrefxix() > 0) {
                ans |= 1<<i;
                node = desiredNode;
            }
            else
                node = node->get(bit);
        }
        return ans;
    }
};
