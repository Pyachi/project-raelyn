#include <QSoundEffect>
#include <QMediaPlayer>
#include "sfx.h"
#include "sound.h"
#include "song.h"

QQueue<QSoundEffect*>* Sound::queue = new QQueue<QSoundEffect*>;
QMediaPlayer* Sound::global_song = nullptr;

bool Sound::ready = false;

void Sound::playSound(SFX effect, qreal vol) {
  if (!ready)
    init();

  QSoundEffect* player = queue->dequeue();
  player->setSource(QUrl(effect.sound_effect));
  player->setVolume(vol);
  player->play();
  queue->enqueue(player);
}

void Sound::playMusic(Song song, int volume) {
  if (global_song == nullptr)
    global_song = new QMediaPlayer;

  global_song->stop();
  global_song->setMedia(QUrl("qrc:/sounds/sounds/music_menu_theme.ogg"));
  global_song->setVolume(100);
  global_song->play();
}

void Sound::pauseMusic() { global_song->pause(); }

void Sound::init() {
  for (int i = 0; i < 32; i++)
    queue->enqueue(new QSoundEffect);
  ready = true;
}
