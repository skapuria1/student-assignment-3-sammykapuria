/**
 *
 * @file extendible_hash.cpp
 * @author Sammyajit Kapuria (sammyajit.kapuria87@myhunter.cuny.edu)
 * @brief Extendible hash table implementation file.
 * @version 0.1
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "extendible_hash.h"

#include <cmath>

using namespace std;

int ExtendHash::Directory::computeSigBits(int size)
{
    return floor(log(size) / log(2) + .5);
}

ExtendHash::Directory::Directory(){};

ExtendHash::Directory::Directory(int size)
{
    //resize this directory to the given size.
    pointers.resize(size);

    // for each pointer.
    for (auto &p : pointers)
        // "clear" out the pointer.
        p = nullptr;

    //calculate and assign the number of significant bits needed for the given size.
    numSigBits = ExtendHash::Directory::computeSigBits(size);
}

int ExtendHash::Directory::size()
{
    //return the number of pointers to blocks.
    return pointers.size();
}

void ExtendHash::Directory::resize(int size)
{
    // resize the pointers.
    pointers.resize(size);

    // for each pointer.
    for (auto &p : pointers)
        // "clear" out the pointer.
        p = nullptr;

    //compute and assign the number of sigificant bits needed for the new, given size.
    numSigBits = ExtendHash::Directory::computeSigBits(size);
}

int ExtendHash::getKey(int data, int size)
{
    data = data >> (INT_BITS - size);
    return data;
}

void ExtendHash::doubleDirectory()
{
    // create a new, temporary directory double the size of this table's directory.
    Directory temp(2 * directory.size());

    //for each directory entry.
    int i = 0;
    for (Node* x : directory.pointers)
    {
        //Perform the directory split (this is slide 68) by copying the old pointers to the new one.
        temp.pointers[i] = x;
        i++;
        temp.pointers[i] = x;
        i++;
    }

    // following the split, increment the number of significant bits.
    ++directory.numSigBits;

    //set this tables directory pointers to the temporary one we created earlier.
    directory.resize(temp.size());
    directory.pointers = temp.pointers;
}

ExtendHash::ExtendHash()
{
    //"Resize" this table's directory to the default size (e.g., like the one one slide 67).
    directory.resize(2);
    //Set the number of significant bits to the default value (e.g., like the one one slide 67).
    directory.numSigBits = 2;
}

void ExtendHash::insert(int d)
{
    // "hash" the data (get its key) given the current directory size.
    int key = getKey(d, directory.size());

    // if the key is too big for the current directory.
    while (key >= directory.size())
    {
        //"split" (double) the directory.
        doubleDirectory();

        // compute and store a new key using the new number of significant bits to consider.
        key = getKey(d, directory.numSigBits);
    }

    // Now, we know we have enough room.
    // Get the node pointer to the block for the given key.
    Node *p = directory.pointers[key];

    // if there is no block for the key.
    if (directory.pointers[key] == nullptr)
    {
        // make a new "block" for the key.
        directory.pointers[key] = new Node();

        // set the pointer to point to it.
        p = directory.pointers[key];
    }

    // Now, p points to the block for the given key. It's time to do the insertion (if we have room in the block).

    // if there is room in the found block for the new piece of data.
    if (p->data.size() < BLOCKSIZE)
    {
        //add the data to the end of the block.
        p->data.push_back(d);
    }
    else // otherwise, we need to "split."
    {
        // for each directory pointer.
        for (int i = 0; i < directory.pointers.size(); i++)
            // if i does not equal the key and the key's block pointer equals the current block pointer.
            if (i != key && directory.pointers[key] == directory.pointers[i])
            {
                //create a new, temporary block data with the old block's data.
                vector<int> tempBlock = p->data;

                // clear the old block's data.
                p->data.clear();

                // create a new block.
                directory.pointers[i] = new Node;

                // insert the old data into the new block.
                for (auto x : tempBlock)
                    insert(x);

                //insert the given data.
                    insert(d);

                // end the function. We're done.
                return;
            }

        //at this point, we need a larger directory. Double it.
            doubleDirectory();
        //then, insert the data.
            insert(d);
    }
}

// NOTE: Do not change.
ostream &operator<<(ostream &os, const ExtendHash &eh)
{
    // For each block pointer.
    for (int i = 0; i < eh.directory.pointers.size(); i++)
    {
        // Insert the block number.
        os << "Block #" << i << endl;

        // if the block pointer points to an actual block.
        if (eh.directory.pointers[i] != nullptr)
        {
            // Insert the block data.
            for (auto x : eh.directory.pointers[i]->data)
                os << x << endl;
        }
    }

    // return the given output stream reference.
    return os;
}