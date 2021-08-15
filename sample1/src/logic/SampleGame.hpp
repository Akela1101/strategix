#pragma once

#include <QObject>
#include <strx/Game.hpp>

#include "../sample1_fwd.hpp"

namespace sample1
{
class SampleGame
        : public QObject
        , public Game
{
	u_p<SampleGameWidget> gameWidget;
	SampleMapWidget* mapWidget;

	int playerSpot;  ///< spot on map

public:
	SampleGame(int playerSpot, ResourcesContext resourcesContext);
	~SampleGame() override;

private:
	void StartGame(s_p<Map> map) override;
	u_p<Player> AddPlayer(s_p<PlayerMessage> playerMessage) override;
	u_p<Entity> AddEntity(s_p<EntityMessage> entityMessage) override;
	void ResourcesChanged(const Resources& newResources) override;
	void ObjectRemoved(IdType id) override;
};

}  // namespace sample1
