#ifndef TICKET_H
#define TICKET_H
#include <iostream>

// class Ticket {
// private:
//     static int count;
//     int id;
//     char* arrival;
//     int wagon;
//     int seat;
//     int price;

// public:
//     Ticket();
//     Ticket(const char* arrival, int wagon, int seat, int price);
//     Ticket(const Ticket& other);
//     ~Ticket();
// };



class Ticket {
    private:
        static int count;
        int id;
        char* arrival;
        int wagon;
        int seat;
        int price;

    public:
        Ticket();
        Ticket(const char* arrival, int wagon, int seat, int price);
        Ticket(const Ticket& other);
        ~Ticket();


        Ticket& operator=(const Ticket& other);
        bool operator<(const Ticket& other) const;
        bool operator==(const Ticket& other) const;

        friend std::istream& operator>>(std::istream& is, Ticket& ticket);
        friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket);
        friend std::ofstream& operator<<(std::ofstream& os, const Ticket& ticket);
        friend std::ifstream& operator>>(std::ifstream& is, Ticket& ticket);

        static void readFromFile(const char* filename, Ticket*& tickets, int& size);
        static void writeToFile(const char* filename, const Ticket* tickets, int size);
        static void Sort(Ticket* tickets, int size);
        static void Add(Ticket*& tickets, int& size, const Ticket& newTicket);
        static void Remove(Ticket*& tickets, int& size, int index);
        static void Edit(Ticket*& tickets, int size, int index);
        static void Print(const Ticket* tickets, int size);

    private:
        void Copy(const Ticket& other);
        void cleanup();
    };


#endif // TICKET_H
