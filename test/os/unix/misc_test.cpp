#include <iostream>
#include <vector>
using namespace std;
namespace vegeta_test_unix {
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
            cout << startPos << " " << delimiterPos << endl;
            if (delimiterPos == path.npos) {
                break;
            } else {
                std::string component = path.substr(startPos, delimiterPos - startPos);
                components.push_back(component);
                cout << "The component is" << component << endl;
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

int main() {
    string path1 = "/home/puneeth/Desktop/Projects/http-server/test";
    string path2 = "/os/unix/";
    vegeta_test_unix::UnixPath path = vegeta_test_unix::join(path1, path2);
    cout << "The cleaned path is" << path << endl;
    return 0;
}