# cmake构建SDL2播放音频
* 通过 OpenGL 和 Direct3D 提供对音频、键盘、鼠标、游戏杆和图形硬件的低级访问。
* 通过提供统一的 API 支持跨平台开发，包括 Windows、macOS、Linux、iOS 和 Android。
* 通过简化多媒体应用程序的开发，提供了一种简单的方法来处理音频、视频和输入设备。

## 构建开始
* ```
    # 克隆github项目
    git clone https://github.com/libsdl-org/SDL.git
    # 或者下载 release的源代码压缩包
    curl -O https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.28.3.zip
    # 解压

    # 创建build目录
    mkdir build
    cd build

    # 配置和生成构建系统的CMake命令。
    cmake -S D:/.important/myCmake/002-test/SDL -B .
    # 返回信息
        --
        -- Configuring done (108.3s)
        -- Generating done (0.1s)
        -- Build files have been written to: D:/.important/myCmake/002-test/SDL/build

    # 开始构建
    cmake --build .
    # 一般在build目录的子目录Debug目录生成库文件(lib,dll)

## c语言链接上面的dll，实现播放指定音频
* ```
    # gcc 编译命令
    gcc test.c -o test.exe 
    -ID:\.important\myCmake\002-test\SDL-release-2.28.3\include 
    -LD:\.important\myCmake\002-test\SDL-release-2.28.3\build\Debug 
    -lSDL2d

    # 优化
    gcc test.c -o test.exe 
    -ID:\.important\myCmake\002-test\SDL-release-2.28.3\include 
    -L./
    -lSDL2d
    
* c源码
* ```
    #include <SDL.h>

    #define FILE_PATH "./Yamete kudasai.wav"

    int WinMain(int argc, char* argv[]) {
        SDL_Init(SDL_INIT_AUDIO);

        SDL_AudioSpec wavSpec;
        Uint8* wavBuffer;
        Uint32 wavLength;

        if (SDL_LoadWAV(FILE_PATH, &wavSpec, &wavBuffer, &wavLength) == NULL) {
            // 加载音频文件失败
            return 1;
        }

        SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
        if (deviceId == 0) {
            // 打开音频设备失败
            SDL_FreeWAV(wavBuffer);
            return 1;
        }

        SDL_QueueAudio(deviceId, wavBuffer, wavLength);
        SDL_PauseAudioDevice(deviceId, 0);

        // 等待音频播放完毕
        while (SDL_GetAudioDeviceStatus(deviceId) == SDL_AUDIO_PLAYING) {
            SDL_Delay(100);
        }

        SDL_CloseAudioDevice(deviceId);
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();

        return 0;
    }

## 只能播放wav格式的音频