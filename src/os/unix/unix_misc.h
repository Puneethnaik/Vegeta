#ifndef UNIX_MISC_H
#define UNIX_MISC_H

#include <string>
#include <vector>

//OS Utility functions. Inspired by the python os module.
namespace vegeta_unix {
    typedef std::string UnixPath;

    std::vector<std::string> split(UnixPath path, char delimiter = '/') {
        /*
         * This function takes in a UnixPath and 
         * splits them into components separated by delimiter
         * Only supports character delimiter for now.
        */
        std::vector<std::string> components;
        int startPos = 0;
        size_t delimiterPos;
        while(true) {
            delimiterPos = path.find("/", startPos);
            if (delimiterPos == path.npos) {
                break;
            } else {
                std::string component = path.substr(startPos, delimiterPos - startPos);
                components.push_back(component);
                startPos = delimiterPos + 1;
            }
        }

        return components;
    }

    UnixPath join(UnixPath path1, UnixPath path2) {
        /*
         * This function takes 2 valid UnixPaths and combines them 
         * to produce a valid UnixPath. However, valid UnixPath is guaranteed only 
         * if path1 and path2 are valid UnixPaths
        */ 
        path1 = "/" + path1 + "/";
        path2 = "/" + path2 + "/";
        UnixPath combinedPath = path1 + path2;
        UnixPath resultPath = "";

        std::vector<std::string> combinedPathComponents = split(combinedPath);
        

        //Join the components together with '/'
        for(std::string combinedPathComponent: combinedPathComponents) {
            if(!combinedPathComponent.empty()) {
                resultPath = resultPath + '/' + combinedPathComponent;
            }
        }
        return resultPath;
    }

}

#endif