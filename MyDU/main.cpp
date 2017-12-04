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
            sizeFiles += file_size(folderPath);
        else if (is_directory(folderPath))
        {
            directory_iterator end_itr;
            for (directory_iterator itr(folderPath); itr != end_itr; ++itr)
            {
                if (is_regular_file(itr->path())) {
                    sizeFiles += file_size(itr->path());
                }
            }
        }
    }
    else
    {
        cout << folderPath << " does not exist\n";
    }

    sizeFiles += 4;
    cout << sizeFiles << endl;
}

int main(int argc, const char * argv[])
{
    size_t size = 0;
    
    // for(recursive_directory_iterator it("./"); it!=recursive_directory_iterator(); it++)
    // {
    //     if(!is_directory(*it))
    //     {
    //         size += file_size(*it);
            
    //         std::cout << size << "\t" << *it << std::endl;
    //     }
    // }

    getSizeFoler("./dossier1");
}

// #include <iostream>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

using namespace boost::filesystem;
using namespace std;

//returns a list of all the files in a given folder.
std::vector<boost::filesystem::directory_entry> GetAllFilesInFolder(boost::filesystem::path folderPath)
{
    try
    {
        if (exists(folderPath))    // does p actually exist?
        {
            std::vector<boost::filesystem::directory_entry> files;

            if (is_regular_file(folderPath))        // is p a regular file?
                cout << folderPath << " size is " << file_size(folderPath) << '\n';



            else if (is_directory(folderPath))      // is p a directory?
            {
                cout << folderPath << " is a directory containing:\n";
                /*
                copy(boost::filesystem::directory_iterator(folderPath), boost::filesystem::directory_iterator(),  // directory_iterator::value_type
                    ostream_iterator<boost::filesystem::directory_entry>(cout, "\n"));  // is directory_entry, which is
                                                                     // converted to a path by the
                                                                     // path stream inserter
                */
                for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(folderPath), {}))
                {
                    std::cout << entry << "\n";
                    files.push_back(entry);
                }
                return files;
            }
        }
        else
        {
            cout << folderPath << " does not exist\n";
        }

    }

    catch (const boost::filesystem::filesystem_error& ex)
    {
        cout << ex.what() << '\n';
    }
}