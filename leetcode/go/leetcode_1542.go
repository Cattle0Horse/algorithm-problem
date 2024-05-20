// https://leetcode.cn/problems/find-longest-awesome-substring/?envType=daily-question&envId=2024-05-20
package leetcode

func longestAwesome(s string) (ans int) {
	const size = 1 << 10
	end := [size]int{}
	n := len(s)
	// [0, i]
	for i, mask := 0, 0; i < n; i++ {
		mask ^= 1 << (s[i] - '0')
		end[mask] = i
	}

	for i, pre := 0, 0; i < n; i++ {
		// find the index of max end
		index := end[pre]
		// flip a bit
		for j := range 10 {
			index = max(index, end[pre^(1<<j)])
		}
		ans = max(ans, index-i+1)

		pre ^= 1 << (s[i] - '0')
	}

	return
}