#pragma once

#include <QObject>
#include <sample1_fwd.hpp>
#include <strx/User.hpp>

namespace sample1
{
class SampleUser
        : public QObject
        , public User
{
	int userId;  //todo: replace with gui selector

public:
	static void Configure();

public:
	SampleUser(int userId) : userId(userId) {}
	~SampleUser() override;

private:
	void MessageReceived(s_p<Message> message) override;
	void HandleContext() override;
	void GameUpdated(GameId gameId, const GameMessage* gameMessage) override;
	u_p<Game> AddGame(GameId gameId, ResourceInfosType resourceInfos) override;
};

}  // namespace sample1
