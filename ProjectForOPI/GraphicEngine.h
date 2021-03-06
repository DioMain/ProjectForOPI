#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <windows.h>
#include "DefaultMath.h"
#include "Compontent.h"

using namespace std;

namespace CE {

	// This class contains information about the game map (size, array of symbols), as well as an array of GameObjects used here
	// Also functions for map manipulate
	class GameMap
	{
	public:

		char defaultSymbol; //Standard background symbol

		/// <summary>
		/// Initialization
		/// </summary>
		/// <param name="size">Map size in Vector2</param>
		/// <param name="defaultSymbol">Standard symbol (for background)</param>
		GameMap(Vector2 size, char defaultSymbol) {
			this->size = size;
			this->defaultSymbol = defaultSymbol;

			for (int y = 0; y < size.y; y++)
			{
				Map.push_back(vector<char>());
				for (int x = 0; x < size.x; x++)
				{
					Map[y].push_back(defaultSymbol);
				}
			}
		}

		/// <summary>
		/// Initialization
		/// </summary>
		GameMap() {
			this->size = Vector2();
			this->defaultSymbol = ' ';
		}

		/// <summary>
		/// Add GameObject to map
		/// </summary>
		/// <param name="gameObject">GameObject pointer</param>
		void addGameObject(GameObject* gameObject) {
			GameObjects.push_back(gameObject);
		}

		/// <summary>
		/// Delete GameObject from map
		/// </summary>
		/// <param name="id">ID</param>
		void deleteGameObjectById(int id) {
			GameObjects.erase(GameObjects.begin() + id);
		}

		/// <summary>
		/// Delete GameObject with current pointer
		/// </summary>
		/// <param name="gameObject">GameObject pointer</param>
		void deleteGameObject(GameObject* gameObject) {
			for (int i = 0; i < (int)GameObjects.size(); i++)
			{
				if (gameObject == GameObjects[i]) { GameObjects.erase(GameObjects.begin() + i); break; }
			}
		}

		/// <summary>
		/// This func drawing map from symbols on console window
		/// </summary>
		void Render() {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFOEX consoleBuffer = CONSOLE_SCREEN_BUFFER_INFOEX();

			GetConsoleScreenBufferInfoEx(hConsole, &consoleBuffer);

			short cursorX = consoleBuffer.dwCursorPosition.X;
			short cursorY = consoleBuffer.dwCursorPosition.Y;

			for (int y = 0; y < size.y; y++)
			{
				for (int x = 0; x < size.x; x++)
				{
					Map[y][x] = defaultSymbol;
				}
			}

			for (int i = 0; i < (int)GameObjects.size(); i++)
			{
				if ((*GameObjects[i]).position.x > -1 && (*GameObjects[i]).position.y > -1
					&& (*GameObjects[i]).position.x < size.x && (*GameObjects[i]).position.y < size.y) {
					Map[(*GameObjects[i]).position.y][(*GameObjects[i]).position.x] = (*GameObjects[i]).Symbol;
				}
				else {
					cout << "GameObject[" << (*GameObjects[i]).Symbol << ", " << (*GameObjects[i]).tag << "] - out of map area!" << endl;
				}

			}

			for (short y = cursorY; y < size.y + cursorY; y++)
			{
				for (short x = cursorX; x < size.x + cursorX; x++)
				{
					SetConsoleCursorPosition(hConsole, { x, y });
					cout << Map[y][x];
				}
			}
		}

		/// <summary>
		/// GameObject function
		/// </summary>
		/// <returns>Count of GameObjects in map</returns>
		int getGameObjectsCount() {
			return GameObjects.size();
		}

		/// <summary>
		/// Map function
		/// </summary>
		/// <returns>Size of map in Vector2</returns>
		Vector2 getSize() {
			return size;
		}

		/// <summary>
		/// GameObject search
		/// </summary>
		/// <param name="pos">position of Object (in Vector2)</param>
		/// <param name="showWarning">Show message that GameObject is not exist?</param>
		/// <returns>GameObject pointer in current position</returns>
		GameObject* getGameObjectByMapPosition(Vector2 pos, bool showWarning = true) {
			GameObject* obj = new GameObject(Vector2(), ' ', "");

			for (int i = 0; i < (int)GameObjects.size(); i++)
			{
				if ((*GameObjects[i]).position == pos) { obj = GameObjects[i]; break; }
			}

			if ((*obj).tag == "" && showWarning) cout << "GameObject no found!" << endl;

			return obj;
		}

