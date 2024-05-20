// https://leetcode.cn/problems/number-of-wonderful-substrings/

package leetcode

func wonderfulSubstrings(word string) (ans int64) {
	const size = 1 << 10
	cnt := [size]int{1}
	pre := 0
	for _, c := range word {
		pre ^= 1 << (c - 'a')
		ans += int64(cnt[pre])
		for i := 1; i < size; i <<= 1 {
			ans += int64(cnt[pre^i])
		}
		cnt[pre]++
	}
	return
}
