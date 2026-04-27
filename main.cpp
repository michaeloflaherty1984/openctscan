#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <random>

class CTScan {
public:
    CTScan(int id, const std::string& patientName)
        : scanId(id), patient(patientName), imageData(generateImageData()) {}

    void displayScanInfo() const {
        std::cout << "CT Scan ID: " << scanId << "\nPatient: " << patient << "\n";
    }

    void displayImageData() const {
        std::cout << "Image Data (simulated):\n";
        for (const auto& row : imageData) {
            for (auto val : row) {
                std::cout << val << " ";
            }
            std::cout << "\n";
        }
    }

private:
    int scanId;
    std::string patient;
    std::vector<std::vector<int>> imageData;

    std::vector<std::vector<int>> generateImageData() {
        std::vector<std::vector<int>> data(10, std::vector<int>(10));
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        for (auto& row : data) {
            for (auto& val : row) {
                val = dis(gen);
            }
        }
        return data;
    }
};

class CTScannerMachine {
public:
    CTScannerMachine(const std::string& location) : machineLocation(location), nextScanId(1) {}

    CTScan performScan(const std::string& patientName) {
        std::cout << "Starting CT scan for patient: " << patientName << " at " << machineLocation << "...\n";
        simulateScanningProcess();
        CTScan scan(nextScanId++, patientName);
        std::cout << "Scan completed.\n";
        return scan;
    }

private:
    std::string machineLocation;
    int nextScanId;

    void simulateScanningProcess() {
        using namespace std::chrono_literals;
        std::cout << "Positioning patient...\n";
        std::this_thread::sleep_for(1s);
        std::cout << "Rotating scanner...\n";
        std::this_thread::sleep_for(2s);
        std::cout << "Capturing images...\n";
        std::this_thread::sleep_for(2s);
        std::cout << "Processing images...\n";
        std::this_thread::sleep_for(1s);
    }
};

int main() {
    CTScannerMachine scanner("City Hospital - Radiology Dept.");

    std::string patientName;
    std::cout << "Enter patient name for CT scan: ";
    std::getline(std::cin, patientName);

    CTScan scan = scanner.performScan(patientName);

    scan.displayScanInfo();
    scan.displayImageData();

    return 0;
}
