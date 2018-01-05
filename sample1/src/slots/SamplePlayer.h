#pragma once

#include <strx/player/PlayerSlot.h>
#include <Sample_fwd.h>
#include <QObject>

namespace sample1
{
class SampleEntity;

class SamplePlayer : public QObject, public PlayerSlot
{
	using PlayerSlot::PlayerSlot;
};
}
