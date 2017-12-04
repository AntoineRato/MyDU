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
                // cout << "file : " << itr->path().string() << endl;
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
    else
    {
        cout << folderPath << " does not exist\n";
    }

    sizeFiles += 4096;
    cout << sizeFiles << "\t" << folderPath << endl;

    return sizeFiles;
}

int main(int argc, const char * argv[])
{
    size_t size = 0;
    
    // for(recursive_directory_iterator it("./"); it!=recursive_directory_iterator(); it++)
    // {
    //     if(!is_directory(*it))
    //     {
    //         // size += file_size(*it);
            
    //         std::cout << file_size(*it) << "\t" << *it << std::endl;
    //     }
    // }

    getSizeFoler("./");
}
