//
// Created by Federico Fuga on 06/11/17.
//

#ifndef MACDEPLOY_TARGET_H
#define MACDEPLOY_TARGET_H

#include "ComponentInfo.h"

#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <set>

class Target final {
    boost::filesystem::path mPath;
    boost::filesystem::path mFrameworksPath, mExePath;
    std::set<std::string> mExclusions;
    std::vector<std::string> mAdditionalLibraryPaths;
public:
    explicit Target(std::string path);

    bool process();

private:
    std::vector<std::string> listAllComponents(std::string path);

    std::list<std::string> collectLinkerReferences(std::string component);

    std::string resolveLibrary(std::string library);

    std::list<ComponentInfo> traverseAppDependencies(std::list<std::string> components);

    void copyObjects(std::list<ComponentInfo> list);

    void fixLinks(std::list<ComponentInfo> components);
};


#endif //MACDEPLOY_TARGET_H
