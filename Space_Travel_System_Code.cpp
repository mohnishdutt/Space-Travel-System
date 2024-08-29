#include <bits/stdc++.h>
using namespace std;
set<int> Id;
set<int> License_Id;

class Planet
{
public:
    static map<string, Planet> Planet_List;
    double Position_X;
    double Position_Y;
    double Position_Z;
    string Name;
    Planet(double X, double Y, double Z, string name)
    {
        Position_X = X;
        Position_Y = Y;
        Position_Z = Z;
        Name = name;
        Planet_List.insert(pair<string, Planet>(Name, *this));
    }
    void Update_X(int X)
    {
        Position_X = X;
    }
    void Update_Y(int Y)
    {
        Position_Y = Y;
    }
    void Update_Z(int Z)
    {
        Position_Z = Z;
    }
    void Update_Name(int name)
    {
        Name = name;
    }
    double GetPosition_X(void)
    {
        return Position_X;
    }
    double GetPosition_Y(void)
    {
        return Position_Y;
    }
    double GetPosition_Z(void)
    {
        return Position_Z;
    }
    string GetName(void)
    {
        return Name;
    }
    void GetPosition(void)
    {
        cout << "X : " << GetPosition_X() << ", Y : " << GetPosition_Y() << ", Z : " << GetPosition_Z() << "\n";
    }
};
map<string, Planet> Planet::Planet_List;

double GetDistance(string a, string b)
{
    auto P1 = Planet::Planet_List.find(a);
    auto P2 = Planet::Planet_List.find(b);
    Planet A = P1->second;
    Planet B = P2->second;
    double square = (A.GetPosition_X() - B.GetPosition_X()) * (A.GetPosition_X() - B.GetPosition_X()) + (A.GetPosition_Y() - B.GetPosition_Y()) * (A.GetPosition_Y() - B.GetPosition_Y()) + (A.GetPosition_Z() - B.GetPosition_Z()) * (A.GetPosition_Z() - B.GetPosition_Z());
    return sqrt(square);
}
void deleteCommanderAstronaut(int a, int b, tm date);
class SpaceTravel
{
public:
    static int ID;
    static map<int, SpaceTravel> SpaceTravel_List;
    int SpaceTravel_ID;
    int Astronaut;
    int Commander;
    vector<int> passenger;
    string Source;
    string Destination;
    tm Travel_Date;
    SpaceTravel(string source, string destination, tm travel_Date, int astronaut, int commander)
    {
        SpaceTravel_ID = ++ID;
        Source = source;
        Destination = destination;
        Travel_Date = travel_Date;
        Astronaut = astronaut;
        Commander = commander;
    }
    void Add_passenger(int id)
    {
        passenger.push_back(id);
        SpaceTravel_List.erase(SpaceTravel_ID);
        SpaceTravel_List.insert(make_pair(SpaceTravel_ID, *this));
    }
    void DeletePassenger(int id)
    {
        if (passenger.size() > 2)
        {
            auto it = std::find(passenger.begin(), passenger.end(), id);
            passenger.erase(it);
            SpaceTravel_List.erase(SpaceTravel_ID);
            SpaceTravel_List.insert(make_pair(SpaceTravel_ID, *this));
        }
        else
        {
            deleteCommanderAstronaut(Commander, Astronaut, Travel_Date);
            SpaceTravel_List.erase(SpaceTravel_ID);
        }
    }
};
int SpaceTravel ::ID = 0;
map<int, SpaceTravel> SpaceTravel::SpaceTravel_List;

