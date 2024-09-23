def merge_intervals(intervals: list[list | tuple]) -> list[list]:
    """区间合并"""
    arr = sorted(intervals)
    ans, i, n = [], 0, len(arr)
    while i < n:
        l, r = arr[i][0], arr[i][1]
        while i < n and arr[i][0] <= r:
            r = max(r, arr[i][1])
            i += 1
        ans.append([l, r])
    return ans


print(merge_intervals([(1, 3), (2, 6), (8, 10), (15, 18)]))
