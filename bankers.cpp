#include <bits/stdc++.h>
using namespace std;

class BankersAlgorithm {
    int n, m;
    vector<vector<int>> max, allocation, need;
    vector<int> available, safeSequence;
    vector<bool> finish;

public:
    void init() {
        cin >> n >> m;
        max.resize(n, vector<int>(m));
        allocation.resize(n, vector<int>(m));
        need.resize(n, vector<int>(m));
        finish.resize(n, false);
        available.resize(m);
        
        cout<<"Enter max matrix:\n";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin>>max[i][j];

        cout<<"Enter allocation matrix:\n";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin>>allocation[i][j];

        cout<<"Enter available resources:\n";
        for (int i = 0; i < m; i++)
            cin>>available[i];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                need[i][j] = max[i][j] - allocation[i][j];
    }

    bool isSafe() {
        vector<int> work = available;
        while (true) {
            bool progress = false;
            for (int i = 0; i < n; i++) {
                if (!finish[i] && canBeExecuted(i, work)) {
                    progress = true;
                    finish[i] = true;
                    safeSequence.push_back(i);
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    break;
                }
            }
            if (!progress) break;
        }

        for (int i = 0; i < n; i++) {
            if (!finish[i]) return false;
        }
        return true;
    }

    bool canBeExecuted(int i, vector<int>& work) {
        for (int j = 0; j < m; j++) {
            if (need[i][j] > work[j]) return false;
        }
        return true;
    }

    void printSafeSequence() {
        if (safeSequence.empty()) {
            cout<<"System is not in a safe state\n";
        } else {
            cout<<"Safe sequence: ";
            for (int i = 0; i < safeSequence.size(); i++) {
                cout<<"P"<<safeSequence[i];
                if (i < safeSequence.size() - 1) cout<< " -> ";
            }
            cout<<"\n";
        }
    }
};

int main() {
    BankersAlgorithm ba;
    ba.init();
    if (ba.isSafe()) {
        cout<<"System is in a safe state\n";
        ba.printSafeSequence();
    } else {
        cout<<"System is not in a safe state\n";
    }
    return 0;
}
