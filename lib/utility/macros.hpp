#ifndef SCRYVER_UTILITY_MACROS_HPP
#define SCRYVER_UTILITY_MACROS_HPP

// namespace Scryver {

// namespace Utility {

// }  // namespace Utility

// }  // namespace Scryver

#define VECTOR_ARRAY_SIZE(vData)        (sizeof(vData[0]) * vData.size())
#define CLAMP(value, min, max)          ((value < min) ? min : ((value > max) ? max : value))

#endif  // SCRYVER_UTILITY_MACROS_HPP
