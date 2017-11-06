//
// Created by Federico Fuga on 06/11/17.
//

#include "Target.h"

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/process.hpp>

#include <algorithm>
#include <set>

using namespace std;

namespace bp = boost::process;

Target::Target(std::string path)
: mPath(std::move(path))
{

}

bool Target::process()
{
    auto executables = listAllComponents("Contents/MacOS/");
    auto frameworks = listAllComponents("Contents/Frameworks/");

    std::list<std::string> components;
    std::copy(executables.begin(), executables.end(), std::back_inserter(components));
    std::copy(frameworks.begin(), frameworks.end(), std::back_inserter(components));

    std::set<std::string> processedComponents;

    while (!components.empty()) {
        auto current = *components.begin();
        components.erase(components.begin());

        BOOST_LOG_TRIVIAL(info) << "Processing: " << current;

        auto external_libs = collectLinkerReferences(current);

        for (auto lib : external_libs) {
            auto comp = processedComponents.find(lib);
            if (comp != processedComponents.end())
                continue;

            // Check for excluded library
        }
    }


    return true;
}

std::vector<std::string> Target::listAllComponents(std::string path)
{
    vector<string> v;

    boost::filesystem::directory_iterator end;

    boost::filesystem::path subpath = mPath / path;

    for(boost::filesystem::directory_iterator itr(subpath); itr != end; ++itr) {
        auto p = *itr;
        v.push_back(p.path().string());
    }
    return v;
}

std::list<std::string> Target::collectLinkerReferences(std::string component)
{
    list<string> v;

    return v;
}
