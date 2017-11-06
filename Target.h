//
// Created by Federico Fuga on 06/11/17.
//

#ifndef MACDEPLOY_TARGET_H
#define MACDEPLOY_TARGET_H

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

class Target final {
    boost::filesystem::path mPath;
public:
    explicit Target(std::string path);

    bool process();

private:
    std::vector<std::string> listAllComponents(std::string path);

    std::list<std::string> collectLinkerReferences(std::string component);
};


#endif //MACDEPLOY_TARGET_H
