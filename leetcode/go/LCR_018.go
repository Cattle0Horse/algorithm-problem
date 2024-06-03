// https://leetcode.cn/problems/XltzEq/
package leetcode

func isPalindrome(s string) bool {
	check := func(c byte) bool {
		return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9')
	}
	toLower := func(c byte) byte {
		return c | 32
	}
	l, r := 0, len(s)-1
	for l < r {
		if !check(s[l]) {
			l++
			continue
		}
		if !check(s[r]) {
			r--
			continue
		}
		if toLower(s[l]) != toLower(s[r]) {
			return false
		}
		l++
		r++
	}
	return true
}
