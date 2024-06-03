// https://leetcode.cn/problems/QTMn0o/
package leetcode

func subarraySum(nums []int, k int) (ans int) {
	// 左边界对应和的个数
	cnt := map[int]int{0: 1}
	pre := 0
	// right - left = k
	for _, v := range nums {
		pre += v
		ans += cnt[pre-k]
		cnt[pre]++
	}
	return
}
