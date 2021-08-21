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

	connect(mainWidget.get(), &MainWidget::CreateGameClicked,
	        [this](const QString& mapName) { AddGame(mapName.toStdString()); });
	connect(mainWidget.get(), &MainWidget::GameSelected, [this](GameId id) { SelectGame(id); });
	connect(mainWidget.get(), &MainWidget::JoinGameClicked, [this]() { JoinGame(); });

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
	mainWidget->AddGameContext(gameMessage);
}

u_p<Game> SampleUser::CreateGame(ResourcesContext resourcesContext)
{
	auto game = make_u<SampleGame>(move(resourcesContext));
	connect(game.get(), &SampleGame::GameWidgetCreated,
	        [this](QWidget* gameWidget) { mainWidget->PrepareGamePage(gameWidget); });
	connect(game.get(), &SampleGame::GameStarted, [this]() { mainWidget->StartGamePage(); });
	return game;
}

}  // namespace sample1
