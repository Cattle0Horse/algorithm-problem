class Employee:
    def __init__(self, id: int, importance: int, subordinates: List[int]):
        self.id = id
        self.importance = importance
        self.subordinates = subordinates


from typing import List


class Solution:
    def getImportance(self, employees: List["Employee"], id: int) -> int:
        mp = {e.id: e for e in employees}

        def dfs(cur) -> int:
            return cur.importance + sum(dfs(mp[i]) for i in cur.subordinates)

        return dfs(mp[id])
