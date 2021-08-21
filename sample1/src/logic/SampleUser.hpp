#pragma once

#include <QObject>
#include <strx/User.hpp>

#include "../sample1_fwd.hpp"

namespace sample1
{
class MainWidget;

class SampleUser
        : public QObject
        , public User
{
	u_p<MainWidget> mainWidget;

public:
	SampleUser();
	~SampleUser() override;

private:
	void MessageReceived(s_p<Message> message) override;
	void HandleContext(const ContextMessage* message) override;
	void HandleGame(const GameMessage* gameMessage) override;
	u_p<Game> CreateGame(ResourcesContext resourcesContext) override;
};

}  // namespace sample1
