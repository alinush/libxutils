/*
 * Timer.cpp
 *
 *  Created on: Aug 25, 2017
 *      Author: alinush
 */

#include "xutils/Timer.h"
#include "xutils/Utils.h"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const AveragingTimer& t) {
    if(t.numIterations() > 0)
        out << t.name << ": "
            << Utils::withCommas(t.averageLapTime()) << " microsec per lap"
            << ", -/+ "
            << t.stddev() << " stddev"
            << ", " << Utils::withCommas(t.min.count()) << " min"
            << ", " << Utils::withCommas(t.max.count()) << " max"
            << " (" << t.numIterations() << " laps)";
    else
        out << t.name << ": did not run any laps yet.";
    return out;
}
