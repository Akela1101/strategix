#pragma once

#include <QObject>
#include <sample1_fwd.hpp>
#include <strx/PlayerSlot.hpp>

namespace sample1
{
class SampleEntity;

class SamplePlayer
        : public QObject
        , public PlayerSlot
{
public:
	SamplePlayer(s_p<PlayerMessage> playerMessage) : PlayerSlot(playerMessage) {}
};
}  // namespace sample1
