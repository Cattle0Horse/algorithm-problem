// https://leetcode.cn/problems/compare-version-numbers/description/

package leetcode

import (
	"strconv"
)

type resFunc1 func() int
type resFunc2 func() bool

// 闭包: 实际就是一个类, 将变量作为属性
func closure(s string) (resFunc1, resFunc2) {
	n := len(s)
	l := 0
	res1 := func() int {
		// [l,r)
		ans := 0
		r := l
		for r < n && s[r] != '.' {
			r++
		}
		if l == r {
			return 0
		}
		ans, _ = strconv.Atoi(s[l:r])
		l = r + 1
		return ans
	}
	res2 := func() bool {
		return l < n
	}
	return res1, res2
}

func compareVersion(version1 string, version2 string) int {
	get1, has1 := closure(version1)
	get2, has2 := closure(version2)

	for has1() || has2() {
		v1, v2 := get1(), get2()
		if v1 < v2 {
			return -1
		}
		if v1 > v2 {
			return 1
		}
	}
	return 0
}
