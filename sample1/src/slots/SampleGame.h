#pragma once

#include <strx/game/GameSlot.h>
#include <Sample_fwd.h>
#include <QObject>

namespace sample1
{
class SampleGame : public QObject, public GameSlot
{
Q_OBJECT
	umap<int, s_p<PlayerMessage>> registeredPlayers;
	umap<int, u_p<SamplePlayer>> players;
	u_p<SampleGameWidget> gameWidget;
	SampleMapWidget* mapWidget;
	ResourceInfosType resourceInfos;

public:
	static void Configure();

	SampleGame();
	~SampleGame() override;

protected:
	void OnReceiveMessage(s_p<Message> message) override { qInvoke(this, [=](){ HandleMessage(message); }); }

private:
	void HandleMessageImpl(s_p<Message> message);
	void StartGame(strx::MapMessage& mapMessage);
	void AddPlayer(s_p<PlayerMessage> playerMessage);
	void InitHuman(SamplePlayer* player);

private slots:
	void HandleMessage(s_p<Message> message);
};

}
