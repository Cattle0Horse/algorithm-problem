/**
 * @file leetcode_1146.cpp
 * @author Cattle_Horse (CattleHorse@duck.com)
 * @brief https://leetcode.cn/problems/snapshot-array/description/?envType=daily-question&envId=2024-04-26
 * @version 0.1
 * @date 2024-04-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <vector>
class SnapshotArray {
private:
    std::vector<std::vector<std::pair<int, int>>> snap_arr;
    int snap_id;

public:
    SnapshotArray(int length): snap_arr(length), snap_id(0) {
        for (auto& arr : snap_arr) {
            arr.emplace_back(0, 0);
        }
    }

    void set(int index, int val) {
        auto& arr = snap_arr[index];
        if (snap_id == arr.back().first) {
            arr.back().second = val;
        } else {
            arr.emplace_back(snap_id, val);
        }
    }

    int snap() {
        return snap_id++;
    }

    int get(int index, int snap_id) {
        const auto& vals = snap_arr[index];
        int l = -1, r = vals.size();
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (vals[mid].first < snap_id) {
                l = mid;
            } else {
                r = mid;
            }
        }
        if (r >= static_cast<int>(vals.size()) || vals[r].first > snap_id) return vals[l].second;
        return vals[r].second;
    }
};

int main() {
    SnapshotArray solution(4);
    std::cout << solution.snap() << std::endl;
    std::cout << solution.snap() << std::endl;
    std::cout << solution.get(3, 1) << std::endl;
    solution.set(2, 4);
    std::cout << solution.snap() << std::endl;
    solution.set(1, 4);
}