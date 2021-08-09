#include <atomic>
#include <boost/asio/steady_timer.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/adaptors.hpp>
#include <future>
#include <memory>
#include <nya/invoker.hpp>
#include <thread>

#include "../../strx/EntityInfo.hpp"
#include "../../strx/Map.hpp"
#include "../../strx/Message.hpp"
#include "../../strx/Resources.hpp"
#include "../../strx/TechTree.hpp"
#include "../entity/Entity.hpp"
#include "../game/Game.hpp"
#include "../game/Player.hpp"
#include "../network/Server.hpp"
#include "ConfigManager.hpp"

#include "../../strx/Kernel.hpp"


namespace strx
{
namespace fs = boost::filesystem;
using st_timer = asio::steady_timer;
using st_clock = chrono::steady_clock;

// Constants
static const auto minTick = 42ms;

// Variables
static umap<int, s_p<GameMessage>> games;    // list of games
static s_p<Game> game;                       // single game
static u_p<thread> kernelThread;             // main kernel thread
static u_p<st_timer> timer;                  // tick timer
static atomic<PlayerId> currentPlayerId{0};  // incrementing player id


void TimerHandler(const boost::system::error_code& error)
{
	static st_clock::time_point lastTime = st_clock::now();
	if (!error)
	{
		if (timer) timer->expires_from_now(minTick);

		using namespace chrono;
		auto now = st_clock::now();
		auto dms = duration_cast<milliseconds>(now - lastTime);
		lastTime = now;

		Kernel::Tick((double) dms.count() / 1000);

		if (timer) timer->async_wait(TimerHandler);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Kernel::Run(const string& configPath)
{
	Init(configPath);
	RunImpl();
}

void Kernel::RunAsync(const string& configPath)
{
	Init(configPath);
	kernelThread.reset(new thread(RunImpl));
}

void Kernel::Finish()
{
	Server::Finish();

	timer.reset();
	if (kernelThread) kernelThread->join();
}

void Kernel::Tick(float seconds)
{
	try
	{
		if (!game) return;

		game->Tick(seconds);
	}
	catch (exception& e)
	{
		error_log << "Error during tick: " << e.what();
	}
}

void Kernel::PrintInfo()
{
	cout << "\nMaps: " << endl;
	for (auto&& mapName : GetMapNames()) cout << mapName << endl;

	cout << "\nRace names: " << endl;
	for (auto&& raceName : GetRaceNames()) cout << raceName << endl;
}

PlayerId Kernel::GetNextPlayerId()
{
	return ++currentPlayerId;
}

void Kernel::SendMessageOne(s_p<Message> message, PlayerId playerId)
{
	if (!message) nya_throw << "Writting null message.";

	Server::invoke(Server::SendMessageOne, move(message), playerId);
}

void Kernel::SendMessageAll(s_p<Message> message)
{
	if (!message) nya_throw << "Writting null message.";

	Server::invoke(Server::SendMessageAll, move(message));
}

void Kernel::OnReceiveMessage(s_p<Message> message, ConnectionId connectionId)
{
	try
	{
		switch (message->GetType())
		{
			case Message::Type::CONTEXT: ContextRequested(connectionId); break;
			case Message::Type::GAME: AddGame(move(message), connectionId); break;
			default: game->ReceiveMessage(move(message), connectionId);
		}
	}
	catch (exception& e)
	{
		error_log << e.what();
	}
}

bool Kernel::CheckResource(const string& name)
{
	auto&& resourceInfos = ConfigManager::GetResourceInfos();
	return find(nya_all(*resourceInfos), name) != resourceInfos->end();
}

const TechTree& Kernel::GetTechTree(const string& raceName)
{
	try
	{
		return *ConfigManager::GetTechTrees().at(raceName);
	}
	catch (out_of_range&)
	{
		nya_throw << "No race [%s] in the tech tree."s % raceName;
	}
}

vector<string> Kernel::GetMapNames()
{
	vector<string> mapNames;
	try
	{
		fs::recursive_directory_iterator it(ConfigManager::GetMapsPath()), eod;
		for (; it != eod; ++it)
		{
			const fs::path& p = *it;
			if (fs::is_regular_file(p) && fs::extension(p) == ".map") mapNames.push_back(p.stem().string());
		}
	}
	catch (fs::filesystem_error& e)
	{
		error_log << e.what();
	}
	return mapNames;
}

vector<string> Kernel::GetRaceNames()
{
	vector<string> raceNames;
	for (auto&& name_tree : ConfigManager::GetTechTrees()) raceNames.push_back(name_tree.second->GetRaceName());
	return raceNames;
}

const ResourceInfosType& Kernel::GetResourceInfos()
{
	return ConfigManager::GetResourceInfos();
}

u_p<Resources> Kernel::MakeResources()
{
	auto resources = make_u<Resources>();
	for (auto&& resourceName : *GetResourceInfos()) *resources += Resource(resourceName, 0);
	return resources;
}

void Kernel::Init(const string& configPath)
{
	ConfigManager::ParseConfig(configPath);

	Server::Run(ConfigManager::GetServerPort());

	timer.reset(new st_timer(eventLoop));
	timer->async_wait(TimerHandler);
}

void Kernel::RunImpl()
{
	nya_thread_name("_kern_");
	try
	{
		eventLoop.run();
	}
	catch (exception& e)
	{
		error_log << "Unexpected error in strategix: " << e.what();
		// @#~ should call game to stop
	}
}

void Kernel::ContextRequested(ConnectionId connectionId)
{
	trace_log << "context requested from: " << connectionId;

	auto contextMessage = make_s<ContextMessage>(ConfigManager::GetResourceInfos());
	Server::SendMessageOne(contextMessage, connectionId);

	auto gamesMessage = make_s<MessageVector>();
	for (auto& gameMessage : games | nya::map_values) gamesMessage->push_back(gameMessage);

	Server::SendMessageOne(gamesMessage, connectionId);
}

void Kernel::AddGame(s_p<Message> message, ConnectionId connectionId)
{
	auto gameMessage = dp_cast<GameMessage>(message);
	if (!gameMessage) nya_throw << "Wrong type of GameMessage from " << connectionId;

	trace_log << "new game on: " << gameMessage->mapName << ", created by: " << gameMessage->creatorName;

	gameMessage->id = 1;
	gameMessage->started = false;
	game = make_s<Game>(gameMessage->mapName);
	games.emplace(1, gameMessage);

	Server::SendMessageAll(move(gameMessage));
}

}  // namespace strx
