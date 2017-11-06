//
// Created by Federico Fuga on 06/11/17.
//

#ifndef MACDEPLOY_TARGET_H
#define MACDEPLOY_TARGET_H

#include <string>

class Target {
    std::string mPath;
public:
    explicit Target(std::string path);

    bool process();
};


#endif //MACDEPLOY_TARGET_H
