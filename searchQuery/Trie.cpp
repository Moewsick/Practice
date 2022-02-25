#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Trie
{
	bool in = false;
	unordered_map<char, Trie> m;
	void insertRecurse(size_t i, Trie& t, const string& str) {
		_ASSERTE(i <= str.length());
		if (i == str.length()) {
			t.in = true;
		}
		else
		{
			auto it = t.m.find(str[i]);
			if (it == t.m.end()) {
				it = t.m.emplace(str[i], Trie()).first;
			}
			insertRecurse(++i, it->second, str);
		}
	};

	void getAllRecurse(const string& prefix, const Trie& t, vector<string>& outs) {
		for (const auto& item : t.m) {
			if (item.second.in) {
				outs.push_back(prefix + item.first);
			}
			getAllRecurse(prefix + item.first, item.second, outs);
		}
	}

	vector<string> getAll(const Trie& t) {
		vector<string> outs;
		getAllRecurse("", t, outs);
		return outs;
	}

	const Trie* find(const Trie& t, const string& prefix, size_t i) const {
		_ASSERTE(i <= prefix.length());
		if (i == prefix.length()) {
			return &t;
		}
		else {
			auto it = t.m.find(prefix[i]);
			if (it == t.m.end()) {
				return nullptr;
			}
			else {
				return find(it->second, prefix, ++i);
			}

		}
	}

public:
	Trie() {
	};

	~Trie() {
	};

	void insert(const string& str) {
		insertRecurse(0, *this, str);
	}

	vector<string> getWithPrefix(const string& prefix) {
		const Trie* t = find(*this, prefix, 0);
		vector<string> outs;
		if (t) {
			auto surfix = getAll(*t);
			for (const auto& item : surfix) {
				outs.push_back(prefix + item);
			}
			if (t->in) {
				outs.push_back(prefix);
			}
		}
		sort(outs.begin(), outs.end());
		return outs;
	}
};