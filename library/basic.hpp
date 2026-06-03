// Basic aliases, constants, and macros for C++17 competitive programming.
#pragma once

#include <bits/stdc++.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

// ============== 基本型 ==============
using ll = long long;
using ull = unsigned long long;
using ld = long double;
template <typename T> using V = vector<T>;
template <typename T> using minpq = priority_queue<T, V<T>, greater<T>>;
using maxpq_ll = priority_queue<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

// ============== 定数 ==============
constexpr ld PI = 3.141592653589793238L;
constexpr int INF = (1 << 30) - 1;
constexpr ll INF_L = (1LL << 60);
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string abc = "abcdefghijklmnopqrstuvwxyz";
constexpr ll modNum = 998244353;

// ============== マクロ ==============
#define rep(i, n) for (int i = 0, i##_n = static_cast<int>(n); i < i##_n; i++)
#define rep1(i, n) for (int i = 1, i##_n = static_cast<int>(n); i <= i##_n; i++)
#define rrep(i, n) for (int i = static_cast<int>(n) - 1; i >= 0; i--)
#define rrep1(i, n) for (int i = static_cast<int>(n); i >= 1; i--)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
