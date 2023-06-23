#include "SoundPlayer.h"
#include <SFML/Audio.hpp>
#include <random>

using namespace std;
using namespace sf;

void SoundPlayer::playRandomSound(vector<Sound>& sounds)
{
	random_device rd;
	mt19937 randNumGenerator(rd());
	uniform_int_distribution<size_t> dist(0, sounds.size() - 1);

	size_t randIndex = dist(randNumGenerator);
	sounds.at(randIndex).play();
}
