#pragma once

#include <Wt/WBrush.h>
#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPaintDevice.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include <Wt/WPainterPath.h>
#include <Wt/WPen.h>
#include <Wt/WPointF.h>
#include <Wt/WSpinBox.h>

#include <Wt/WTemplate.h>

#define GRID_SIZE 640
#define CASE_SIZE 40
#define CASE_NUM 16

#define ROBOT_SIZE 32

class WidgetGrille : public Wt::WPaintedWidget
{

private:
	Grid* grid;
	int hoveredItem = -1;
	std::vector<int> routePositions;
	Robot* selectedRobot = nullptr;

public:
	WidgetGrille() : WPaintedWidget()
	{	
		resize(GRID_SIZE, GRID_SIZE);  // 32x32
	}

	void setGrid(Grid* grid) {
		this->grid = grid;
	}
protected:
	void paintEvent(Wt::WPaintDevice* paintDevice) {
		Wt::WPainter painter(paintDevice);

		// Main frame
		drawNonFilledRect(painter, 0, 0, GRID_SIZE, GRID_SIZE, Wt::WColor(Wt::StandardColor::Yellow));

		// Grid
		//int *board = this->grid->getBoard();
		for (int i = 0; i < CASE_NUM; i++) {
			for (int j = 0; j < CASE_NUM; j++) {
				painter.setBrush(Wt::WColor(Wt::StandardColor::Red));

				Wt::WColor color;
				color.setRgb(40, 40, 40, 100);

				//griid
				//drawNonFilledRect(painter, j * CASE_SIZE, i * CASE_SIZE, CASE_SIZE, CASE_SIZE, color);
				int position = (i * CASE_NUM + j);
				switch (this->grid->getBoard()[position]) {
				case 16:
					// NORTH
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, NORTH, Wt::WColor(Wt::StandardColor::DarkBlue));
					break;
				case 4:
					// EAST
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, EAST, Wt::WColor(Wt::StandardColor::DarkBlue));
					break;
				case 8:
					// SOUTH
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, SOUTH, Wt::WColor(Wt::StandardColor::DarkBlue));
					break;
				case 2:
					// WEST
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, WEST, Wt::WColor(Wt::StandardColor::DarkBlue));
					break;
				case 18:
					// WEST + NORTH
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, NORTH, Wt::WColor(Wt::StandardColor::DarkBlue));
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, WEST, Wt::WColor(Wt::StandardColor::DarkBlue));
					break;
				case 10:
					// WEST + SOUTH
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, SOUTH, Wt::WColor(Wt::StandardColor::DarkBlue));
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, WEST, Wt::WColor(Wt::StandardColor::DarkBlue));
					break;
				case 20:
					// EAST + NORTH
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, EAST, Wt::WColor(Wt::StandardColor::DarkBlue));
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, NORTH, Wt::WColor(Wt::StandardColor::DarkBlue));
					break;
				case 12:
					// EAST + SOUTH
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, EAST, Wt::WColor(Wt::StandardColor::DarkBlue));
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, SOUTH, Wt::WColor(Wt::StandardColor::DarkBlue));
					break;
				case 24:
					// NORTH + SOUTH
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, NORTH, Wt::WColor(Wt::StandardColor::DarkBlue));
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, SOUTH, Wt::WColor(Wt::StandardColor::DarkBlue));
					break;
				case 6:
					// EAST + WEST
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, EAST, Wt::WColor(Wt::StandardColor::DarkBlue));
					drawPartialLine(painter, j * CASE_SIZE, i * CASE_SIZE, WEST, Wt::WColor(Wt::StandardColor::DarkBlue));
					break;
				}

				painter.save();
			}
		}

		this->clicked().connect([=] (const Wt::WMouseEvent& e) {
			int x = e.widget().x;
			int y = e.widget().y;
			int realX = (x / CASE_SIZE);
			int realY = (y / CASE_SIZE);
			int positionTab = (realY * CASE_NUM + realX);
			std::cout << "Clicked tab = " << positionTab << " !" << std::endl;

			Robot* robot = getRobot(positionTab);
			if (robot != nullptr) {
				setRobotSelected(positionTab);
				selectedRobot = robot;
			} else {
				if (selectedRobot != nullptr) {
					//if (this->grid->canMove(getRobotIndex(selectedRobot), positionTab)) {
						std::cout << "titi : " << std::endl;
						char dir = '-';
						int rPos = selectedRobot->getPosition();
						int rX = rPos % CASE_NUM;
						int rY = rPos / CASE_NUM;
						if (realY == rY || realX == rX) {
							if (realY > rY) dir = 's';
							else if (realY < rY) dir = 'z';
							else if (realX > rX) dir = 'd';
							else if (realX < rX) dir = 'q';

							this->grid->deplacerRobot(selectedRobot, dir);
						}
					//}
				}
			}
			
			update();
		});

		/*
		this->mouseMoved().connect(bindSafe([this, &painter] (const Wt::WMouseEvent& e) {
			int x = e.widget().x;
			int y = e.widget().y;
			int realX = (x / CASE_SIZE);
			int realY = (y / CASE_SIZE);
			int positionTab = (realY * CASE_NUM + realX);


			Robot* robot = getRobot(positionTab);
			if (robot != nullptr) {
				int x = positionTab % CASE_NUM;
				int y = positionTab / CASE_NUM;
				//drawRoute(painter, x, y);
			}

			std::cout << "Hover:  " << positionTab << " !" << std::endl;
		}));
		*/

		for (int i = 0; i < this->grid->getRobots().size(); i++) {
			Robot* robot = this->grid->getRobots().at(i);
			int position = robot->getPosition();
			int x = position % CASE_NUM;
			int y = position / CASE_NUM;
			

			int red = (robot->getColor() & 0xFF000000) >> 24;
			int green = (robot->getColor() & 0x00FF0000) >> 16;
			int blue = (robot->getColor() & 0x0000FF00) >> 8;

			if (robot->getTarget()) {
				drawNonFilledRect(painter, x * CASE_SIZE + 4, y * CASE_SIZE + 4, CASE_SIZE - 8, CASE_SIZE - 8, Wt::StandardColor::Black);
			}

			drawRobot(painter, x, y, Wt::WColor(red, green, blue, 255));
		}

		int positionMission = this->grid->getGoal();
		int xMission = positionMission % CASE_NUM;
		int yMission = positionMission / CASE_NUM;
		drawMission(painter, xMission, yMission, Wt::WColor(Wt::StandardColor::Yellow));
	}

	// x, y grid pas en coordonnées
	void drawRoute(Wt::WPainter& painter, int x, int y) {
		//TODO: get color from robot
		Wt::WColor color;
		color.setRgb(255, 0, 0, 100);
		painter.setBrush(Wt::WBrush(color));

		//sides n,e,w,s
		int WIDTH = (CASE_NUM * CASE_SIZE) - (x * CASE_SIZE);
		int HEIGHT = 10;
		painter.drawRect(x * CASE_SIZE, y * CASE_SIZE, WIDTH, HEIGHT);
		painter.save();
	}

	Robot* getRobot(int position) {
		for (auto& robot : this->grid->getRobots()) {
			if (robot->getPosition() == position)
				return robot;
		}
		return nullptr;
	}

	Robot* getSelectedRobot() {
		for (auto& robot : this->grid->getRobots()) {
			if (robot->getTarget())
				return robot;
		}
		return nullptr;
	}

	int getRobotIndex(Robot* robot) {
		for (int i = 0; i < this->grid->getRobots().size(); i++) {
			Robot* r = this->grid->getRobots().at(i);
			if (r == robot) return i;
		}
		return -1;
	}

	void setRobotSelected(int position) {
		for (auto& robot : this->grid->getRobots()) {
			robot->setTarget(false);
			if (robot->getPosition() == position)
				robot->setTarget(true);
		}

	}

	// x, y grid pas en coordonnées
	void drawRobot(Wt::WPainter& painter, int x, int y, Wt::WColor color) {
		painter.setBrush(Wt::WBrush(color));
		painter.drawEllipse(x * CASE_SIZE + ((CASE_SIZE - ROBOT_SIZE) / 2), y * CASE_SIZE + ((CASE_SIZE - ROBOT_SIZE) / 2), ROBOT_SIZE, ROBOT_SIZE);
		painter.save();
	}

	void drawMission(Wt::WPainter& painter, int x, int y, Wt::WColor color) {
		painter.setBrush(Wt::WBrush(color));
		painter.drawRect(x * CASE_SIZE, y * CASE_SIZE, ROBOT_SIZE, ROBOT_SIZE);
		painter.save();
	}

	
	void drawNonFilledRect(Wt::WPainter& painter, double x, double y, double width, double height, Wt::WColor color) {
		painter.setBrush(Wt::WBrush(color));
		painter.drawLine(x, y, x + width, y); // haut
		painter.drawLine(x, y + height, x + width, y + height); // bas
		painter.drawLine(x, y, x, y + height); // gauche
		painter.drawLine(x + width, y, x + width, y + height); // droite 
		painter.save();
	}

	void drawPartialLine(Wt::WPainter& painter, double x, double y, int side, Wt::WColor color) {
		painter.setBrush(color);
		if (side == NORTH) {
			painter.drawLine(x, y, x + CASE_SIZE, y); // haut
		} else if (side == SOUTH) {
			painter.drawLine(x, y + CASE_SIZE, x + CASE_SIZE, y + CASE_SIZE); // bas
		} else if (side == WEST) {
			painter.drawLine(x, y, x, y + CASE_SIZE); // gauche
		} else if (side == EAST) {
			painter.drawLine(x + CASE_SIZE, y, x + CASE_SIZE, y + CASE_SIZE); // droite 
		}
		painter.save();
	}


};