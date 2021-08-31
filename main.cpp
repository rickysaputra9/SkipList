//
// Created by Ricky Saputra on 02/23/2020
//

#include "skiplist.h"
#include <iostream>
#include <sstream>

using namespace std;

int totalPassed = 0;
int totalTests = 0;

template <typename T> string isOK(const T& got, const T& expected) {
    ++totalTests;
    if (got == expected) {
        ++totalPassed;
        return "OK: ";
    } else {
        cout << "    Got   " << got << "\n expected " << expected << endl;
        return "ERR: ";
    }
}

void test02() {
    SkipList skipList(3);
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(), string("Level: 2 -- -2147483648, 2147483647, \n"
                                  "Level: 1 -- -2147483648, 2147483647, \n"
                                  "Level: 0 -- -2147483648, 2147483647, \n"))
                .c_str()
         << "Empty SkipList of Depth=3" << endl;
    srand(100);
    skipList.add(10);
    skipList.add(30);
    skipList.add(5);
    skipList.add(25);
    skipList.add(15);
    skipList.add(1000);
    skipList.add(27);
    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                     "Level: 2 -- -2147483648, 5, 1000, 2147483647, \n"
                     "Level: 1 -- -2147483648, 5, 27, 1000, 2147483647, \n"
                     "Level: 0 -- -2147483648, 5, 10, 15, 25, 27, 30, 1000, 2147483647, \n"))
         << "SkipList of Depth=3 with 10, 30, 5, 25, 15, 1000, 27" << endl;
    cout << isOK(skipList.contains(10), true) << "Contains 10" << endl;
    cout << isOK(skipList.contains(30), true) << "Contains 30" << endl;
    cout << isOK(skipList.contains(71), false) << "Does not contain 71" << endl;

    cout << isOK(skipList.remove(30), true) << "Remove 30" << endl;
    cout << isOK(skipList.remove(68), false) << "Does not remove 68" << endl;

    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 "Level: 2 -- -2147483648, 5, 1000, 2147483647, \n"s +
                 "Level: 1 -- -2147483648, 5, 27, 1000, 2147483647, \n"s +
                 "Level: 0 -- -2147483648, 5, 10, 15, 25, 27, 1000, 2147483647, \n"s)
         << "SkipList of Depth=3 with 10, 5, 25, 1000, 27" << endl;
}

void test01() {
    SkipList skipList;
    stringstream ss;
    ss << skipList;
    cout << isOK(ss.str(), string("Level: 0 -- -2147483648, 2147483647, \n"))
         << "Empty SkipList" << endl;
    skipList.add(10);
    skipList.add(30);
    skipList.add(5);
    skipList.add(25);
    ss.str("");
    ss << skipList;
    cout << isOK(ss.str(),
                 string(
                     "Level: 0 -- -2147483648, 5, 10, 25, 30, 2147483647, \n"))
         << "Added 10, 30, 5, 25," << endl;
}


// Added extensive test on SkipList
void test03() {
    srand(7859);
    SkipList Skip(8);
    stringstream Ss;

    // Adding the first 150 prime number to SkipList
    int i = 0;
    int Num = 0;
    for (i = 1; i < 150; i++) {
        int Counter = 0;
        for (Num =i; Num>=1; Num--) {
            if(i % Num == 0) {
                Counter = Counter + 1;
            }
        }
        if (Counter == 2) {
            Skip.add(i);
        }
    }
    Ss << Skip;
    cout << Ss.str() << endl;

    cout << endl;
    cout << "=========================" << endl;
    cout << "Testing adding duplicates" << endl;
    cout << "=========================" << endl;
    cout << endl;

    cout << isOK(Skip.add(3), false) << "Did not add duplicate 3" << endl;
    cout << isOK(Skip.add(83), false) << "Did not add duplicate 83" << endl;
    cout << isOK(Skip.add(107), false) << "Did not add duplicate 107" << endl;

    cout << endl;
    cout << Skip << endl;

    cout << endl;
    cout << "=========================" << endl;
    cout << "    Testing contains     " << endl;
    cout << "=========================" << endl;
    cout << endl;

    cout << isOK(Skip.contains(3), true) << "Contains 3" << endl;
    cout << isOK(Skip.contains(7), true) << "Contains 7" << endl;
    cout << isOK(Skip.contains(23), true) << "Contains 23" << endl;
    cout << isOK(Skip.contains(47), true) << "Contains 47" << endl;
    cout << isOK(Skip.contains(101), true) << "Contains 101" << endl;
    cout << isOK(Skip.contains(107), true) << "Contains 107" << endl;
    cout << isOK(Skip.contains(149), true) << "Contains 149" << endl;

    cout << isOK(Skip.contains(4), false) << "Does not contains 4" << endl;
    cout << isOK(Skip.contains(42), false) << "Does not contains 42" << endl;
    cout << isOK(Skip.contains(68), false) << "Does not contains 68" << endl;
    cout << isOK(Skip.contains(150), false) << "Does not contain 150" << endl;
    cout << isOK(Skip.contains(-11), false) << "Does not contains -11" << endl;
    cout << isOK(Skip.contains(9999), false) << "Does not contains 9999" << endl;

    cout << endl;
    cout << "=========================" << endl;
    cout << "      Testing Remove     " << endl;
    cout << "=========================" << endl;
    cout << endl;

    cout << isOK(Skip.remove(2), true) << "Remove 2" << endl;
    cout << isOK(Skip.remove(23), true) << "Remove 23" << endl;
    cout << isOK(Skip.remove(101), true) << "Remove 101" << endl;
    cout << isOK(Skip.remove(127), true) << "Remove 127" << endl;

    cout << isOK(Skip.remove(-11), false) << "Does not remove -11" << endl;
    cout << isOK(Skip.remove(9999), false) << "Does not remove 9999" << endl;

    cout << endl;
    cout << Skip << endl;

}

int main() {
    cout << "Because of the random nature of SkipList, "
         << "the skip list levels may not match" << endl;
    // Set the random seed for easy debugging
    // NOLINTNEXTLINE
    srand(424242);
    test01();
    test02();

    cout << endl;
    cout << "=========================" << endl;
    cout << "     Added Extensive     " << endl;
    cout << "     Test on SkipList    " << endl;
    cout << "  First 150 prime number " << endl;
    cout << "    in 8 level SkipList  " << endl;
    cout << "=========================" << endl;
    cout << endl;

    test03();

    cout << "Passed: " << totalPassed << "/" << totalTests << endl;
    return 0;
}