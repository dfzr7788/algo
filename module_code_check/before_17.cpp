#include <bits/stdc++.h>
using namespace std;
vector<string> board(8);
bool col[8]{}, diag1[15]{}, diag2[15]{};
int ans = 0;
void dfs(int row) {
    if (row == 8) { ++ans; return; }
    for (int c=0; c<8; ++c) {
        int d1=row-c+7, d2=row+c;
        if (board[row][c]=='*' || col[c] || diag1[d1] || diag2[d2]) continue;
        col[c]=diag1[d1]=diag2[d2]=true;
        dfs(row+1);
        col[c]=diag1[d1]=diag2[d2]=false;
    }
}
int main() {
    for (auto &s : board) cin >> s;
    dfs(0); cout << ans << '\n';
}
