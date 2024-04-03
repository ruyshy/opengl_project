#include <pch.h>
#include <Game/Scene/SceneBase.h>

SceneBase::SceneBase(Game* game) : mpGame(game), mID(0), mName("") { initializeScene(); }
SceneBase::SceneBase(Game* game, unsigned int id, string name) : mpGame(game), mID(id), mName(name) { initializeScene(); }

