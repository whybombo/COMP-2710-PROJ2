/*
* FILE NAME: project2_Nelson_bzn0021
* AUTHOR: Blake Nelson
* Code to test for the chances of 3 people shooting in separate cases/strategies and who lives/dies.
* COMPILE: g++ project2_Nelson_bzn0021.cpp -o project2.out
* 
* I used the framework given by the instructor to help write out the beginning code. I used the online resource stackoverflow to help with starting how I would write out the 4 strategies
* and prob of each person and their strategys to hit. I also used it to figure out how to write out the protoypes returns. I used chatgbt to help organize and understand parts of the code 
* I had trouble working around (mainly the test cases) and it also helped me develop the 4 void simulations because they were giving me a hard time on how to actually used their probability
* and apply it. From classmates I learned how much using boolean for if they were alive or dead is useful to this type of quesiton and implemented that strategy.
*/
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>

using namespace std;

//prototypes
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
// test proto
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);
//constant
const int NUM_DUELS = 1000000;

int main() {
    // random number generator
    srand(time(0));

    cout << "*** Welcome to Blake's Duel Simulator ***\n";

    // Unit tests
    test_at_least_two_alive();
    test_Aaron_shoots1();
    test_Bob_shoots();
    test_Charlie_shoots();
    test_Aaron_shoots2();

    // Strategy 1
    cout << "Ready to test strategy 1 (run " << NUM_DUELS << " times):\n";
    cout << "Press Enter to continue...";
    cin.ignore().get();

    int aaron_wins_1 = 0, bob_wins_1 = 0, charlie_wins_1 = 0;

    for (int i = 0; i < NUM_DUELS; i++) {
        bool A_alive = true, B_alive = true, C_alive = true;

        while (at_least_two_alive(A_alive, B_alive, C_alive)) {
            if (A_alive)
                Aaron_shoots1(B_alive, C_alive);
            if (B_alive)
                Bob_shoots(A_alive, C_alive);
            if (C_alive)
                Charlie_shoots(A_alive, B_alive);
        }

        if (A_alive)
            aaron_wins_1++;
        else if (B_alive)
            bob_wins_1++;
        else
            charlie_wins_1++;
    }
    // Strategy 1 output
    cout << "Aaron won " << aaron_wins_1 << "/" << NUM_DUELS << " duels or "
         << static_cast<double>(aaron_wins_1) / NUM_DUELS * 100 << "%\n";
    cout << "Bob won " << bob_wins_1 << "/" << NUM_DUELS << " duels or "
         << static_cast<double>(bob_wins_1) / NUM_DUELS * 100 << "%\n";
    cout << "Charlie won " << charlie_wins_1 << "/" << NUM_DUELS << " duels or "
         << static_cast<double>(charlie_wins_1) / NUM_DUELS * 100 << "%\n";

    // Strategy 2
    cout << "\nReady to test strategy 2 (run " << NUM_DUELS << " times):\n";
    cout << "Press Enter to continue...";
    cin.ignore().get();

    int aaron_wins_2 = 0, bob_wins_2 = 0, charlie_wins_2 = 0;

    for (int i = 0; i < NUM_DUELS; i++) {
        bool A_alive = true, B_alive = true, C_alive = true;

        while (at_least_two_alive(A_alive, B_alive, C_alive)) {
            if (A_alive)
                Aaron_shoots2(B_alive, C_alive);
            if (B_alive)
                Bob_shoots(A_alive, C_alive);
            if (C_alive)
                Charlie_shoots(A_alive, B_alive);
        }

        if (A_alive)
            aaron_wins_2++;
        else if (B_alive)
            bob_wins_2++;
        else
            charlie_wins_2++;
    }
    // Strategy 2 output
    cout << "Aaron won " << aaron_wins_2 << "/" << NUM_DUELS << " duels or "
         << static_cast<double>(aaron_wins_2) / NUM_DUELS * 100 << "%\n";
    cout << "Bob won " << bob_wins_2 << "/" << NUM_DUELS << " duels or "
         << static_cast<double>(bob_wins_2) / NUM_DUELS * 100 << "%\n";
    cout << "Charlie won " << charlie_wins_2 << "/" << NUM_DUELS << " duels or "
         << static_cast<double>(charlie_wins_2) / NUM_DUELS * 100 << "%\n";
    
    // compare 1 and 2 (2 should win)
    if (aaron_wins_2 > aaron_wins_1)
        cout << "\nStrategy 2 is better than strategy 1.\n";
    else
        cout << "\nStrategy 1 is better than strategy 2.\n";

    return 0;
}
// function see if 2 or more are alive
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
    int alive_count = A_alive + B_alive + C_alive;
    return alive_count >= 2;
}
// Aaron shoots - Strategy 1
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
    int shoot_target_result = rand() % 3;
    if (shoot_target_result == 0) {
        if (C_alive)
            C_alive = false;
        else
            B_alive = false;
    }
}
// Bob strategy
void Bob_shoots(bool& A_alive, bool& C_alive) {
    int shoot_target_result = rand() % 2;
    if (shoot_target_result == 0) {
        if (C_alive)
            C_alive = false;
        else
            A_alive = false;
    }
}
// Charlie strategy
void Charlie_shoots(bool& A_alive, bool& B_alive) {
    int shoot_target_result = rand() % 2;
    if (shoot_target_result == 0) {
        if (B_alive)
            B_alive = false;
        else
            A_alive = false;
    }
}
// Aaron shoots - Strategy 2
void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    if (B_alive || C_alive) {
        int shoot_target_result = rand() % 2;
        if (shoot_target_result == 0 && B_alive)
            B_alive = false;
        else if (C_alive)
            C_alive = false;
    }
}

