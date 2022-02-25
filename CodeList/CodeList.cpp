// CodeList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

vector<string> parseString(const string& str) {
    vector<string> outs;
    stringstream toProc(str);
    string word;
    while (getline(toProc, word, ' ')) {
        outs.push_back(word);
    };
    return outs;
}

vector<vector<string>> buildCodeList(const vector<string>& codeList) {
    vector<vector<string>> outs;
    for (const string& str : codeList) {
        outs.push_back(parseString(str));
    }
    return outs;
}

bool matchAt(int posCart, const vector<string>& shoppingCart,
    const vector<string> codeBucket) {
    for (const string& str : codeBucket) {
        if (posCart == static_cast<int>(shoppingCart.size())) return false;
        if (str != "anything" && str != shoppingCart[posCart]) {
            return false;
        }
        posCart++;
    }
    return true;
}

int foo(vector<string> codeList, vector<string> shoppingCart) {
    vector<vector<string>> codeBuckets = buildCodeList(codeList);
    int posCart = 0;
    bool win = true;
    vector<vector<string>>::iterator itCb = codeBuckets.begin();
    while (itCb != codeBuckets.end() && win) {
        if (posCart == static_cast<int>(shoppingCart.size())) {
            win = false;
        }
        if (matchAt(posCart, shoppingCart, *itCb)) {
            posCart += static_cast<int>(itCb->size());
            itCb++;
        }
        else
        {
            posCart++;
        }
    }
    return win;
}

void Print(const vector<string>& lst) {
    for (const auto& item : lst) {
        cout << item << endl;
    }
}

void Print2D(queue<vector<string>> lst2D) {
    while (!lst2D.empty()) {
        cout << "//////" << endl;
        for (const auto& str : lst2D.front()) {
            cout << str << endl;
        }
        lst2D.pop();
    }
}

int main()
{
    cout << "------" << endl;
    Print(parseString("Hello world!"));
    cout << "------" << endl;
    Print(parseString(""));
    cout << "------" << endl;
    Print(parseString("Hello world! "));
    cout << "------" << endl;
    Print(parseString(" Hello world!"));
    cout << "------" << endl;
    Print(parseString(" Hello world! "));
    cout << "------" << endl;
    Print(parseString(" Hello    world! "));
    cout << "------" << endl;

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
