'''
1450. 在既定时间做作业的学生人数
https://leetcode.cn/problems/number-of-students-doing-homework-at-a-given-time/
'''
from typing import List


class Solution:
    def busyStudent(self, startTime: List[int], endTime: List[int], queryTime: int) -> int:
        return sum(1 for s, e in zip(startTime, endTime) if s <= queryTime <= e)