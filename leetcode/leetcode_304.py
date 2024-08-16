from typing import List


class NumMatrix:

    def __init__(self, matrix: List[List[int]]):
        n, m = len(matrix), len(matrix[0])
        p = [[0] * (m + 1) for _ in range(n + 1)]
        for i, row in enumerate(matrix):
            for j, x in enumerate(row):
                p[i + 1][j + 1] = p[i + 1][j] + p[i][j + 1] + matrix[i][j] - p[i][j]
        self.s = p

    # 返回左上角在 (r1,c1) 右下角在 (r2,c2) 的子矩阵元素和

    def sumRegion(self, r1: int, c1: int, r2: int, c2: int) -> int:
        return self.s[r2 + 1][c2 + 1] - self.s[r2 + 1][c1] - self.s[r1][c2 + 1] + self.s[r1][c1]


# Your NumMatrix object will be instantiated and called as such:
# obj = NumMatrix(matrix)
# param_1 = obj.sumRegion(row1,col1,row2,col2)
