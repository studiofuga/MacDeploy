//
// Created by Federico Fuga on 06/11/17.
//

#include "Dependency.h"

const std::string &Dependency::getPath() const
{
    return mPath;
}

void Dependency::setPath(const std::string &mPath)
{
    Dependency::mPath = mPath;
}

const std::string &Dependency::getName() const
{
    return mName;
}

void Dependency::setName(const std::string &mName)
{
    Dependency::mName = mName;
}
