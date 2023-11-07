#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <fstream>
using namespace std;
// ADMIN IS ABLE TO ADD NEW FLIGHTS INTO OUR SYSTEM
// ADMIN IS ABLE TO SEE THE LIST OF ALL THE PEOPLE WHO HAVE BOOKED A PARTICULAR FLIGHT
#include <iostream>
#include <map>
#include <vector>
#include <ctime>
using namespace std;
struct Flight
{
    std::string airline;
    std::string flight;
    std::string source_city;
    std::string departure_time;
    std::string destination_city;
    int stops;
    std::string duration;
    double price;
    // seats are starting from starting seat like a1 and ending at ending seat say z5
    string startingSeatNumber;
    string endingSeatNumber;
};
std::map<int, std::map<std::string, std::vector<Flight>>> finalflight;
class Node
{
public:
    // will store firstName of person boarding the flight
    string firstName;
    // will store last Name of person boarding
    string lastName;
    // will tell seat equipped to nhui
    bool taken;
    long long unsigned int phoneNumber;
    int age;
    string seatNumber;
    bool vegetarian;
    Node *prev;
    Node *next;
    Node(string seatNumber)
    {
        this->seatNumber = seatNumber;
        this->prev = NULL;
        this->next = NULL;
    }
    void setFirstName(const string &firstName)
    {
        this->firstName = firstName;
    }

    void setLastName(const string &lastName)
    {
        this->lastName = lastName;
    }

    void setTaken(bool isTaken)
    {
        taken = isTaken;
    }

    void setPhoneNumber(int phoneNumber)
    {
        this->phoneNumber = phoneNumber;
    }
    void setVegetarian(bool isVegetarian)
    {
        vegetarian = isVegetarian;
    }
    void setAge(int hisAge)
    {
        this->age = hisAge;
    }
};

int getIndices(const map<int, map<string, vector<Flight>>> &flightData, string date)
{
    std::vector<int> vect;
    for (const auto &index : flightData)
    {
        vect.push_back(index.first);
    }
    // create a mapping of currentDate to the elements of vector
    map<string, int> correspondingDates;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;
    int currentMonth = ltm->tm_mon;
    int currentDate = ltm->tm_mday;
    int numberOfDays;
    if (currentMonth == 0 || currentMonth == 2 || currentMonth == 4 || currentMonth == 6 || currentMonth == 7 || currentMonth == 9 || currentMonth == 11)
    {
        numberOfDays = 31;
    }
    else if (currentMonth == 3 || currentMonth == 5 || currentMonth == 8 || currentMonth == 10)
    {
        numberOfDays = 30;
    }
    else if (currentMonth == 1)
    {
        if ((currentYear % 4 == 0 && currentYear % 100 != 0) || (currentYear % 400 == 0))
        {
            numberOfDays = 29;
        }
        else
        {
            numberOfDays = 28;
        }
    }
    for (int i = 0; i < vect.size(); i++)
    {
        int targetDate = (currentDate + i) % numberOfDays;
        int targetMonth = currentMonth + 1;
        int targetYear = currentYear;

        if (currentDate + i > numberOfDays)
        {
            targetDate = (currentDate + i) % numberOfDays;
            targetMonth = currentMonth + 1;
            if (targetDate == 0)
            {
                targetDate = numberOfDays;
                targetMonth++;
            }
            if (targetMonth > 12)
            {
                targetMonth = 1;
                targetYear++;
            }
        }
        string dateKey = to_string(targetDate) + "." + to_string(targetMonth) + "." + to_string(targetYear);

        // Store the mapping in the map
        correspondingDates[dateKey] = vect[i];
    }
    // CORRESPONDING DATES HAS NOW FLIGHTS MAPPED TO THE DATES TODAY AND UPCOMING
    if (correspondingDates.find(date) != correspondingDates.end())
    {
        return correspondingDates[date];
    }
    // meaning that date wasnt found
    return -1;
}
void printFlightData(const std::map<int, std::map<std::string, std::vector<Flight>>> &flightData)
{
    for (const auto &indexEntry : flightData)
    {
        int index_number = indexEntry.first;
        std::cout << "Index Number: " << index_number << std::endl;

        const std::map<std::string, std::vector<Flight>> &flightMap = indexEntry.second;

        for (const auto &flightEntry : flightMap)
        {
            const std::string &flightKey = flightEntry.first;
            const std::vector<Flight> &flights = flightEntry.second;

            std::cout << "Flight Key: " << flightKey << std::endl;
            std::cout << "------------------------------------------------------------------------------------------------------------------" << std::endl;

            // Set column widths
            std::cout << std::left << std::setw(12) << "Airline";
            std::cout << std::left << std::setw(8) << "Flight";
            std::cout << std::left << std::setw(15) << "Source City";
            std::cout << std::left << std::setw(16) << "Departure Time";
            std::cout << std::left << std::setw(18) << "Destination City";
            std::cout << std::left << std::setw(6) << "Stops";
            std::cout << std::left << std::setw(10) << "Duration";
            std::cout << std::left << std::setw(10) << "Price";
            std::cout << std::left << std::setw(15) << "Seat Matrix" << std::endl;

            for (const Flight &flight : flights)
            {
                std::cout << std::left << std::setw(12) << flight.airline;
                std::cout << std::left << std::setw(8) << flight.flight;
                std::cout << std::left << std::setw(15) << flight.source_city;
                std::cout << std::left << std::setw(16) << flight.departure_time;
                std::cout << std::left << std::setw(18) << flight.destination_city;
                std::cout << std::left << std::setw(6) << flight.stops;
                std::cout << std::left << std::setw(10) << flight.duration;
                std::cout << std::left << std::setw(10) << flight.price;
                std::cout << std::left << std::setw(15) << flight.startingSeatNumber << "-" << flight.endingSeatNumber << std::endl;
            }
            std::cout << "------------------------------------------------------------------------------------------------------------------" << std::endl;
        }
    }
}

