#pragma once

#include "WidgetGrille.h"

class WidgetGrilleMove : public Wt::WPaintedWidget
{
private:
	Grid* grid;
	Robot* selectedRobot = nullptr;

public:
	WidgetGrilleMove() : WPaintedWidget()
	{
		resize(GRID_SIZE, GRID_SIZE);  // 32x32
	}

	void setGrid(Grid* grid) {
		this->grid = grid;
		selectedRobot = this->grid->getRobots().at(0);
	}

protected:
		int* intToRGB(int color) {
		int rtn[3];
		rtn[0] = (color & 0x00ff0000) >> 16;
		rtn[1] = (color & 0x0000ff00) >> 8;
		rtn[2] = (color & 0x000000ff);

		return rtn;
	}
	void paintEvent(Wt::WPaintDevice* paintDevice) {
		Wt::WPainter painter(paintDevice);
		// Main frame
		drawNonFilledRect(painter, 0, 0, GRID_SIZE, GRID_SIZE, Wt::WColor(Wt::StandardColor::Yellow));

		for (int i = 0; i < CASE_NUM; i++) {
			for (int j = 0; j < CASE_NUM; j++) {
				drawNumber(painter, i, j);
				painter.save();
			}
		}
	}
	void drawNonFilledRect(Wt::WPainter& painter, double x, double y, double width, double height, Wt::WColor color) {
		painter.setBrush(Wt::WBrush(color));
		painter.drawLine(x, y, x + width, y); // haut
		painter.drawLine(x, y + height, x + width, y + height); // bas
		painter.drawLine(x, y, x, y + height); // gauche
		painter.drawLine(x + width, y, x + width, y + height); // droite 
		painter.save();
	}

	void drawNumber(Wt::WPainter& painter, int x, int y) {
		painter.setBrush(Wt::WBrush(Wt::StandardColor::Black));
		Wt:WString* s;
		Wt::WFlags<Wt::AlignmentFlag> flags(Wt::AlignmentFlag::Center);
		if (grid->getPrecomputeMinimumMovesArray()[x * CASE_NUM + y] != INT_MAX && grid->getPrecomputeMinimumMovesArray()[y * CASE_NUM + x] != 0) {
			s = new Wt::WString(std::to_string(grid->getPrecomputeMinimumMovesArray()[y * CASE_NUM + x]));
			painter.drawText(x * CASE_SIZE + ((CASE_SIZE - ROBOT_SIZE) / 2), y * CASE_SIZE + ((CASE_SIZE - ROBOT_SIZE) / 2), ROBOT_SIZE, ROBOT_SIZE, flags,  *s);
		}
		else if (grid->getPrecomputeMinimumMovesArray()[y * CASE_NUM + x] == 0) {
			s = new Wt::WString(std::to_string(grid->getPrecomputeMinimumMovesArray()[y * CASE_NUM + x]));
			painter.drawText(x * CASE_SIZE + ((CASE_SIZE - ROBOT_SIZE) / 2), y * CASE_SIZE + ((CASE_SIZE - ROBOT_SIZE) / 2), ROBOT_SIZE, ROBOT_SIZE, flags, "X");
		}
		else {
			s = new Wt::WString(std::to_string(grid->getPrecomputeMinimumMovesArray()[x * CASE_NUM + y]));
			painter.drawText(x * CASE_SIZE + ((CASE_SIZE - ROBOT_SIZE) / 2), y * CASE_SIZE + ((CASE_SIZE - ROBOT_SIZE) / 2), ROBOT_SIZE, ROBOT_SIZE, flags, "");
		}
	}
};