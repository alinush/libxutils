/*
 * OtherTests.cpp
 *
 *  Created on: Thursday, September 21st, 2017
 *      Author: alinush
 */

#include <map>
#include <set>
#include <vector>
#include <string>
#include <cassert>
#include <memory>
#include <algorithm>
#include <stdexcept>

#include <xutils/Log.h>
#include <xutils/Timer.h>
#include <xutils/Utils.h>
#include <xutils/NotImplementedException.h>
#include <xassert/XAssert.h>

using namespace std;

void testUtils();
void testRandomSubsets();

int main(int argc, char * argv[]) {
    (void)argc;
    (void)argv;

    unsigned int seed = static_cast<unsigned int>(time(NULL));
    loginfo << "Randomness seed passed to srand(): " << seed << endl;
    srand(seed);

    testUtils();
    for(int i = 0; i < 10; i++) {
        testRandomSubsets();
    }

    testAssertEqual(Utils::smallestPowerOfTwoAbove(0), 1);
    testAssertEqual(Utils::smallestPowerOfTwoAbove(1), 1);
    testAssertEqual(Utils::smallestPowerOfTwoAbove(2), 2);
    testAssertEqual(Utils::smallestPowerOfTwoAbove(3), 4);
    testAssertEqual(Utils::smallestPowerOfTwoAbove(4), 4);
    testAssertEqual(Utils::smallestPowerOfTwoAbove(5), 8);
    testAssertEqual(Utils::smallestPowerOfTwoAbove(6), 8);

    testAssertEqual(Utils::greatestPowerOfTwoBelow(0), 0);
    testAssertEqual(Utils::greatestPowerOfTwoBelow(1), 1);
    testAssertEqual(Utils::greatestPowerOfTwoBelow(2), 2);
    testAssertEqual(Utils::greatestPowerOfTwoBelow(3), 2);
    testAssertEqual(Utils::greatestPowerOfTwoBelow(4), 4);
    testAssertEqual(Utils::greatestPowerOfTwoBelow(5), 4);
    testAssertEqual(Utils::greatestPowerOfTwoBelow(6), 4);

    testAssertEqual(Utils::log2floor(1), 0);
    testAssertEqual(Utils::log2floor(2), 1);
    testAssertEqual(Utils::log2floor(3), 1);
    testAssertEqual(Utils::log2floor(4), 2);
    testAssertEqual(Utils::log2floor(5), 2);
    testAssertEqual(Utils::log2floor(6), 2);
    testAssertEqual(Utils::log2floor(7), 2);
    testAssertEqual(Utils::log2floor(8), 3);
    testAssertEqual(Utils::log2floor(15), 3);
    testAssertEqual(Utils::log2floor(16), 4);
    testAssertEqual(Utils::log2floor(512), 9);
    testAssertEqual(Utils::log2floor(1024*1024), 20);

    testAssertEqual(Utils::log2ceil(1), 0);
    testAssertEqual(Utils::log2ceil(2), 1);
    testAssertEqual(Utils::log2ceil(3), 2);
    testAssertEqual(Utils::log2ceil(4), 2);
    testAssertEqual(Utils::log2ceil(5), 3);
    testAssertEqual(Utils::log2ceil(6), 3);
    testAssertEqual(Utils::log2ceil(7), 3);
    testAssertEqual(Utils::log2ceil(8), 3);
    testAssertEqual(Utils::log2ceil(15), 4);
    testAssertEqual(Utils::log2ceil(16), 4);
    testAssertEqual(Utils::log2ceil(511), 9);
    testAssertEqual(Utils::log2ceil(512), 9);
    testAssertEqual(Utils::log2ceil(513), 10);
    testAssertEqual(Utils::log2ceil(1024*1024), 20);

    try {
        std::string a("abc");
        throw libxutils::NotImplementedException(a);
        throw libxutils::NotImplementedException();
        throw libxutils::NotImplementedException("a");
    } catch(const libxutils::NotImplementedException& e) {
        loginfo << "Caught NotImplementedException: " << e.what() << endl;
    } catch(const std::exception& e) {
        assertFail("Did not expect another exception");
    }

    {
        ScopedTimer<> t(std::cout, "Default ", " microseconds\n");
    }

    {
        ScopedTimer<std::chrono::seconds> t(std::cout, "Seconds ", " seconds\n");
    }

    loginfo << "Exited gracefully with 0."<< endl;
    return 0;
}

void testUtils()
{
    testAssertEqual(Utils::numBits(1), 1);
    testAssertEqual(Utils::numBits(2), 2);
    testAssertEqual(Utils::numBits(3), 2);
    testAssertEqual(Utils::numBits(4), 3);
    testAssertEqual(Utils::numBits(5), 3);
    testAssertEqual(Utils::numBits(6), 3);
    testAssertEqual(Utils::numBits(7), 3);
    testAssertEqual(Utils::numBits(8), 4);

    loginfo << "Utils::numBits passed!" << endl;

    testAssertEqual(Utils::pow2(0), 1);
    testAssertEqual(Utils::pow2(1), 2);
    testAssertEqual(Utils::pow2(2), 4);
    testAssertEqual(Utils::pow2(3), 8);
    testAssertEqual(Utils::pow2(4), 16);
    testAssertEqual(Utils::pow2(5), 32);

    loginfo << "Utils::pow2 passed!" << endl;

    testAssertEqual(Utils::withCommas(3), "3");
    testAssertEqual(Utils::withCommas(30), "30");
    testAssertEqual(Utils::withCommas(100), "100");
    testAssertEqual(Utils::withCommas(1234), "1,234");
    testAssertEqual(Utils::withCommas(91234), "91,234");
    testAssertEqual(Utils::withCommas(191234), "191,234");
    testAssertEqual(Utils::withCommas(7191234), "7,191,234");

    loginfo << "Utils::withCommas passed!" << endl;
}

void testRandomSubsets() 
{
    std::vector<int> v;
    std::set<int> s;
    const int max = 10;
    Utils::randomSubset(v, max, 6);
    Utils::randomSubset(s, max, 6);
    testAssertEqual(v.size(), s.size());

    std::for_each(v.begin(), v.end(), [](int &el) {
        assertGreaterThanOrEqual(el, 0);
        assertStrictlyLessThan(el, max);
    });
}