map<int, map<string, vector<Flight>>> alreadyAddedFlights()
{
    map<int, map<string, vector<Flight>>> flightData;

    flightData[0]["SG-0400"].push_back({"SpiceJet", "SG-0400", "Delhi", "04:00a.m.", "Mumbai", 0, "02hr10min", 15953, "A1", "X4"});
    flightData[0]["SG-0900"].push_back({"SpiceJet", "SG-0900", "Delhi", "09:00a.m.", "Mumbai", 0, "02hr20min", 15955, "A1", "X5"});
    flightData[0]["SG-1400"].push_back({"SpiceJet", "SG-1400", "Delhi", "14:00p.m.", "Mumbai", 0, "02hr33min", 15960, "A1", "X6"});
    flightData[0]["SG-1800"].push_back({"SpiceJet", "SG-1800", "Delhi", "18:00p.m.", "Mumbai", 0, "02hr00min", 16000, "A1", "Y4"});

    flightData[0]["VS-1200"].push_back({"Vistara", "VS-1200", "Delhi", "12:00p.m.", "Mumbai", 0, "01hr45min", 15800, "A1", "Y5"});
    flightData[0]["VS-1900"].push_back({"Vistara", "VS-1900", "Delhi", "19:00p.m.", "Mumbai", 0, "02hr30min", 15875, "A1", "Y6"});

    flightData[0]["IG-1000"].push_back({"Indigo", "IG-1000", "Delhi", "10:00a.m.", "Mumbai", 0, "02hr20min", 15550, "A1", "X4"});
    flightData[0]["IG-2100"].push_back({"Indigo", "IG-2100", "Delhi", "21:00p.m.", "Mumbai", 0, "02hr15min", 15560, "A1", "X5"});
    flightData[0]["IG-0100"].push_back({"Indigo", "IG-0100", "Delhi", "01:00a.m.", "Mumbai", 0, "02hr35min", 15675, "A1", "X6"});

    flightData[0]["AA-0930"].push_back({"AirAsia", "AA-0930", "Delhi", "09:30a.m.", "Mumbai", 0, "02hr14min", 15600, "A1", "Y4"});

    flightData[1]["SG-0400"].push_back({"SpiceJet", "SG-0400", "Delhi", "04:00a.m.", "Mumbai", 1, "02hr10min", 10953, "A1", "X4"});
    flightData[1]["SG-0900"].push_back({"SpiceJet", "SG-0900", "Delhi", "09:00a.m.", "Mumbai", 1, "02hr20min", 10955, "A1", "X5"});
    flightData[1]["SG-1400"].push_back({"SpiceJet", "SG-1400", "Delhi", "14:00p.m.", "Mumbai", 1, "02hr33min", 10960, "A1", "X6"});
    flightData[1]["SG-1800"].push_back({"SpiceJet", "SG-1800", "Delhi", "18:00p.m.", "Mumbai", 1, "02hr00min", 10000, "A1", "Y4"});

    flightData[1]["VS-1200"].push_back({"Vistara", "VS-1200", "Delhi", "12:00p.m.", "Mumbai", 1, "01hr45min", 10800, "A1", "Y5"});
    flightData[1]["VS-1900"].push_back({"Vistara", "VS-1900", "Delhi", "19:00p.m.", "Mumbai", 1, "02hr30min", 10875, "A1", "Y6"});

    flightData[1]["IG-1000"].push_back({"Indigo", "IG-1000", "Delhi", "10:00a.m.", "Mumbai", 1, "02hr20min", 10550, "A1", "X4"});
    flightData[1]["IG-2100"].push_back({"Indigo", "IG-2100", "Delhi", "21:00p.m.", "Mumbai", 1, "02hr15min", 10560, "A1", "X5"});
    flightData[1]["IG-0100"].push_back({"Indigo", "IG-0100", "Delhi", "01:00a.m.", "Mumbai", 1, "02hr35min", 10675, "A1", "X6"});
    flightData[1]["AA-0930"].push_back({"AirAsia", "AA-0930", "Delhi", "09:30a.m.", "Mumbai", 1, "02hr14min", 10600, "A1", "Y4"});

    flightData[2]["SG-0400"].push_back({"SpiceJet", "SG-0400", "Delhi", "04:00a.m.", "Mumbai", 0, "02hr10min", 9953, "A1", "X4"});
    flightData[2]["SG-0900"].push_back({"SpiceJet", "SG-0900", "Delhi", "09:00a.m.", "Mumbai", 0, "02hr20min", 9955, "A1", "X5"});
    flightData[2]["SG-1400"].push_back({"SpiceJet", "SG-1400", "Delhi", "14:00p.m.", "Mumbai", 0, "02hr33min", 9960, "A1", "X6"});
    flightData[2]["SG-1800"].push_back({"SpiceJet", "SG-1800", "Delhi", "18:00p.m.", "Mumbai", 0, "02hr00min", 9000, "A1", "Y4"});
    flightData[2]["VS-1200"].push_back({"Vistara", "VS-1200", "Delhi", "12:00p.m.", "Mumbai", 0, "01hr45min", 9800, "A1", "Y5"});
    flightData[2]["VS-1900"].push_back({"Vistara", "VS-1900", "Delhi", "19:00p.m.", "Mumbai", 0, "02hr30min", 9875, "A1", "Y6"});
    flightData[2]["IG-1000"].push_back({"Indigo", "IG-1000", "Delhi", "10:00a.m.", "Mumbai", 0, "02hr20min", 9550, "A1", "X4"});
    flightData[2]["IG-2100"].push_back({"Indigo", "IG-2100", "Delhi", "21:00p.m.", "Mumbai", 0, "02hr15min", 9560, "A1", "X5"});
    flightData[2]["IG-0100"].push_back({"Indigo", "IG-0100", "Delhi", "01:00a.m.", "Mumbai", 0, "02hr35min", 9675, "A1", "X6"});
    flightData[2]["AA-0930"].push_back({"AirAsia", "AA-0930", "Delhi", "09:30a.m.", "Mumbai", 0, "02hr14min", 9600, "A1", "Y4"});

    flightData[3]["SG-0400"].push_back({"SpiceJet", "SG-0400", "Delhi", "04:00a.m.", "Mumbai", 0, "02hr10min", 8953, "A1", "X4"});
    flightData[3]["SG-0900"].push_back({"SpiceJet", "SG-0900", "Delhi", "09:00a.m.", "Mumbai", 0, "02hr20min", 8955, "A1", "X5"});
    flightData[3]["SG-1400"].push_back({"SpiceJet", "SG-1400", "Delhi", "14:00p.m.", "Mumbai", 0, "02hr33min", 8960, "A1", "X6"});
    flightData[3]["SG-1800"].push_back({"SpiceJet", "SG-1800", "Delhi", "18:00p.m.", "Mumbai", 0, "02hr00min", 8000, "A1", "Y4"});
    flightData[3]["VS-1200"].push_back({"Vistara", "VS-1200", "Delhi", "12:00p.m.", "Mumbai", 0, "01hr45min", 8800, "A1", "Y5"});
    flightData[3]["VS-1900"].push_back({"Vistara", "VS-1900", "Delhi", "19:00p.m.", "Mumbai", 0, "02hr30min", 8875, "A1", "Y6"});
    flightData[3]["IG-1000"].push_back({"Indigo", "IG-1000", "Delhi", "10:00a.m.", "Mumbai", 0, "02hr20min", 8550, "A1", "X4"});
    flightData[3]["IG-2100"].push_back({"Indigo", "IG-2100", "Delhi", "21:00p.m.", "Mumbai", 0, "02hr15min", 8560, "A1", "X5"});
    flightData[3]["IG-0100"].push_back({"Indigo", "IG-0100", "Delhi", "01:00a.m.", "Mumbai", 0, "02hr35min", 8875, "A1", "X6"});
    flightData[3]["AA-0930"].push_back({"AirAsia", "AA-0930", "Delhi", "09:30a.m.", "Mumbai", 0, "02hr14min", 8600, "A1", "Y4"});

    flightData[4]["SG-0400"].push_back({"SpiceJet", "SG-0400", "Delhi", "04:00a.m.", "Mumbai", 0, "02hr10min", 7953, "A1", "X4"});
    flightData[4]["SG-0900"].push_back({"SpiceJet", "SG-0900", "Delhi", "09:00a.m.", "Mumbai", 0, "02hr20min", 7955, "A1", "X5"});
    flightData[4]["SG-1400"].push_back({"SpiceJet", "SG-1400", "Delhi", "14:00p.m.", "Mumbai", 0, "02hr33min", 7960, "A1", "X6"});
    flightData[4]["SG-1800"].push_back({"SpiceJet", "SG-1800", "Delhi", "18:00p.m.", "Mumbai", 0, "02hr00min", 7000, "A1", "Y4"});
    flightData[4]["VS-1200"].push_back({"Vistara", "VS-1200", "Delhi", "12:00p.m.", "Mumbai", 0, "01hr45min", 7800, "A1", "Y5"});
    flightData[4]["VS-1900"].push_back({"Vistara", "VS-1900", "Delhi", "19:00p.m.", "Mumbai", 0, "02hr30min", 7875, "A1", "Y6"});
    flightData[4]["IG-1000"].push_back({"Indigo", "IG-1000", "Delhi", "10:00a.m.", "Mumbai", 0, "02hr20min", 7550, "A1", "X4"});
    flightData[4]["IG-2100"].push_back({"Indigo", "IG-2100", "Delhi", "21:00p.m.", "Mumbai", 0, "02hr15min", 7560, "A1", "X5"});
    flightData[4]["IG-0100"].push_back({"Indigo", "IG-0100", "Delhi", "01:00a.m.", "Mumbai", 0, "02hr35min", 7675, "A1", "X6"});
    flightData[4]["AA-0930"].push_back({"AirAsia", "AA-0930", "Delhi", "09:30a.m.", "Mumbai", 0, "02hr14min", 7600, "A1", "Y4"});

    flightData[5]["SG-0400"].push_back({"SpiceJet", "SG-0400", "Delhi", "04:00a.m.", "Mumbai", 0, "02hr10min", 8953, "A1", "X4"});
    flightData[5]["SG-0900"].push_back({"SpiceJet", "SG-0900", "Delhi", "09:00a.m.", "Mumbai", 0, "02hr20min", 8955, "A1", "X5"});
    flightData[5]["SG-1400"].push_back({"SpiceJet", "SG-1400", "Delhi", "14:00p.m.", "Mumbai", 0, "02hr33min", 8960, "A1", "X6"});
    flightData[5]["SG-1800"].push_back({"SpiceJet", "SG-1800", "Delhi", "18:00p.m.", "Mumbai", 0, "02hr00min", 8000, "A1", "Y4"});
    flightData[5]["VS-1200"].push_back({"Vistara", "VS-1200", "Delhi", "12:00p.m.", "Mumbai", 0, "01hr45min", 8800, "A1", "Y5"});
    flightData[5]["VS-1900"].push_back({"Vistara", "VS-1900", "Delhi", "19:00p.m.", "Mumbai", 0, "02hr30min", 8875, "A1", "Y6"});
    flightData[5]["IG-1000"].push_back({"Indigo", "IG-1000", "Delhi", "10:00a.m.", "Mumbai", 0, "02hr20min", 8550, "A1", "X4"});
    flightData[5]["IG-2100"].push_back({"Indigo", "IG-2100", "Delhi", "21:00p.m.", "Mumbai", 0, "02hr15min", 8560, "A1", "X5"});
    flightData[5]["IG-0100"].push_back({"Indigo", "IG-0100", "Delhi", "01:00a.m.", "Mumbai", 0, "02hr35min", 8875, "A1", "X6"});
    flightData[5]["AA-0930"].push_back({"AirAsia", "AA-0930", "Delhi", "09:30a.m.", "Mumbai", 0, "02hr14min", 8600, "A1", "Y4"});

    flightData[6]["SG-0400"].push_back({"SpiceJet", "SG-0400", "Delhi", "04:00a.m.", "Mumbai", 0, "02hr10min", 9953, "A1", "X4"});
    flightData[6]["SG-0900"].push_back({"SpiceJet", "SG-0900", "Delhi", "09:00a.m.", "Mumbai", 0, "02hr20min", 9955, "A1", "X5"});
    flightData[6]["SG-1400"].push_back({"SpiceJet", "SG-1400", "Delhi", "14:00p.m.", "Mumbai", 0, "02hr33min", 8910, "A1", "X6"});
    flightData[6]["SG-1800"].push_back({"SpiceJet", "SG-1800", "Delhi", "18:00p.m.", "Mumbai", 0, "02hr00min", 9100, "A1", "Y4"});
    flightData[6]["VS-1200"].push_back({"Vistara", "VS-1200", "Delhi", "12:00p.m.", "Mumbai", 0, "01hr45min", 9800, "A1", "Y5"});
    flightData[6]["VS-1900"].push_back({"Vistara", "VS-1900", "Delhi", "19:00p.m.", "Mumbai", 0, "02hr30min", 8875, "A1", "Y6"});
    flightData[6]["IG-1000"].push_back({"Indigo", "IG-1000", "Delhi", "10:00a.m.", "Mumbai", 0, "02hr20min", 7850, "A1", "X4"});
    flightData[6]["IG-2100"].push_back({"Indigo", "IG-2100", "Delhi", "21:00p.m.", "Mumbai", 0, "02hr15min", 7660, "A1", "X5"});
    flightData[6]["IG-0100"].push_back({"Indigo", "IG-0100", "Delhi", "01:00a.m.", "Mumbai", 0, "02hr35min", 8775, "A1", "X6"});
    flightData[6]["AA-0930"].push_back({"AirAsia", "AA-0930", "Delhi", "09:30a.m.", "Mumbai", 0, "02hr14min", 8900, "A1", "Y4"});

    flightData[7]["SG-0400"].push_back({"SpiceJet", "SG-0400", "Delhi", "04:00a.m.", "Mumbai", 0, "02hr10min", 9183, "A1", "X4"});
    flightData[7]["SG-0900"].push_back({"SpiceJet", "SG-0900", "Delhi", "09:00a.m.", "Mumbai", 0, "02hr20min", 9355, "A1", "X5"});
    flightData[7]["SG-1400"].push_back({"SpiceJet", "SG-1400", "Delhi", "14:00p.m.", "Mumbai", 0, "02hr33min", 8110, "A1", "X6"});
    flightData[7]["SG-1800"].push_back({"SpiceJet", "SG-1800", "Delhi", "18:00p.m.", "Mumbai", 0, "02hr00min", 9400, "A1", "Y4"});
    flightData[7]["VS-1200"].push_back({"Vistara", "VS-1200", "Delhi", "12:00p.m.", "Mumbai", 0, "01hr45min", 9100, "A1", "Y5"});
    flightData[7]["VS-1900"].push_back({"Vistara", "VS-1900", "Delhi", "19:00p.m.", "Mumbai", 0, "02hr30min", 8375, "A1", "Y6"});
    flightData[7]["IG-1000"].push_back({"Indigo", "IG-1000", "Delhi", "10:00a.m.", "Mumbai", 0, "02hr20min", 7250, "A1", "X4"});
    flightData[7]["IG-2100"].push_back({"Indigo", "IG-2100", "Delhi", "21:00p.m.", "Mumbai", 0, "02hr15min", 7560, "A1", "X5"});
    flightData[7]["IG-0100"].push_back({"Indigo", "IG-0100", "Delhi", "01:00a.m.", "Mumbai", 0, "02hr35min", 8175, "A1", "X6"});
    flightData[7]["AA-0930"].push_back({"AirAsia", "AA-0930", "Delhi", "09:30a.m.", "Mumbai", 0, "02hr14min", 8200, "A1", "Y4"});

    // ERROR COMING HERE DO CHECK IT FAST
    flightData[8]["SG-0400"].push_back({"SpiceJet", "SG-0400", "Delhi", "04:00a.m.", "Mumbai", 0, "02hr10min", 5953, "A1", "X4"});
    flightData[8]["SG-0900"].push_back({"SpiceJet", "SG-0900", "Delhi", "09:00a.m.", "Mumbai", 0, "02hr20min", 5955, "A1", "X5"});
    flightData[8]["SG-1400"].push_back({"SpiceJet", "SG-1400", "Delhi", "14:00p.m.", "Mumbai", 0, "02hr33min", 5960, "A1", "X6"});
    flightData[8]["SG-1800"].push_back({"SpiceJet", "SG-1800", "Delhi", "18:00p.m.", "Mumbai", 0, "02hr00min", 6000, "A1", "Y4"});
    flightData[8]["VS-1200"].push_back({"Vistara", "VS-1200", "Delhi", "12:00p.m.", "Mumbai", 0, "01hr45min", 5800, "A1", "Y5"});
    flightData[8]["VS-1900"].push_back({"Vistara", "VS-1900", "Delhi", "19:00p.m.", "Mumbai", 0, "02hr30min", 5875, "A1", "X6"});
    flightData[8]["IG-1000"].push_back({"Indigo", "IG-1000", "Delhi", "10:00a.m.", "Mumbai", 0, "02hr20min", 5550, "A1", "X4"});
    flightData[8]["IG-2100"].push_back({"Indigo", "IG-2100", "Delhi", "21:00p.m.", "Mumbai", 0, "02hr15min", 5560, "A1", "X5"});
    flightData[8]["IG-0100"].push_back({"Indigo", "IG-0100", "Delhi", "01:00a.m.", "Mumbai", 0, "02hr35min", 5675, "A1", "X6"});
    flightData[8]["AA-0930"].push_back({"AirAsia", "AA-0930", "Delhi", "09:30a.m.", "Mumbai", 0, "02hr14min", 5600, "A1", "Y4"});

    flightData[9]["SG-0400"].push_back({"SpiceJet", "SG-0400", "Delhi", "04:00a.m.", "Mumbai", 0, "02hr10min", 6953, "A1", "X4"});
    flightData[9]["SG-0900"].push_back({"SpiceJet", "SG-0900", "Delhi", "09:00a.m.", "Mumbai", 0, "02hr20min", 6955, "A1", "X5"});
    flightData[9]["SG-1400"].push_back({"SpiceJet", "SG-1400", "Delhi", "14:00p.m.", "Mumbai", 0, "02hr33min", 6960, "A1", "X6"});
    flightData[9]["SG-1800"].push_back({"SpiceJet", "SG-1800", "Delhi", "18:00p.m.", "Mumbai", 0, "02hr00min", 6000, "A1", "Y4"});
    flightData[9]["VS-1200"].push_back({"Vistara", "VS-1200", "Delhi", "12:00p.m.", "Mumbai", 0, "01hr45min", 6800, "A1", "Y5"});
    flightData[9]["VS-1900"].push_back({"Vistara", "VS-1900", "Delhi", "19:00p.m.", "Mumbai", 0, "02hr30min", 6875, "A1", "Y6"});
    flightData[9]["IG-1000"].push_back({"Indigo", "IG-1000", "Delhi", "10:00a.m.", "Mumbai", 0, "02hr20min", 6550, "A1", "X4"});
    flightData[9]["IG-2100"].push_back({"Indigo", "IG-2100", "Delhi", "21:00p.m.", "Mumbai", 0, "02hr15min", 6560, "A1", "X5"});
    flightData[9]["IG-0100"].push_back({"Indigo", "IG-0100", "Delhi", "01:00a.m.", "Mumbai", 0, "02hr35min", 6675, "A1", "X6"});
    flightData[9]["AA-0930"].push_back({"AirAsia", "AA-0930", "Delhi", "09:30a.m.", "Mumbai", 0, "02hr14min", 6600, "A1", "Y4"});
    return flightData;
}

