# WeatherApp
WeatherApp is a C++ application designed to provide users with real-time weather information for their location. Leveraging the libcurl library for API handling, this project fetches data from a weather API provider and presents it to users in a simple command-line interface.

**Features:**

Weather Data Retrieval: Fetches current weather conditions, including temperature, humidity, wind speed, and forecasts, from a weather API.
Location Detection: Automatically detects the user's location using IP geolocation or GPS coordinates for localized weather forecasts.
User Interface: Offers an intuitive command-line interface for user interaction, allowing users to input their location or opt for automatic detection.
API Integration: Demonstrates effective integration with the weather API, handling HTTP requests, parsing JSON/XML responses, and extracting relevant weather data.
Error Handling: Implements robust error handling mechanisms to gracefully handle API request failures and network issues, ensuring a smooth user experience.

**Technologies Used:**

C++: Core programming language for project development.
libcurl: Utilized for handling HTTP requests and interacting with the weather API.
JSON/XML Parsing: Libraries employed for parsing JSON or XML responses from the API.
IP Geolocation/GPS: Methods integrated for dynamic location detection.
Getting Started:
To run WeatherApp locally, ensure you have C++ compiler installed. Clone the repository and compile the source code using your preferred compiler. Run the executable and follow the on-screen instructions to retrieve weather data.

**Contributing:**
Contributions are welcome! Feel free to open issues for bug fixes, feature requests, or enhancements. Pull requests are encouraged for implementing new features or addressing existing issues.

**Acknowledgments:**
Special thanks to the developers of libcurl and the weather API provider for their invaluable contributions to this project.
