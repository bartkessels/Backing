# Backing

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Build Status](https://travis-ci.org/bartkessels/backing.svg?branch=development)](https://travis-ci.org/bartkessels/backing)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/f9919567041d4715889d643b784e661f)](https://www.codacy.com/manual/bartkessels/backing?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=bartkessels/backing&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/bartkessels/backing/branch/development/graph/badge.svg)](https://codecov.io/gh/bartkessels/backing)

Application to mock your back-end for front-end testing

## Table of contents

- [1. Screenshots](#1-screenshots)
- [2. Features](#2-features)
- [3. Roadmap](#3-roadmap)
- [4. Required packages](#4-required-packages)
- [5. Build](#5-build)
    - [5.1 Tests](#51-tests)
        - [5.1.1 Test coverage](#511-test-coverage)
    - [5.2 Application](#52-application)

## 1. Screenshots

![Mainwindow for Backing](data/screenshot_1.png)

## 2. Features

Simply setup a uri and you're able to mock multiple HTTP methods. For each
mocked method you're able to set the status code, headers and ofcourse the body.

All requests will be logged to the output at the bottom of the screen
so you can easily detect if your front-end is sending data to the expected
back-end.

## 3. Roadmap

Unfortunately not all the features we'd like are implemented just yet. Som of the features
we'd like to implement in foreseeable future are:

- Saving the mocks
- Opening the mocks 

There are some things we want get up and running to make life easier for the developers of Backing, mostly for distributing the application.

- Setup an automated CD pipeline
- Setup CI for Windows machine
- Setup GUI test framework

## 4. Required packages

Backing relies on a couple of external packages, some are being fetched using Cmake's `FetchContent` while others
are expected to be installed on your system.

The packages that are fetched by Cmake are [CppRestRequest](https://github.com/microsoft/cpprestsdk), a library from
[Microsoft](https://microsoft.com) to send HTTP requests using an easy C++ interface. This package is both used for
building the `backing` executable as well as the `backing_tests` executable. For the `backing_tests` executable the
[Catch2](https://github.com/catchorg/catch2) library is fetched as the unit-tests framework used by Backing.

The packages you need to install

- `Qt5`, this is used for the GUI of Backing
- `Boost`, these libraries are used within [CppRestSdk](https://github.com/microsoft/cpprestsdk) library
- `CMake`, this is the build system used by Backing

## 5. Build

Once you've installed the required packages you're ready to compile Backing or the Backing tests.

### 5.1 Tests

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make backing_tests
$ ./bin/backing_tests
```

#### 5.1.1 Test coverage

When building the tests the required compiler flags are set to generate the coverage reports for each individual
source file. The coverage reports can be bundled using `lcov` which will generate a `*.info` file which can be transformed
into a `html` file using the `genhtml` command.

```bash
$ lcov --directory tests/CMakeFiles/backing_tests.dir --capture --output-file backing_coverage.info
$ genhtml -o coverage/ backing_coverage.info
$ open coverage/index.html
```

### 5.2 Application

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make backing
$ ./bin/backing
```
