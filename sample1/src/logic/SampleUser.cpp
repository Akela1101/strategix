#include <MapInfo.hpp>
#include <strx/strx.hpp>

#include "../ui/MainWidget.hpp"
#include "SampleGame.hpp"

#include "SampleUser.hpp"


namespace sample1
{
SampleUser::SampleUser() : mainWidget(new MainWidget())
{
	using namespace map_info;
	MapInfo::QRegisterTypes();
	MapInfo::LoadTerrainTools();
	MapInfo::LoadObjectTools();

	connect(mainWidget.get(), &MainWidget::createGame, [this](const QString& mapName) { AddGame(mapName.toStdString()); });
	connect(mainWidget.get(), &MainWidget::joinGame, [this](GameId id) { JoinGame(id); });

	mainWidget->show();
}

SampleUser::~SampleUser() = default;

void SampleUser::MessageReceived(s_p<Message> message)
{
	qInvoke(this, [this, message] {
		Message::Type type = message->GetType();
		try
		{
			ReceiveMessage(move(message));
		}
		catch (exception& e)
		{
			error_log << "Error while handling message %s: %s"s % type.c_str() % e.what();
		}
	});
}

void SampleUser::HandleContext(const ContextMessage* message)
{
	mainWidget->SetMaps(message->mapContexts);
}

void SampleUser::HandleGame(const GameMessage* gameMessage)
{
	mainWidget->AddGame(gameMessage);
}

u_p<Game> SampleUser::CreateGame(ResourcesContext resourcesContext)
{
	return make_u<SampleGame>(1, move(resourcesContext));
}

void SampleUser::AddGame(const string& mapName)
{
	auto gameMessage = make_s<GameMessage>();
	gameMessage->mapName = mapName;
	gameMessage->creatorName = "user 1";
	SendMessageOne(move(gameMessage));
}

}  // namespace sample1
