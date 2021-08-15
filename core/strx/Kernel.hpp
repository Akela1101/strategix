#pragma once

#include <nya/invoker.hpp>

#include "NetworkCommon.hpp"
#include "strx_fwd.hpp"

/**
 * Main functionality is here.
 */
namespace strx
{
class Kernel : public nya::static_invoker<Kernel, boost::asio::io_context>
{
	Kernel() = delete;

public:
	static void Run(const string& configPath);
	static void RunAsync(const string& configPath);
	static void Finish();

	static void Tick(float seconds);
	static void PrintInfo();

	static PlayerId GetNextPlayerId();
	static void SendMessageOne(s_p<Message> message, PlayerId playerId);
	static void SendMessageAll(s_p<Message> message);
	static void OnReceiveMessage(s_p<Message> message, ConnectionId connectionId);

	static bool CheckResource(const string& name);
	static const TechTree& GetTechTree(const string& raceName);
	static vector<string> GetRaceNames();
	static const ResourcesContext& GetResourcesContext();
	static u_p<Resources> MakeResources();

private:
	static void Init(const string& configPath);
	static void LoadMapContexts();
	static void RunImpl();
	static void ContextRequested(ConnectionId connectionId);
	static void AddGame(s_p<Message> message, ConnectionId connectionId);
};
}  // namespace strx
