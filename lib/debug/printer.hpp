#ifndef SCRYVER_DEBUG_PRINTER_HPP
#define SCRYVER_DEBUG_PRINTER_HPP

#ifndef NDEBUG
#include <iostream>
#endif

// namespace Scryver {

// namespace Debug {

// namespace Printer
// {

#ifndef NDEBUG

#define debugPrint(msg) \
    do { \
        std::cout << "DEBUG::" << __FILE__ << ":" << __LINE__ << ":" << __func__ << ": " \
                  << msg << std::endl; } while (0)

#define debugPrintStart() \
    do { std::cout << "DEBUG::" << __FILE__ << ":" << __LINE__ << ":" << __func__ << ": "; } while (0)

#define debugPrintMessage(msg) \
    do { std::cout << msg; } while (0)

#define debugPrintStop() \
    do { std::cout << std::endl; } while (0)

#define errorPrint(msg) \
    do { \
        std::cerr << "ERROR::" << __FILE__ << ":" << __LINE__ << ":" << __func__ << ": " \
                  << msg << std::endl; } while (0)

#define errorPrintStart() \
    do { std::cerr << "ERROR::" << __FILE__ << ":" << __LINE__ << ":" << __func__ << ": "; } while (0)

#define errorPrintMessage(msg) \
    do { std::cerr << msg; } while (0)

#define errorPrintStop() \
    do { std::cerr << std::endl; } while (0)

#else

#define debugPrint(msg)         do { } while (0)
#define debugPrintStart()       do { } while (0)
#define debugPrintMessage(msg)  do { } while (0)
#define debugPrintStop()        do { } while (0)
#define errorPrint(msg)         do { } while (0)
#define errorPrintStart()       do { } while (0)
#define errorPrintMessage(msg)  do { } while (0)
#define errorPrintStop()        do { } while (0)

#endif
// }

// }  // namespace Debug

// }  // namespace Scryver

#endif  // SCRYVER_DEBUG_PRINTER_HPP
