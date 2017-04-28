#ifndef SCRYVER_UTILS_TYPE_UTILS_HPP
#define SCRYVER_UTILS_TYPE_UTILS_HPP

namespace Scryver {

namespace Utils {

template<class Tag, class impl, impl default_value>
class ID
{
public:
    static ID invalid() { return ID(); }

    // Defaults to ID::invalid()
    ID() : m_val(default_value) { }

    // Explicit constructor:
    explicit ID(impl val) : m_val(val) { }

    // Explicit conversion to get back the impl:
    explicit operator impl() const { return m_val; }

    friend bool operator==(ID a, ID b) { return a.m_val == b.m_val; }
    friend bool operator!=(ID a, ID b) { return a.m_val != b.m_val; }

private:
    impl m_val;
};

}  // namespace Utils

}  // namespace Scryver

#endif  // SCRYVER_UTILS_TYPE_UTILS_HPP
