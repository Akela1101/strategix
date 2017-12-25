#pragma once

#include <Strategix_fwd.h>
#include <strx/network/NetworkCommon.h>
#include <nya/signal.hpp>

/**
 * Main functionality is here.
 */
namespace strx
{
class Kernel : public nya::event_loop_holder<Kernel>
{
	Kernel() = delete;
	
public:
	// keep this calling order
	static void Run(const string& configPath);
	static void RunAsync(const string& configPath);
	static void LoadMap(const string& mapName);
	static void AddPlayer(const string& name, PlayerType type, int playerId, const string& raceName);
	static void Start(s_p<Game> game);
	static void Finish();
	
	static void Tick(float seconds);
	static void PrintInfo();
	
	static void OnReceiveMessage(s_p<Message> message, NetId clientId);
	
	static bool CheckResource(const string& name);
	static const TechTree& GetTechTree(const string& raceName);
	static vector <string> GetMapNames();
	static vector <string> GetRaceNames();
	static const ResourceInfosType& GetResourceInfos();
	static u_p<Resources> MakeResources();
	
private:
	static void Init(const string& configPath);
	static void RunImpl();
};
}
