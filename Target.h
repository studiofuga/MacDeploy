//
// Created by Federico Fuga on 06/11/17.
//

#ifndef MACDEPLOY_TARGET_H
#define MACDEPLOY_TARGET_H

#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <set>

class Target final {
    boost::filesystem::path mPath;
    std::set<std::string> mExclusions;
    std::vector<std::string> mAdditionalLibraryPaths;
public:
    explicit Target(std::string path);

    bool process();

private:
    std::vector<std::string> listAllComponents(std::string path);

    std::list<std::string> collectLinkerReferences(std::string component);

    std::string resolveLibrary(std::string library);

    std::list<std::string> traverseAppDependencies(std::list<std::string> components);
};


#endif //MACDEPLOY_TARGET_H
