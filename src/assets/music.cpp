#include "music.h"
#include <SFML/Audio.hpp>

Array<Ref<Music> > Music::list;
float Music::volume = 100;
sf::Music Music::player;

void Music::play() const {
  player.stop();
  player.openFromFile(file);
  player.setVolume(volume);
  player.setLoop(true);
  player.play();
}

const Music Music::MENU("assets/music/music_menu_theme.ogg");
const Music Music::LVL1("assets/music/music_lvl1_theme.ogg");
const Music Music::LVL2("assets/music/music_lvl2_theme.ogg");
const Music Music::LVL3("assets/music/music_lvl3_theme.ogg");
const Music Music::BOSS1("assets/music/music_lvl1_boss.ogg");
const Music Music::BOSS2("assets/music/music_lvl2_boss.ogg");
const Music Music::BOSS3("assets/music/music_lvl3_boss.ogg");
const Music Music::LOSS("assets/music/music_credits.ogg");
const Music Music::END("assets/music/music_credits.ogg");
