#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class cityClass {
public:
    void setCityName(string cityName);

    [[nodiscard]] const string &getCity() const;

    void setCityFahrenheit(int fahrenheitValue);

    void setCityCelsius(int celsiusValue);

    int getCityCelsius() const;

    const int getCityFahrenheit() const;


private:
    string city;
    int fahrenheit{};
    int celsius{};

};


void cityClass::setCityName(string cityName) {
    city = std::move(cityName);
}

void cityClass::setCityFahrenheit(int fahrenheitValue) {
    fahrenheit = fahrenheitValue;
}

void cityClass::setCityCelsius(int celsiusValue) {
    celsius = celsiusValue;
}



const int cityClass::getCityFahrenheit() const {
    return fahrenheit;
}

int cityClass::getCityCelsius() const {
    return celsius;
}

const string &cityClass::getCity() const {
    return city;
}

void FileWrite(ostream& output, const string& writeCityName, int writeCityTemp) {
    output << writeCityName << " " << writeCityTemp << endl;
}

int main() {
    // Creates vector to store all city names
    vector<cityClass> listOfCities;


    int C_TEMP;

    cityClass inputCity;

    std::cout << "Starting program" << std::endl;

    // Declares variable to store file read input
    ifstream inData;
    ofstream outData;

    // Stores currently read city name
    string inputCityName;

    int cityTemperatureFahrenheit;
    int cityTemperatureCelsius;


    cout << "%==================================================%" << endl;
    cout << "| |  Running city temperature conversion tool.  | |" << endl;
    cout << "| |                                             | |" << endl;
    cout << "| |  Written by Isa Ali. 7/24/2022              | |" << endl;
    cout << "%==================================================%" << endl;

    inData.open(R"(C:\Users\isaja\CLionProjects\CityTemperatures\FahrenheitTemperature.txt)", ios::out);

    if (!inData) {
        cout << "%=========================%" << endl;
        cout << "|| Unable to open file. ||" << endl;
        cout << "|| Program unsuccessful. ||" << endl;
        cout << "|| Exiting program... ||" << endl;
        cout << "%=========================%" << endl;
        exit(1);
    }
    // Reads input
    inData >> inputCityName;
    inData >> cityTemperatureFahrenheit;
    // Keep reading till input ends
    cout << "Reading city input values:" << endl;
    while (!inData.eof()) {
        // Assigns the value of currently read city data to our inputCity vector.

        inputCity.setCityName(inputCityName);
        inputCity.setCityFahrenheit(cityTemperatureFahrenheit);

        // Inserts new value at the back of the vector

        listOfCities.push_back(inputCity);

        // Displays read data to user

        cout << inputCityName << " --> " << cityTemperatureFahrenheit << " Fahrenheit" << endl;

        // Ends data reading if no more data found

        inData >> inputCityName;
        inData >> cityTemperatureFahrenheit;
    }

    inData.close();

    outData.open(R"(C:\Users\isaja\CLionProjects\CityTemperatures\CelsiusTemperature.txt)");
    if (outData.is_open())
    {
        int i;
        cout << "The output values are: " << endl;

        for (i=0; i < listOfCities.size(); i++) {
            // Clear city value
            cityTemperatureFahrenheit = 0;

            // Read each F_TEMP value
            int F_TEMP = listOfCities.at(i).getCityFahrenheit();

            // Convert to Celsius
            cityTemperatureCelsius = (F_TEMP - 32.0) * 5.0 / 9.0;

            // Write output to celsius variable
            listOfCities.at(i).setCityCelsius(cityTemperatureCelsius);

            cout << inputCityName << " --> " << cityTemperatureCelsius << " Celsius" << endl;
            // Write to file with city values
            cityTemperatureFahrenheit = listOfCities.at(i).getCityCelsius();

            inputCityName = listOfCities.at(i).getCity();

            FileWrite(outData, inputCityName, cityTemperatureCelsius);
        }
        cout << "%=========================%" << endl;

        cout << "|| Program Successful. ||" << endl;

        cout << "%=========================%" << endl;


    }
    else {
        cout << "%=========================%" << endl;
        cout << "|| Unable to open file. ||" << endl;
        cout << "|| Program unsuccessful. ||" << endl;
        cout << "|| Exiting program... ||" << endl;
        cout << "%=========================%" << endl;
        return 1;
    }
    return 0;
}

