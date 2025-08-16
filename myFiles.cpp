#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <list>

// Volume preset management
std::vector<int> getUpdatedVolumePresets(int newPreset) {
    const std::vector<int> defaultPresets = {5, 10, 15, 20, 25};
    std::vector<int> volumePresets(defaultPresets);
    if (newPreset >= 0) {
        volumePresets.push_back(newPreset);
    }
    return volumePresets;
}
void manageVolumePresets(int newPreset) {
    std::vector<int> volumePresets = getUpdatedVolumePresets(newPreset);
    std::cout << "Current Volume Presets: ";
    for (const auto& preset : volumePresets) {
        std::cout << preset << " ";
    }
    std::cout << std::endl;
}
// User input event queue
class UserInputEventQueue {
private:
    std::deque<std::string> eventQueue;

public:
    UserInputEventQueue() = default;

    void addEvent(const std::string& event) {
        eventQueue.push_back(event);
    }

    void addPriorityEvent(const std::string& event) {
        eventQueue.push_front(event);
    }

    void processEvents() {
        if (eventQueue.empty()) {
            std::cout << "No events to process." << std::endl;
            return;
        }
        while (!eventQueue.empty()) {
            std::cout << "Processing event: " << eventQueue.front() << std::endl;
            eventQueue.pop_front();
        }
    }
};

// Audio control action history
class AudioControlHistory {
private:
    std::list<std::string> actions;

public:
    AudioControlHistory() = default;

    void addAction(const std::string& action) {
        actions.push_back(action);
    }

    void undoLastAction() {
        if (!actions.empty()) {
            std::cout << "Undoing action: " << actions.back() << std::endl;
            actions.pop_back();
        } else {
            std::cout << "No actions to undo." << std::endl;
        }
    }

    void displayHistory() const {
        std::cout << "Audio Control History: ";
        for (const auto& action : actions) {
            std::cout << action << " | ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Volume presets demo
    manageVolumePresets(30);
    manageVolumePresets(-5); // Test negative value

    // User input event queue demo
    UserInputEventQueue queue;
    queue.processEvents(); // Test empty queue
    queue.addEvent("MouseClick");
    queue.addEvent("KeyPress");
    queue.addPriorityEvent("EmergencyStop");
    queue.processEvents();

    // Audio control history demo
    AudioControlHistory history;
    history.addAction("Volume Up");
    history.addAction("Mute");
    history.addAction("Volume Down");
    history.displayHistory();
    history.undoLastAction();
    history.displayHistory();

    return 0;
}