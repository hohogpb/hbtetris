#include "audio.h"

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

// playfromstart: string Pcommand = "play "  + Alias + " from 0";
// stop:          string Pcommand = "stop "  + Alias;
// close:         string Pcommand = "close " + Alias;
// loop:          string Pcommand = "play "  + Alias + " repeat";

int mci_open_alias(const TCHAR* media, const TCHAR* alias) {
  TCHAR cmd[MAX_PATH] = {0};
  _stprintf_s(cmd, L"open \"%s\" alias %s", media, alias);
  return mciSendString(cmd, NULL, 0, NULL);
}

int mci_play(const TCHAR* alias) {
  TCHAR cmd[MAX_PATH] = {0};
  _stprintf_s(cmd, L"play \"%s\" from 0", alias);
  return mciSendString(cmd, NULL, 0, NULL);
}

void audio_play_key_press() {
  const TCHAR* key_press_music = L"music/key_press.wav";
  const TCHAR* key_press_alias = L"key_press";

  static bool loaded = false;
  if (!loaded)
    loaded = mci_open_alias(key_press_music, key_press_alias);

  if (loaded)
    mci_play(key_press_alias);
}

void audio_play_clear() {
  const TCHAR* music = L"music/clear.wav";
  const TCHAR* alias = L"clear";

  static bool loaded = false;
  if (!loaded)
    loaded = mci_open_alias(music, alias) == 0;

  if (loaded)
    mci_play(alias);
}

void audio_play_down() {
  const TCHAR* music = L"music/down.wav";
  const TCHAR* alias = L"down";

  static int loaded = false;
  if (!loaded)
    loaded = mci_open_alias(music, alias) == 0;

  if (loaded)
    mci_play(alias);
}
