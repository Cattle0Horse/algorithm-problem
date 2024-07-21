#ifndef LEETCODE_H
#define LEETCODE_H
// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

#include "dbg.h"

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
    static ListNode* create(const std::string& d, std::vector<ListNode>& nodes) {
        std::string s;
        int len = 0;
        for (int i = 0; i < static_cast<int>(d.size()); i++) {
            if (isalnum(d[i]) || d[i] == '-')
                s.push_back(d[i]);
            if (s.size() && (d[i] == ',' || i == static_cast<int>(d.size()) - 1)) {
                nodes.push_back(stoi(s));
                len++;
                s.clear();
            }
        }
        if (!len) return nullptr;
        for (int i = nodes.size() - len + 1; i < static_cast<int>(nodes.size()); i++)
            nodes[i - 1].next = &nodes[i];
        return &nodes[0];
    }
    static std::string serialize(ListNode* head) {
        if (!head) return "[]";
        std::string s = "[";
        for (; head; head = head->next)
            s += std::to_string(head->val) + ',';
        s.back() = ']';
        return s;
    }
};
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right): val(x), left(left), right(right) {}
    static TreeNode* create(const std::string& d, std::vector<TreeNode>& nodes) {
        std::string s;
        std::vector<std::pair<int, bool>> pars;
        for (int i = 0, j = 0, l = -1; i < static_cast<int>(d.size()); i++) {
            if (isalnum(d[i]) || d[i] == '-')
                s.push_back(d[i]);
            if (s.size() && (d[i] == ',' || i == static_cast<int>(d.size()) - 1)) {
                if (s != "null") {
                    nodes.push_back(stoi(s));
                    pars.push_back({j, !l});
                }
                if (++l == 2) ++j, l = 0;
                s.clear();
            }
        }
        for (int i = 1; i < static_cast<int>(pars.size()); i++) {
            auto [p, l] = pars[i];
            (l ? nodes[p].left : nodes[p].right) = &nodes[i];
        }
        return nodes.empty() ? nullptr : &nodes[0];
    }
    static std::string serialize(TreeNode* root) {
        if (!root) return "[]";
        std::queue<TreeNode*> q;
        q.push(root);
        std::string s = "[";
        size_t len = 1;
        while (q.size()) {
            TreeNode* p = q.front();
            q.pop();
            if (!p) s += "null,";
            else {
                s += std::to_string(p->val) + ',';
                len = s.size() - 1;
                q.push(p->left);
                q.push(p->right);
            }
        }
        s.resize(len + 1);
        s.back() = ']';
        return s;
    }
};
#endif
