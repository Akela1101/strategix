#pragma once

#include <strx/game/GameSlot.h>
#include <Sample_fwd.h>
#include <QObject>

namespace sample1
{
class SampleGame : public QObject, public GameSlot
{
Q_OBJECT
	umap<string, u_p<SamplePlayer>> playerSlots;
	u_p<SampleGameWidget> gameWidget;
	SampleMapWidget* mapWidget;

	ResourceInfosType resourceInfos;
	umap<int, s_p<PlayerMessage>> registeredPlayers;

public:
	static void Configure();

	SampleGame();
	~SampleGame() override;

protected:
	void OnReceiveMessage(s_p<Message> message) override { qInvoke(this, [=](){ HandleMessage(message); }); }

private:
	void Started();
	void HandleMessageInstance(s_p<Message> message);
	void StartGame(strx::MapMessage& mapMessage);
	void AddPlayer(s_p<PlayerMessage> playerMessage);
	void InitHuman(SamplePlayer* player);

private slots:
	void HandleMessage(s_p<Message> message);
};

}
