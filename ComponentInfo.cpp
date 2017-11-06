//
// Created by Federico Fuga on 06/11/17.
//

#include "ComponentInfo.h"

const std::string &ComponentInfo::getName() const
{
    return mName;
}

void ComponentInfo::setName(const std::string &mName)
{
    ComponentInfo::mName = mName;
}

const std::string &ComponentInfo::getPath() const
{
    return mPath;
}

void ComponentInfo::setPath(const std::string &mPath)
{
    ComponentInfo::mPath = mPath;
}

const std::vector<Dependency> &ComponentInfo::getDependencies() const
{
    return mDependencies;
}

void ComponentInfo::addDependency(Dependency dependency)
{
    mDependencies.emplace_back(dependency);
}
