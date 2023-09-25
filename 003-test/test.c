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