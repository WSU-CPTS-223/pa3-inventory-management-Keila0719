template<typename Key, typename Value>
class hashNode{
public:
    Key key;
    Value value;
    HashNode* next;
    
    hashNode(const Key& key, const Value& value): key(key), value(value), next(nullptr){};
};