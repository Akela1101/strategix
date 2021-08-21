#include <GameWidget.hpp>
#include <logic/SampleEntity.hpp>
#include <logic/SamplePlayer.hpp>
#include <strx/strx.hpp>

#include "../ui/SampleGameWidget.hpp"
#include "../ui/SampleMapWidget.hpp"

#include "SampleGame.hpp"


namespace sample1
{
SampleGame::SampleGame(ResourcesContext resourcesContext)
        : Game(move(resourcesContext)), gameWidget(nullptr), mapWidget(nullptr)
{}

SampleGame::~SampleGame() = default;

void SampleGame::OnMapReceived(s_p<Map> map)
{
	gameWidget = new SampleGameWidget(GetResourcesContext());
	emit GameWidgetCreated(gameWidget);

	mapWidget = gameWidget->CreateMapWidget<SampleMapWidget>();
	mapWidget->SetMap(move(map));

	Game::OnMapReceived(nullptr);  //@#~
}

void SampleGame::OnGameStarted()
{
	emit GameStarted();
}

u_p<Player> SampleGame::OnPlayerAdded(s_p<PlayerMessage> playerMessage)
{
	auto player = make_u<SamplePlayer>(move(playerMessage));

	if (player->GetType() == PlayerType::SELF) { mapWidget->Init(this, player.get()); }
	return player;
}

u_p<Entity> SampleGame::OnEntityAdded(s_p<EntityMessage> entityMessage)
{
	auto entity = make_u<SampleEntity>(move(entityMessage), mapWidget);
	auto mapEntity = (MapEntity*) mapWidget->GetMapObject(entity->GetId());
	mapEntity->SetMaxHp(entity->GetMaxHp());
	return entity;
}

void SampleGame::OnResourcesChanged(const Resources& newResources)
{
	gameWidget->OnResourcesChanged(newResources);
}

void SampleGame::OnObjectRemoved(IdType id)
{
	mapWidget->ObjectRemoved(id);
}

}  // namespace sample1
