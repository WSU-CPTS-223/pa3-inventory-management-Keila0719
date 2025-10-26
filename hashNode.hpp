#pragma once

template<typename Key, typename Value>
class HashNode{
public:
    Key key;
    Value value;
    HashNode* next;

    HashNode(const Key& key, const Value& value): key(key), value(value), next(nullptr){};
};