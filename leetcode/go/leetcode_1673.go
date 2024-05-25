// https://leetcode.cn/problems/find-the-most-competitive-subsequence/?envType=daily-question&envId=2024-05-24
package leetcode

func mostCompetitive(nums []int, k int) []int {
	st, n := []int{}, len(nums)
	for i, num := range nums {
		for len(st) > 0 && num < st[len(st)-1] && len(st)+n-i > k {
			st = st[:len(st)-1]
		}
		if len(st) < k {
			st = append(st, num)
		}
	}
	return st
}
