#include <algorithm>
#include <vector>
namespace OI::Intervals {
template<typename T>
void mergeRange(std::vector<std::vector<T>>& intervals) {
    std::sort(intervals.begin(), intervals.end());
    int index{0};
    for (int i{0}, n{static_cast<int>(intervals.size())}; i < n;) {
        intervals[index][0] = intervals[i][0];
        int right{intervals[i][1]};
        // i 走到第一个不能合并的区间
        for (; i < n && intervals[i][0] <= right; ++i) {
            right = std::max(right, intervals[i][1]);
        }
        intervals[index][1] = right;
        ++index;
    }
    intervals.resize(index);
}
template<typename T>
void mergeRange(std::vector<std::pair<T, T>>& intervals) {
    std::sort(intervals.begin(), intervals.end());
    int index{0};
    for (int i{0}, n{static_cast<int>(intervals.size())}; i < n;) {
        intervals[index].first = intervals[i].first;
        int right{intervals[i].second};
        // i 走到第一个不能合并的区间
        for (; i < n && intervals[i].first <= right; ++i) {
            right = std::max(right, intervals[i].second);
        }
        intervals[index].second = right;
        ++index;
    }
    intervals.resize(index);
}
} // namespace OI::Intervals