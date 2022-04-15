/**
 * @file hash_driver.cpp
 * @author Sammyajit Kapuria (sammyajit.kapuria87@myhunter.cuny.edu)
 * @brief Tests a extendible hashing data structure.
 * @version 0.1
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include "extendible_hash.h"

using namespace std;

int main()
{
    // TODO: Create an extendable hash table.
    ExtendHash Table;

    // for 30 iterations.
    for (int i = 0; i < 30; i++)
    {
        // TODO: Insert the value i * 8 into the table.
        Table.insert(i*8);
    }

    // TODO: Output the table to standard output.
    cout << Table;
    cout<<"Test";
    return 0;
}