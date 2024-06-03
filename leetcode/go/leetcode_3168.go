// https://leetcode.cn/problems/minimum-number-of-chairs-in-a-waiting-room/description/
package leetcode

func minimumChairs(s string) int {
	cur, ans := 0, 0
	for i := range s {
		if s[i] == 'E' {
			cur += 1
		} else {
			cur -= 1
		}
		ans = max(ans, cur)
	}

	return ans
}
