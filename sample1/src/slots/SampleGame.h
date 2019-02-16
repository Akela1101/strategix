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

	int playerSpot; /// spot on map

public:
	SampleGame(int playerSpot);
	~SampleGame() override;

	static void Configure();

private:
	void MessageReceived(s_p<Message> message) override;
	void GameUpdated(GameId gameId, const GameMessage* gameMessage) override;
	void StartGame(s_p<Map> map) override;
	u_p<PlayerSlot> AddPlayer(s_p<PlayerMessage> playerMessage) override;
	u_p<EntitySlot> AddEntity(s_p<EntityMessage> entityMessage) override;
	void ResourcesChanged(const Resources& newResources) override;
	void ObjectRemoved(IdType id) override;
};

}
