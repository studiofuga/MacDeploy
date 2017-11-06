//
// Created by Federico Fuga on 06/11/17.
//

#include <boost/program_options.hpp>
#include <boost/log/trivial.hpp>

#include <iostream>
#include <vector>
#include <string>
#include "Target.h"

namespace po = boost::program_options;

int main(int argc, char const *argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("input-file", po::value< std::vector<std::string> >(), "input file")
            ;

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cerr << desc << "\n";
        return 1;
    }

    auto srcs = vm["input-file"].as< std::vector<std::string> >();
    for (auto src : srcs) {
        Target target(src);

        if (!target.process()) {
            BOOST_LOG_TRIVIAL(error) << "Target " << src << " processed with error.";
        } else {
            BOOST_LOG_TRIVIAL(info) << "Target " << src << " processed successfully.";
        }
    }

    return 0;
}

