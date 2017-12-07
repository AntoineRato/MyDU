//
//  main.cpp
//  MyDU
//
//  Created by Antoine Rato on 03/12/2017.
//  Copyright © 2017 Antoine Rato. All rights reserved.
//

#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;
using namespace std;

int getSizeFoler(boost::filesystem::path folderPath)
{
    int sizeFiles = 0;

    if(exists(folderPath))
    {
        if (is_regular_file(folderPath))
        {
            sizeFiles += double(file_size(folderPath));
        }
        else if (is_directory(folderPath))
        {
            directory_iterator end_itr;
            for (directory_iterator itr(folderPath); itr != end_itr; ++itr)
            {
                if (is_regular_file(itr->path()))
                {
                    sizeFiles += double(file_size(itr->path()));
                }
                else if (is_directory(itr->path()))
                {
                    sizeFiles += getSizeFoler(itr->path());
                }
            }
        }
    }

    sizeFiles += 4096;

    if(folderPath.string() == "./")
        cout << sizeFiles << "\t" << "." << endl;
    else
        cout << sizeFiles << "\t" << folderPath.string() << endl;

    return sizeFiles;
}

int getSizeFoler(boost::filesystem::path folderPath, int nbIteration, int depth)
{
    int sizeFiles = 0;

    if(exists(folderPath))
    {
        if (is_regular_file(folderPath))
        {
            sizeFiles += double(file_size(folderPath));
        }
        else if (is_directory(folderPath))
        {
            directory_iterator end_itr;
            for (directory_iterator itr(folderPath); itr != end_itr; ++itr)
            {
                if (is_regular_file(itr->path()))
                {
                    sizeFiles += double(file_size(itr->path()));
                }
                else if (is_directory(itr->path()))
                {
                    sizeFiles += getSizeFoler(itr->path(), nbIteration + 1, depth);
                }
            }
        }
    }

    sizeFiles += 4096;

    if(nbIteration <= depth && depth == 0)
    {
        cout << sizeFiles << "\t" << "." << endl;
    }
    else if(nbIteration <= depth)
    {
        cout << sizeFiles << "\t" << folderPath.string() << endl;
    }

    return sizeFiles;
}

int main(int argc, const char * argv[])
{
    size_t size = 0;

    if(argc >= 3)
        getSizeFoler("./", 0, atoi(argv[2]));
    else 
        getSizeFoler("./");
}
