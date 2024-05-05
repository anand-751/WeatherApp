#include <iostream>
#include <curl/curl.h>
#include <iomanip> 
#include <ctime>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Callback function to write received data into a string
size_t writeCallback(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}


// Function to fetch weather data for a city
json fetchWeather(const std::string& apiKey, const std::string& cityName) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl" << std::endl;
        return json();
    }

    // Set the URL to the weather API
    std::string url = "https://api.openweathermap.org/data/2.5/weather?q=" + cityName + "&appid=" + apiKey;

    // Set curl options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

    std::string response;

    // Write the response data to a string
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return json();
    }

    // Parse JSON response
    json jsonResponse;
    try {
        jsonResponse = json::parse(response);
    } catch (const std::exception& e) {
        std::cerr << "Failed to parse JSON response: " << e.what() << std::endl;
    }

    // Cleanup
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return jsonResponse;
}


// Function to validate city name input
bool isValidCityName(const std::string& cityName) {
    // Check if the city name is not empty
    if (cityName.empty()) {
        std::cerr << "City name cannot be empty" << std::endl;
        return false;
    }
    // Add more validation rules as needed
    return true;
}

int main() {
    // Provide your OpenWeatherMap API key here
    std::string apiKey = "3b51a5b645af9e6f2f2aebb14ffab483";

    std::string city;
    std::cout << "Enter city name: ";
    std::getline(std::cin, city);

    // Validate city name input
    if (!isValidCityName(city)) {
        return 1; // Exit with error code
    }

    // Fetch current weather for the specified city
    json currentWeatherData = fetchWeather(apiKey, city);

    if (!currentWeatherData.empty()) {
        std::cout << "Weather for " << city << ":" << std::endl;
        std::cout << std::setw(20) << std::left << "Country Code :" << currentWeatherData["sys"]["country"] << std::endl;
        std::cout << std::setw(20) << std::left << "Description:" << currentWeatherData["weather"][0]["description"] << std::endl;
        double temperatureCelsius = currentWeatherData["main"]["temp"].get<double>() - 273.15;
        std::cout << std::setw(20) << std::left << "Temperature :" << std::fixed << std::setprecision(2) << temperatureCelsius << "(°C)" << std::endl;
        std::cout << std::setw(20) << std::left << "Humidity :" << currentWeatherData["main"]["humidity"]<< "(%)" << std::endl;
        std::cout << std::setw(20) << std::left << "Wind Speed :" << currentWeatherData["wind"]["speed"] <<"(m/s)"<< std::endl;

        time_t date = currentWeatherData["dt"];
        std::cout << std::setw(20) << std::left << "Date:" << std::put_time(std::localtime(&date), "%Y-%m-%d") << std::endl;
        time_t sunrise = currentWeatherData["sys"]["sunrise"];
        std::cout << std::setw(20) << std::left << "Sunrise:" << std::put_time(std::localtime(&sunrise), "%H:%M:%S") << std::endl;
        time_t sunset = currentWeatherData["sys"]["sunset"];
        std::cout << std::setw(20) << std::left << "Sunset:" << std::put_time(std::localtime(&sunset), "%H:%M:%S") << std::endl;
    } else {
        std::cerr << "Failed to fetch weather data for " << city << std::endl;
    }


    return 0;
}
