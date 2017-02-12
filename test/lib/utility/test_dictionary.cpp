#include <gtest/gtest.h>

// Following sys headers are to set/restore core dump.
// We need this because of a death test in this test code.
#include <sys/time.h>
#include <sys/resource.h>

#include <ctime>
#include <random>

#include "Scryver/Utility/Dictionary.hpp"

std::mt19937 dictRandEngine(time(NULL));

#if defined(FULL_TESTS) && FULL_TESTS
std::uniform_int_distribution<int> dictNrTestGen(100, 1000);
#else  // Fast testing
std::uniform_int_distribution<int> dictNrTestGen(1, 10);
#endif

std::uniform_int_distribution<int> dictIntGen(-65536, 65535);

using Scryver::Utility::Dictionary;
using Scryver::Utility::DictKey;
using Scryver::Utility::KeySet;

static struct rlimit old_limit;

void limit_core(void) {
  struct rlimit rlim;

  rlim.rlim_cur = rlim.rlim_max = 0;
  getrlimit(RLIMIT_CORE, &old_limit);
  setrlimit(RLIMIT_CORE, &rlim);
}

void restore_core(void) {
  setrlimit(RLIMIT_CORE, &old_limit);
}

namespace {
    struct Packet {
        int x;
        int y;
        explicit Packet(int x = 0, int y = 0) : x(x), y(y) { }
    };
}


TEST(Dictionary, Constructor)
{
    Dictionary<int> d;

    EXPECT_TRUE(d.isEmpty());
}

TEST(Dictionary, ConstructorWithType)
{
    Dictionary<int> d(2);

    EXPECT_EQ(d.getItemTypeId(), 2u);
}

TEST(Dictionary, ConstructorReserve)
{
    Dictionary<int> d(0, 13);

    EXPECT_EQ(d.capacity(), 13u);
}

TEST(Dictionary, Insertion)
{
    Dictionary<int> d(0, 1);

    DictKey handle = d.insert(5);
    int i = d[handle];

    EXPECT_EQ(i, 5);
}

TEST(Dictionary, Insertions)
{
    Dictionary<int> d;

    std::vector<DictKey> handles;
    handles.resize(d.capacity());
    for (size_t i = 0; i < handles.size(); i++)
    {
        handles[i] = d.insert(i);
    }

    for (size_t i = 0; i < handles.size(); i++)
    {
        EXPECT_EQ(d[handles[i]], static_cast<int>(i));
    }
}

TEST(Dictionary, FreeList)
{
    Dictionary<int> d(0, 2);

    DictKey handle1 = d.insert(5);
    DictKey handle2 = d.insert(3);

    d.erase(handle1);

    DictKey handle3 = d.insert(4);

    EXPECT_EQ(d[handle2], 3);
    EXPECT_EQ(d[handle3], 4);
    limit_core();
    EXPECT_DEATH(d[handle1], "at called with old generation");
    restore_core();

    EXPECT_EQ(d.size(), 2u);
    EXPECT_EQ(d.capacity(), d.size());
}

TEST(Dictionary, HandleValidity)
{
    Dictionary<int> d;

    DictKey falseHandle;
    falseHandle.value = 23;

    EXPECT_FALSE(d.isValid(falseHandle));
    DictKey handle = d.insert(34);

    EXPECT_TRUE(d.isValid(handle));
    falseHandle.value = handle.value - 2;
    EXPECT_FALSE(d.isValid(falseHandle));

    EXPECT_EQ(0u, d.erase(falseHandle));
    EXPECT_NE(0u, d.erase(handle));
}

TEST(Dictionary, GetItem)
{
    Dictionary<int> d;
    DictKey item = d.insert(15);

    const Dictionary<int> constD = d;

    int normItem = d[item];
    const int constItem = constD[item];

    EXPECT_EQ(15, normItem);
    EXPECT_EQ(15, constItem);

    int normItem2 = d.at(item);
    const int constItem2 = constD.at(item);

    EXPECT_EQ(15, normItem2);
    EXPECT_EQ(15, constItem2);
}

TEST(Dictionary, EmplaceItem)
{
    Dictionary<Packet> d;
    DictKey i = d.emplace(4, 5);

    Packet p = d[i];
    EXPECT_EQ(p.x, 4);
    EXPECT_EQ(p.y, 5);
}

TEST(Dictionary, EmplaceItems)
{
    Dictionary<Packet> d;
    KeySet keys = d.emplaceItems(dictNrTestGen(dictRandEngine), 154, 6574);

    for (size_t i = 0; i < keys.size(); i++)
    {
        Packet p = d[keys[i]];
        EXPECT_EQ(p.x, 154);
        EXPECT_EQ(p.y, 6574);
    }
}

TEST(Dictionary, FastIteration)
{
    Dictionary<Packet> d;
    KeySet keys = d.emplaceItems(dictNrTestGen(dictRandEngine), 354, 3774);

    for (auto i = d.begin(); i != d.end(); i++)
    {
        Packet p = *i;
        EXPECT_EQ(p.x, 354);
        EXPECT_EQ(p.y, 3774);
    }

    for (auto i = d.cbegin(); i != d.cend(); i++)
    {
        const Packet& p = *i;
        EXPECT_EQ(p.x, 354);
        EXPECT_EQ(p.y, 3774);
    }
}


TEST(Dictionary, ClearAndUseFreeList)
{
    const size_t NUM_TESTS = dictNrTestGen(dictRandEngine) + 5;

    Dictionary<Packet> d;
    KeySet keys = d.emplaceItems(NUM_TESTS, 354, 3774);

    EXPECT_EQ(NUM_TESTS, keys.size());
    d.clear();

    keys = d.emplaceItems(NUM_TESTS - 5, 234, 404);
    EXPECT_EQ(d.getFreeListFront(), NUM_TESTS - 5);
    EXPECT_EQ(d.getFreeListBack(), NUM_TESTS - 1);
    EXPECT_EQ(NUM_TESTS - 5, keys.size());
}

