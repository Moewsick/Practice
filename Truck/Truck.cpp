// Truck.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

const int GAS = 0;
const int DIS = 1;

bool canReachNext(int tank, int distance) {
    return tank >= distance;
}

int getNext(int curr, vector<vector<int>> petrolpumps, int& tank) {
    tank -= petrolpumps[curr][DIS];
    ++curr;
    return curr == static_cast<int>(petrolpumps.size()) ? 0 : curr;
}

int truckTour(vector<vector<int>> petrolpumps) {
    int numOfPumps = static_cast<int>(petrolpumps.size());
    int failedAt = 0;
    for (int start = 0; start < numOfPumps; start = failedAt + 1) {
        int curr = start;
        int tank = 0;
        do {
            tank += petrolpumps[curr][GAS];
            if (!canReachNext(tank, petrolpumps[curr][DIS])) {
                failedAt = curr;
                curr = numOfPumps;
                break;
            }
            curr = getNext(curr, petrolpumps, tank);
        } while (curr != start);
        if (curr == start) {
            return start;
        }
    }
    return numOfPumps;
}

int main()
{
    std::cout << "Hello World!\n";

    truckTour({ {1,5}, {10,3}, {3,4} });

    int n;
    cin >> n;
    int tank = 0;
    int pump = 0;
    for (int i = 0; i < n; ++i) {
        int liters;
        int kilometers;
        cin >> liters >> kilometers;
        tank += liters - kilometers;
        if (tank < 0) {
            pump = i + 1;
            tank = 0;
        }
    }
    cout << pump << endl;
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
