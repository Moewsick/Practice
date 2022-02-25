// NewYear.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <math.h>

using namespace std;

struct Node
{
    vector<int> q;
    vector<int> bribes;
    int lv = 0;

    Node() {
    }

    Node(const Node& n) {
        q = n.q;
        bribes = n.bribes;
        lv = n.lv;
    }

    ~Node() {
    }

    void initNode(int size) {
        for (int i = 0; i < size; i++) {
            q.push_back(i);
        }
        bribes = vector<int>(size, 0);
    }

    unsigned long hash() const {
        unsigned long h = 0;
        for (int i = 0; i < q.size(); i++) {
            h += pow(10, i) * q[i];
        }
        return h;
    }

    bool operator==(const Node& n) const {
        return q == n.q;
    }
};

class Graph
{
    unordered_map<unsigned long, vector<Node>> visited;

public:

    Graph() {
    }
    ~Graph() {
    }

    bool isVisited(const Node& n) const {
        auto it = visited.find(n.hash());
        if (it != visited.end()) {
            for (const auto& item : it->second) {
                if (n == item) {
                    return true;
                }
            }
        }
        return false;
    }

    void visitNow(const Node& n) {
        unsigned long id = n.hash();
        auto it = visited.find(id);
        if (it != visited.end()) {
            it->second.push_back(n);
        }
        else {
            visited.emplace(id, vector<Node>(1, n));
        }
    }

    vector<Node> getNeighbors(const Node& n) {
        vector<Node> outs;
        for (int pos = 1; pos < n.q.size(); pos++) {
            int briber = n.q[pos];
            if (n.bribes[briber] < 2) {
                Node cn = n;
                cn.bribes[briber]++;
                cn.q[pos] = n.q[pos - 1];
                cn.q[pos - 1] = briber;
                cn.lv = n.lv + 1;
                outs.push_back(cn);
            }
        }
        return outs;
    }
};

void minimumBribes(vector<int> q) {
    Node scr;
    Node target;
    scr.initNode(q.size());
    target.q = q;
    for (auto& item : target.q) {
        item--;
    }

    Graph g;
    queue<Node> toProc;
    toProc.push(scr);

    Node* found = nullptr;

    while (!toProc.empty()) {
        auto cn = toProc.front();
        toProc.pop();
        g.visitNow(cn);
        if (cn == target) {
            found = new Node(cn);
            break;
        }
        for (const auto& nn : g.getNeighbors(cn)) {
            if (!g.isVisited(nn)) {
                toProc.push(nn);
            }
        }
    }

    if (found) {
        cout << found->lv << endl;
    }
    else {
        cout << "Too chaotic" << endl;
    }

    delete found;
}

int main()
{
    minimumBribes({ 1,2,5,3,7,8,6,4,9,10,11,12,13 });

    return 0;
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
