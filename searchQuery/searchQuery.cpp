// searchQuery.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

void toLower(string& str) {
	for (char& c : str) {
		c = tolower(c);
	}
}

vector<string> buildPrefix(const string& query) {
	vector<string> outs;
	for (int i = 2; i <= static_cast<int>(query.size()); i++) {
		outs.push_back(query.substr(0, i));
	}
	return outs;
}

bool hasPrefix(const string& word, const string& prefix) {
	int posWord = 0;
	for (char c : prefix) {
		if (posWord == word.size()) {
			return false;
		}
		else if (word[posWord] != c) {
			return false;
		}
		posWord++;
	}
	return true;
}

vector<vector<string>> searchSuggestions(vector<string> repository, string customerQuery) {
	for (string& str : repository) {
		toLower(str);
	}
	toLower(customerQuery);
	sort(repository.begin(), repository.end());
	vector<string> prefixes = buildPrefix(customerQuery);
	vector<vector<string>> outs;
	for (const string& pre : prefixes) {
		vector<string> currOuts;
		for (const string& str : repository) {
			if (hasPrefix(str, pre) && currOuts.size() < 3) {
				currOuts.push_back(str);
			}
		}
		outs.push_back(currOuts);
	}
	return outs;
}

void Print(const vector<string>& lst) {
	for (const auto& item : lst) {
		cout << item << endl;
	}
}

void Print2D(const vector<vector<string>> lst2D) {
	for (const auto& lst : lst2D) {
		cout << "//////" << endl;
		for (const auto& str : lst) {
			cout << str << endl;
		}
	}
}

int main() {
	//Trie t1;
	//Print(t1.getWithPrefix(""));
	//cout << "---" << endl;
	//
	//t1.insert("string");
	//t1.insert("by");
	//t1.insert("sea");
	//t1.insert("sells");
	//t1.insert("she");
	//t1.insert("shells");
	//t1.insert("shore");
	//t1.insert("the");
	//
	//Print(t1.getWithPrefix(""));
	//cout << "---" << endl;
	//
	//Print(t1.getWithPrefix("sh"));
	//cout << "---" << endl;

	vector<string> t0 = {
	"cOde",
	"code",
	"cODe",
	"CoDe",
	"codePhone",
	"coddle",
	"coddles",
	"codes"
	};

	sort(t0.begin(), t0.end());

	Print(t0);

	cout << "------//---" << endl;
	
	vector<string> test = {
	"code",
	"codePhone",
	"coddle",
	"coddles",
	"codes"
	};

	Print2D(searchSuggestions(test, "coddle"));
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
