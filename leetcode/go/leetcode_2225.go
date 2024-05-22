// https://leetcode.cn/problems/find-players-with-zero-or-one-losses/?envType=daily-question&envId=2024-05-22
package leetcode

func findWinners(matches [][]int) [][]int {
	const size = 100001
	degree := [size]int{}
	has := [size]bool{}
	for _, match := range matches {
		degree[match[1]]++
		has[match[0]] = true
		has[match[1]] = true
	}
	ans := make([][]int, 2)
	for key, val := range degree {
		if has[key] && val <= 1 {
			ans[val] = append(ans[val], key)
		}
	}
	return ans
}