bool isSameDate(const tm &date1, const tm &date2)
{
    return (date1.tm_year == date2.tm_year) && (date1.tm_mon == date2.tm_mon) && (date1.tm_mday == date2.tm_mday);
}
int getAstronaut(tm date);
int getCommander(tm date);
class Ticket
{
public:
    static int ID;
    static map<int, Ticket> Ticket_List;
    int Ticket_ID;
    int Passenger_ID;
    int Travel_ID;
    string Source;
    string Destination;
    double Cost;
    tm Booking_Time;
    tm Travel_Date;
    tm Valid_Upto;
    string Status;
    Ticket(int passenger_ID, string source, string destination, tm booking_Time, tm travel_Date)
    {
        Ticket_ID = ++ID;
        Passenger_ID = passenger_ID;
        Source = source;
        Destination = destination;
        Booking_Time = booking_Time;
        Travel_Date = travel_Date;
        Status = "Pending";
        Cost = 1000 * GetDistance(source, destination) / (difftime(mktime(&travel_Date), mktime(&booking_Time)) / (60 * 60 * 24) + 1);
        booking_Time.tm_year = booking_Time.tm_year + 100;
        Valid_Upto = booking_Time;
        Ticket_List.insert(make_pair(Ticket_ID, *this));
    }
    void Print_Ticket()
    {
        cout << "\n======================================" << endl;
        cout << "               InterPlanet            " << endl;
        cout << "           Ticket Confirmation        " << endl;
        cout << "======================================" << endl;
        cout << "  Ticket ID     : " << Ticket_ID << endl;
        cout << "  Passenger ID  : " << Passenger_ID << endl;
        cout << "  Source        : " << Source << endl;
        cout << "  Destination   : " << Destination << endl;
        cout << "  Booking Time  : " << Booking_Time.tm_mday << "/" << Booking_Time.tm_mon + 1 << "/" << Booking_Time.tm_year + 1900 << endl;
        cout << "  Travel Date   : " << Travel_Date.tm_mday << "/" << Travel_Date.tm_mon + 1 << "/" << Travel_Date.tm_year + 1900 << endl;
        cout << "  Valid Upto    : " << Valid_Upto.tm_mday << "/" << Valid_Upto.tm_mon + 1 << "/" << Valid_Upto.tm_year + 1900 << endl;
        cout << "  Cost          : $" << fixed << setprecision(2) << Cost << endl;
        cout << "  Travel Status : " << Status << endl;
        cout << "======================================" << endl;
    }
    void delete_ticket()
    {
        Ticket_List.erase(Ticket_ID);
    }
    void update_travel()
    {
        for (auto it1 = Ticket_List.begin(); it1 != Ticket_List.end(); ++it1)
        {
            for (auto it2 = next(it1); it2 != Ticket_List.end(); ++it2)
            {
                string check = "Confirmed";
                if ((isSameDate(it1->second.Travel_Date, it2->second.Travel_Date)) && (it1->second.Source == it2->second.Source) && (it1->second.Destination == it2->second.Destination))
                {
                    if ((it1->second.Status != check) && (it2->second.Status != check))
                    {
                        if (getAstronaut(it1->second.Travel_Date) && getCommander(it1->second.Travel_Date))
                        {
                            SpaceTravel s(it1->second.Source, it1->second.Destination, it1->second.Travel_Date, getAstronaut(it1->second.Travel_Date), getCommander(it1->second.Travel_Date));
                            s.Add_passenger(it1->second.Passenger_ID);
                            s.Add_passenger(it2->second.Passenger_ID);
                            it1->second.Update_status(check);
                            it2->second.Update_status(check);
                            it1->second.Update_TravelID(s.SpaceTravel_ID);
                            it2->second.Update_TravelID(s.SpaceTravel_ID);
                        }
                    }
                    else if ((it1->second.Status == check) && (it2->second.Status != check))
                    {
                        SpaceTravel s = SpaceTravel::SpaceTravel_List.find(it1->second.Travel_ID)->second;
                        if (s.passenger.size() < 10)
                        {
                            s.Add_passenger(it2->second.Passenger_ID);
                            it2->second.Update_status(check);
                            it2->second.Update_TravelID(s.SpaceTravel_ID);
                        }
                    }
                    else if ((it1->second.Status != check) && (it2->second.Status == check))
                    {
                        SpaceTravel s = SpaceTravel::SpaceTravel_List.find(it2->second.Travel_ID)->second;
                        if (s.passenger.size() < 10)
                        {
                            s.Add_passenger(it1->second.Passenger_ID);
                            it1->second.Update_status(check);
                            it1->second.Update_TravelID(s.SpaceTravel_ID);
                        }
                    }
                }
            }
        }
    }
    void Update_time(tm date)
    {
        Travel_Date = date;
        Cost = 1000 * GetDistance(Source, Destination) / (difftime(mktime(&Travel_Date), mktime(&Booking_Time)) / (60 * 60 * 24) + 1);
        if (Status == "Confirmed")
        {
            SpaceTravel::SpaceTravel_List.find(Travel_ID)->second.DeletePassenger(Passenger_ID);
        }
        Status = "Pending";
        Ticket_List.erase(Ticket_ID);
        Ticket_List.insert(make_pair(Ticket_ID, *this));
    }
    void Update_status(string status)
    {
        Status = status;
        Ticket_List.erase(Ticket_ID);
        Ticket_List.insert(make_pair(Ticket_ID, *this));
    }
    void Update_TravelID(int x)
    {
        Travel_ID = x;
        Ticket_List.erase(Ticket_ID);
        Ticket_List.insert(make_pair(Ticket_ID, *this));
    }
    void Update_source(string source)
    {
        Source = source;
        Cost = 1000 * GetDistance(Source, Destination) / (difftime(mktime(&Travel_Date), mktime(&Booking_Time)) / (60 * 60 * 24) + 1);
        if (Status == "Confirmed")
        {
            SpaceTravel::SpaceTravel_List.find(Travel_ID)->second.DeletePassenger(Passenger_ID);
        }
        Status = "Pending";
        Ticket_List.erase(Ticket_ID);
        Ticket_List.insert(make_pair(Ticket_ID, *this));
    }
    void Update_destination(string destination)
    {
        Destination = destination;
        Cost = 1000 * GetDistance(Source, Destination) / (difftime(mktime(&Travel_Date), mktime(&Booking_Time)) / (60 * 60 * 24) + 1);
        if (Status == "Confirmed")
        {
            SpaceTravel::SpaceTravel_List.find(Travel_ID)->second.DeletePassenger(Passenger_ID);
        }
        Status = "Pending";
        Ticket_List.erase(Ticket_ID);
        Ticket_List.insert(make_pair(Ticket_ID, *this));
    }
};
map<int, Ticket> Ticket::Ticket_List;
int Ticket::ID = 0;
class Traveller
{
public:
    string Name;
    int ID;
    string GetName(void)
    {
        return Name;
    }
    int GetID(void)
    {
        return ID;
    }
    int VerifyID(int id)
    {
        if (Id.find(id) != Id.end())
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void UpdateName(string name)
    {
        Name = name;
    }
    void UpdateID(int id)
    {
        if (!VerifyID(id))
        {
            Id.erase(ID);
            ID = id;
            Id.insert(id);
        }
        else
        {
            cout << "\nID is Already Existing\n"
                 << endl;
        }
    }
};
class Passenger : public Traveller
{
public:
    static map<int, Passenger> Passenger_List;
    vector<int> List_of_tickets;
    void List_tickets()
    {
        if (List_of_tickets.size() == 0)
            cout << "\nYou do not have Upcoming Journeys\n\n";
        for (auto x : List_of_tickets)
        {
            Ticket T = Ticket::Ticket_List.find(x)->second;
            cout << x << " " << T.Source << " to " << T.Destination << " on " << T.Travel_Date.tm_mday << "/" << T.Travel_Date.tm_mon + 1 << "/" << T.Travel_Date.tm_year + 1900 << endl;
        }
    }
    void Get_ticket(int x)
    {
        Ticket::Ticket_List.find(x)->second.Print_Ticket();
    }
    Passenger(string name, int id)
    {
        Name = name;
        ID = id;
        Id.insert(id);
        Passenger_List.insert(make_pair(ID, *this));
    }
};

class Astronaut : public Traveller
{
public:
    static map<int, Astronaut> Astronaut_List;
    vector<tm> Working_dates;
    int License_ID;
    int Experience;
    Astronaut(string name, int id, int license_id, int experience)
    {
        Name = name;
        ID = id;
        License_ID = license_id;
        Experience = experience;
        Id.insert(id);
        Astronaut_List.insert(make_pair(ID, *this));
    }
    void show_Working_dates()
    {
        if (Working_dates.size() == 0)
            cout << "\nNo Working Days\n\n";
        for (auto it1 = Working_dates.begin(); it1 != Working_dates.end(); )
        {
            cout << "Working Day  : " << it1->tm_mday << "/" << it1->tm_mon + 1 << "/" << it1->tm_year + 1900 << endl;
            it1++;
        }
    }
    void Update_LicenceID(int x)
    {
        License_ID = x;
        Astronaut_List.erase(ID);
        Astronaut_List.insert(make_pair(ID, *this));
    }
    void add_working_day(tm date)
    {
        Working_dates.push_back(date);
        Astronaut_List.erase(ID);
        Astronaut_List.insert(make_pair(ID, *this));
    }
    void delete_working_day(tm date)
    {
        for (auto it = Working_dates.begin(); it != Working_dates.end();)
        {
            if (isSameDate(*it, date))
            {
                it = Working_dates.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
};

class Commander : public Traveller
{

public:
    vector<tm> Working_dates;
    static map<int, Commander> Commander_List;
    int License_ID;
    int Experience;
    Commander(string name, int id, int license_id, int experience)
    {
        Name = name;
        ID = id;
        License_ID = license_id;
        Experience = experience;
        Id.insert(id);
        Commander_List.insert(make_pair(ID, *this));
    }
    void show_Working_dates()
    {
        if (Working_dates.size() == 0)
            cout << "\nNo Working Days\n\n";
        for (auto it1 = Working_dates.begin(); it1 != Working_dates.end(); )
        {
            cout << "Working Day  : " << it1->tm_mday << "/" << it1->tm_mon + 1 << "/" << it1->tm_year + 1900 << endl;
            it1++;
        }
    }
    void Update_LicenceID(int x)
    {
        License_ID = x;
        Commander_List.erase(ID);
        Commander_List.insert(make_pair(ID, *this));
    }
    void List_travels()
    {
        if (SpaceTravel::SpaceTravel_List.size() == 0)
            cout << "\nThere are no Upcoming Journeys\n\n";
        for (auto x : SpaceTravel::SpaceTravel_List)
        {
            SpaceTravel T = x.second;
            cout << T.Source << " to " << T.Destination << " on " << T.Travel_Date.tm_mday << "/" << T.Travel_Date.tm_mon + 1 << "/" << T.Travel_Date.tm_year + 1900 << endl;
        }
    }
    void List_authorities(){
    for (auto it = Astronaut::Astronaut_List.begin(); it != Astronaut::Astronaut_List.end();){
        cout <<it->second.ID <<" ";
        it->second.show_Working_dates();
        ++it;
    }for (auto it = Commander::Commander_List.begin(); it != Commander::Commander_List.end();){
        cout <<it->second.ID <<" ";
        it->second.show_Working_dates();
        ++it;
    }
    }
    void add_working_day(tm date)
    {
        Working_dates.push_back(date);
        Commander_List.erase(ID);
        Commander_List.insert(make_pair(ID, *this));
    }
    void delete_working_day(tm date)
    {
        for (auto it = Working_dates.begin(); it != Working_dates.end();)
        {
            if (isSameDate(*it, date))
            {
                it = Working_dates.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
};
map<int, Passenger> Passenger::Passenger_List;
map<int, Astronaut> Astronaut::Astronaut_List;
map<int, Commander> Commander ::Commander_List;
int getAstronaut(tm date)
{
    for (auto x = Astronaut::Astronaut_List.begin() ; x!=Astronaut::Astronaut_List.end();)
    {
        int k = 1;
        for (int i = 0; i < x->second.Working_dates.size(); i++)
        {
            if (isSameDate(x->second.Working_dates[i], date))
                k = 0;
        }
        if (k)
        {
            x->second.add_working_day(date);
            return x->second.ID;
        }else x++;
    }
    return 0;
}
int getCommander(tm date)
{
    for (auto x = Commander::Commander_List.begin() ; x!=Commander::Commander_List.end();)
    {
        int k = 1;
        for (int i = 0; i < x->second.Working_dates.size(); i++)
        {
            if (isSameDate(x->second.Working_dates[i], date))
                k = 0;
        }
        if (k)
        {
            x->second.add_working_day(date);
            return x->second.ID;
        }else x++;
    }
    return 0;
}
void deleteCommanderAstronaut(int a, int b, tm date)
{
    Astronaut::Astronaut_List.find(b)->second.delete_working_day(date);
    Commander::Commander_List.find(b)->second.delete_working_day(date);
}
int main()
{
    Planet Earth(0, 0, 0, "Earth");
    Planet Moon(1.5, 2.0, 1.3, "Moon");
    Planet Mars(3.5, 2.75, 3, "Mars");
    Passenger P1("P1", 1);
    Passenger P2("P2", 2);
    Passenger P3("P3", 3);
    Passenger P4("P4", 4);
    Passenger P5("P5", 5);
    Passenger P6("P6", 6);
    Passenger P7("P7", 7);
    Passenger P8("P8", 8);
    Passenger P9("P9", 9);
    Passenger P10("P10", 10);
    Passenger P11("P11", 11);
    Astronaut A1("A1", 12, 42345, 8);
    Astronaut A2("A2", 13, 56789, 4);
    Commander C1("C1", 14, 12345, 18);
    Commander C2("C2", 15, 16789, 14);
    string S;
    string exit = "exit()";
    string help = "help()";
    string Plogin = "Passenger.login()";
    string Alogin = "Astronaut.login()";
    string Clogin = "Commander.login()";
    string logout = "logout()";
    cout << "\nWelcome to the InterPlanet System! \n\nFor User manual please type help().\n\n";
    while (S != exit)
    {
        cin >> S;
        if (S == help)
        {
            cout << "\nYou can login as a Passenger or Astronaut or Commander by the following commands. \n 1.Passenger.login() \n 2.Astronaut.login() \n 3.Commander.login() \nYou should enter your name and ID to login to your Account. \n \nPlease note that the program terminates only on Ctrl + C or exit() when logged out. \n\nTo logout please enter logout().\nTo exit the program please enter exit().\n\n";
        }
        else if (S == Plogin)
        {
            string name;
            int id;
            cout << "\nPlease Enter Your  Name : ";
            cin >> name;
            cout << "Please Enter Your ID : ";
            cin >> id;
            if (Passenger::Passenger_List.find(id) != Passenger::Passenger_List.end() && Passenger::Passenger_List.find(id)->second.GetName() == name)
            {
                Passenger P = Passenger::Passenger_List.find(id)->second;
                cout << "\nWelcome Passenger " << name << "! \n\nYou can do the following tasks \n A) Book a Ticket \n B) See all your booked tickets \n C) Print a ticket \n D) Update a ticket \n E) Cancel a ticket \n\nYou can use logout() here any time \n \nPlease Select Your Choice : ";
                cin >> S;
                while (S != logout)
                {
                    int ret = 0;
                    if (S == "A")
                    {
                        cout << "\nCurrently we are operating between these Planets -";
                        for (auto pair : Planet::Planet_List)
                        {
                            cout << pair.first << " ";
                        }
                        cout << ".\n\n";
                        string source, destination, day;
                        tm date = {};
                        cout << "Please Select Your Source : ";
                        cin >> source;
                        cout << "Please Select Your Destination : ";
                        cin >> destination;
                        cout << "Please Select Your Travel Date in DD-MM-YYYY format : ";
                        cin >> day;
                        auto now = chrono::system_clock::now();
                        time_t time_now = chrono::system_clock::to_time_t(now);
                        tm *ptm = localtime(&time_now);
                        ptm->tm_hour = 0;
                        ptm->tm_min = 0;
                        ptm->tm_sec = 0;
                        if (source == destination || Planet::Planet_List.find(source) == Planet::Planet_List.end() || Planet::Planet_List.find(destination) == Planet::Planet_List.end() || strptime(day.c_str(), "%d-%m-%Y", &date) == nullptr || (difftime(mktime(&date), mktime(ptm)) < 0))
                        {
                            cout << "\nInvalid Credentials\n\n";
                        }
                        else
                        {
                            Ticket T(id, source, destination, *ptm, date);
                            cout << "\nThe cost of the ticket is " << fixed << setprecision(2) << T.Cost << " \nDo you want to continue to Book (Yes/No) ? ";
                            string confirm;
                            cin >> confirm;
                            if (confirm == "Yes")
                            {
                                P.List_of_tickets.push_back(T.Ticket_ID);
                                T.update_travel();
                                cout << "\nYour ticket is booked . You can see the ticket in your tickets now. Do you want to continue to book return ticket (Yes/No) ? ";
                                cin >> confirm;
                                if (confirm == "Yes")
                                {
                                    ret = 1;
                                }
                            }
                            else
                                T.delete_ticket();
                        }
                    }
                    else if (S == "B")
                    {
                        P.List_tickets();
                    }
                    else if (S == "C")
                    {
                        int x;
                        cout << "Enter the ticket ID :";
                        cin >> x;
                        P.Get_ticket(x);
                    }
                    else if (S == "D")
                    {
                        int x;
                        cout << "Enter the ticket ID :";
                        cin >> x;
                        if (Ticket::Ticket_List.find(x) != Ticket::Ticket_List.end())
                        {
                            cout << "\nA) Change Travel_Date \nB) Change Destination \nC) Change Source \n\n";
                            string choice;
                            cout << "Please Select Your Choice : ";
                            cin >> choice;
                            Ticket T = Ticket::Ticket_List.find(x)->second;
                            if (choice == "A")
                            {
                                string day;
                                tm date = {};
                                auto now = chrono::system_clock::now();
                                time_t time_now = chrono::system_clock::to_time_t(now);
                                tm *ptm = localtime(&time_now);
                                ptm->tm_hour = 0;
                                ptm->tm_min = 0;
                                ptm->tm_sec = 0;
                                cout << "Please Select Your Travel Date in DD-MM-YYYY format : ";
                                cin >> day;
                                if (strptime(day.c_str(), "%d-%m-%Y", &date) == nullptr || (difftime(mktime(&date), mktime(ptm)) < 0))
                                {
                                    cout << "\nInvalid Credentials\n\n";
                                }
                                else
                                {
                                    double p = T.Cost;
                                    T.Update_time(date);
                                    T.update_travel();
                                    double q = T.Cost;
                                    cout << "\nSuccesfully updated Travel Date. Your Balance was changed by $" << fixed << setprecision(2) << p - q << " \n\n";
                                }
                            }
                            else if (choice == "B")
                            {
                                string destination;
                                cout << "Please Select Your Destination : ";
                                cin >> destination;
                                if (T.Source == destination || Planet::Planet_List.find(destination) == Planet::Planet_List.end())
                                {
                                    cout << "\nInvalid Credentials\n\n";
                                }
                                else
                                {
                                    double p = T.Cost;
                                    T.Update_destination(destination);
                                    T.update_travel();
                                    double q = T.Cost;
                                    cout << "\nSuccesfully updated Destination. Your Balance was changed by $" << fixed << setprecision(2) << p - q << " \n\n";
                                }
                            }
                            else if (choice == "C")
                            {
                                string source;
                                cout << "Please Select Your Source : ";
                                cin >> source;
                                if (source == T.Destination || Planet::Planet_List.find(source) == Planet::Planet_List.end())
                                {
                                    cout << "\nInvalid Credentials\n\n";
                                }
                                else
                                {
                                    double p = T.Cost;
                                    T.Update_source(source);
                                    T.update_travel();
                                    double q = T.Cost;
                                    cout << "\nSuccesfully updated Source. Your Balance was changed by $" << fixed << setprecision(2) << p - q << " \n\n";
                                }
                            }
                        }
                    }
                    else if (S == "E")
                    {
                        int x;
                        cout << "Enter the ticket ID :";
                        cin >> x;
                        Ticket::Ticket_List.find(x)->second.delete_ticket();
                        cout << "\nYour Ticket is Successfully Cancelled!\n\n";
                    }
                    if (!ret)
                    {
                        cout << "Please Select Your Choice : ";
                        cin >> S;
                    }
                }
            }
            else
            {
                cout << "\nInvalid Credentials \nYou are taken to main Page \nPlease login again\n\n";
                S = logout;
            }
        }
        else if (S == Alogin)
        {
            string name;
            int id;
            cout << "\nPlease Enter Your  Name : ";
            cin >> name;
            cout << "Please Enter Your ID : ";
            cin >> id;
            if (Astronaut::Astronaut_List.find(id) != Astronaut::Astronaut_List.end() && Astronaut::Astronaut_List.find(id)->second.GetName() == name)
            {
                Astronaut A = Astronaut::Astronaut_List.find(id)->second;
                cout << "\nWelcome Astronaut " << name << "! \n\nYou can do the following tasks \n A) See your Working days \n B) Update your License_ID \n\nYou can use logout() here any time \n \nPlease Select Your Choice : ";
                cin >> S;
                while (S != logout)
                {
                    if (S == "A")
                    {
                        A.show_Working_dates();
                    }
                    else if (S == "B")
                    {
                        int x;
                        cout << "Enter License ID :";
                        cin >> x;
                        if (License_Id.find(x) == License_Id.end())
                        {
                            License_Id.erase(A.License_ID);
                            A.Update_LicenceID(x);
                            License_Id.insert(A.License_ID);
                            cout << "\nUpdated Sucessfully\n\n";
                        }
                        else
                        {
                            cout << "\nInvalid License_ID\n\n";
                        }
                    }
                    cout << "Please Select Your Choice : ";
                    cin >> S;
                }
            }
            else
            {
                cout << "\nInvalid Credentials \nYou are taken to main Page \nPlease login again\n\n";
                S = logout;
            }
        }
        else if (S == Clogin)
        {

            string name;
            int id;
            cout << "\nPlease Enter Your  Name : ";
            cin >> name;
            cout << "Please Enter Your ID : ";
            cin >> id;
            if (Commander::Commander_List.find(id) != Commander::Commander_List.end() && Commander::Commander_List.find(id)->second.GetName() == name)
            {
                Commander c = Commander::Commander_List.find(id)->second;
                cout << "\nWelcome Commander " << name << "! \n\nYou can do the following tasks \n A) See your Working days \n B) See all the Travels \n C)See all the working days of authorities\n D) Update your License_ID \n\nYou can use logout() here any time \n \nPlease Select Your Choice : ";
                cin >> S;
                while (S != logout)
                {
                    if (S == "A")
                    {
                        c.show_Working_dates();
                    }
                    else if (S == "B")
                    {
                        c.List_travels();
                    }
                    else if(S=="C"){
                        c.List_authorities();
                    }
                    else if (S == "D")
                    {
                        int x;
                        cout << "Enter License ID :";
                        cin >> x;
                        if (License_Id.find(x) == License_Id.end())
                        {
                            License_Id.erase(c.License_ID);
                            c.Update_LicenceID(x);
                            License_Id.insert(c.License_ID);
                            cout << "\nUpdated Sucessfully\n\n";
                        }
                        else
                        {
                            cout << "\nInvalid License_ID\n\n";
                        }
                    }
                    cout << "Please Select Your Choice : ";
                    cin >> S;
                }
            }
            else
            {
                cout << "\nInvalid Credentials \nYou are taken to main Page \nPlease login again\n\n";
                S = logout;
            }
        }
    }

    return 0;
}