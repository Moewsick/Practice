#include <string>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'noPrefix' function below.
 *
 * The function accepts STRING_ARRAY words as parameter.
 */

class Trie {
    vector<Trie*> chdr;
    bool isEnd;
public:
    Trie() : chdr('j' + 1 - 'a'), isEnd(false) {}
    ~Trie() {
        for (Trie* c : chdr) {
            delete c;
        }
    }
    bool insert(const string& str) {
        bool hasPre = false;
        bool hasExt = true;
        Trie* curr = this;
        for (char c : str) {
            if (!curr->chdr[c - 'a']) {
                curr->chdr[c - 'a'] = new Trie();
                hasExt = false;
            }
            curr = curr->chdr[c - 'a'];
            hasPre |= curr->isEnd;
        }
        curr->isEnd = true;
        return hasPre || hasExt;
    }
};

void noPrefix(vector<string> words) {
    Trie t;
    for (const string& str : words) {
        if (t.insert(str)) {
            cout << "BAD SET" << endl;
            cout << str << endl;
            return;
        }
    }
    cout << "GOOD SET" << endl;
    return;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> words(n);

    for (int i = 0; i < n; i++) {
        string words_item;
        getline(cin, words_item);

        words[i] = words_item;
    }

    noPrefix(words);

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
