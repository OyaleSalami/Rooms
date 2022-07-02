#pragma once
#include "Player.h"

namespace Network
{
	class Lobby
	{
	public:
		int maxPlayers; 
		//std::vector<Player> players;

		Lobby(const int &_maxPlayers)
		{
			maxPlayers = _maxPlayers;
			//players.reserve(maxPlayers);
		}

		bool isFull()
		{
			for(int i = 1; i <= maxPlayers; i++)
			{
				/*
				if (players[i].tcpClient)
				{
					return true;
				}
				*/
			}

			return false;
		}

	private:
		void Preload()
		{
			for (int i = 1; i <= maxPlayers; i++)
			{
				///players.push_back(Player(i));
			}
		}
	};
}