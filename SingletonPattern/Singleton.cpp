#include <iostream>
using namespace std;

struct Node {
    int key;
    int value;
    Node* next;
    Node* prev;


    Node(int _key, int _value)
        :key(_key), value(_value){
            next = nullptr;
            prev = nullptr;
    }
};


class Logger {
public:
    Logger(){}

    void LogInfo(string message){
        cout << "[INFO] " << message << endl;
    }

    void LogError(string message){
        cerr << "[ERROR] " << message << endl;
    }
};


class LRUcache {
private:

    Node* m_left;
    Node* m_right;
    int m_capacity;
    int m_currentCapacity;
    unordered_map<int,Node*> m_map;
    Logger* m_logger;

    LRUcache(int _capacity)
        :m_capacity(_capacity) {
        m_left = new Node(0,0);
        m_right = new Node(0,0);

        m_left->next = m_right;
        m_right->prev = m_left;

        m_logger = new Logger();
        m_currentCapacity = 0;
        cout << "Created LRU Cache with capacity of " << m_capacity << endl;
    }


public: 
    static LRUcache& getInstance(int capacity){
        static LRUcache* s_instance = new LRUcache(capacity);
        return *s_instance;
    }

    void showRecencyOrdering(){
        Node* pre = m_right->prev;

        cout << "Recency Ordering Max Size: " << m_capacity << endl;
        cout << "----------------" << endl;

        while(pre != m_left){
            cout << "Key: " << pre->key << endl;
            pre = pre->prev; 
        }

        cout << "------------" << endl;
        cout << "Least Recent" << endl;
    }

    void makeMostRecent(Node* node){
        Node* mostRecent = m_right->prev;

        // prev value of next node = the previous node 
        node->next->prev = node->prev;

        // next value of previous node = next node 
        node->prev->next = node->next;

        node->next = m_right;
        node->prev = mostRecent;

        mostRecent->next = node;
        m_right->prev = node;
    }


    // Returns a value for a given key. Returns -1 if key DNE
    int get(int key) {

        m_logger->LogInfo("Fetching value for key: " + to_string(key));
        if (m_map.contains(key)) {
            Node* node = m_map[key];

            // make node the most recently accessed
            makeMostRecent(node);

            m_logger->LogInfo("Key: " + to_string(key) + " Value: " + to_string(node->value));
            return node->value;
        }
        m_logger->LogInfo("Key " + to_string(key) + " not found");
        return -1;
    }

    // Returns a status success (0), fail(1)
    void put(int key, int value) {

        m_logger->LogInfo("Inserting (key,value) pair : (" + to_string(key) + "," + to_string(value) + ")");

        // if we already have node we can update that node and make it most recent
        if (m_map.contains(key)) {
            Node* node = m_map[key];

            makeMostRecent(node);
            node->value = value;
            return;
        }

        // if our capacity is greater than max we override least recent node with our new key,value
        if (m_currentCapacity >= m_capacity) {
            Node* leastRecent = m_left->next;

            m_map.erase(leastRecent->key);

            leastRecent->key = key;
            leastRecent->value = value;

            makeMostRecent(leastRecent);

            m_map[key] = leastRecent;
        } else { // if capacity limit is not hit we can just add to map and DLL
            Node* node = new Node(key,value);
            Node* mostRecent = m_right->prev;
          
            node->next = m_right;
            node->prev = mostRecent;
    
            mostRecent->next = node;
            m_right->prev = node;

            m_map[key] = node;

            m_currentCapacity++;
        }
    }
};


int main(){
    LRUcache& cacheInstance = LRUcache::getInstance(1);
    int output;

    // Put 1 and 2 in cache
    cacheInstance.put(1,100);
    cacheInstance.put(2,200);
    cacheInstance.put(3,300);

    output = cacheInstance.get(2);
    cacheInstance.showRecencyOrdering();
};