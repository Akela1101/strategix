#pragma once

#include <QObject>
#include <sample1_fwd.hpp>
#include <strx/GameSlot.hpp>

namespace sample1
{
class SampleGame
        : public QObject
        , public GameSlot
{
	u_p<SampleGameWidget> gameWidget;
	SampleMapWidget* mapWidget;

	int playerSpot;  ///< spot on map

public:
	SampleGame(int playerSpot, ResourceInfosType resourceInfos);
	~SampleGame() override;

private:
	void StartGame(s_p<Map> map) override;
	u_p<PlayerSlot> AddPlayer(s_p<PlayerMessage> playerMessage) override;
	u_p<EntitySlot> AddEntity(s_p<EntityMessage> entityMessage) override;
	void ResourcesChanged(const Resources& newResources) override;
	void ObjectRemoved(IdType id) override;
};

}  // namespace sample1
