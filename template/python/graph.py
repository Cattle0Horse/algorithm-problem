import math
from typing import Any, Callable, Generator


class Edge:
    def __init__(self, u: int, v: int, w=None) -> None:
        self.u = u
        self.v = v
        self.w = w

    def __getitem__(self, index):
        if index == 0:
            return self.u
        if index == 1:
            return self.v
        return self.w

    def __iter__(self):
        return iter((self.u, self.v, self.w))

    def __repr__(self) -> str:
        return f"({self.u}, {self.v}, {self.w})"


EdgeType = tuple[int, int, Any] | tuple[int, int] | Edge | list[int]


class Graph:
    """链式前向星
    - vertex_size: 节点数
    - head: 每个节点的最后插入的边的索引(尾插法)
    - edges: 边集
    - next: 每条边的下一条边
    - END_INDEX: 标记next无下一条边
    - INF: 边权无穷大
    节点编号区间[0, vertex_size)
    """

    def __init__(self, vertex_size: int, END_INDEX: int = 10**8, INF: int | float = math.inf) -> None:
        self.vertex_size: int = vertex_size
        self.head: int = [END_INDEX] * vertex_size
        self.edges: list[EdgeType] = []
        self.next: list[int] = []
        self.END_INDEX: int = END_INDEX
        self.INF: int | float = INF

    @property
    def edge_size(self) -> int:
        return len(self.edges)

    def traverse(self, u: int) -> Generator[EdgeType, None, None]:
        """遍历节点 u 的所有邻接边"""
        i = self.head[u]
        while i != self.END_INDEX:
            yield self.edges[i]
            i = self.next[i]

    def traverse_with_index(self, u: int) -> Generator[tuple[int, EdgeType], None, None]:
        """遍历节点 u 的所有邻接边"""
        i = self.head[u]
        while i != self.END_INDEX:
            yield i, self.edges[i]
            i = self.next[i]

    def add_edge(self, u: int, v: int, w=None) -> None:
        """添加有向边"""
        self.edges.append(Edge(u, v, w))
        self.next.append(self.head[u])
        self.head[u] = self.edge_size - 1

    def add_edge2(self, u: int, v: int, w=None) -> None:
        """添加无向边"""
        self.add_edge(u, v, w)
        self.add_edge(v, u, w)

    def indegree(self) -> list[int]:
        """计算每个节点的入度"""
        degree = [0] * self.vertex_size
        for e in self.edges:
            degree[e[1]] += 1
        return degree

    def outdegree(self) -> list[int]:
        """计算每个节点的出度"""
        degree = [0] * self.vertex_size
        for e in self.edges:
            degree[e[0]] += 1
        return degree

    def topology(self) -> list[int]:
        """拓扑排序，返回节点编号的拓扑序列。若有环，则返回的列表长度不等于节点数"""
        degree = self.indegree()
        result = [i for i in range(self.vertex_size) if degree[i] == 0]
        i = 0
        while i != len(result):
            for e in self.traverse(result[i]):
                degree[e[1]] -= 1
                if degree[e[1]] == 0:
                    result.append(e[1])
            i += 1
        return result

    def sort_edge(self) -> None:
        """对边集排序，要求Edge的w属性支持__lt__方法"""
        self.edges.sort(key=lambda e: e[2])

    def rebuild_next(self) -> None:
        for i in range(self.vertex_size):
            self.head[i] = self.END_INDEX
        dif = self.edge_size - len(self.next)
        if dif > 0:
            self.next.extend([0] * dif)
        else:
            self.next = self.next[:dif]
        self.next = [0] * self.edge_size
        for i in range(self.edge_size - 1, -1, -1):
            self.next[i] = self.head[self.edges[i][0]]
            self.head[self.edges[i][0]] = i

    def dijkstra_heap(self, source: int, initial: int | float = 0) -> list[int | float]:
        """单源最短路(堆优化Dijkstra)"""
        from heapq import heappush, heappop

        distances = [self.INF] * self.vertex_size
        vis = [False] * self.vertex_size
        distances[source] = initial
        q = [(initial, source)]
        for _ in range(self.vertex_size):
            while q:
                _, u = heappop(q)
                if not vis[u]:
                    break
            else:
                break
            vis[u] = True
            for e in self.traverse(u):
                dis = distances[u] + e[2]
                if not vis[e[1]] and distances[e[1]] > dis:
                    distances[e[1]] = dis
                    heappush(q, (dis, e[1]))
        return distances

    def dijkstra(self, source: int, initial: int | float = 0) -> list[int | float]:
        """单源最短路(Dijkstra)"""
        distances = [self.INF] * self.vertex_size
        vis = [False] * self.vertex_size
        distances[source] = initial
        for _ in range(self.vertex_size):
            u, minimum = None, self.INF
            for i in range(self.vertex_size):
                if not vis[i] and distances[i] < minimum:
                    u, minimum = i, distances[i]
            if u is None:
                break
            vis[u] = True
            for e in self.traverse(u):
                dis = distances[u] + e[2]
                if not vis[e[1]] and distances[e[1]] > dis:
                    distances[e[1]] = dis
        return distances

    def floyd(self, initial: int | float = 0) -> list[list[int | float]]:
        """全源最短路(Floyd)"""
        distances = [[self.INF] * self.vertex_size for _ in range(self.vertex_size)]
        for i in range(self.vertex_size):
            distances[i][i] = initial
        for e in self.edges:
            distances[e[0]][e[1]] = e[2]
        for k in range(self.vertex_size):
            for i in range(self.vertex_size):
                for j in range(self.vertex_size):
                    if distances[i][j] > distances[i][k] + distances[k][j]:
                        distances[i][j] = distances[i][k] + distances[k][j]
        return distances

    @staticmethod
    def __find(x: int, parent: list[int]) -> int:
        root = x
        while root != parent[root]:
            root = parent[root]
        while x != root:
            parent[x], x = root, parent[x]
        return root

    def kruskal(self, op: Callable[[EdgeType], None], sort: bool = True) -> bool:
        """最小生成树(Kruskal)
        - op处理选择的边
        - 返回是否能够构成最小生成树
        """
        from functools import partial

        if sort:
            self.sort_edge()
            self.rebuild_next()
        chosen, parent = 0, [*range(self.vertex_size)]
        find = partial(self.__find, parent=parent)
        for e in self.edges:
            ru, rv = find(e[0]), find(e[1])
            if ru != rv:
                parent[rv] = ru
                op(e)
                chosen += 1
                if chosen == self.vertex_size - 1:
                    return True
        return False

    def prim_heap(self, op: Callable[[EdgeType], None], source: int = 0, initial: int | float = 0) -> bool:
        """最小生成树(堆优化Prim)
        - op处理选择的边
        - 返回是否能够构成最小生成树
        """
        from heapq import heappush, heappop

        distances = [self.INF] * self.vertex_size
        vis = [False] * self.vertex_size
        # 每一个点通过哪条边选中
        index = [self.END_INDEX] * self.vertex_size
        distances[source] = initial
        q = [(initial, source)]
        for _ in range(self.vertex_size):
            while q:
                _, u = heappop(q)
                if not vis[u]:
                    break
            else:
                return False
            vis[u] = True
            if u != source:
                op(self.edges[index[u]])
            for i, e in self.traverse_with_index(u):
                if not vis[e[1]] and distances[e[1]] > e[2]:
                    distances[e[1]] = e[2]
                    index[e[1]] = i
                    heappush(q, (e[2], e[1]))
        return True

    def prim(self, op: Callable[[EdgeType], None], source: int = 0, initial: int | float = 0) -> bool:
        """最小生成树(Prim)
        - op处理选择的边
        - 返回是否能够构成最小生成树
        """
        distances = [self.INF] * self.vertex_size
        vis = [False] * self.vertex_size
        # 每一个点通过哪条边选中
        index = [self.END_INDEX] * self.vertex_size
        distances[source] = initial
        for _ in range(self.vertex_size):
            u, minimum = None, self.INF
            for i in range(self.vertex_size):
                if not vis[i] and distances[i] < minimum:
                    u, minimum = i, distances[i]
            if u is None:
                return False
            vis[u] = True
            if u != source:
                op(self.edges[index[u]])
            for i, e in self.traverse_with_index(u):
                if not vis[e[1]] and distances[e[1]] > e[2]:
                    distances[e[1]] = e[2]
                    index[e[1]] = i
        return True
