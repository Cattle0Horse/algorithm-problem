package leetcode

/*
// src/runtime/slice.go
type slice struct {
    array unsafe.Pointer // 元素指针
    len   int // 长度
    cap   int // 容量
}

值传递!!!
*/
func pathTarget(root *TreeNode, target int) (ans [][]int) {
	if root == nil {
		return
	}
	var dfs func(cur *TreeNode, path []int, sum int)
	dfs = func(cur *TreeNode, path []int, sum int) {
		path = append(path, cur.Val)
		sum += cur.Val
		if cur.Left == nil && cur.Right == nil {
			if sum == target {
				// !!! copy
				ans = append(ans, append([]int{}, path...))
			}
			return
		}
		if cur.Left != nil {
			dfs(cur.Left, path, sum)
		}
		if cur.Right != nil {
			dfs(cur.Right, path, sum)
		}
	}
	dfs(root, make([]int, 0), 0)
	return
}
