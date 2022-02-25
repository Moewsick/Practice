#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

class vector_int_hasher {
public:
    size_t operator()(const vector<int>& vec) const {
        size_t ret = vec.size();
        for (int i : vec) {
            ret ^= i + 0x9e3779b9 + (ret << 6) + (ret >> 2);
        }
        return ret;
    }
};

template<class Func>
void do_something(Func f)
{
    f();
}


int main() {
    string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
        "Sed laoreet sem leo, in posuere orci elementum.";
    char space_char = ' ';
    vector<string> words{};

    stringstream sstream(text);
    string word;
    while (std::getline(sstream, word, space_char)) {
        //word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        words.push_back(word);
    }

    for (const auto& str : words) {
        //cout << str << endl;
    }

    vector<int> vi = { 1,2,3,4,5 };

    auto dis1 = distance(vi.begin(), vi.end());
    auto dis2 = distance(vi.begin(), find_if(vi.begin(), vi.end(), [](int i) {return i == 3; }));
    cout << dis1 << endl;
    cout << dis2 << endl;

    vector<string> outs;
    copy_if(words.begin(), words.end(), back_inserter(outs), [](const string& str) {
        return str[0] == 'a';
        });

    int i = 10;
    while (i > 0) {
        vector<int> outs;
        outs.push_back(i);
        cout << "line " << i << endl;
        for (int i : outs) {
            cout << i << endl;
        }
        i--;
    }

    cout << "map example" << endl;
    unordered_map<vector<int>, bool, vector_int_hasher> m;

    m.emplace(vector<int>({ 1,2,3 }), true);
    m.emplace(vector<int>({ 1,2,3,4 }), true);
    m.emplace(vector<int>({ 1,3 }), true);
    m.emplace(vector<int>({ 2,3 }), true);

    auto it = m.find(vector<int>({ 1,3 }));

    cout << it->first[1] << endl;

    cout << ceil(2.5 / 2) << endl;

    int* pi = nullptr;
    pi = reinterpret_cast<int*> (&pi);

    do_something([]() {
        cout << "Hello World" << endl;
        }); 

    return EXIT_SUCCESS;
}