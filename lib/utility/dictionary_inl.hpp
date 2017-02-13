template <typename T>
Dictionary<T>::Dictionary(uint16_t itemTypeId, size_t reserveCount)
    : m_itemTypeId(itemTypeId)
{
    m_sparseIds.reserve(reserveCount);
    m_items.reserve(reserveCount);
    m_meta.reserve(reserveCount);
}

template <typename T>
T& Dictionary<T>::at(DictKey handle)
{
    assert(handle.index < m_sparseIds.size() && "outer index out of range");

    DictKey innerId = m_sparseIds[handle.index];

    assert(handle.typeId == m_itemTypeId && "typeId mismatch");
    assert(handle.generation == innerId.generation && "at called with old generation");
    assert(innerId.index < m_items.size() && "inner index out of range");

    return m_items[innerId.index];
}

template <typename T>
const T& Dictionary<T>::at(DictKey handle) const
{
    assert(handle.index < m_sparseIds.size() && "outer index out of range");

    DictKey innerId = m_sparseIds[handle.index];

    assert(handle.typeId == m_itemTypeId && "typeId mismatch");
    assert(handle.generation == innerId.generation && "at called with old generation");
    assert(innerId.index < m_items.size() && "inner index out of range");

    return m_items[innerId.index];
}

template <typename T>
T& Dictionary<T>::operator[](DictKey handle)
{
    return at(handle);
}

template <typename T>
const T& Dictionary<T>::operator[](DictKey handle) const
{
    return at(handle);
}

template <typename T>
template <typename... Params>
DictKey Dictionary<T>::emplace(Params... args) {
    return insert(T{ args... });
}

template <typename T>
template <typename... Params>
KeySet Dictionary<T>::emplaceItems(int n, Params... args)
{
    KeySet handles(n);
    assert(n > 0 && "emplaceItems called with n = 0");
    m_fragmented = 1;

    m_items.reserve(m_items.size() + n); // reserve the space we need (if not already there)
    m_meta.reserve(m_meta.size() + n);

    std::generate_n(handles.begin(), n, [&, this](){ return emplace(args...); });

    return handles; // efficient to return vector by value, copy elided with NVRO (or with C++11 move semantics)
}


template <typename T>
typename Dictionary<T>::DenseSet_t::iterator Dictionary<T>::begin()
{
    return m_items.begin();
}

template <typename T>
typename Dictionary<T>::DenseSet_t::const_iterator Dictionary<T>::cbegin() const
{
    return m_items.cbegin();
}

template <typename T>
typename Dictionary<T>::DenseSet_t::iterator Dictionary<T>::end()
{
    return m_items.end();
}

template <typename T>
typename Dictionary<T>::DenseSet_t::const_iterator Dictionary<T>::cend() const
{
    return m_items.cend();
}

template <typename T>
size_t Dictionary<T>::erase(DictKey handle)
{
    if (!isValid(handle)) {
        return 0;
    }
    m_fragmented = 1;

    DictKey innerId = m_sparseIds[handle.index];
    uint32_t innerIndex = innerId.index;

    // push this slot to the back of the freelist
    innerId.free = 1;
    ++innerId.generation; // increment generation so remaining outer ids go stale
    innerId.index = 0xFFFFFFFF; // max numeric value represents the end of the freelist
    m_sparseIds[handle.index] = innerId; // write outer id changes back to the array

    if (freeListEmpty()) {
        // if the freelist was empty, it now starts (and ends) at this index
        m_freeListFront = handle.index;
        m_freeListBack = m_freeListFront;
    }
    else {
        m_sparseIds[m_freeListBack].index = handle.index; // previous back of the freelist points to new back
        m_freeListBack = handle.index; // new freelist back is stored
    }

    // remove the component by swapping with the last element, then pop_back
    if (m_items.size() > 1) {
        std::swap(m_items.at(innerIndex), m_items.back());
        std::swap(m_meta.at(innerIndex), m_meta.back());

        // fix the ComponentId index of the swapped component
        m_sparseIds[m_meta.at(innerIndex).denseToSparse].index = innerIndex;
    }

    m_items.pop_back();
    m_meta.pop_back();

    return 1;
}

template <typename T>
size_t Dictionary<T>::eraseItems(const KeySet& handles)
{
    size_t count = 0;
    for (auto h : handles) {
        count += erase(h);
    }
    return count;
}

template <typename T>
DictKey Dictionary<T>::insert(T&& i)
{
    DictKey handle = { 0 };
    m_fragmented = 1;

    if (freeListEmpty()) {
        DictKey innerId = {
            (uint32_t)m_items.size(),
            1,
            m_itemTypeId,
            0
        };

        handle = innerId;
        handle.index = (uint32_t)m_sparseIds.size();

        m_sparseIds.push_back(innerId);
    }
    else {
        uint32_t outerIndex = m_freeListFront;
        DictKey &innerId = m_sparseIds.at(outerIndex);

        m_freeListFront = innerId.index; // the index of a free slot refers to the next free slot
        if (freeListEmpty()) {
            m_freeListBack = m_freeListFront;
        }

        // convert the index from freelist to inner index
        innerId.free = 0;
        innerId.index = (uint32_t)m_items.size();

        handle = innerId;
        handle.index = outerIndex;
    }

    m_items.push_back(std::forward<T>(i));
    m_meta.push_back({ handle.index });

    return handle;
}

template <typename T>
DictKey Dictionary<T>::insert(const T& i)
{
    return insert(std::move(T{ i }));
}