// --TESTS--

// Test for function see if 2 or more are alive
void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n";
    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n";
    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed ...\n";
    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed ...\n";
    cout << "\tPress any key to continue...";
    cin.ignore().get();
}

// test for aarons shot with first strategy
void test_Aaron_shoots1(void) {
    cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
    bool Bob_alive = true;
    bool Charlie_alive = true;

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    Aaron_shoots1(Bob_alive, Charlie_alive);
    assert(Bob_alive == true || Charlie_alive == true);
    cout << "\t\tAaron is shooting at Charlie\n";

    Bob_alive = false;
    Charlie_alive = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n";
    Aaron_shoots1(Bob_alive, Charlie_alive);
    assert(Bob_alive == false || Charlie_alive == true);
    cout << "\t\tAaron is shooting at Charlie\n";

    Bob_alive = true;
    Charlie_alive = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n";
    Aaron_shoots1(Bob_alive, Charlie_alive);
    assert(Bob_alive == true || Charlie_alive == false);
    cout << "\t\tAaron is shooting at Bob\n";

    cout << "Press any key to continue...";
    cin.ignore().get();
}

// test for bob's accuracy
void test_Bob_shoots(void) {
    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
    bool Aaron_alive = true;
    bool Charlie_alive = true;

    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    Bob_shoots(Aaron_alive, Charlie_alive);
    assert(Aaron_alive == true || Charlie_alive == true);
    cout << "\t\tBob is shooting at Charlie\n";

    Aaron_alive = false;
    Charlie_alive = true;
    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    Bob_shoots(Aaron_alive, Charlie_alive);
    assert(Aaron_alive == false || Charlie_alive == true);
    cout << "\t\tBob is shooting at Charlie\n";

    Aaron_alive = true;
    Charlie_alive = false;
    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    Bob_shoots(Aaron_alive, Charlie_alive);
    assert(Aaron_alive == true || Charlie_alive == false);
    cout << "\t\tBob is shooting at Aaron\n";

    cout << "Press any key to continue...";
    cin.ignore().get();
}

// test for charlie's accuracy
void test_Charlie_shoots(void) {
    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
    bool Aaron_alive = true;
    bool Bob_alive = true;

    cout << "\tCase 1: Aaron alive, Bob alive\n";
    Charlie_shoots(Aaron_alive, Bob_alive);
    assert(Aaron_alive == true || Bob_alive == true);
    cout << "\t\tCharlie is shooting at Bob\n";

    Aaron_alive = false;
    Bob_alive = true;
    cout << "\tCase 2: Aaron dead, Bob alive\n";
    Charlie_shoots(Aaron_alive, Bob_alive);
    assert(Aaron_alive == false || Bob_alive == true);
    cout << "\t\tCharlie is shooting at Bob\n";

    Aaron_alive = true;
    Bob_alive = false;
    cout << "\tCase 3: Aaron alive, Bob dead\n";
    Charlie_shoots(Aaron_alive, Bob_alive);
    assert(Aaron_alive == true || Bob_alive == false);
    cout << "\t\tCharlie is shooting at Aaron\n";

    cout << "Press any key to continue...";
    cin.ignore().get();
}

// test for aaron's 2nd strategy
void test_Aaron_shoots2(void) {
    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
    bool Bob_alive = true;
    bool Charlie_alive = true;

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    Aaron_shoots2(Bob_alive, Charlie_alive);
    assert(Bob_alive == true || Charlie_alive == true);
    cout << "\t\tAaron intentionally misses his first shot\n";
    cout << "\t\tBoth Bob and Charlie are alive.\n";


    Bob_alive = false;
    Charlie_alive = true;
    cout << "\tCase 2: Bob dead, Charlie alive\n";
    Aaron_shoots2(Bob_alive, Charlie_alive);
    assert(Bob_alive == false || Charlie_alive == true);
    cout << "\t\tAaron is shooting at Charlie\n";

    Bob_alive = true;
    Charlie_alive = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n";
    Aaron_shoots2(Bob_alive, Charlie_alive);
    assert(Bob_alive == true || Charlie_alive == false);
    cout << "\t\tAaron is shooting at Bob\n";

    cout << "Press any key to continue...";
    cin.ignore().get();
}