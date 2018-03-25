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

#include "xutils/Log.h"
#include "xutils/Utils.h"
#include "xassert/XAssert.h"

using namespace std;

void testUtils();

int main(int argc, char * argv[]) {
    (void)argc;
    (void)argv;

    unsigned int seed = static_cast<unsigned int>(time(NULL));
    loginfo << "Randomness seed passed to srand(): " << seed << endl;
    srand(seed);

    testUtils();

    loginfo << "Exited gracefully with 0."<< endl;
    return 0;
}

void testUtils() {
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
