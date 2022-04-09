/**
 * TODO: Fill this out:
 *
 * @file extendible_hash.cpp
 * @author your name (you@domain.com)
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
    // TODO: resize this directory to the given size.

    // TODO: calculate and assign the number of significant bits needed for the given size.
}

int ExtendHash::Directory::size()
{
    // TODO: return the number of pointers to blocks.
}

void ExtendHash::Directory::resize(int size)
{
    // resize the pointers.
    pointers.resize(size);

    // for each pointer.
    for (auto &p : pointers)
        // "clear" out the pointer.
        p = nullptr;

    // TODO: compute and assign the number of sigificant bits needed for the new, given size.
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

    // TODO: for each directory entry.
    {
        // TODO: Perform the directory split (this is slide 68) by copying the old pointers to the new one.
    }

    // following the split, increment the number of significant bits.
    ++directory.numSigBits;

    // TODO: set this tables directory pointers to the temporary one we created earlier.
}

ExtendHash::ExtendHash()
{
    // TODO: "Resize" this table's directory to the default size (e.g., like the one one slide 67).

    // TODO: Set the number of significant bits to the default value (e.g., like the one one slide 67).
}

void ExtendHash::insert(int d)
{
    // "hash" the data (get its key) given the current directory size.
    int key = getKey(d, directory.size());

    // if the key is too big for the current directory.
    while (key >= directory.size())
    {
        // TODO: "split" (double) the directory.

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
        // TODO: add the data to the end of the block.
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

                // TODO: insert the given data.

                // end the function. We're done.
                return;
            }

        // TODO: at this point, we need a larger directory. Double it.

        // TODO: then, insert the data.
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