#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;



class TextEditor {
    struct op_arg {
        short op;
        string arg;
        op_arg(short opIn, const string& argIn) :
            op(opIn),
            arg(argIn) {
        }
        ~op_arg() {
        }
    };

    vector<op_arg> undo;
    string S;
    void operate(const op_arg& opArg) {
        switch (opArg.op) {
        case 1:
            S.append(opArg.arg);
            break;
        case 2:
            S.erase(S.end() - stoi(opArg.arg), S.end());
            break;
        case 3:
            cout << S[stoi(opArg.arg) - 1] << endl;
            break;
        case 4:
            if (!undo.empty()) {
                operate(undo.back());
                undo.pop_back();
            }
            break;
        default:
            break;
        }
    }
public:
    TextEditor() {
    }
    ~TextEditor() {
    }
    void run() {
        int Q = 0;
        cin >> Q;

        while (Q--) {
            short op;
            string arg;
            cin >> op;
            if (op != 4) {
                cin >> arg;
            }
            if (op == 1) {
                undo.emplace_back(2, to_string(arg.length()));
            }
            else if (op == 2) {
                int rmLen = stoi(arg);
                undo.emplace_back(1, S.substr(S.length() - rmLen, rmLen));
            }
            operate({ op, arg });
        }
    }
};

int main() {
    TextEditor te;
    te.run();
    return 0;
}
