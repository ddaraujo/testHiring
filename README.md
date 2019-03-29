PAYTV HIRING TEST

ENVIRONMENT:
OS: CentOS release 6.4 (Final)
Kernel: 2.6.32-358.23.2.el6.x86_64
LibCurl: 7.19.7-37.el6_5.3.x86_64
gtest: 1.5.0-5.el6.x86_64
GCC: 4.4.7-23.el6.i686

#COMPILE OPTIONS:

g++ src/*.cpp -lcurl -ljson -o paytvHiringProject

# UNIT TESTS COMPILE OPTIONS:
g++ unit_test/unittest*.cpp src/InputOptions.cpp src/OmdbSearch.cpp -lcurl -ljson -o unittest_Main -lgtest -lgtest_main -pthread
