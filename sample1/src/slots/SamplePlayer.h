#pragma once

#include <QObject>
#include <Sample_fwd.h>
#include <strx/player/PlayerSlot.h>

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