template <typename T>
void Dictionary<T>::clear() noexcept
{
    uint32_t size = static_cast<uint32_t>(m_sparseIds.size());

    if (size > 0) {
        m_items.clear();
        m_meta.clear();

        m_freeListFront = 0;
        m_freeListBack = size - 1;
        m_fragmented = 0;

        for (uint32_t i = 0; i < size; ++i) {
            auto& id = m_sparseIds[i];
            id.free = 1;
            ++id.generation;
            id.index = i + 1;
        }
        m_sparseIds[size - 1].index = 0xFFFFFFFF;
    }
}

template <typename T>
void Dictionary<T>::reset() noexcept
{
    m_freeListFront = 0xFFFFFFFF;
    m_freeListBack = 0xFFFFFFFF;
    m_fragmented = 0;

    m_items.clear();
    m_meta.clear();
    m_sparseIds.clear();
}

template <typename T>
bool Dictionary<T>::isValid(DictKey handle) const
{
    if (handle.index >= m_sparseIds.size()) {
        return false;
    }

    DictKey innerId = m_sparseIds[handle.index];

    return (innerId.index < m_items.size() &&
            handle.typeId == m_itemTypeId &&
            handle.generation == innerId.generation);
}

template <typename T>
bool Dictionary<T>::isEmpty() const noexcept
{
    return m_items.size() == 0;
}

template <typename T>
size_t Dictionary<T>::size() const noexcept
{
    return m_items.size();
}

template <typename T>
size_t Dictionary<T>::capacity() const noexcept
{
    return m_items.capacity();
}

template <typename T>
template <typename Compare>
size_t Dictionary<T>::defragment(Compare comp, size_t maxSwaps)
{
    if (m_fragmented == 0) { return 0; }
    size_t swaps = 0;

    int i = 1;
    for (; i < m_items.size() && (maxSwaps == 0 || swaps < maxSwaps); ++i) {
        T tmp = m_items[i];
        Meta_t tmpMeta = m_meta[i];

        int j = i - 1;
        int j1 = j + 1;

        // trivially copyable implementation
        if (std::is_trivially_copyable<T>::value) {
            while (j >= 0 && comp(m_items[j], tmp)) {
                m_sparseIds[m_meta[j].denseToSparse].index = j1;
                --j;
                --j1;
            }
            if (j1 != i) {
                memmove(&m_items[j1+1], &m_items[j1], sizeof(T) * (i - j1));
                memmove(&m_meta[j1+1], &m_meta[j1], sizeof(Meta_t) * (i - j1));
                ++swaps;

                m_items[j1] = tmp;
                m_meta[j1] = tmpMeta;
                m_sparseIds[m_meta[j1].denseToSparse].index = j1;
            }
        }
        // standard implementation
        else {
            while (j >= 0 && (maxSwaps == 0 || swaps < maxSwaps) &&
                   comp(m_items[j], tmp))
            {
                m_items[j1] = std::move(m_items[j]);
                m_meta[j1] = std::move(m_meta[j]);
                m_sparseIds[m_meta[j1].denseToSparse].index = j1;
                --j;
                --j1;
                ++swaps;
            }

            if (j1 != i) {
                m_items[j1] = tmp;
                m_meta[j1] = tmpMeta;
                m_sparseIds[m_meta[j1].denseToSparse].index = j1;
            }
        }
    }
    if (i == m_items.size()) {
        m_fragmented = 0;
    }

    return swaps;
}

template <typename T>
typename Dictionary<T>::DenseSet_t& Dictionary<T>::getItems()
{
    return m_items;
}

template <typename T>
const typename Dictionary<T>::DenseSet_t& Dictionary<T>::getItems() const
{
    return m_items;
}

template <typename T>
typename Dictionary<T>::MetaSet_t& Dictionary<T>::getMeta()
{
    return m_meta;
}

template <typename T>
const typename Dictionary<T>::MetaSet_t& Dictionary<T>::getMeta() const
{
    return m_meta;
}

template <typename T>
KeySet& Dictionary<T>::getIds()
{
    return m_sparseIds;
}

template <typename T>
const KeySet& Dictionary<T>::getIds() const
{
    return m_sparseIds;
}

template <typename T>
uint32_t Dictionary<T>::getFreeListFront() const
{
    return m_freeListFront;
}

template <typename T>
uint32_t Dictionary<T>::getFreeListBack() const
{
    return m_freeListBack;
}

template <typename T>
uint16_t Dictionary<T>::getItemTypeId() const
{
    return m_itemTypeId;
}

template <typename T>
uint32_t Dictionary<T>::getInnerIndex(DictKey handle) const
{
    assert(handle.index < m_sparseIds.size() && "outer index out of range");

    DictKey innerId = m_sparseIds[handle.index];

    assert(handle.typeId == m_itemTypeId && "typeId mismatch");
    assert(handle.generation == innerId.generation && "at called with old generation");
    assert(innerId.index < m_items.size() && "inner index out of range");

    return innerId.index;
}

template <typename T>
bool Dictionary<T>::freeListEmpty() const
{
    return (m_freeListFront == 0xFFFFFFFF);
}

// struct DictKey comparison functions
bool operator==(const DictKey& a, const DictKey& b)
{
    return (a.value == b.value);
}

bool operator!=(const DictKey& a, const DictKey& b)
{
    return (a.value != b.value);
}

bool operator< (const DictKey& a, const DictKey& b)
{
    return (a.value < b.value);
}

bool operator> (const DictKey& a, const DictKey& b)
{
    return (a.value > b.value);
}

