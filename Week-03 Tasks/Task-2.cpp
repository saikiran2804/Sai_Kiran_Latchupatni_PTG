#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;


class VehicleData {
private:
    int speed;
    int fuelLevel;
    int temperature;

    mutable mutex dataMutex;

public:
    VehicleData() : speed(0), fuelLevel(100), temperature(70) {}

    void updateData() {
        lock_guard<mutex> lock(dataMutex);
        speed = rand() % 121;
        fuelLevel = max(0, fuelLevel - rand() % 5);
        temperature = 70 + rand() % 41;
    }

    int getSpeed() const {
        lock_guard<mutex> lock(dataMutex);
        return speed;
    }

    int getFuelLevel() const {
        lock_guard<mutex> lock(dataMutex);
        return fuelLevel;
    }

    int getTemperature() const {
        lock_guard<mutex> lock(dataMutex);
        return temperature;
    }
};


class Display {
public:
    static void showData(const VehicleData& data) {
        //system("clear");
        int speed = data.getSpeed();
        int fuel = data.getFuelLevel();
        int temp = data.getTemperature();

        cout << "================ Instrument Cluster ================" << endl;
        cout << "Speed       : " << speed << " km/h" << endl;
        cout << "Fuel Level  : " << fuel << "%" <<endl;
        cout << "Temperature : " << temp << "°C " << endl;

        if (temp > 100)
            cout << "WARNING: Engine overheating! " <<endl;
        if (fuel < 10)
            cout << "WARNING: Low fuel level!" <<endl;
        cout << "===================================================" << endl;
    }
};

void dataUpdater(VehicleData& data) {
    while (true) {
        data.updateData();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void dataDisplayer(VehicleData& data) {
    while (true) {
        Display::showData(data);
        this_thread::sleep_for(chrono::seconds(2));
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    VehicleData vehicleData;
   
    thread updater(dataUpdater, ref(vehicleData));
    thread displayer(dataDisplayer, ref(vehicleData));

    updater.join();
    displayer.join();

    return 0;
}