map<int, map<string, vector<Flight>>> addnewFlight(map<int, map<string, vector<Flight>>> &flt1)
{
    std::cout << "YOU ARE ONLY ABLE TO ADD FLIGHTS FOR THE NEXT 10 DAYS" << endl;
    string flightDate;
    // YOU ARE ONLY ABLE TO ADD FLIGHTS FOR THE NEXT 10 DAYS
    std::cout << "Enter the date of flight in this format dd.mm.yy example 5.11.2023 or 10.11.2023" << endl;
    std::cin >> flightDate;
    int addFlightIndex = getIndices(flt1, flightDate);
    // INDEX NUMBER WILL BE TAKEN ITSELF I.E. ONE NEXT THAN THE FLIGHT ALREADY ADDED
    if (flt1.find(addFlightIndex) != flt1.end())
    {

        std::string airline;
        std::string flight;
        std::string source_city;
        std::string departure_time;
        std::string destination_city;
        int stops;
        std::string duration;
        double price;
        std::cout << "Enter the flight details" << endl;
        std::cout << "Enter airline name" << endl;
        std::cin >> airline;
        std::cout << "Enter flight number" << endl;
        std::cin >> flight;
        std::cout << "Enter source city" << endl;
        std::cin >> source_city;
        std::cout << "Enter departure time" << endl;
        std::cin >> departure_time;
        std::cout << "Enter destination city" << endl;
        std::cin >> destination_city;
        std::cout << "Enter number of stops in between destination and source city" << endl;
        std::cin >> stops;
        std::cout << "Enter amount of time required for the flight" << endl;
        std::cin >> duration;
        std::cout << "Enter the price of flight" << endl;
        std::cin >> price;
        string startNumber;
        std::cout << "Enter the starting seatNumber of flight" << endl;
        cin >> startNumber;
        string endNumber;
        std::cout << "Enter the ending seatNumber of flight" << endl;
        cin >> endNumber;

        flt1[addFlightIndex][flight].push_back({airline, flight, source_city, departure_time, destination_city, stops, duration, price, startNumber, endNumber});
    }
    return flt1;
}
map<int, map<string, vector<Flight>>>
deleteFlight(map<int, map<string, vector<Flight>>> &flightData, const string &flightNumber)
{
    for (int index = 0; index < flightData.size(); index++)
    {
        auto &innerMap = flightData[index];
        auto it2 = innerMap.find(flightNumber);
        if (it2 != innerMap.end())
        {
            auto &flightVector = it2->second;
            flightVector.clear();
            if (flightVector.empty())
            {
                innerMap.erase(flightNumber);
            }
            return flightData;
        }
    }
    std::cout << "Flight with flight number " << flightNumber << " not found." << std::endl;
    return flightData;
}
map<int, map<string, vector<Flight>>> editFlightInformation(map<int, map<string, vector<Flight>>> &flightData, int editFlightIndex, const string &airline, const string &newFlightNumber, const string &source_city, const string &departure_time, const string &destination_city, int stops, const string &duration, double price)
{
    if (flightData.find(editFlightIndex) != flightData.end())
    {
        for (auto &flight : flightData[editFlightIndex][newFlightNumber])
        {
            flight.airline = airline;
            flight.flight = newFlightNumber; // Use the provided new flight number
            flight.source_city = source_city;
            flight.departure_time = departure_time;
            flight.destination_city = destination_city;
            flight.stops = stops;
            flight.duration = duration;
            flight.price = price;
        }
    }
    return flightData;
}
int countLinesInFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return 0; // File not found
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(file, line))
    {
        lineCount++;
    }

    return lineCount;
}
void printAdmin()
{
    std::cout << "##########################" << endl;

    bool b = true;
    while (b)
    {
        std::cout << "If you want to add a new Flight press 1" << endl;
        cout << "If you want to edit the details of flight press 3" << endl;
        std::cout << "To view the number of remanining and reserved seats press 2" << endl;
        std::cout<<"To see the details of all the flight press 4"<<endl;
        std::cout << "To exit u can press 0" << endl;
        int input;
        std::cin >> input;

        if (input == 1)
        {
            finalflight = addnewFlight(finalflight);
            cout << "New flight has been added successfully.Here is ur new record" << endl;
            printFlightData(finalflight);
        }
        else if (input == 0)
        {
            break;
        }

        else if (input == 2)
        {
            string str1, str2;
            cout << "Enter the date of flight" << endl;
            cin >> str1;
            cout << "Enter the flight number" << endl;
            cin >> str2;
            string str3 = str1 + str2 + ".txt";
            int a = countLinesInFile(str3);
            cout << "The number of reserved seats are" << a << endl;
        }
        else if (input == 3)
        {
            cout << "Enter the date of flight u want to edit" << endl;
            string flightDate;
            cin >> flightDate;
            int editFlightIndex = getIndices(finalflight, flightDate);
            // INDEX NUMBER WILL BE TAKEN ITSELF I.E. ONE NEXT THAN THE FLIGHT ALREADY ADDED
            if (finalflight.find(editFlightIndex) != finalflight.end())
            {

                std::string airline;
                std::string flight;
                std::string source_city;
                std::string departure_time;
                std::string destination_city;
                int stops;
                std::string duration;
                double price;
                cout << "Enter the flight details" << endl;
                cout << "Enter airline name" << endl;
                cin >> airline;
                cout << "Enter flight number" << endl;
                cin >> flight;
                cout << "Enter source city" << endl;
                cin >> source_city;
                cout << "Enter departure time" << endl;
                cin >> departure_time;
                cout << "Enter destination city" << endl;
                cin >> destination_city;
                cout << "Enter number of stops in between destination and source city" << endl;
                cin >> stops;
                cout << "Enter amount of time required for the flight" << endl;
                cin >> duration;
                cout << "Enter the price of flight" << endl;
                cin >> price;

                finalflight = editFlightInformation(finalflight, editFlightIndex, airline, flight, source_city, departure_time, destination_city, stops, duration, price);
            }
        }
        else if(input==4)
        {
            printFlightData(finalflight);
        }
    }
}
bool isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return true; // It's a leap year
    }
    return false; // It's not a leap year
}

