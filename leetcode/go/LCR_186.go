// https://leetcode.cn/problems/bu-ke-pai-zhong-de-shun-zi-lcof/
package leetcode

import "math"

func checkDynasty(places []int) bool {
	set := map[int]bool{}
	maxn, minn := 0, math.MaxInt
	for _, v := range places {
		if v == 0 {
			continue
		}
		if set[v] {
			return false
		}
		set[v] = true
		maxn = max(maxn, v)
		minn = min(minn, v)
	}
	return maxn-minn < len(places)
}
