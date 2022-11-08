#include "audio.h"


#include <Windows.h>

void audio_play_key_press() {
  PlaySound(L"music/key_press.wav", NULL,
            SND_FILENAME | SND_ASYNC | SND_NOWAIT);
}

void audio_play_clear() {
  PlaySound(L"music/clear.wav", NULL,
            SND_FILENAME | SND_ASYNC | SND_NOWAIT);
}
