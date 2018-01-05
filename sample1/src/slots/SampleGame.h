#pragma once

#include <strx/game/GameSlot.h>
#include <Sample_fwd.h>
#include <QObject>

namespace sample1
{
class SampleGame : public QObject, public GameSlot
{
	u_p<SampleGameWidget> gameWidget;
	SampleMapWidget* mapWidget;

public:
	static void Configure();

	SampleGame();
	~SampleGame() override;

private:
	void MessageReceived(s_p<Message> message) override { qInvoke(this, [=](){ ReceiveMessage(move(message)); }); }
	void StartGame(s_p<Map> map) override;
	u_p<PlayerSlot> AddPlayer(s_p<PlayerMessage> playerMessage) override;
	u_p<EntitySlot> AddEntity(s_p<EntityMessage> entityMessage) override;
	void MineRemoved(IdType id) override;
};

}
