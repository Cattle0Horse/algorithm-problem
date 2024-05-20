// https://leetcode.cn/problems/super-pow/
package leetcode

/*
13/2
(10+3)/2
113/2=26
100/2+10/2+3/2
(50 + 3) / 2 =26

除个位外, 若当前位不能整除, 则 下一位+10
*/
func superPow(a int, b []int) int {
	const mod = 1337
	ans := 1
	a %= mod
	for len(b) != 0 {
		n := len(b)
		for i := 0; i < n; i++ {
			if b[i]%2 == 1 {
				if i == n-1 {
					ans = ans * a % mod
				} else {
					b[i+1] += 10
				}
			}
			b[i] >>= 1
		}
		for len(b) != 0 && b[0] == 0 {
			b = b[1:]
		}
		a = a * a % mod
	}
	return ans
}
