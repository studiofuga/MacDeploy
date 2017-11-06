//
// Created by Federico Fuga on 06/11/17.
//

#include "Target.h"

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/process.hpp>

#include <algorithm>
#include <set>
#include <regex>

using namespace std;

namespace bp = boost::process;
namespace bf = boost::filesystem;

namespace {
class CantResolveLibraryException {
};
}

Target::Target(std::string path)
: mPath(std::move(path))
{
    list<string> defaultExclusions {
            "^/usr/lib/.*",
            ".*\\.framework/.*"
    };

    std::copy(defaultExclusions.begin(), defaultExclusions.end(), inserter(mExclusions, mExclusions.end()));

    vector<string> defaultAdditionalLibrarySearchPath {
            "/usr/local/lib"
    };

    std::copy(defaultAdditionalLibrarySearchPath.begin(), defaultAdditionalLibrarySearchPath.end(),
              back_inserter(mAdditionalLibraryPaths)
    );
}

bool Target::process()
{
    auto executables = listAllComponents("Contents/MacOS/");
    auto frameworks = listAllComponents("Contents/Frameworks/");

    std::list<std::string> components;
    std::copy(executables.begin(), executables.end(), std::back_inserter(components));
    std::copy(frameworks.begin(), frameworks.end(), std::back_inserter(components));

    auto objects = traverseAppDependencies (components);

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

    bp::ipstream out;
    auto otool = bp::search_path("otool");
    bp::child chld(otool, bp::args = {std::string{"-L"}, component}, bp::std_out > out);

    std::string line;
    std::regex regex{R"(^\s+([^@\s][\S]*))"};
    smatch match;
    while (chld.running() && std::getline(out, line) && !line.empty()) {
        if (regex_search(line, match, regex)) {
            v.push_back(match[1]);
        }
    }

    chld.wait();

    return v;
}

std::string Target::resolveLibrary(std::string library)
{
    bf::path current_resolved(library);
    if (!bf::exists(current_resolved)) {
        current_resolved = bp::search_path(library);

        if (bf::exists(current_resolved)) {
            return current_resolved.string();
        }

        // try each additional path
        for (auto path : mAdditionalLibraryPaths) {
            bf::path c = bf::path{path} / library;

            if (bf::exists(c)) {
                return c.string();
            }
        }

        throw CantResolveLibraryException();
    } else {
        return library;
    }
}

std::list<std::string> Target::traverseAppDependencies(std::list<std::string> components)
{
    std::list<string> dependencyList;

    std::set<std::string> processedComponents;
    while (!components.empty()) {
        auto current = *components.begin();
        components.erase(components.begin());

        BOOST_LOG_TRIVIAL(debug) << "Searching: " << current;

        try {
            current = resolveLibrary(current);
        } catch (CantResolveLibraryException &) {
            BOOST_LOG_TRIVIAL(error) << "Can't resolve: " << current << "; skipping.";
            continue;
        }

        BOOST_LOG_TRIVIAL(info) << "Processing: " << current;

        auto comp = processedComponents.find(current);
        if (comp != processedComponents.end())
            continue;

        auto external_libs = collectLinkerReferences(current);

        for (auto lib : external_libs) {
            auto comp = processedComponents.find(lib);
            if (comp != processedComponents.end())
                continue;

            bool excluded = false;
            // Check for excluded library
            for (auto x : mExclusions) {
                regex r(x);
                if (regex_search(lib,r)) {
                    excluded = true;
                    break;
                }
            }
            if (excluded)
                continue;

            BOOST_LOG_TRIVIAL(debug) << "Found: " << lib;
            components.push_back(lib);
            dependencyList.push_back(lib);
        }
        processedComponents.insert(current);
    }

    return dependencyList;
}
