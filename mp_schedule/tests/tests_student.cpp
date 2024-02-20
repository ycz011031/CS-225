#include <catch2/catch_test_macros.hpp>


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "schedule.h"
#include "tests_util.h"

// You may write your own test cases in this file to test your code.
// Test cases in this file are not graded.

TEST_CASE("My Test Case", "") {
    const V2D roster = {{"A", "ae_", "ac_"},\
     {"B", "be_", "bc_", "bd_"}, \
     {"C", "ac_", "bc_","cd_" }, \
     {"D", "bd_", "cd_", "de_"}, \
     {"E", "ae_", "be_", "de_"}
     };

    std::vector<std::string> timeslots = {"9AM", "11AM", "1PM"};

    V2D out = schedule(roster, timeslots);
    for (unsigned i =0; i<out.size(); i++){
        for (unsigned j=0; j<out[i].size();j++){
            cout << out[i][j] << endl;
        }
    }


    verifySchedule(roster, out, 3);
}
