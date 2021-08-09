#pragma once

#include <QObject>
#include <sample1_fwd.hpp>
#include <strx/Player.hpp>

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
