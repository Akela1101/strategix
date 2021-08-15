#include <GameWidget.hpp>
#include <logic/SampleEntity.hpp>
#include <logic/SamplePlayer.hpp>
#include <strx/strx.hpp>

#include "../ui/SampleGameWidget.hpp"
#include "../ui/SampleMapWidget.hpp"

#include "SampleGame.hpp"


namespace sample1
{
SampleGame::SampleGame(int playerSpot, ResourcesContext resourcesContext)
        : Game(move(resourcesContext)), gameWidget(nullptr), mapWidget(nullptr), playerSpot(playerSpot)
{}

SampleGame::~SampleGame() = default;

void SampleGame::StartGame(s_p<Map> map)
{
	gameWidget.reset(new SampleGameWidget(GetResourcesContext()));
	mapWidget = gameWidget->CreateMapWidget<SampleMapWidget>();
	mapWidget->SetMap(move(map));

	Game::StartGame(nullptr);  //@#~

	gameWidget->show();
}

u_p<Player> SampleGame::AddPlayer(s_p<PlayerMessage> playerMessage)
{
	auto player = make_u<SamplePlayer>(move(playerMessage));

	if (player->GetType() == PlayerType::HUMAN) { mapWidget->Init(this, player.get()); }
	return player;
}

u_p<Entity> SampleGame::AddEntity(s_p<EntityMessage> entityMessage)
{
	auto entity = make_u<SampleEntity>(move(entityMessage), mapWidget);
	auto mapEntity = (MapEntity*) mapWidget->GetMapObject(entity->GetId());
	mapEntity->SetMaxHp(entity->GetMaxHp());
	return entity;
}

void SampleGame::ResourcesChanged(const Resources& newResources)
{
	gameWidget->OnResourcesChanged(newResources);
}

void SampleGame::ObjectRemoved(IdType id)
{
	mapWidget->ObjectRemoved(id);
}

}  // namespace sample1
