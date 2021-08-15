#pragma once

#include <QWidget>

#include "../sample1_fwd.hpp"

namespace sample1
{
QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
	Q_OBJECT
	Ui::MainWidget* ui;

public:
	explicit MainWidget(QWidget* parent = nullptr);
	~MainWidget() override;

	void SetMaps(s_p<vector<MapContext>> maps);
	void AddGame(const GameMessage* gameMessage);

signals:
	void createGame(const QString& mapName);
	void joinGame(GameId id);
};
}  // namespace sample1
