//
// Created by Federico Fuga on 06/11/17.
//

#ifndef MACDEPLOY_COMPONENTINFO_H
#define MACDEPLOY_COMPONENTINFO_H

#include <string>
#include <vector>
#include "Dependency.h"

class ComponentInfo {
public:
    const std::string &getName() const;
    void setName(const std::string &mName);
    const std::string &getPath() const;
    void setPath(const std::string &mPath);
    const std::vector<Dependency> &getDependencies() const;
    void addDependency(Dependency dependency);

private:
    std::string mName;
    std::string mPath;
    std::vector<Dependency> mDependencies;
};


#endif //MACDEPLOY_COMPONENTINFO_H
