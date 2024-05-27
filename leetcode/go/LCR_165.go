// https://leetcode.cn/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/description/
package leetcode

import "strconv"

func crackNumber(ciphertext int) int {
	s := strconv.Itoa(ciphertext)
	n := len(s)
	memo := make([]int, n)
	var dfs func(i int) int
	dfs = func(i int) (ans int) {
		if i == n {
			return 1
		}
		if memo[i] != 0 {
			return memo[i]
		}
		ans += dfs(i + 1)
		if s[i] != '0' && i+1 < n && (s[i]-'0')*10+(s[i+1]-'0') < 26 {
			ans += dfs(i + 2)
		}
		memo[i] = ans
		return
	}
	return dfs(0)
}
