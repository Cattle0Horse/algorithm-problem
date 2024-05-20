// https://leetcode.cn/problems/can-make-palindrome-from-substring/
package leetcode

import "math/bits"

func canMakePaliQueries(s string, queries [][]int) []bool {
	n := len(s)
	pre := make([]int, n+1)

	for i := 0; i < n; i++ {
		pre[i+1] = pre[i] ^ (1 << (s[i] - 'a'))
	}
	ans := make([]bool, len(queries))
	for i, query := range queries {
		l, r, k := query[0], query[1], query[2]
		mask := pre[r+1] ^ pre[l]
		cnt := bits.OnesCount(uint(mask))
		ans[i] = cnt-2*k <= 1
	}
	return ans
}
