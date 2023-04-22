
#include <signal.h>

#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include "DirectoryLoader.h"
#include "StringUtils.h"
#include "Index.h"
#include "Logger.h"
#include "Player.h"
#include "Room.h"

#define FPS 15
#define MILLISECONDS_PER_FRAME 1000 / FPS

SharedRoomPtr GetNextRoom(Index<Room>* index, SharedRoomPtr room, const std::string& direction) {
	const std::string& next_room_id = room->GetNextRoomId(direction);
	if (next_room_id.empty()) {
		Log("There is no where to go in the %s direction", direction.c_str());
		return nullptr;
	}

	SharedRoomPtr proposed_room = index->get_object(next_room_id);
	if (!proposed_room) {
		Log("There was a room proposed for %s but it does not exist in the index",
			direction.c_str());
		return nullptr;
	}

	return proposed_room;
}

#define PlayerInputAsync                      \
  std::async(std::launch::async, [&]() {      \
    Log("Awaiting player input");             \
    std::string s = "";                       \
    std::getline(std::cin, s);                \
    Log("Exact Player input: (%s)", s.c_str()); \
    return s;                                 \
  });

namespace Game {
	Index<Room>* rooms;
	std::atomic<bool> running = true;
};

// Properly shutsdown the game. Only call this once.
void Shutdown() {
	if (Game::running) {
		Game::running = false;
		Log("Shutting down the game");
		if (Game::rooms) {
			Log("Clearing the rooms");
			Game::rooms->clear();
			delete Game::rooms;
			Game::rooms = nullptr;
		}
		Logger::Instance().Shutdown();
	} else Log("Shutdown called twice.  Ignoring second call.");
}

int main() {
	auto fmt = "logs/log_%i.txt";
	char buf[100];
	snprintf(buf, 100, fmt, time(NULL));
	if (!Logger::Instance().Initialize(buf)) {
		std::cerr << "Cannot initialize the logger" << std::endl;
		return EXIT_FAILURE;
	}
	LogDebug("Starting the game at time %i", time(NULL));

	signal(SIGINT, [](int termSignal) { Log("Received signal %i", termSignal); exit(EXIT_FAILURE); });
	atexit([]() { Shutdown(); });
	LogDebug("Creating the player");
	Player player("Player1", "Player1", "A non-descript player.  They are grey-ish");

	LogDebug("Creating the rooms index");
	Game::rooms = new Index<Room>();

	LogDebug("Loading the rooms");
	DirectoryLoader::LoadDirectoryOfRooms("./data/rooms/", Game::rooms);

	std::string starting_room = "mrober10-room-a";

	LogDebug("Getting the starting room");
	SharedRoomPtr room = Game::rooms->get_object(starting_room);

	LogDebug("Got the starting room");

	if (!room) {
		LogError("Cannot find the starting room : %s", starting_room.c_str());
		player.clear();
		return EXIT_FAILURE;
	}

	player.SetCurrentRoom(room);
	Message("\n");

	player.Look();

	std::string input_line;

	// Begin player input
	auto playerInput = PlayerInputAsync;

	auto currentTime = std::chrono::high_resolution_clock::now();
	while (true) {
		auto playerInputStatus = playerInput.wait_until(currentTime);
		bool playerInputReady = playerInputStatus == std::future_status::ready;
		if (playerInputReady) {
			input_line = playerInput.get();
			input_line = StringUtils::Trim(input_line);
			// Lowercase for consistency
			std::transform(input_line.begin(), input_line.end(), input_line.begin(), ::tolower);

			// Check if we are quitting
			if (input_line == "q" || input_line == "quit" || input_line == "exit") {
				Message("bye");
				player.clear();
				return EXIT_SUCCESS;
			}

			LogDebug("Trimmed player input: (%s) size (%i)", input_line.c_str(), input_line.size());
			if (input_line == "look") {
				player.Look();
			} else if (input_line.find("go ", 0) == 0) {
				auto sp = StringUtils::Split(input_line, " \t");

				if (sp.size() <= 1) {
					Message("I need a valid direction to go in.");
				} else {
					const std::string& direction = sp.at(1);

					SharedRoomPtr current_room = player.GetCurrentRoom();

					if (!current_room) {
						LogError("You are standing nowhere, so can't go anywhere.  Shutting down game.");
						exit(EXIT_FAILURE);
					}

					SharedRoomPtr proposed_room = GetNextRoom(Game::rooms, current_room, direction);
					if (proposed_room) {
						player.SetCurrentRoom(proposed_room);
						Log("\n");
						player.Look();
					} else Log("There isn't anything in that direction");
				}
			} else {
				Log("The command %s is not recognized", input_line.c_str());
			}
			input_line.clear();
			playerInput = PlayerInputAsync;
		}
		LogDebug("Sleeping for %i milliseconds time %i", MILLISECONDS_PER_FRAME, time(NULL));
		currentTime += std::chrono::milliseconds(MILLISECONDS_PER_FRAME);
		std::this_thread::sleep_until(currentTime);
	}
}
