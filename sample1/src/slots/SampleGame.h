#pragma once

#include <strx/kernel/GameSlot.h>
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

public:
	static void Configure();
	
	SampleGame();
	~SampleGame() override;
	
	//void Start();
	//void PlayerAdded(Player* player);

protected:
	void OnReceiveMessage(s_p<Message> message) override { qInvoke(this, [=](){ HandleMessage(message); }); }

private:
	void InitHuman(SamplePlayer* playerSlot);
	
private slots:
	void HandleMessage(s_p<Message> message);
};

}
