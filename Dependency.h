//
// Created by Federico Fuga on 06/11/17.
//

#ifndef MACDEPLOY_DEPENDENCY_H
#define MACDEPLOY_DEPENDENCY_H

#include <string>

class Dependency {
public:
    const std::string &getPath() const;
    void setPath(const std::string &mPath);
    const std::string &getName() const;
    void setName(const std::string &mName);

private:
    std::string mPath;
    std::string mName;
};


#endif //MACDEPLOY_DEPENDENCY_H
