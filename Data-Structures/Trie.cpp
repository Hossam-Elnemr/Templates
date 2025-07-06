struct Node {
    Node* links[26];
    bool end = false;
    int countPrefix = 0, countEnds = 0;
    bool containsKey(char c) {
        return links[c - 'a'] != nullptr && links[c - 'a']->countPrefix > 0;
    }
    void put(char c, Node* node) {
        links[c - 'a'] = node;
    }
    Node* get(char c) {
        return links[c - 'a'];
    }
    void increasePrefix() {
        ++countPrefix;
    }
    void increaseEnds() {
        ++countEnds;
    }
    int getEnd() {
        return countEnds;
    }
    int getPrefix() {
        return countPrefix;
    }
    void decreasePrefix() {
        --countPrefix;
    }
    void decreaseWords() {
        --countEnds;
    }
    void setEnd() {
        end = true;
    }
    bool isEnd() {
        return end;
    }
};
class Trie {
    Node* root;
public:
    Trie() {
        root = new Node();
    }
    void insert(string word) {
        Node* node = root;
        for (int i = 0; i<word.length(); ++i) {
            if (!node->containsKey(word[i]))
                node->put(word[i], new Node());

            node = node->get(word[i]);
            node->increasePrefix();
        }
        node->setEnd();
        node->increaseEnds();
    }
    void erase(string word) {
        Node* node = root;
        for (int i = 0; i<word.length(); ++i) {
            if (!node->containsKey(word[i]))
                return;
            node = node->get(word[i]);

            node->decreasePrefix();
        }
        node->decreaseWords();
    }
    int countWordsEqualTo(string word) {
        Node* node = root;
        for (int i = 0; i<word.length(); ++i) {
            if (!node->containsKey(word[i]))
                return 0;
            node = node->get(word[i]);
        }
        return node->getEnd();
    }
    int countPrefixEqualTo(string word) {
        Node* node = root;
        for (int i = 0; i<word.length(); ++i) {
            if (!node->containsKey(word[i]))
                return 0;
            node = node->get(word[i]);
        }
        return node->getPrefix();
    }
    bool search(string word) {
        Node* node = root;
        for (int i = 0; i<word.length(); ++i) {
            if (!node->containsKey(word[i]))
                return false;

            node = node->get(word[i]);
        }
        return node->isEnd();
    }
    bool isPrefix(string word) {
        Node* node = root;
        for (int i = 0; i<word.length(); ++i) {
            if (!node->containsKey(word[i]))
                return false;

            node = node->get(word[i]);
        }
        return true;
    }
};
