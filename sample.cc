// Arg Machine Copyright © 2017, 2020 Ramsey Dow.
// SPDX-License-Identifier: MIT

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

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
  argument::processor arg_machine(ac, av, {&debug_conf, &output_conf, &verbose_conf}, "Arg Machine Copyright © 2017, 2020 Ramsey Dow. All rights reserved.");
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
