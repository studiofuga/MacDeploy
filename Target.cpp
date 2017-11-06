//
// Created by Federico Fuga on 06/11/17.
//

#include "Target.h"

Target::Target(std::string path)
: mPath(std::move(path))
{

}

bool Target::process()
{
    return true;
}
