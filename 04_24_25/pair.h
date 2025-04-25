#ifndef PAIR_H
#define PAIR_H

template <class k, class v>
class pair
{
public:
    pair(const pair<k, v> &oth);
    pair(const k &key, const v &value);
    pair(const k &key);
    v &getValue();
    k getKey();
    void setValue(const v &value);
    bool operator>(const pair<k, v> &oth) const;
    bool operator>=(const pair<k, v> &oth) const;
    bool operator<(const pair<k, v> &oth) const;
    bool operator<=(const pair<k, v> &oth) const;
    bool operator==(const pair<k, v> &oth) const;
    bool operator!=(const pair<k, v> &oth) const;
    const pair<k, v> &operator=(const pair<k, v> &oth);
    ~pair();

private:
    void copyPair(const pair<k, v> &oth);
    k *key;
    v *value;
};

template <class k, class v>
pair<k, v>::pair(const pair<k, v> &oth)
{
    key = nullptr;
    value = nullptr;
    copyPair(oth);
}
template <class k, class v>
pair<k, v>::pair(const k &key, const v &value)
{
    this->key = new k(key);
    this->value = new v(value);
}
template <class k, class v>
pair<k, v>::pair(const k &key)
{
    this->value = nullptr;
    this->key = new k(key);
}
template <class k, class v>
v &pair<k, v>::getValue()
{
    return *this->value;
}
template <class k, class v>
k pair<k, v>::getKey()
{
    return *this->key;
}
template <class k, class v>
void pair<k, v>::setValue(const v &value)
{
    delete this->value;
    this->value = new v(value);
}
template <class k, class v>
bool pair<k, v>::operator>(const pair<k, v> &oth) const
{
    return *this->key > *oth.key;
}
template <class k, class v>
bool pair<k, v>::operator>=(const pair<k, v> &oth) const
{
    return *this->key >= *oth.key;
}
template <class k, class v>
bool pair<k, v>::operator<(const pair<k, v> &oth) const
{
    return *this->key < *oth.key;
}
template <class k, class v>
bool pair<k, v>::operator<=(const pair<k, v> &oth) const
{
    return *this->key <= *oth.key;
}
template <class k, class v>
bool pair<k, v>::operator==(const pair<k, v> &oth) const
{
    return *this->key == *oth.key;
}
template <class k, class v>
bool pair<k, v>::operator!=(const pair<k, v> &oth) const
{
    return *this->key != *oth.key;
}
template <class k, class v>
const pair<k, v> &pair<k, v>::operator=(const pair<k, v> &oth)
{
    if (this != &oth)
        copyPair(oth);
    return *this;
}
template <class k, class v>
pair<k, v>::~pair()
{
    delete key;
    delete value;
}
template <class k, class v>
void pair<k, v>::copyPair(const pair<k, v> &oth)
{
    delete key;
    delete value;
    this->key = new k(*oth.key);
    this->value = new v(*oth.value);
}

#endif