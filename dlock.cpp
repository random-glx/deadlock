#include <bits/stdc++.h>
using namespace std;

class DeadlockDetection {
    int n, m;
    vector<vector<int>> allocation, request;
    vector<int> available;

public:
    void init() {
        cin >> n >> m;
        allocation.resize(n, vector<int>(m));
        request.resize(n, vector<int>(m));
        available.resize(m);
        
        cout<<"Enter allocation matrix:\n";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin>>allocation[i][j];

        cout<<"Enter request matrix:\n";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin>>request[i][j];

        cout<<"Enter available resources:\n";
        for (int i = 0; i < m; i++)
            cin>>available[i];
    }

    bool isSafe() {
        vector<int> work = available;
        vector<bool> finish(n, false);

        while (true) {
            bool progress = false;
            for (int i = 0; i < n; i++) {
                if (!finish[i] && canProceed(i, work)) {
                    progress = true;
                    finish[i] = true;
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
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

    bool canProceed(int i, vector<int>& work) {
        for (int j = 0; j < m; j++) {
            if (request[i][j] > work[j]) return false;
        }
        return true;
    }

    void printDeadlockStatus() {
        if (isSafe()) {
            cout<<"System is in a safe state. No deadlock.\n";
        } else {
            cout<<"System is in a deadlock state.\n";
        }
    }
};

int main() {
    DeadlockDetection dd;
    dd.init();
    dd.printDeadlockStatus();
    return 0;
}
