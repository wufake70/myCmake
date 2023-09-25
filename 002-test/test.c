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
        SDL_Delay(1);
    }

    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();

    return 0;
}