// https://leetcode.cn/problems/0on3uN/
package leetcode

import (
	"strconv"
	"strings"
)

func restoreIpAddresses(s string) (ans []string) {
	const size = 4
	n := len(s)
	var dfs func(int, []string)
	dfs = func(index int, part []string) {
		if len(part) == size {
			if index == n {
				ans = append(ans, strings.Join(part, "."))
			}
			return
		}
		for length := 1; length < size; length++ {
			if index+length > n {
				return
			}
			if length != 1 && s[index] == '0' {
				return
			}
			str := s[index : index+length]
			if num, _ := strconv.Atoi(str); num > 255 {
				return
			}
			dfs(index+length, append(part, str))
		}
	}
	dfs(0, make([]string, 0, size))
	return
}
