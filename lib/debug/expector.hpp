#ifndef SCRYVER_DEBUG_EXPECTOR_HPP
#define SCRYVER_DEBUG_EXPECTOR_HPP

#ifndef NDEBUG
#include <cassert>
#endif

// namespace Scryver {

// namespace Debug {

// namespace Printer
// {

#ifndef NDEBUG

#define makeSure(expectation, msg) \
    do { assert(expectation && msg); } while (0)

#else

#define makeSure(expectation, msg)  do { } while (0)

#endif
// }

// }  // namespace Debug

// }  // namespace Scryver

#endif  // SCRYVER_DEBUG_EXPECTOR_HPP
