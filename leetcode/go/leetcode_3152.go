// https://leetcode.cn/problems/special-array-ii/description/
package leetcode

func isArraySpecial(nums []int, queries [][]int) []bool {
	n := len(nums)
	pre := make([]int, n)
	// 以i结尾的奇偶性相同=1
	for i := 1; i < n; i++ {
		if nums[i]%2 == nums[i-1]%2{
			pre[i]=1
		}
		pre[i] += pre[i-1]
	}
	ans := make([]bool, len(queries))
	for i, query  := range queries {
		l, r := query[0], query[1]
		ans[i] = pre[r] == pre[l]
	}
	return ans
}