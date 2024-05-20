// https://leetcode.cn/problems/find-the-longest-substring-containing-vowels-in-even-counts/description/
package leetcode

func findTheLongestSubstring(s string) (ans int) {
	const mask = (1 << ('a' - 'a')) |
		(1 << ('e' - 'a')) |
		(1 << ('i' - 'a')) |
		(1 << ('o' - 'a')) |
		(1 << ('u' - 'a'))
	pos := map[int]int{}
	pre := 0
	for i, c := range s {
		pre ^= 1 << (c - 'a')
		// pre[i+1] = pre[i] ^ (1 << (c - 'a'))
		pos[pre&mask] = i
	}
	pre = 0
	for i, c := range s {
		if val, ok := pos[pre&mask]; ok {
			ans = max(ans, val-i+1)
		}
		pre ^= 1 << (c - 'a')
	}
	return
}
