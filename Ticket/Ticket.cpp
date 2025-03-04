#include "Ticket.h"
#include <cstring>
#include <algorithm>
#include <fstream>

Ticket::Ticket() : arrival(nullptr), wagon(0), seat(0), price(0) {
}

Ticket::Ticket(const char* arrival, int wagon, int seat, int price)
    : wagon(wagon), seat(seat), price(price) {
    this->arrival = new char[strlen(arrival) + 1];
    strcpy(this->arrival, arrival);
}

Ticket::Ticket(const Ticket& other) : arrival(nullptr) {
    Copy(other);
}

Ticket::~Ticket() {
    cleanup();
}


Ticket& Ticket::operator=(const Ticket& other) {
    if (this != &other) {
        cleanup();
        Copy(other);
    }
    return *this;
}

bool Ticket::operator<(const Ticket& other) const {
    if (wagon != other.wagon) {return wagon < other.wagon;} else
    if (seat != other.seat) {return seat < other.seat;} else
     {return price < other.price;}
}



bool Ticket::operator==(const Ticket& other) const {
    return (wagon == other.wagon) &&  (seat == other.seat) &&  (price == other.price);
}


std::istream& operator>>(std::istream& is, Ticket& ticket) {
    char arrival[256];
    is >> arrival;
    delete[] ticket.arrival;
    ticket.arrival = new char[strlen(arrival) + 1];
    strcpy(ticket.arrival, arrival);
    is >> ticket.wagon >> ticket.seat >> ticket.price;
    return is;
}

std::ofstream& operator<<(std::ofstream& os, const Ticket& ticket) {
    os << ticket.arrival << " " << ticket.wagon << " " << ticket.seat << " " << ticket.price;
    return os;
}


std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
    os << ticket.arrival << " " << ticket.wagon << " " << ticket.seat << " " << ticket.price;
    return os;
}

std::ifstream& operator>>(std::ifstream& is, Ticket& ticket) {
    char arrival[256];
    is >> arrival;
    delete[] ticket.arrival;
    ticket.arrival = new char[strlen(arrival) + 1];
    strcpy(ticket.arrival, arrival);
    is >> ticket.wagon >> ticket.seat >> ticket.price;
    return is;
}

void Ticket::readFromFile(const char* filename, Ticket*& tickets, int& size) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "!!!ОШИБКА!!!" << std::endl << "Не удалось открыть файл!" << std::endl;
        return;
    }

    int newSize;
    file >> newSize;
    if (newSize <= 0) {
        std::cout << "Некорректный размер в файле!" << std::endl;
        file.close();
        return;
    }

    file.ignore();
    std::cout << "УСПЕШНО!" << std::endl;

    Ticket* newTickets = new Ticket[newSize];
    bool success = true;

    for (int i = 0; i < newSize; i++) {
        char arrival[256];
        long long diam;
        int life;
        int sat;

        if (file >> arrival >> diam >> life >> sat) {
            newTickets[i] = Ticket(arrival, diam, life, sat);
        } else {
            std::cerr << "Ошибка при чтении билета " << i << std::endl;
            success = false;
            break;
        }
    }

    file.close();

    if (success) {
        if (tickets != nullptr) {
            delete[] tickets;
        }
        tickets = newTickets;
        size = newSize;
    } else {
        delete[] newTickets;
        std::cout << "Произошла ошибка при чтении файла" << std::endl;
    }
}



void Ticket::writeToFile(const char* filename, const Ticket* tickets, int size) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return;
    }
    std::cout << "Производится запись в файл." << std::endl;
    file << size << std::endl;
    for (int i = 0; i < size; i = i + 1) {
        std::cout << tickets[i] << std::endl;
        file << tickets[i] << std::endl;
    }
    file.close();
    std::cout << "Успешно!" << std::endl;
}

void swap(Ticket& a, Ticket& b)
{
    Ticket c = a;
    a = b;
    b = c;

}

void Ticket::Sort(Ticket* tickets, int size) {
    bool swapped;
    for (size_t i = 0; i < size; ++i)
    {
        swapped = false;
        for (size_t j = 0; j < size - i - 1; ++j)
        {
            if (tickets[j + 1] < tickets[j]) {
                swap(tickets[j], tickets[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void Ticket::Add(Ticket*& tickets, int& size, const Ticket& newTicket) {
    Ticket* newArray = new Ticket[size + 1];
    for (int i = 0; i < size; ++i) {
        newArray[i] = tickets[i];
    }
    newArray[size] = newTicket;
    delete[] tickets;
    tickets = newArray;
    ++size;
}

void Ticket::Remove(Ticket*& tickets, int& size, int index) {
    Ticket* newArray = new Ticket[size - 1];
    int j = 0;
    for (int i = 0; i < size; ++i) {
        if (i != index) {
            newArray[j++] = tickets[i];
        }
    }
    delete tickets[index].arrival;
    delete[] tickets;
    tickets = newArray;
    --size;
}

void Ticket::Edit(Ticket*& tickets, int size, int index) {
    Ticket ticket;
    std::cout << "Введите новые данные для билета РЖД (должны быть заполнены все 4 поля):" << std::endl;
    std::cin >> ticket;
    tickets[index] = ticket;
}

void Ticket::Print(const Ticket* tickets, int size) {
    std::cout << "Количество железнодорожных билетов: " << size << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << tickets[i] << std::endl;
    }
}


void Ticket::Copy(const Ticket& other) {
    if (other.arrival) {
        arrival = new char[strlen(other.arrival) + 1];
        strcpy(arrival, other.arrival);
    } else {
        arrival = nullptr;
    }
    wagon = other.wagon;
    price = other.price;
    seat = other.seat;
}

void Ticket::cleanup() {
    delete[] arrival;
    arrival = nullptr;
}
