// Write Catch2 unit tests in C++ for the following:
// 1. A function `getUpdatedVolumePresets(int)` that adds a non-negative volume preset to a vector of {5, 10, 15, 20, 25}.
//    - Test that valid presets are added.
//    - Test that negative presets are not added.
// 2. A class `UserInputEventQueue` with:
//    - `addEvent()` which adds to the back of a deque.
//    - `addPriorityEvent()` which adds to the front.
//    - `processEvents()` which removes events FIFO.
//    - Test correct ordering and clearing after processing.
// 3. A class `AudioControlHistory` with:
//    - `addAction()` to add string to list.
//    - `undoLastAction()` to pop from back.
//    - Test tracking, undo, and safety on empty list.

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>
#include <deque>
#include <list>
#include <algorithm>

// === Code Under Test ===
// Copy these declarations or #include your main file with only function/class definitions (no main)

std::vector<int> getUpdatedVolumePresets(int newPreset) {
    const std::vector<int> defaultPresets = {5, 10, 15, 20, 25};
    std::vector<int> volumePresets(defaultPresets);
    if (newPreset >= 0) {
        volumePresets.push_back(newPreset);
    }
    return volumePresets;
}

class UserInputEventQueue {
private:
    std::deque<std::string> eventQueue;

public:
    void addEvent(const std::string& event) {
        eventQueue.push_back(event);
    }

    void addPriorityEvent(const std::string& event) {
        eventQueue.push_front(event);
    }

    std::deque<std::string> getQueue() const {
        return eventQueue;
    }

    void processEvents() {
        while (!eventQueue.empty()) {
            eventQueue.pop_front();
        }
    }
};

class AudioControlHistory {
private:
    std::list<std::string> actions;

public:
    void addAction(const std::string& action) {
        actions.push_back(action);
    }

    void undoLastAction() {
        if (!actions.empty()) {
            actions.pop_back();
        }
    }

    std::list<std::string> getHistory() const {
        return actions;
    }
};

// === Test Cases ===

TEST_CASE("Volume Presets behave correctly", "[volume]") {
    SECTION("Adds valid preset") {
        auto result = getUpdatedVolumePresets(30);
        REQUIRE(result.back() == 30);
        REQUIRE(result.size() == 6);
    }

    SECTION("Rejects negative preset") {
        auto result = getUpdatedVolumePresets(-10);
        REQUIRE(result.size() == 5);
        REQUIRE(std::find(result.begin(), result.end(), -10) == result.end());
    }
}

TEST_CASE("User Input Event Queue works as expected", "[event]") {
    UserInputEventQueue queue;

    SECTION("Regular and priority events are ordered properly") {
        queue.addEvent("VolumeUp");
        queue.addEvent("Mute");
        queue.addPriorityEvent("PhoneCallAudio");

        auto q = queue.getQueue();
        REQUIRE(q.front() == "PhoneCallAudio");
        REQUIRE(q[1] == "VolumeUp");
        REQUIRE(q[2] == "Mute");
    }

    SECTION("Processing clears the queue") {
        queue.addEvent("VolumeDown");
        queue.addPriorityEvent("PhoneCallAudio");
        queue.processEvents();

        REQUIRE(queue.getQueue().empty());
    }
}

TEST_CASE("Audio Control History tracks and undoes actions", "[history]") {
    AudioControlHistory history;

    SECTION("Tracks added actions") {
        history.addAction("Set Volume 15");
        history.addAction("Mute");

        auto log = history.getHistory();
        REQUIRE(log.back() == "Mute");
        REQUIRE(log.front() == "Set Volume 15");
    }

    SECTION("Undo removes last action") {
        history.addAction("Set Volume 15");
        history.addAction("Mute");
        history.undoLastAction();

        auto log = history.getHistory();
        REQUIRE(log.size() == 1);
        REQUIRE(log.back() == "Set Volume 15");
    }

    SECTION("Undo on empty list is safe") {
        history.undoLastAction();  // Should not crash
        REQUIRE(history.getHistory().empty());
    }
}
