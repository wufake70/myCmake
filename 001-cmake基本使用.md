# cmake 基本使用
```
    CMake是一个跨平台的安装（编译）工具。
    它能够输出各种各样的makefile或者project文件，能测试编译器所支持的C++特性。
    CMake是一种高级编译配置工具，可以用来配置和编译我们的C/C++程序。
    CMake是一个开源的、跨平台的构建工具，可以用简单的语句来描述所有平台的安装(编译过程)。
    它可以控制编译过程的生成，例如编译器选择、库选择和可执行文件生成。

```
## 环境配置

* 构建工具：Download | CMake
* 编译工具：Downloads - MinGW-w64、Visual Studio 2023
* 需要注意的是，CMake 和 MinGW 安装好后，要手动添加到环境变量。

## 基本命令
### cmake 构建项目(可能是exe，dll,lib...)
```
    # 创建需要构建项目的build目录(最好在根目录下)，并进入
    mkdir build
    cd build

    # 配置和生成构建系统的CMake命令。
    cmake -S "git clone path" -B .

    # 开始构建
    cmake --build .
    
```


### CMakeLists.txt 的命令
```
    # cmake最低版本
    cmake_minimum_required(VERSION 3.15)

    # 项目名字
    project(Tutorial)

    # 用一个变量来表示这多个源文件：
    set(SRC_LIST a.cpp b.cpp c.cpp)

    # 添加可执行文件
    add_executable(${PROJECT_NAME} ${SRC_LIST})



```


