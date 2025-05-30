#pragma once 
#include "Menu.h"
#include "raygui.h"
#include "VisualUtilities.h"
#include "string"


class MainUI
{

private:
	float userVelocity_ = 500.0f;
	float userAngle_ = 45.0f;


	char velocityInput[6] = "500";
	char angleInput[4] = "45";

	bool fireRequested_ = false;

	bool velocityEditMode = false;
	bool angleEditMode = false;

public:
	void DrawUIPanel()
	{
		DrawRectangleRec(uiPanel, LIGHTGRAY);
		DrawText("Input Parameters",
			uiPanel.x + 10,
			uiPanel.y + 10,
			20,
			DARKGRAY);
	}

	// Velocity
	void DrawVelocityInput()
	{
		Rectangle v0Field = {uiPanel.x + 100, uiPanel.y + 50, 100, 30};
		GuiTextBox(v0Field, velocityInput, 6, velocityEditMode);
		DrawText("v0 = ", v0Field.x - 30, v0Field.y + 10, 16, DARKGRAY);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			velocityEditMode = CheckCollisionPointRec(GetMousePosition(), v0Field);
			
		}

	}
	void DrawAngleInput()
	{
		Rectangle angleField = {uiPanel.x+100, uiPanel.y +100, 100, 30};
		GuiTextBox( angleField, angleInput, 4, angleEditMode);
		DrawText("angle = ", angleField.x - 50, angleField.y + 10, 14, DARKGRAY);
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
		{
			angleEditMode = CheckCollisionPointRec(GetMousePosition(), angleField);
			
		}
	}
	// Fire button
	void DrawPlayButton()
	{
		Rectangle playButton = { uiPanel.x + 80, uiPanel.y + 150, 140, 40 };
		if (GuiButton(playButton, "Launch Bullet")) {
			userVelocity_ = atof(velocityInput);
			userAngle_ = atof(angleInput);
			fireRequested_ = true;
		}
	}
	//Speed button
	void DrawTimeScaleToggle(float &timeScale)
	{
		Rectangle buttonNormalSpeed = { toolPanel.x, toolPanel.y + 20, 80, 30 };
		const char* label = "Speed: Normal";

		if (GuiButton(buttonNormalSpeed, label)) {
			slowMotion = false;
			timeScale = 1.0f;
		}

		Rectangle buttonSlowedSpeed(toolPanel.x -100, toolPanel.y + 20, 60, 30);
		const char* slowLabel = "Speed Slow";
		if (GuiButton(buttonSlowedSpeed, slowLabel))
		{
			slowMotion = true;
			timeScale = 0.1f;
		}

		Rectangle buttonPauseSpeed(toolPanel.x-30 , toolPanel.y + 20, 20, 30);
		const char* pauseLabel = "||";
		if (GuiButton(buttonPauseSpeed, pauseLabel))
		{
			slowMotion = true;
			timeScale = 0.0f;
		}
		
	}
	
	void DrawObjectData(const RenderBullet & bullet) const
	{
		Rectangle horizontalData = { toolPanel.x -250, toolPanel.y + 5, 50, 20 };
		//X:
		DrawText("x: ", horizontalData.x - 20, horizontalData.y, 16, DARKGRAY);
		DrawRectangle(horizontalData.x, horizontalData.y, horizontalData.width, horizontalData.height, LIGHTGRAY);
		string xCoordinate = to_string(bullet.getPostition().x);
		xCoordinate.resize(4);
		const char *bufferX = xCoordinate.c_str();
		DrawText(bufferX, horizontalData.x+5, horizontalData.y+4, 14, DARKGRAY);
		
		// Y: 
		DrawText("y: ", horizontalData.x - 20, horizontalData.y+25, 16, GRAY);
		DrawRectangle(horizontalData.x, horizontalData.y+25, horizontalData.width, horizontalData.height, LIGHTGRAY);
		string yCoordinate = to_string(bullet.getPostition().y);
		yCoordinate.resize(4);
		const char* bufferY = yCoordinate.c_str();
		DrawText(bufferY, horizontalData.x+5, horizontalData.y+29, 14, DARKGRAY);
	}

	bool getFireRequested()
	{
		return fireRequested_;
	}
	void setFireRequested(bool fireRequested)
	{
		fireRequested_ = fireRequested;
	}
	float getUserVelocity()
	{
		return userVelocity_;
	}
	float getUserAngle()
	{
		return userAngle_;
	}
};

