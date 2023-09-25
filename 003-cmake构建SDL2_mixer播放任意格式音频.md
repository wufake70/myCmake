# cmake构建SDL2_mixer播放任意格式音频
```
    SDL2只能播放wav格式音频
    SDL2_mixer 是基于SDL2构建，在编译连接SDL2_mixer时，也要链接SDL2库
```
## 构建开始
* ```
    # 克隆github项目
    git clone https://github.com/libsdl-org/SDL.git
    # 或者下载 release的源代码压缩包(比较稳定)
    curl -O https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.28.3.zip
    # 解压

    # 创建build目录
    mkdir build
    cd build

    # 配置和生成构建系统的CMake命令。
    cmake -S D:\.important\myCmake\003-test\SDL_mixer-release-2.6.3 -B .
    # 返回信息(报错信息)
        -- Selecting Windows SDK version 10.0.22621.0 to target Windows 10.0.22631.
        -- Configuring SDL2_mixer 2.6.3
        -- Using private SDL2 find module
        CMake Error at D:/SoftWareSpace/CMake/share/cmake-3.27/Modules/FindPackageHandleStandardArgs.cmake:230 (message):
        Could NOT find PrivateSDL2 (missing: SDL2_LIBRARY SDL2_INCLUDE_DIR) # ①不能找到 SDL2_LIBRARY SDL2_INCLUDE_DIR
        (Required is at least version "2.0.9")
        Call Stack (most recent call first):
        D:/SoftWareSpace/CMake/share/cmake-3.27/Modules/FindPackageHandleStandardArgs.cmake:600 (_FPHSA_FAILURE_MESSAGE)
        cmake/FindPrivateSDL2.cmake:33 (find_package_handle_standard_args)
        cmake/PrivateSdlFunctions.cmake:63 (find_package)
        CMakeLists.txt:174 (sdl_find_sdl2)
        -- Configuring incomplete, errors occurred!
    # 解决问题①,将已经构建好的SDL2项目中include目录地址，SDL2库文件(.lib)地址分别赋值给SDL2_LIBRARY SDL2_INCLUDE_DIR
    # 在CMakeLists.txt前部分中使用set函数赋值即可
        set(SDL2_INCLUDE_DIR D:/.important/myCmake/002-test/SDL-release-2.28.3/include)
        set(SDL2_LIBRARY D:/.important/myCmake/002-test/SDL-release-2.28.3/build/Debug/SDL2d.lib)

    # 继续执行配置构建系统命令，又报错
        -- Using vendored libogg
        CMake Error at cmake/PrivateSdlFunctions.cmake:217 (message):
        No cmake project for ogg found in external/ogg.     # ②在根目录下external(第三方库目录)目录没找到ogg 
        Run the download script in the external folder, or re-configure with
        -DSDL2MIXER_VENDORED=OFF to use system packages.
        Call Stack (most recent call first):
        CMakeLists.txt:324 (sdl_check_project_in_subfolder)
        -- Configuring incomplete, errors occurred!
    # 根目录下的.gitmodules存放着该项目所必须库及下载地址，第三方库放在external目录下
    # 在external编写一个download.sh脚本(可以在git bash内执行)，来下载必须库。
    # download.sh源码
        #!/bin/sh
        set -e
        cd "$(dirname "$0")/.."
        cat .gitmodules |
        while IFS= read -r line; do
        if echo "$line" | grep -q '\[submodule'; then
            read -r path_line
            read -r url_line
            read -r branch_line
            path=$(echo "$path_line" | awk '{print $3}')
            url=$(echo "$url_line" | awk '{print $3}')
            branch=$(echo "$branch_line" | awk '{print $3}')
            
            # 检查目标路径是否已存在，如果存在则跳过下载
            if [ -d "$path" ]; then
            echo "submoudle existed：$path"
            else
            git clone "$url" "$path" -b "$branch" --recursive
            fi
        fi
        done
    # git bash中执行(win下)即可完成子模块下载

    # 继续执行配置构建系统命令
        -- Looking for strings.h
        -- Looking for strings.h - not found
        -- Looking for sinf
        -- Looking for sinf - found
        -- Dynamic modplug: $<TARGET_FILE_NAME:modplug>
        -- Could NOT find SDL2main (missing: SDL2_MAIN_LIBRARY)
        -- Configuring done (123.8s)
        -- Generating done (0.5s)
        -- Build files have been written to: D:/.important/myCmake/003-test/SDL_mixer-release-2.6.3/build

    # 开始构建
    cmake --build .
    # 一般在build目录的子目录Debug目录生成库文件(lib,dll)

## c语言链接上面的dll，实现播放指定音频
* ```
    # gcc编译
    gcc test.c -o test.exe 
    -ID:\.important\myCmake\003-test\SDL_mixer-release-2.6.3\include
    -ID:\.important\myCmake\002-test\SDL-release-2.28.3\include
    -LD:\.important\myCmake\003-test\SDL_mixer-release-2.6.3\build\Debug
    -LD:\.important\myCmake\002-test\SDL-release-2.28.3\build\Debug
    -lSDL2d -lSDL2_mixerd
    # 注意需要指定SDL2的include目录、SDL2d.dll文件地址

    # 优化
    gcc test.c -o test.exe 
    -ID:\.important\myCmake\003-test\SDL_mixer-release-2.6.3\include
    -ID:\.important\myCmake\002-test\SDL-release-2.28.3\include
    -L./ -lSDL2d -lSDL2_mixerd
* ```
    # C源代码
    #include <SDL.h>
    #include <SDL_mixer.h>
    #include <stdio.h>

    int WinMain(int argc, char* argv[]) {
        // 初始化SDL
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            printf("SDL初始化失败: %s\n", SDL_GetError());
            return -1;
        }

        // 初始化SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("SDL_mixer初始化失败: %s\n", Mix_GetError());
            return -1;
        }

        // 加载并播放MP3音频文件
        Mix_Music* music = Mix_LoadMUS("./Yamete kudasai.mp3");
        if (music == NULL) {
            printf("音频文件加载失败: %s\n", Mix_GetError());
            return -1;
        }

        if (Mix_PlayMusic(music, 1) < 0) {
            printf("音频播放失败: %s\n", Mix_GetError());
            return -1;
        }

        // 等待音频播放完毕
        while (Mix_PlayingMusic()) {
            SDL_Delay(100);
        }

        // 清理资源
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();

        return 0;
    }