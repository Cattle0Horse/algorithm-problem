// https://leetcode.cn/problems/A1NYOS/description/
package leetcode

func findMaxLength(nums []int) (ans int) {
	left := map[int]int{0: -1}
	pre := 0
	for i, num := range nums {
		if num == 0 {
			pre--
		} else {
			pre++
		}
		l, ok := left[pre]
		if ok {
			ans = max(ans, i-l)
		} else {
			left[pre] = i
		}
	}
	return
}
