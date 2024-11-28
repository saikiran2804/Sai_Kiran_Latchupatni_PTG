#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;


class Event {
public:
    string eventType;
    int x, y;        
    int xEnd, yEnd;  
    string timestamp;

    Event(const string& type, int x, int y, const string& time, int xEnd = 0, int yEnd = 0)
        : eventType(type), x(x), y(y), xEnd(xEnd), yEnd(yEnd), timestamp(time) {}
};


string generateTimestamp() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
    return string(buffer);
}


queue<Event> eventQueue;


void generateEvents() {
    while (true) {
        string eventType = (rand() % 2 == 0) ? "Tap" : "Swipe";
        int x = rand() % 500;
        int y = rand() % 500;
        string timestamp = generateTimestamp();

        if (eventType == "Tap") {
            eventQueue.push(Event("Tap", x, y, timestamp));
        } else {
            int xEnd = x + (rand() % 201 - 100);
            int yEnd = y + (rand() % 201 - 100);
            eventQueue.push(Event("Swipe", x, y, timestamp, xEnd, yEnd));
        }

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}


void processEvents() {
    while (true) {
        if (!eventQueue.empty()) {
            Event currentEvent = eventQueue.front();
            eventQueue.pop();

            cout << "Event at " << currentEvent.timestamp << ": ";

            if (currentEvent.eventType == "Tap") {
                cout << "Tap at (" << currentEvent.x << ", " << currentEvent.y << ")" << endl;
            } else if (currentEvent.eventType == "Swipe") {
                int dx = currentEvent.xEnd - currentEvent.x;
                int dy = currentEvent.yEnd - currentEvent.y;

                string direction;
                if (abs(dx) > abs(dy)) {
                    direction = (dx > 0) ? "Right" : "Left";
                } else {
                    direction = (dy > 0) ? "Down" : "Up";
                }

                cout << "Swipe from (" << currentEvent.x << ", " << currentEvent.y << ") "
                     << "to (" << currentEvent.xEnd << ", " << currentEvent.yEnd << ") - "
                     << "Direction: " << direction << endl;
            }

            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

 
    thread eventGenerator(generateEvents);
    thread eventProcessor(processEvents);

    eventGenerator.join();
    eventProcessor.join();

    return 0;
}