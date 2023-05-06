// https://leetcode.com/problems/replace-words/description/

#include <cassert>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int char_to_int(char c) {
    return c - 'a';
}

class TrieNode {
   private:
    TrieNode* children[26];
    // std::unordered_map<char, TrieNode*> children;
    bool end_of_word = false;

   public:
    TrieNode() {
        for (auto& p : children) {
            p = nullptr;
        }
    }

    virtual ~TrieNode() {
        for (auto p : children) {
            delete p;
        }
    }

    void insert(const std::string& word) {
        if (word.length() == 0) {
            end_of_word = true;
            return;
        }
        int c = char_to_int(word[0]);
        if (children[c] == nullptr) {
            children[c] = new TrieNode();
        }
        std::string rest_of_string(word, 1, word.length() - 1);
        (children[c])->insert(rest_of_string);
    }

    std::string get(const std::string& word, const std::string& root) {
        if (end_of_word) {
            return root;
        }
        if (word.length() == 0) {
            return "";
        }
        int c = char_to_int(word[0]);
        if (children[c] != nullptr) {
            std::string rest_of_string(word, 1, word.length() - 1);
            return (children[c])->get(rest_of_string, root + word[0]);
        }
        return "";
    }
};

class Trie {
    TrieNode* root;

   public:
    Trie() { root = new TrieNode(); }

    virtual ~Trie() { delete root; }

    void insert(const std::string& word) { root->insert(word); }

    std::string getRoot(const std::string& word) { return root->get(word, ""); }
};

std::string replaceWords(const std::vector<std::string>& dictionary, const std::string sentence) {
    std::string response;
    std::string word;
    Trie trie;
    for (const std::string& root : dictionary) {
        trie.insert(root);
    }
    for (unsigned i = 0; i < sentence.length(); ++i) {  // n
        char c = sentence[i];
        word += c;
        if (c == ' ' || i == sentence.length() - 1) {
            //std::string root = getRoot(word, dictionary);
            std::string root = trie.getRoot(word);
            if (!root.empty()) {
                response += root;
                if (c == ' ')
                    response += " ";
            } else {
                response += word;
            }
            word = "";
        }
    }
    return response;
}

int main() {
    assert(replaceWords({"cat", "bat", "rat"}, "the cattle was rattled by the battery") ==
           "the cat was rat by the bat");
    assert(replaceWords({"a", "b", "c"}, "aadsfasf absbs bbab cadsfafs") == "a a b c");
    std::cout << "OK" << std::endl;
}
