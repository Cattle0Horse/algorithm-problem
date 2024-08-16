from cmath import inf
import heapq
from typing import List


class Solution:
    def minimumTime(self, n: int, edges: List[List[int]], disappear: List[int]) -> List[int]:
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        distances, vis = [inf] * n, [False] * n
        distances[0] = 0
        q = [(0, 0)]
        for _ in range(n - 1):
            # pick the minimum node
            while q:
                _, u = heapq.heappop(q)
                if not vis[u]:
                    break
            else:
                break
            # choose the node
            vis[u] = True
            # update the distances
            for v, w in adj[u]:
                dis = distances[u] + w
                if not vis[v] and distances[v] > dis and disappear[v] > dis:
                    distances[v] = dis
                    heapq.heappush(q, (dis, v))

        return [dis if dis != inf else -1 for dis in distances]
