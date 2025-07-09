#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    string word;

    TrieNode() {
        isEndOfWord = false;
        word = "";
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

    void dfsWithPrefix(TrieNode* node, vector<string>& suggestions) {
        if (suggestions.size() >= 5) return;
        if (node->isEndOfWord)
            suggestions.push_back(node->word);
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i])
                dfsWithPrefix(node->children[i], suggestions);
        }
    }

public:
    Trie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            int index = tolower(c) - 'a';
            if (!current->children[index])
                current->children[index] = new TrieNode();
            current = current->children[index];
        }
        current->isEndOfWord = true;
        current->word = word;
    }

    bool search(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            int index = tolower(c) - 'a';
            if (!current->children[index])
                return false;
            current = current->children[index];
        }
        return current->isEndOfWord;
    }

    vector<string> getSuggestions(const string& prefix) {
        vector<string> suggestions;
        TrieNode* current = root;
        for (char c : prefix) {
            int index = tolower(c) - 'a';
            if (!current->children[index])
                return suggestions;
            current = current->children[index];
        }
        dfsWithPrefix(current, suggestions);
        return suggestions;
    }
};

// Levenshtein distance for fuzzy matching
int editDistance(const string& a, const string& b) {
    int m = a.length(), n = b.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;
    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (tolower(a[i - 1]) == tolower(b[j - 1]))
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
        }
    }
    return dp[m][n];
}

vector<string> getClosestWords(const string& word, const unordered_set<string>& dictionary) {
    vector<pair<int, string>> distances;
    for (const auto& dictWord : dictionary) {
        int dist = editDistance(word, dictWord);
        if (dist <= 2)  // Tune this threshold
            distances.emplace_back(dist, dictWord);
    }
    sort(distances.begin(), distances.end());
    vector<string> result;
    for (int i = 0; i < min(5, (int)distances.size()); i++)
        result.push_back(distances[i].second);
    return result;
}

int main() {
    Trie trie;
    unordered_set<string> dictionary;
    ifstream infile("dictionary.txt");
    string word;
    while (getline(infile, word)) {
        trie.insert(word);
        dictionary.insert(word);
    }
    infile.close();

    cout << "Enter a word to check spelling (type 'exit' to quit):\n";
    while (true) {
        cout << "> ";
        string input;
        cin >> input;
        if (input == "exit") break;

        if (trie.search(input)) {
            cout  << input << "' is spelled correctly.\n";
        } else {
            cout  << input << "' is not found.\n";

            // Suggest using prefix
            auto suggestions = trie.getSuggestions(input);
            if (suggestions.empty()) {
                // Fall back to fuzzy matching
                suggestions = getClosestWords(input, dictionary);
            }

            if (!suggestions.empty()) {
                cout << " Did you mean:\n";
                for (const string& suggestion : suggestions)
                    cout << suggestion << '\n';
            } else {
                cout << "  No suggestions found.\n";
            }
        }
    }

    return 0;
}
