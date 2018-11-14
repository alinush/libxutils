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
    assertEqual(Utils::numBits(1), 1);
    assertEqual(Utils::numBits(2), 2);
    assertEqual(Utils::numBits(3), 2);
    assertEqual(Utils::numBits(4), 3);
    assertEqual(Utils::numBits(5), 3);
    assertEqual(Utils::numBits(6), 3);
    assertEqual(Utils::numBits(7), 3);
    assertEqual(Utils::numBits(8), 4);

    loginfo << "Utils::numBits passed!" << endl;

    assertEqual(Utils::pow2(0), 1);
    assertEqual(Utils::pow2(1), 2);
    assertEqual(Utils::pow2(2), 4);
    assertEqual(Utils::pow2(3), 8);
    assertEqual(Utils::pow2(4), 16);
    assertEqual(Utils::pow2(5), 32);

    loginfo << "Utils::pow2 passed!" << endl;

}

void testRandomSubsets() 
{
    std::vector<int> v;
    std::set<int> s;
    const int max = 10;
    Utils::randomSubset(v, max, 6);
    Utils::randomSubset(s, max, 6);
    assertEqual(v.size(), s.size());

    std::for_each(v.begin(), v.end(), [&max](int &el) {
        assertGreaterThanOrEqual(el, 0);
        assertStrictlyLessThan(el, max);
    });
}
