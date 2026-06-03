// DP template snippet.
// 問題ごとに状態・遷移・初期値を書き換えて使う。

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
template <typename T> using V = vector<T>;
constexpr ll INF_L = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    V<ll> dp(n + 1, INF_L);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        // TODO: 問題に合わせて遷移を書く。
        // dp[i + 1] = min(dp[i + 1], dp[i] + cost);
    }

    cout << dp[n] << '\n';
    return 0;
}
