// https://leetcode.cn/problems/find-the-peaks/?envType=daily-question&envId=2024-05-28
package leetcode

func findPeaks(mountain []int) (ans []int) {
	n := len(mountain) - 1
	for i := 1; i < n; i++ {
		if mountain[i-1] < mountain[i] && mountain[i] > mountain[i+1] {
			ans = append(ans, i)
		}
	}
	return
}
