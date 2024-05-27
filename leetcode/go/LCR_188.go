// https://leetcode.cn/problems/gu-piao-de-zui-da-li-run-lcof/
package leetcode

import "math"

func bestTiming(prices []int) (ans int) {
	// 维护当前元素左侧的最小值
	minn := math.MaxInt
	for _, price := range prices {
		minn = min(minn, price)
		ans = max(ans, price-minn)
	}
	return
}
