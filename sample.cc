// Arg Machine Copyright © 2017 Ramsey Dow. All rights reserved.

// Arg Machine is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Arg Machine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public License
// along with Arg Machine. If not, see <http://www.gnu.org/licenses/>.

// Compile with:
// clang++ -I. -std=c++14 -Wall -Wextra -Werror sample.cc

#include <string>
#include <arguments>
#include <iostream>
#include <cstdlib> // ::exit

// Program state container.
struct runtime_state {
  bool debug;
  std::string output_pathname;
  bool verbose;
};

// For simplicity, all Arg Machine processing happens in this function.
void process_arguments(int& ac, char**& av, runtime_state& state) {
  // --debug, no short variant
  auto debug_conf{argument::config('\0', "debug", "Enable debug mode", argument::parameter_type::none, "", [&flag = state.debug](const char* __unused param) { flag = true; })};

  // -o,--output <pathname>
  auto output_conf{argument::config('o', "output", "Output file pathname", argument::parameter_type::required, "pathname", [&pathname = state.output_pathname](const char* param) { pathname = param; })};

  // -v (verbosity), no long variant
  auto verbose_conf{argument::config('v', "", "Increase verbosity", argument::parameter_type::none, "", [&flag = state.verbose](const char* __unused param) { flag = true; })};

  // ^ That was all setup. Here's where the action is…
  argument::processor arg_machine(ac, av, {&debug_conf, &output_conf, &verbose_conf}, "Arg Machine Copyright © 2017 Ramsey Dow. All rights reserved.");
  try {
    arg_machine.process(ac, av);
  }
  catch (argument::bad_argument& e) {
    std::cerr << arg_machine.program_name() << ": " << e.what() << "\n";
    ::exit(EXIT_FAILURE);
  }
}

int main(int ac, char** av) {
  // Initialize state.
  runtime_state state{false, "", false};

  // Process command line arguments.
  process_arguments(ac, av, state);

  // Display what we got…
  std::cout << "debug " << std::boolalpha << state.debug << std::noboolalpha << "\n";
  std::cout << "output " << state.output_pathname << "\n";
  std::cout << "verbose " << std::boolalpha << state.verbose << std::noboolalpha << "\n";

  if (ac) {
    std::cout << ac << " input argumen" << ((ac != 1) ? "ts" : "t") << ":\n";
    for (int i{0}; i < ac; ++i) { std::cout << av[i] << "\n"; }
  } else {
    std::cout << "no input arguments\n";
  }

  ::exit(EXIT_SUCCESS);
}