int getDaysInMonth(int year, int month)
{
    if (month < 1 || month > 12)
    {
        return -1;
    }

    int daysInMonth;

    switch (month)
    {
    case 2: // February
        daysInMonth = isLeapYear(year) ? 29 : 28;
        break;
    case 4:  // April
    case 6:  // June
    case 9:  // September
    case 11: // November
        daysInMonth = 30;
        break;
    default:
        daysInMonth = 31;
        break;
    }

    return daysInMonth;
}
void searchFLights2()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;
    int currentDate = ltm->tm_mday;
    int currentMonth = ltm->tm_mon;
    for (int i = 0; i < 10; i++)
    {
        if (currentDate + i <= getDaysInMonth(currentYear, currentMonth + 1) && (currentMonth + 1) != 12)
        {
            std::cout << currentDate + i << "." << currentMonth + 1 << "." << currentYear << " ";
        }
        else if (currentDate + i > getDaysInMonth(currentYear, currentMonth + 1) && (currentMonth + 1) != 12)
        {
            std::cout << currentDate + i << "." << currentMonth + 1 + 1 << "." << currentYear << " ";
        }
        else if (currentDate + i > getDaysInMonth(currentYear, currentMonth + 1) && (currentMonth + 1) == 12)
        {
            std::cout << currentDate + i << "." << currentMonth + 1 + 1 << "." << currentYear + 1 << " ";
        }
    }
    cout << endl;
}

