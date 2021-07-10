#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// lru，缓存淘汰机制
// 队列尾部的是最应该被淘汰的
// 队列头部是最近刚使用的，刚插入，刚更新，刚访问，都要把这个元素放到队列头
// 每次  get / put / update 的操作都要对这个队列做更新
// 用链表比较合适，因为每次都会有数据的插入删除，如果在数组当中，所有元素都要平移
// 数据结构: 双向循环链表，需要又一个单独的头，还要定义这个结构体
// 接口    ：create, get, put, free
// 流程    ：create 就是创建这个缓冲区，这个缓冲区有大小限制，
//                  缓存的空间需要先申请好吗，从 LRU 的含义上来说，是需要先申请好的，
//                  像 CPU 的 cache 也是在硬件里边固定死的，
//                  但是对于这个问题来说先申请好有什么不行呢，也是可以的啊，
//                  都挂到链上不太好，用一个内存池，
//                  一开始都挂到链上，这样插入数据的时候不好弄啊，还要先申请数据这些东西，
//                  真正的缓存时这个内存池，create, free, get, put 都是操作这个内存池的   
//           free 就是把这个缓冲区的额内存释放掉
//           put 往这个缓冲区里边加一个数据，如果 key 原来没有，就插入一个新元素
//               如果这个 key 原来存在，就更新这个值,
//               如果是插入，就直接插入到这个头部
//               如果是更新，就先更新，然后再把这个节点从原来的位置删除，然后插入到头部
//           get 从缓冲区里边查到这个节点
//               然后从原来的位置删除，插入到新节点上，如果这个 key 原来就不存在，那就返回空，链表不做变化
// get 和 put 的时候，都有一个查找的过程，就是看看这个 key 原来是不是存在
// 如果遍历链表的话，这个事件复杂度就是  O(n) 的，这样是比较慢的
// 可以把 key 当作数组下标，数组里边存放这个数组的地址，直接就能查到，
// 但是数组的使用，key 值的大小需要是固定的，大小固定


typedef struct cache{
    int key;
    int value;
    int capacity;
    struct cache *prev;
    struct cache *next;
} LRUCache;

LRUCache *addr_array[10001] = {NULL};
int cnt = 0;

LRUCache *buff_pool_head= NULL;
void *buff_pool_addr = NULL;
int create_cache_pool(int size) {
    LRUCache *addr = malloc(size * sizeof(LRUCache));
    buff_pool_addr = (void *)addr;
    
    if (addr == NULL) {
        return -1;
    }
    memset(addr, 0, size * sizeof(LRUCache));
    
    // 头插法插入一个链表
    for (int i = 0; i < size; i++) {
        LRUCache *tmp = addr + i;
        if (buff_pool_head == NULL) {
            buff_pool_head = tmp;
            buff_pool_head->next = NULL;
        } else {
            tmp->next = buff_pool_head;
            buff_pool_head = tmp;
        }
    }

    return 0;
}

// 只有一个头结点来维护这个链表
// 获取一个节点和插入一个节点的时候都是在链表的头部做操作
// 自己犯过一个错误，就是在 ucx netlib 的 call back 函数里边
// 获取一个 buff 或者释放一个 buff 的时候需要对头结点进行更新
// 如果头结点
LRUCache *get_a_cache_node() {
    LRUCache *ret = buff_pool_head;
    buff_pool_head = buff_pool_head->next;
    return ret;
}

int put_a_cache_node(LRUCache *buff) {
    buff->next = buff_pool_head;
    buff_pool_head = buff;
    return 0;
}

int free_cache_pool() {
    free(buff_pool_addr);
    return 0;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *ret = NULL;
    
    ret = (LRUCache *)malloc(sizeof(LRUCache));
    if (ret == NULL) {
        printf("malloc for ret failed\n");
        return NULL;
    }
    ret->key   = -1;
    ret->value = -1;
    ret->capacity = capacity;
    ret->prev = ret;
    ret->next = ret;

    buff_pool_head= NULL;
    buff_pool_addr = NULL;
    create_cache_pool(capacity);

    for (int i = 0; i < 3001; i++) {
        addr_array[i] = NULL;
    }
    cnt = 0;

    return ret;
}

int lRUCacheGet(LRUCache* obj, int key) {
    LRUCache *tmp = addr_array[key];

    if (tmp != NULL) {
        int value = tmp->value;

        LRUCache *del = tmp;
        LRUCache *prev = del->prev;
        LRUCache *next = del->next;
        prev->next = next;
        next->prev = prev;

        LRUCache *add = tmp;
        LRUCache *prev1 = obj;
        LRUCache *next1 = obj->next;
        prev1->next = add;
        add->prev   = prev1;
        next1->prev = add;
        add->next   = next1;

        return value;
    }

    return -1;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    int num = 0;

    LRUCache *tmp = addr_array[key];
    if (tmp != NULL) {
        tmp->value = value;

        LRUCache *del = tmp;
        LRUCache *prev = del->prev;
        LRUCache *next = del->next;
        prev->next = next;
        next->prev = prev;

        LRUCache *add = tmp;
        LRUCache *prev1 = obj;
        LRUCache *next1 = obj->next;
        prev1->next = add;
        add->prev   = prev1;
        next1->prev = add;
        add->next   = next1;

        return;
    }
    if (cnt >= obj->capacity) {
        LRUCache *to_del = obj->prev;
        LRUCache *prev = to_del->prev;
        LRUCache *next = to_del->next;
        prev->next = next;
        next->prev = prev;
        addr_array[to_del->key] = NULL;
        cnt--;

        put_a_cache_node(to_del);
    }

    LRUCache *prev1 = obj;
    LRUCache *next1 = obj->next;
    LRUCache *new = get_a_cache_node();
    if (new == NULL) {
        return;
    }
    new->key = key;
    new->value = value;
    prev1->next = new;
    new->prev   = prev1;
    next1->prev = new;
    new->next   = next1;

    addr_array[key] = new;
    cnt++;

    return;
}

void lRUCacheFree(LRUCache* obj) {
    free_cache_pool();
    free(obj);

    return;
}
