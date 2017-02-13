# Arg Machine

Copyright &copy; 2017 Ramsey Dow. All rights reserved.

[![AUR](https://img.shields.io/badge/license-LPGL%20v3-blue.svg)]()
![Platforms](https://img.shields.io/badge/platform-macOS%20|%20Linux%20|%20Windows-lightgrey.svg)

- [What is Arg Machine?](#1)
- [What Arg Machine doesn't do](#2)
- [Requirements](#3)
- [Using Arg Machine](#4)
- [Where to go next](#5)

Arg Machine is free software. It is distributed under the terms of version 3 of the [GNU Lesser General Public License](https://www.gnu.org/licenses/lgpl.html), permitting its use within proprietary programs.

## <a id="1"></a> What is Arg Machine?

Arg Machine is a portable command line argument processor that runs on Unix and Unix-like operating systems like Linux and macOS. It also runs on Windows. In fact, Arg Machine can run anywhere that supports modern C++ applications. Arg Machine implements the functionality you've come to expect from GNU [`getopt`](https://www.gnu.org/software/libc/manual/html_node/Getopt.html), but in a simpler, more straightforward manner.

Arg Machine is opinionated. Instead of requiring you to write the logic to process `argc` and `argv**`, it does the work for you. Just configure the arguments that your program accepts, instantiate the argument processor with those arguments, and invoke the `process` method. Arg Machine will translate command line arguments into runtime state for your program.

Arg Machine understands short (`-h`) and long (`--help`) arguments, including variants that support only one type (e.g., short only with no corresponding long variant). Arguments may be configured to take an additional paramter, but this is not required. Additional parameters may be optional or they may be required.

Non-argument inputs may be freely interspersed throughout the command line. These will be ignored by the argument processor. In fact, arguments will be removed as they are processed, leaving `argv**` to contain only the non-argument inputs. `argc` is automatically updated to the correct count. The user program can then make use of these additional program inputs once argument processing has completed.

Arg Machine provides several convenience features:

- The base name of the program
- The complete, original command line invocation (useful for logging purposes)
- Detailed usage information available via the `-h` and `--help` arguments
- The ability to add an additional string to `usage` output, e.g., a copyright statement

Arg Machine favors convention over configuration, allowing you to add standard argument processing capabilities to your programs quickly and easily. Arg Machine allows you to focus on your app instead of the intricacies of argument processing.

Additional benefits:

- Distributed as a single header file (just `#include` the header and use the API)
- Flexible argument configuration using initialized lambda captures to define your program's runtime state
- No memory allocations on the heap

Please note that Arg Machine has not been tested for multithread safety. It is meant to be invoked by `main` and executed in the main thread.

### <a id="2"></a> What Arg Machine doesn't do

Arg Machine does not perform argument validation. It has no idea what constitutes a valid argument for your app. Similarly, Arg Machine does not assign default values to arguments with parameters or ensure that all required arguments have been invoked. These are all tasks best left to the application developer.

Arg Machine follows the [Unix tradition](https://en.wikipedia.org/wiki/Unix_philosophy) of doing one thing and doing it well. In this case, translating command line arguments into actionable runtime state. What you do with that state (and any left over, non-argument input parameters) is up to you.

Arg Machine was born in the Unix world where `main` doesn't have a `wchar_t` variant (like [`WinMain`](https://msdn.microsoft.com/en-us/library/windows/desktop/ms633559(v=vs.85).aspx) on Windows platforms). As such, Arg Machine does not currently support wide arguments on Windows. This shortcoming will be addressed in a future release.

## <a id="3"></a> Requirements

This all sounds great so far, but what's the catch?

> Arg Machine requires a modern C++ compiler because it makes liberal use of [initialized lambda captures](http://en.cppreference.com/w/cpp/language/lambda), a C++14 extension.

That's it!

## <a id="4"></a> Using Arg Machine

Arg Machine is supplied as a single header file. Just `#include <arguments>` in your C++ application and you are ready to go. Using the API is straightforward:

- Initialize one `argument::config` instance per argument.
- Instantiate an `argument::processor` instance, passing in a `std::initialization_list` of the `argument::config` instances.
- Invoke the `process` method on your `argument::processor` instance.
- Catch and deal with any `argument::bad_argument` exceptions that arise.

Assuming no exceptional conditions, the command line arguments will have been processed and the runtime state configured as specified by your `argument::config` instances. The program's `argc` and `argv**` will have been rewritten to include any non-arguments that the processor skipped.

At this point you will perform argument validation, initialize unspecified arguments to sane defaults, and deal with any non-argument input parameters.

## <a id="5"></a> Where to go next

Refer to [`sample.cc`]() for a complete example that illustrates how to use the Arg Machine API.

All of Arg Machine's documentation can be found in the [project wiki](). In addition to API documentation, there are pages that detail additional topics, including how to contribute to the project.
