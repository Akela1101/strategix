#pragma once

#include <QObject>
#include <strx/Entity.hpp>
#include <strx/Game.hpp>
#include <strx/Player.hpp>

#include "../sample1_fwd.hpp"

namespace sample1
{
class SampleGame
        : public QObject
        , public Game
{
	Q_OBJECT
	SampleGameWidget* gameWidget;
	SampleMapWidget* mapWidget;

public:
	SampleGame(ResourcesContext resourcesContext);
	~SampleGame() override;

private:
	void OnMapReceived(s_p<Map> map) override;
	void OnGameStarted() override;
	u_p<Player> OnPlayerAdded(s_p<PlayerMessage> playerMessage) override;
	u_p<Entity> OnEntityAdded(s_p<EntityMessage> entityMessage) override;
	void OnResourcesChanged(const Resources& newResources) override;
	void OnObjectRemoved(IdType id) override;

signals:
	void GameWidgetCreated(QWidget* gameWidget);
	void GameStarted();
};

}  // namespace sample1
