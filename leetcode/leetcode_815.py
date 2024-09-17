"""
https://leetcode.cn/problems/bus-routes/?envType=daily-question&envId=2024-09-17
815. 公交路线
"""

from collections import defaultdict, deque
from typing import List


class Solution:
    def numBusesToDestination(self, routes: List[List[int]], source: int, target: int) -> int:
        if source == target:
            return 0
        # i号站点经过的公交车id
        g = defaultdict(list)
        for id, route in enumerate(routes):
            for station in route:
                g[station].append(id)
        if source not in g or target not in g:
            return -1
        dis = {source: 0}
        vis = [False] * len(routes)
        q = deque([source])
        while q:
            cur_station = q.popleft()
            new_dis = dis[cur_station] + 1
            for id in g[cur_station]:
                if not vis[id]:
                    for route in routes[id]:
                        if route not in dis:
                            dis[route] = new_dis
                            q.append(route)
                    vis[id] = True
        return dis.get(target, -1)
