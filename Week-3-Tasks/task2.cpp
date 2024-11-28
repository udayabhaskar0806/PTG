#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>
using namespace std;
class VehicleData {
public:
    atomic<int> speed;          // Speed in km/h
    atomic<int> fuelLevel;      // Fuel level in percentage (0-100)
    atomic<int> engineTemp;     // Engine temperature in Celsius (°C)

    VehicleData() : speed(0), fuelLevel(100), engineTemp(80) {}

    void updateData() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> speedDist(0, 180);          
        uniform_int_distribution<> fuelDist(0, 100);            
        uniform_int_distribution<> tempDist(60, 120);          

        while (true) {
            speed = speedDist(gen);
            fuelLevel = fuelDist(gen);
            engineTemp = tempDist(gen);
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};

class Display {
public:
    void showData(const VehicleData& data) {
        while (true) {

            cout << "Speed: " << data.speed.load() << " km/h\n";
            cout << "Fuel Level: " << data.fuelLevel.load() << "%\n";
            cout << "Engine Temperature: " << data.engineTemp.load() << "°C\n";
            cout <<"========="<<endl;
            // Display warnings if thresholds are exceeded
            if (data.fuelLevel.load() < 10) {
                cout << "\033[1;31mWarning: Fuel level is below 10%!\033[0m\n";
            }
            if (data.engineTemp.load() > 100) {
                cout << "\033[1;31mWarning: Engine temperature is above 100°C!\033[0m\n";
            }
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};

int main() {
    VehicleData vehicleData;
    Display display;

    thread updateThread(&VehicleData::updateData, &vehicleData);

    thread displayThread(&Display::showData, &display, ref(vehicleData));

    updateThread.join();
    displayThread.join();

    return 0;
}
