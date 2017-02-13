#ifndef SCRYVER_UTILITY_DICTIONARY_HPP
#define SCRYVER_UTILITY_DICTIONARY_HPP

#include <cstdint>
#include <vector>
#include <cassert>
#include <algorithm>
#include <type_traits>

// https://github.com/y2kiah/griffin-containers/blob/master/handle_map.h
// https://www.gamedev.net/resources/_/technical/general-programming/game-engine-containers-handle-map-r4495

namespace Scryver {

namespace Utility {

/**
 * @struct DictKey
 * @var    free        0 if active, 1 if slot is part of freelist, only applicable to inner ids
 * @var    typeId      relates to m_itemTypeId parameter of Dictionary
 * @var    generation  incrementing generation of data at the index, for tracking accesses to old data
 * @var    index       When used as a handle (outer id, given to the client):
 *                        free==0, index of id in the sparseIds array
 *                    When used as an inner id (stored in sparseIds array):
 *                        free==0, index of the item in the dense items array
 *                        free==1, index of next free slot, forming an embedded linked list
 * @var    value       unioned with the above four vars, used for direct comparison of ids
 */
struct DictKey {
    union {
        /**
        * the order of this bitfield is important for sorting prioritized by free, then typeId,
        * then generation, then index
        */
        struct {
            uint32_t index;
            uint16_t generation;
            uint16_t typeId : 15;
            uint16_t free   : 1;
        };
        uint64_t value;
    };
};
typedef std::vector<DictKey> KeySet;
#define NullDictKey          DictKey{}

template <typename T>
class Dictionary {
public:
    struct Meta_t {
        uint32_t    denseToSparse;  //!< index into m_sparseIds array stored in m_meta
    };

    typedef std::vector<T>      DenseSet_t;
    typedef std::vector<Meta_t> MetaSet_t;

    explicit Dictionary(uint16_t itemTypeId = 0, size_t reserveCount = 16);

    // Functions
    inline T&          at(DictKey handle);
    inline const T&    at(DictKey handle) const;
    inline T&          operator[](DictKey handle);
    inline const T&    operator[](DictKey handle) const;

    template <typename... Params>
    inline DictKey emplace(Params... args);

    template <typename... Params>
    KeySet emplaceItems(int n, Params... args);

    inline typename DenseSet_t::iterator       begin();
    inline typename DenseSet_t::const_iterator cbegin() const;
    inline typename DenseSet_t::iterator       end();
    inline typename DenseSet_t::const_iterator cend() const;

    size_t erase(DictKey handle);
    size_t eraseItems(const KeySet& handles);

    DictKey insert(T&& i);
    DictKey insert(const T& i);

    void clear() noexcept;
    void reset() noexcept;

    inline bool isValid(DictKey handle) const;
    inline bool isEmpty() const noexcept;

    inline size_t size() const noexcept;
    inline size_t capacity() const noexcept;

    template <typename Compare>
    size_t defragment(Compare comp, size_t maxSwaps = 0);

    inline DenseSet_t&         getItems();
    inline const DenseSet_t&   getItems() const;
    inline MetaSet_t&          getMeta();
    inline const MetaSet_t&    getMeta() const;
    inline KeySet&             getIds();
    inline const KeySet&       getIds() const;

    inline uint32_t            getFreeListFront() const;
    inline uint32_t            getFreeListBack() const;

    inline uint16_t            getItemTypeId() const;

    inline uint32_t            getInnerIndex(DictKey handle) const;

private:
    inline bool freeListEmpty() const;

    // Variables
    uint32_t    m_freeListFront = 0xFFFFFFFF; //!< start index in the embedded ComponentId freelist
    uint32_t    m_freeListBack  = 0xFFFFFFFF; //!< last index in the freelist

    uint16_t    m_itemTypeId;   //!< the DictKey::typeId to use for ids produced by this Dictionary<T>

    uint8_t     m_fragmented = 0; //<! set to 1 if modified by insert or erase since last complete defragment

    KeySet      m_sparseIds;    //!< stores a set of DictKeys, these are "inner" ids indexing into m_items
    DenseSet_t  m_items;        //!< stores items of type T
    MetaSet_t   m_meta;         //!< stores Meta_t type for each item
};

// struct DictKey comparison functions
inline bool operator==(const DictKey& a, const DictKey& b);
inline bool operator!=(const DictKey& a, const DictKey& b);
inline bool operator< (const DictKey& a, const DictKey& b);
inline bool operator> (const DictKey& a, const DictKey& b);

#include "dictionary_inl.hpp"

} // namespace Utility

} // namespace Scryver

#endif  // SCRYVER_UTILITY_DICTIONARY_HPP
