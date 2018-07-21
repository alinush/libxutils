/*
 * Utils.h
 *
 *  Created on: Oct 10, 2014
 *      Author: Alin Tomescu <alinush@mit.edu>
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <string>
#include <set>

#include "xassert/XAssert.h"

// TODO: namespace into libxutils

class Utils {
public:
    /**
     * @param T is the type of the elements being averaged
     * @Param E is the type of the average itself
     */
    template<class T, class E>
    class MinMaxAvg {
    public:
        T min, max;
        E avg;

    public:
        static MinMaxAvg<T, E> compute(const std::vector<T>& v) {
            MinMaxAvg<T, E> mma;
            mma.min = v[0];
            mma.max = v[0];
            mma.avg = 0;

            for(auto it = v.begin(); it != v.end(); it++) {
                if(*it < mma.min) {
                    mma.min = *it;
                }
                if(*it > mma.max) {
                    mma.max = *it;
                }
                mma.avg += static_cast<E>(*it);
            }

            mma.avg = mma.avg / static_cast<E>(v.size());

            return mma;
        }
    };

public:
    template<class C, class V>
    static void removeFirst(C& c, const V& v) {
        auto it = std::find(c.begin(), c.end(), v);
        if (it != c.end()) {
            c.erase(it);
        }
    }

    static bool fileExists(const std::string& filename);

    /**
     * Returns the number of bits needed to represent a positive integer n:
     * Specifically, return 1 if n == 0 and ceil(log_2(n)) otherwise.
     * e.g., numBits(1) = 1
     * e.g., numBits(2) = 2
     * e.g., numBits(3) = 2
     * e.g., numBits(4) = 3
     */
    static int numBits(int n) {
        assertGreaterThanOrEqual(n, 0);
        if(n == 0)
            return 1;

        int l = 0;
        while(n > 0) {
            n = n / 2;
            l++;
        }

        return l;
    }

    template <class T>
    static int numDigits(T number)
    {
        int digits = 0;

        if (number < 0)
            digits++;

        while(number > 0) {
            number /= 10;
            digits++;
        }

        return digits;
    }

    /**
     * Returns floor(log2(n))
     */
    template<class T>
    static T log2floor(T n) {
        if(n < 0)
            throw std::logic_error("log2 on negative numbers doesn't work");

        T res = 0;
        while (n /= 2) {
            res++;
        }
        return res;
    }

    /**
     * Returns 2^exp
     */
    static int pow2(int exp) {
        if(exp >= 0) {
            return 1 << exp;
        } else {
            throw std::logic_error("Power must be positive");
        }
    }

    /**
     * Used to be called: int nearestPowerOfTwo(int n)
     */
    static int smallestPowerOfTwoAbove(int n) {
        assertGreaterThanOrEqual(n, 0);

        int power = 1;
        while(power < n) {
            power *= 2;
        }
        return power;
    }

    static int greatestPowerOfTwoBelow(int n) {
        if(n == 0)
            return 0;

        int ret = 1;

        while(n >>= 1)
            ret <<= 1;

        return ret;
    }

    template<class T>
    static std::string humanizeBytes(T bytes) {
        std::ostringstream str;
        long double result = static_cast<long double>(bytes);
        const char * units[] = { "bytes", "KB", "MB", "GB", "TB" };
        unsigned int i = 0;
        while(result >= 1024.0) {
            result /= 1024.0;
            i++;
        }

        str << result;
        str << " ";
        str << units[i];

        return str.str();
    }

    /**
     * Returns k random numbers in the range [0, n) + offset as an std::set
     */
    template<class T>
    static void randomSubset(std::set<T>& rset, int n, int k, T offset = 0) {
        // NOTE: Does not need cryptographically secure RNG
        while (rset.size() < static_cast<typename std::set<T>::size_type>(k)) {
            T i = static_cast<T>(rand() % n) + offset;

            rset.insert(i);
        }
    }

    /**
     * Returns k random numbers in the range [0, n) + offset as an std::vector
     */
    template<class T>
    static void randomSubset(std::vector<T>& v, int n, int k, T offset = 0) {
        std::set<T> s;
        v.resize(static_cast<size_t>(k));

        randomSubset(s, n, k, offset);
        v.assign(s.begin(), s.end());
        assertEqual(s.size(), v.size());
    }

    static void hex2bin(const char * hexBuf, int hexBufLen, unsigned char * bin, int binCapacity);
    static void bin2hex(const void * data, int dataLen, char * hexBuf, int hexBufCapacity);

    static std::string bin2hex(const void * data, int dataLen);
    static void hex2bin(const std::string& hexStr, unsigned char * bin, int binCapacity);
};
