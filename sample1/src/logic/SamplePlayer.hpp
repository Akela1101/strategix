#pragma once

#include <QObject>
#include <strx/Player.hpp>

#include "../sample1_fwd.hpp"

namespace sample1
{
class SampleEntity;

class SamplePlayer
        : public QObject
        , public Player
{
public:
	SamplePlayer(s_p<PlayerMessage> playerMessage) : Player(playerMessage) {}
};
}  // namespace sample1
