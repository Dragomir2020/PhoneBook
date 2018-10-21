# PhoneBook [![Build Status](https://travis-ci.org/Dragomir2020/PhoneBook.svg?branch=master)](https://travis-ci.org/Dragomir2020/PhoneBook)  [![Coverage Status](https://coveralls.io/repos/github/Dragomir2020/PhoneBook/badge.svg?branch=master)](https://coveralls.io/github/Dragomir2020/PhoneBook?branch=master)

BST implemented in c++ that has a phone book interface
Templated to allow for multiple data types
## Install cxxtest
- go to https://sourceforge.net/projects/cxxtest/files/cxxtest/
- install folder in directory with code
## Make File
- Open make file and change directory path to path where code cxxtest exists
## Install valgrind
```
sudo apt-get install valgrind
```
## Compile Code
```
make
```
- compiles sample code in bstsandbox
- Use this as guide when using BST header
## Test Code
```
make test
```
## Check for Memory Leaks
```
valgrind ./testrunner
```
