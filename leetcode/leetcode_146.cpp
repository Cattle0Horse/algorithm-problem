// @date 2024/8/16 23:44:42
// @author Cattle_Horse (CattleHorse@duck.com)
// @problem 146. LRU 缓存
// @link https://leetcode.cn/classic/problems/lru-cache/description/

#ifdef Cattle_Horse
#include "leetcode.h" // IWYU pragma: keep
using namespace std;
#else
#define dbg(...) void(114514)
#endif

[[maybe_unused]] auto __init_io__ = []() {
    return std::cin.tie(nullptr)->sync_with_stdio(false);
}();

struct Node {
    int key = -1, val = -1;
    Node *prev = nullptr, *next = nullptr;
};

class LRUCache {
private:
    size_t m_capacity;
    // 可以使用dummy的prev标记最后一个节点，这样就只需要一个指针了
    Node *dummy_front, *dummy_back;
    std::unordered_map<int, Node*> m_map;

public:
    LRUCache(int capacity): m_capacity(capacity), dummy_front(new Node()), dummy_back(new Node()), m_map(capacity) {
        assert(m_capacity > 0);
        dummy_front->next = dummy_back;
        dummy_back->prev = dummy_front;
    }
    ~LRUCache() {
        for (Node* node = dummy_front->next; node != dummy_back; node = node->next) {
            delete node->prev;
        }
        delete dummy_back;
    }
    void adjust(Node* node) {
        // 如果是第一个节点则不用调整链表
        if (node->prev == dummy_front) return;
        node->prev->next = node->next;
        node->next->prev = node->prev;

        dummy_front->next->prev = node;
        node->next = dummy_front->next;
        dummy_front->next = node;
        node->prev = dummy_front;
    }

    int get(int key) {
        if (auto it = m_map.find(key); it != m_map.end()) {
            Node* node = it->second;
            adjust(node);
            return node->val;
        }
        return -1;
    }

    void put(int key, int value) {
        if (auto it = m_map.find(key); it != m_map.end()) {
            // 修改值并调整位置
            Node* node = it->second;
            node->val = value;
            adjust(node);
        } else {
            if (m_map.size() == m_capacity) {
                // 删除末尾节点后添加新节点，相当于修改末尾节点后放到首部
                m_map.erase(dummy_back->prev->key);
                dummy_back->prev->key = key;
                dummy_back->prev->val = value;
                m_map[key] = dummy_back->prev;
                adjust(dummy_back->prev);
            } else {
                Node* node = new Node(key, value, dummy_front, dummy_front->next);
                dummy_front->next->prev = node;
                dummy_front->next = node;
                m_map[key] = node;
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// LRUCache::LRUCache(int capacity)
// int LRUCache::get(int key)
// void LRUCache::put(int key, int value)

#ifdef Cattle_Horse
int main() {
    std::cout << "*** 146. LRU 缓存 ***" << std::endl
              << std::endl;

    std::cout << "Test 0: " << std::endl;
    std::cout << "  # 0: ";

    int capacity0 = 2;
    LRUCache s0(capacity0);
    std::cout << "Yes" << std::endl;

    {
        std::cout << "  # 1: ";

        int key1 = 1;
        int value1 = 1;
        s0.put(key1, value1);
        std::cout << "Yes" << std::endl;
    }

    {
        std::cout << "  # 2: ";

        int key2 = 2;
        int value2 = 2;
        s0.put(key2, value2);
        std::cout << "Yes" << std::endl;
    }

    {
        std::cout << "  # 3: ";

        int key3 = 1;
        int ans3 = s0.get(key3);
        int exp3 = 1;

        if (ans3 == exp3) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "    Answer: " << ans3 << std::endl;
            std::cout << "    Expect: " << exp3 << std::endl;
        }
    }

    {
        std::cout << "  # 4: ";

        int key4 = 3;
        int value4 = 3;
        s0.put(key4, value4);
        std::cout << "Yes" << std::endl;
    }

    {
        std::cout << "  # 5: ";

        int key5 = 2;
        int ans5 = s0.get(key5);
        int exp5 = -1;

        if (ans5 == exp5) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "    Answer: " << ans5 << std::endl;
            std::cout << "    Expect: " << exp5 << std::endl;
        }
    }

    {
        std::cout << "  # 6: ";

        int key6 = 4;
        int value6 = 4;
        s0.put(key6, value6);
        std::cout << "Yes" << std::endl;
    }

    {
        std::cout << "  # 7: ";

        int key7 = 1;
        int ans7 = s0.get(key7);
        int exp7 = -1;

        if (ans7 == exp7) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "    Answer: " << ans7 << std::endl;
            std::cout << "    Expect: " << exp7 << std::endl;
        }
    }

    {
        std::cout << "  # 8: ";

        int key8 = 3;
        int ans8 = s0.get(key8);
        int exp8 = 3;

        if (ans8 == exp8) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "    Answer: " << ans8 << std::endl;
            std::cout << "    Expect: " << exp8 << std::endl;
        }
    }

    {
        std::cout << "  # 9: ";

        int key9 = 4;
        int ans9 = s0.get(key9);
        int exp9 = 4;

        if (ans9 == exp9) {
            std::cout << "Yes" << std::endl;
        } else {
            std::cout << "No" << std::endl;
            std::cout << "    Answer: " << ans9 << std::endl;
            std::cout << "    Expect: " << exp9 << std::endl;
        }
    }

    return 0;
}
#endif