vector<string> optionToSearch()
{
    string date;
    string sourceCity;
    string destinationCity;

    std::cout << "Enter date when you want to search flights" << endl;
    std::cout << "You can book a flight from today to the upcoming 10 days" << endl;
    std::cout << "Here is a list of days on which flight can be booked" << endl;
    searchFLights2();
    std::cin >> date;

    std::cout << "Enter source city" << endl;
    std::cin >> sourceCity;

    std::cout << "Enter destination city" << endl;
    std::cin >> destinationCity;

    vector<string> arr;
    arr.push_back(date);
    arr.push_back(sourceCity);
    arr.push_back(destinationCity);

    return arr;
}
bool compareFlightsByTime(const Flight &flight1, const Flight &flight2)
{
    return flight1.departure_time < flight2.departure_time;
}

bool compareFlightsByPrice(const Flight &flight1, const Flight &flight2)
{
    return flight1.price < flight2.price;
}

bool compareFlightsByStops(const Flight &flight1, const Flight &flight2)
{
    return flight1.stops < flight2.stops;
}
void displayFlights(map<int, map<string, vector<Flight>>> flightData, string date, string sourceCity, string destinationCity, string sortOption)
{
    int searchDate = getIndices(flightData, date);

    if (flightData.find(searchDate) != flightData.end())
    {
        map<string, vector<Flight>> &flightsOnDate = flightData[searchDate];

        std::cout << setw(12) << "Index Number" << setw(15) << "Flight Number" << setw(15) << "Airline" << setw(15) << "Source City"
                  << setw(15) << "Destination City" << setw(15) << "Departure Time" << setw(10) << "Stops"
                  << setw(15) << "Duration" << setw(10) << "Price" << setw(20) << "TIcket matrix" << endl;

        vector<Flight> selectedFlights;

        for (auto it = flightsOnDate.begin(); it != flightsOnDate.end(); ++it)
        {
            const string &flightNumber = it->first;
            const vector<Flight> &flights = it->second;

            for (const Flight &flight : flights)
            {
                if (flight.source_city == sourceCity && flight.destination_city == destinationCity)
                {
                    selectedFlights.push_back(flight);
                }
            }
        }

        if (sortOption == "time")
        {
            sort(selectedFlights.begin(), selectedFlights.end(), compareFlightsByTime);
        }
        else if (sortOption == "price")
        {
            sort(selectedFlights.begin(), selectedFlights.end(), compareFlightsByPrice);
        }
        else if (sortOption == "stops")
        {
            sort(selectedFlights.begin(), selectedFlights.end(), compareFlightsByStops);
        }
        int i = 1;

        for (const Flight &flight : selectedFlights)
        {
            std::cout << setw(12) << i << setw(15) << flight.flight << setw(15) << flight.airline << setw(15) << flight.source_city
                      << setw(15) << flight.destination_city << setw(15) << flight.departure_time << setw(10) << flight.stops
                      << setw(15) << flight.duration << setw(10) << flight.price << setw(15) << flight.startingSeatNumber + "-" + flight.endingSeatNumber << endl;
            i++;
        }
    }
    else
    {
        std::cout << "No flights found for the specified date." << endl;
    }
}

