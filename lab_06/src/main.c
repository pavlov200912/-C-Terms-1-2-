#include "phonebook.h"

int main() {
    int n;
    cin >> n;
    vector<int> d(3*n + 1, 0);
    vector<int> p(n);
    d[1] = 0;
    for (int i = 2; i <= n; i++) {
        p[i] = i - 1;
        d[i] = d[i - 1] + 1;
        if(i % 2 == 0 && d[i/2] + 1 < d[i]) {
            d[i] = d[i/2] + 1;
            p[i] = i/2;
        }
        if(i % 3 == 0 && d[i/3] + 1 < d[i]) {
            d[i] = d[i/3] + 1;
            p[i] = i/3;
        }
        cout << d[i] << ' ';
    }
    cout << d[n];
}
