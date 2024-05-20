// https://leetcode.cn/problems/sum-of-digit-differences-of-all-pairs/description/
package leetcode

func sumDigitDifferences(nums []int) int64 {
	ans, n := int64(0), len(nums)

	cnt := [10][10]int{}
	for _, num := range nums {
		for i := 0; num != 0; i, num = i+1, num/10 {
			cnt[i][num%10]++
		}
	}

	for _, num := range nums {
		for i := 0; num != 0; i, num = i+1, num/10 {
			ans += int64(n - cnt[i][num%10])
		}
	}

	return ans / 2
}
