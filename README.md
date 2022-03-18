# 【字学镜像计划 后端&大数据-中级】支持Select&Update操作及数据库索引
**注：运行sh configure.sh命令安装google test framework，若已安装先运行sh build.sh --clean --lab1 --lab2命令后运行cd build && ctest -VV -R "database_*" -j进行lab1和lab2test。**<br>
![](https://s3.bmp.ovh/imgs/2022/03/122d555393e56cb3.jpg)
**阿里云双核2G ecs.t6-c1m1.large (性能约束实例)云服务器多次lab1与lab2测试，通过全部测试的时间多次出现为0.03s。**

This is a project based on stanford cs245.

# Prerequisite
- cmake version(recommended): >=3.9.2
- C++ version: >=C++11
- gcc/g++ version: >=6.3.0

# Step 1
Configure googletest framework in your environment.

`sh configure.sh`

After configuration, binary files of google test will be installed in your environment.

# Step 2
Implement your database in C++, then build binary outputs (executables for unit test).

If you are working with lab1, you can build unit tests only for lab1,

`sh build.sh --clean --lab1`

or for lab2,

`sh build.sh --clean --lab2`

or for both labs

`sh build.sh --clean --lab1 --lab2`

# Step 3
Enter the test directory, run all unit tests.

`cd build && ctest -VV -R "database_*" -j`
