
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <list>


/**
 * @brief Returns a list of volume presets, optionally including a new preset.
 *
 * This function creates a vector of default volume presets and, if the provided
 * newPreset value is non-negative, appends it to the list. The resulting vector
 * is returned.
 *
 * @param newPreset The new volume preset to add. If negative, no preset is added.
 * @return std::vector<int> The updated list of volume presets.
 */

std::vector<int> getUpdatedVolumePresets(int newPreset) {
    const std::vector<int> defaultPresets = {5, 10, 15, 20, 25};
    std::vector<int> volumePresets(defaultPresets);
    if (newPreset >= 0) {
        volumePresets.push_back(newPreset);
    }
    return volumePresets;
}
/**
 * @brief Manages volume presets by updating and displaying them.
 *
 * This function retrieves the updated volume presets based on the provided
 * newPreset value and prints them to the console.
 *
 * @param newPreset The new volume preset to add. If negative, no preset is added.
 */

void manageVolumePresets(int newPreset) {
    std::vector<int> volumePresets = getUpdatedVolumePresets(newPreset);
    std::cout << "Current Volume Presets: ";
    for (const auto& preset : volumePresets) {
        std::cout << preset << " ";
    }
    std::cout << std::endl;
}

/**
 * @class UserInputEventQueue
 * @brief Manages a queue of user input events, allowing for both regular and priority event insertion.
 *
 * This class provides methods to add events to the queue, either at the back (regular events)
 * or at the front (priority events). It also provides a method to process all queued events
 * in order, printing each event as it is processed.
 *
 * @note Events are represented as strings.
 *
 * @method UserInputEventQueue() Default constructor.
 * @method void addEvent(const std::string& event) Adds a regular event to the back of the queue.
 * @method void addPriorityEvent(const std::string& event) Adds a priority event to the front of the queue.
 * @method void processEvents() Processes and prints all events in the queue. If the queue is empty, prints a message.
 */
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


/**
 * @class AudioControlHistory
 * @brief Manages a history of audio control actions, allowing undo and display operations.
 *
 * This class maintains a list of audio control actions performed by the user.
 * It provides functionality to add new actions, undo the last action, and display
 * the history of actions.
 *
 * Usage example:
 * @code
 * AudioControlHistory history;
 * history.addAction("Play");
 * history.addAction("Pause");
 * history.undoLastAction();
 * history.displayHistory();
 * @endcode
 */
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