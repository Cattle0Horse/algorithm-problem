// https://leetcode.cn/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/
package leetcode

import (
	"sort"
	"strconv"
	"strings"
)

func crackPassword(password []int) string {
	s := make([]string, 0, len(password))
	for _, p := range password {
		s = append(s, strconv.Itoa(p))
	}
	sort.Slice(s, func(i, j int) bool {
		return s[i]+s[j] < s[j]+s[i]
	})
	return strings.Join(s, "")
}