void firstFunction()
{
    vector<string> arr = optionToSearch();
    bool sorting = true;

    std::cout << "Enter sorting option (time, price, stops): ";
    string sortOption;
    std::cin >> sortOption;

    displayFlights(finalflight, arr[0], arr[1], arr[2], sortOption);
    int takeInput;
}
pair<string, string> giveInput()
{
    string str1;
    string str2;
    std::cout << "Enter date of flight booking" << endl;
    searchFLights2();
    std::cin >> str1;
    std::cout << "Enter flight number as displayed in searching scenario" << endl;
    std::cin >> str2;
    return make_pair(str1, str2);
}
void print(Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (!temp->taken)
        {
            std::cout << temp->seatNumber << " ";
        }
        else
        {
            std::cout << "tkn ";
        }

        if (temp->next != nullptr && temp->seatNumber[0] != temp->next->seatNumber[0])
        {
            std::cout << endl;
        }

        temp = temp->next;
    }
    std::cout << endl;
}
void insertAtHead(Node *&head, string seatNumber)
{
    if (head == NULL)
    {
        Node *temp = new Node(seatNumber);
        head = temp;
    }
    else
    {
        Node *temp = new Node(seatNumber);
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
}
void insertAtTail(Node *&head, Node *&tail, string seatNumber)
{
    if (head == NULL)
    {
        Node *temp = new Node(seatNumber);
        head = temp;
        tail = temp;
        temp->setTaken(false);
    }
    else
    {
        Node *temp = new Node(seatNumber);
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
        temp->setTaken(false);
    }
}
void setSeatsTaken(Node *head, const string &fileName)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "Entire flight empty" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        istringstream ss(line);
        string seatNumber;
        if (getline(ss, seatNumber, ','))
        {

            Node *current = head;
            while (current != nullptr)
            {
                if (current->seatNumber == seatNumber)
                {
                    current->setTaken(true);
                    break;
                }
                current = current->next;
            }
        }
    }

    file.close();
}
Node *findSeat(Node *head, const string &seatNumber)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (!temp->taken && temp->seatNumber == seatNumber)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr; // Seat not found or already taken
}
Node *findSeat2(Node *head, const string &seatNumber)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->seatNumber == seatNumber)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
void deleteSeat(Node *seatToDelete)
{
    if (seatToDelete)
    {
        seatToDelete->setFirstName("");
        seatToDelete->setLastName("");
        seatToDelete->setPhoneNumber(0);
        seatToDelete->setTaken(false);
        seatToDelete->setVegetarian(false);
        seatToDelete->setAge(0);
    }
}
void normalreserving()
{
    Node *head = nullptr;
    Node *tail = nullptr;
    pair<string, string> strings = giveInput();
    // strings.first being the date nd stringssecond being the flight number
    std::cout << "You have opted for flight" << strings.second << "on date being" << strings.first << endl;
    string flightNumber = strings.first;
    string airline = strings.second;

    int key = getIndices(finalflight, strings.first);
    std::cout << key << endl;
    string str1;
    string str2;
    for (const auto &indexEntry : finalflight)
    {
        int index_number = indexEntry.first;

        if (index_number == key)
        {
            const map<string, vector<Flight>> &flightMap = indexEntry.second;

            for (const auto &flightEntry : flightMap)
            {
                const string &flightKey = flightEntry.first;
                const vector<Flight> &flights = flightEntry.second;

                if (flightKey == airline)
                {
                    for (const Flight &flight : flights)
                    {
                        str1 = flight.startingSeatNumber;
                        str2 = flight.endingSeatNumber;
                    }
                }
            }
        }
    }
    // str1 is now the starting seat number
    // and str2 is the ending seat number
    char letter1 = str1[0];
    char letter2 = str2[0];
    int number1 = std::stoi(str1.substr(1));
    int number2 = std::stoi(str2.substr(1));

    for (char letter = letter1; letter <= letter2; letter++)
    {
        for (int number = number1; number <= number2; number++)
        {
            string k = letter + to_string(number);
            insertAtTail(head, tail, k);
        }
    }
    string fileName = flightNumber + airline + ".txt";
    setSeatsTaken(head, fileName);
    print(head);
    int numberofSeatstobook;
    cout << "How many seats do you want to book" << endl;
    cin >> numberofSeatstobook;
    Node *choosenSeat;
    for (int i = 1; i <= numberofSeatstobook; i++)
    {
        cout << " Choose the required seat number from this list for"
             << "seat number" << i << endl;
        cout << "Each seat at the corner of the row represents window seat" << endl;
        string chooseNumber;
        cin >> chooseNumber;
        choosenSeat = findSeat(head, chooseNumber);
        if (choosenSeat)
        {
            string name1 = strings.first;
            string name2 = strings.second;
            string conc = name1 + name2 + ".txt";
            ofstream file(conc, std::ios::app);
            cout << "This seat is available" << endl;
            cout << "You can enter your details to proceed" << endl;
            string firstName;
            string lastName;
            long long unsigned int phoneNumber;
            int age;
            bool menuPreference;
            cout << "Enter your first name" << endl;
            cin >> firstName;
            cout << "Enter your last name" << endl;
            cin >> lastName;
            cout << "Enter your phone number" << endl;
            cin >> phoneNumber;
            cout << "What's your age" << endl;
            cin >> age;

            // TO CHOOSE FOR VEGETARIAN AND NON-VEGETARIAN
            cout << "Choose menu preference" << endl;
            cout << "Press 1 for veg and 0 for non-veg" << endl;
            cin >> menuPreference;
            if (file.is_open())
            {
                file << chooseNumber << "," << firstName << "," << lastName << "," << phoneNumber << "," << age << "," << menuPreference << endl;
                file.close();
            }
            choosenSeat->setFirstName(firstName);
            choosenSeat->setLastName(lastName);
            choosenSeat->setPhoneNumber(phoneNumber);
            choosenSeat->setTaken(true);
            choosenSeat->setVegetarian(menuPreference);
            choosenSeat->setAge(age);
        }
        else
        {
            i = i - 1;
            // I-1 SINCE AGAR USKO SEAT NHI MILI HE WILL GO FOR ANOTHER ONE
            cout << "sorry seat not found or is already taken" << endl;
        }
    }
    print(head);
    string seatNumber;
    // cout<<"Enter the seat number whose details you want to edit"<<endl;
    // cin>>seatNumber;
    // Node *seatToEdit=findSeat2(head,seatNumber);
    // if(seatToEdit)
    // {
    //     if(seatToEdit->taken)
    //     {
    //         vector<string>arr1={"first name","last name","phone number","age","vegeterian"};
    //         vector<string>arr2={seatToEdit->firstName,seatToEdit->lastName,to_string(seatToEdit->phoneNumber),to_string(seatToEdit->age),to_string(seatToEdit->vegetarian)};
    //         int count=0;
    //         for(string i:arr1)
    //         {
    //             cout<<"Your "<<arr1[count]<<" "<<arr2[count]<<endl;
    //             int pressed;
    //             cout<<"To change "<<arr1[count]<<" press 1"<<endl;
    //             cout<<"else press 0"<<endl;
    //             cin>>pressed;
    //             if(pressed==1)
    //             {
    //                 string news;
    //                 cout<<"Enter new"<<arr1[count]<<endl;
    //                 cin>>news;
    //                 arr2[count]=news;
    //                 count++;

    //             }
    //             else if(pressed==0)
    //             {
    //                 count++;
    //             }

    //         }
    //         for(string i:arr2)
    //         {
    //             cout<<i<<endl;
    //         }
    //         // Node *newSeat=findSeat(head,seatToEdit->seatNumber);
    //         seatToEdit->setFirstName(arr2[0]);
    //         seatToEdit->setLastName(arr2[1]);
    //         seatToEdit->setPhoneNumber(stoi(arr2[2]));
    //         seatToEdit->setAge(stoi(arr2[3]));
    //         seatToEdit->setTaken(true);
    //         seatToEdit->setVegetarian(stoi(arr2[5]));

    //     }
    // }
    int numberTODelete;
    string date;
    cout << "How many seats do you want to delete" << endl;
    cin >> numberTODelete;
    for (int i = 1; i <= numberTODelete; i++)
    {
        cout << "Enter the seat number you want to delete" << endl;
        string seatToDeleteNumber;
        cin >> seatToDeleteNumber;
        Node *seatToDelete = findSeat2(head, seatToDeleteNumber);
        if (seatToDelete)
        {
            if (seatToDelete->taken)
            {
                
                deleteSeat(seatToDelete);
                cout << "Seat has been successffuly deleted" << endl;
            }
            else
            {
                cout << "Seat is not occupied and cannot be deleted" << endl;
                cout << "Please input ur seat only" << endl;
                i = i - 1;
            }
        }
        else
        {
            cout << "Seat" << seatToDeleteNumber << "not found.Please try again" << endl;
            i = i - 1;
        }
    }
    print(head);
    int press;
    cout << "Press 1 to print the reservation report" << endl;
    cin >> press;
    cout << setw(10) << "FirstName" << setw(10) << "Last Name" << setw(10) << "\t"
         << "Phone Number" << setw(10) << "age" << setw(10) << endl;
    cout << choosenSeat->firstName << "\t" << choosenSeat->lastName << "\t" << choosenSeat->phoneNumber << "\t" << choosenSeat->age << endl;
}
void printuser()
{
    bool stillInput = true;
    int takeInput;
    while (stillInput)
    {
        std::cout << "    Search Available Flights ------[1]" << endl;
        std::cout << "      Manage your reservation-make,cancel or edit or print it--[2]" << endl;
        // std::cout << "      Make multiple reservation at the same time---[5]";
        // std::cout << "    Print status report -only for those who are waitlisted inside the queue---[3]" << endl;
        std::cout << "    Check number of available and reserved seats---[4]" << endl;
        std::cout << "    Quit -----[0]" << endl;
        std::cin >> takeInput;
        if (takeInput == 1)
        {
            firstFunction();
        }
        else if (takeInput == 2)
        {
            // proceeding with the  reservation centric files over here
            normalreserving();
        }
        else if (takeInput == 0)
        {
            break;
        }
        else if (takeInput == 4)
        {
            string str1, str2;
            cout << "Enter flight date" << endl;
            cin >> str1;
            cout << "Enter flight code" << endl;
            cin >> str2;
            string str3 = str1 + str2 + ".txt";
            cout << "The number of reserved seats are" << countLinesInFile(str3);
        }
    }
}
bool validate_login(const std::string &username, const std::string &password)
{
    ifstream MyExcelFile("D:\\datasets\\Book1.csv");
    string line;
    while (getline(MyExcelFile, line))
    {
        size_t pos = line.find(",");
        if (pos != string::npos)
        {
            string uname = line.substr(0, pos);
            string upwd = line.substr(pos + 1);
            if (uname == username && upwd == password)
            {
                MyExcelFile.close();
                return true;
                // yaani matching user mil gaya hai hmein aab
            }
        }
    }
    MyExcelFile.close();
    return false;
}
void proceedToLogin()
{
    string username, password;
    std::cout << "Enter username" << endl;
    std::cin >> username;
    std::cout << "Enter password" << endl;
    std::cin >> password;
    bool validated = true;
    while (validated == true)
    {
        if (validate_login(username, password))
        {
            std::cout << "You have successfully logged into the system" << endl;
            printuser();
            validated = false;
        }
        else
        {
            std::cout << "Please check your log-in details";
            std::cout << "Enter username" << endl;
            std::cin >> username;
            std::cout << "Enter password" << endl;
            std::cin >> password;
        }
    }
}
void login_system()
{
    int userExist;
    std::cout << "   ARE YOU AN EXISTING USER----[1]" << endl;
    std::cout << "   ARE YOU A NEW USER-----[2]" << endl;
    std::cin >> userExist;
    if (userExist == 1)
    {
        proceedToLogin();
    }
    if (userExist == 2)
    {
        ofstream MyExcelFile;
        // ::ios::app ka mtlb opened for appending or i can say the file has been opened for writing into it
        MyExcelFile.open("D:\\datasets\\Book1.csv", std::ios::app);
        string username, password;
        std::cout << "Enter your username" << endl;
        std::cin >> username;
        std::cout << "Enter your password" << endl;
        std::cin >> password;
        if (MyExcelFile.is_open())
        {
            MyExcelFile << username << "," << password << std::endl;
            std::cout << "Your Login Credentials have been created successfully" << endl;
            std::cout << "You can now proceed to your login page" << endl;
            int wantToLOgin;
            std::cout << "FOr proceeding to login, press 1" << endl;
            std::cin >> wantToLOgin;
            if (wantToLOgin == 1)
            {
                proceedToLogin();
            }
            MyExcelFile.close(); // Close the file
        }
        else
        {
            // cerr means the standard error . Can use cout too here but cerr is good

            std::cerr << "Unable to open the file for writing." << std::endl;
        }
    }
}

void printbasics()
{
    std::cout << "###########################################" << endl;
    std::cout << "Welcome to Airline Reservation System Sir" << endl;
    std::cout << "###########################################" << endl;

    bool a = true;
    while (a)
    {
        std::cout << "Press 1 if you are an admin else press 2 if you are a user" << endl;
        std::cout << "Press 0 to quit" << endl;
        int userPressed;
        std::cin >> userPressed;
        if (userPressed == 1)
        {
            string username;
            string password;
            std::cout << "Enter your username" << endl;
            std::cin >> username;
            std::cout << "ENter your password" << endl;
            std::cin >> password;
            if (username == "username" && password == "password")
            {
                std::cout << "You are an admin. Procceed to admin files here" << endl;
                printAdmin();
            }
            else
            {
                std::cout << "Please enter valid entries" << endl;
            }
        }
        else if (userPressed == 2)
        {
            std::cout << "You are a user. Proceed to user files" << endl;
            login_system();
        }
        else if (userPressed == 0)
        {
            break;
        }
    }
}

int main()
{
    finalflight = alreadyAddedFlights();
    printbasics();
    return 0;
}