		/// <summary>
		/// GameObject search
		/// </summary>
		/// <param name="tag">Tag of GameObjects</param>
		/// <param name="showWarning">Show message that GameObject is not exist?</param>
		/// <returns>GameObject pointer with this tag</returns>
		GameObject* getGameObjectByTag(string tag, bool showWarning = true) {
			GameObject* obj = new GameObject(Vector2(), ' ', "");

			for (int i = 0; i < (int)GameObjects.size(); i++)
			{
				if ((*GameObjects[i]).tag == tag) { obj = GameObjects[i]; break; }
			}

			if ((*obj).tag == "" && showWarning) cout << "GameObject no found!" << endl;

			return obj;
		}

		/// <summary>
		/// GameObjects search
		/// </summary>
		/// <param name="pos">Position of GameObjects (in Vector2)</param>
		/// <returns>Dynamic array (vector) of GameoObject pointers</returns>
		vector<GameObject*> getGameObjectsByMapPosition(Vector2 pos) {
			vector<GameObject*> objs;

			for (int i = 0; i < (int)GameObjects.size(); i++)
			{
				if ((*GameObjects[i]).position == pos) objs.push_back(GameObjects[i]);
			}

			return objs;
		}

		/// <summary>
		/// GameObjects search
		/// </summary>
		/// <param name="tag">Tag of GameObjects</param>
		/// <returns>Dynamic array (vector) of GameObject pointers</returns>
		vector<GameObject*> getGameObjectsByTag(string tag) {
			vector<GameObject*> objs;

			for (int i = 0; i < (int)GameObjects.size(); i++)
			{
				if ((*GameObjects[i]).tag == tag) objs.push_back(GameObjects[i]);
			}

			return objs;
		}

		/// <summary>
		/// GameObjects search
		/// </summary>
		/// <param name="ObjectType">Type of GameObjects</param>
		/// <returns>Dynamic array (vector) of GameObject pointers</returns>
		vector<GameObject*> getGameObjectsByType(ObjectType type) {
			vector<GameObject*> objs;

			for (int i = 0; i < (int)GameObjects.size(); i++)
			{
				if ((*GameObjects[i]).type == type) objs.push_back(GameObjects[i]);
			}

			return objs;
		}

		/// <summary>
		/// GameObject search
		/// </summary>
		/// <param name="id">ID</param>
		/// <returns>GameObject pointer with this id</returns>
		GameObject* getGameObjectById(int id) {
			return GameObjects[id];
		}

	private:

		vector<GameObject*> GameObjects; // Array of GameObjects
		vector<vector<char>> Map; // Char matrix
		Vector2 size; // map size

	};

	enum ConsoleColor {
		white,
		black,
		gray,
		darkgray,
		red,
		blue,
		green,
		orange,
		cyan,
		darkcyan,
		whitegreen,
		purple,
		pink,
		whitered,
		whiteblue
	};

	void SetConsoleColor(ConsoleColor color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		DWORD textStyle = DWORD();

		switch (color)
		{
		case CE::white:
			textStyle = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
			break;
		case CE::black:
			textStyle;
			break;
		case CE::gray:
			textStyle = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
			break;
		case CE::darkgray:
			textStyle = FOREGROUND_INTENSITY;
			break;
		case CE::red:
			textStyle = FOREGROUND_RED;
			break;
		case CE::blue:
			textStyle = FOREGROUND_BLUE;
			break;
		case CE::green:
			textStyle = FOREGROUND_GREEN;
			break;
		case CE::orange:
			textStyle = FOREGROUND_GREEN | FOREGROUND_RED;
			break;
		case CE::cyan:
			textStyle = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
			break;
		case CE::darkcyan:
			textStyle = FOREGROUND_BLUE | FOREGROUND_GREEN;
			break;
		case CE::whitegreen:
			textStyle = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
			break;
		case CE::purple:
			textStyle = FOREGROUND_BLUE | FOREGROUND_RED;
			break;
		case CE::pink:
			textStyle = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
			break;
		case CE::whitered:
			textStyle = FOREGROUND_RED | FOREGROUND_INTENSITY;
			break;
		case CE::whiteblue:
			textStyle = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
			break;
		}

		SetConsoleTextAttribute(hConsole, textStyle);
	}
}


