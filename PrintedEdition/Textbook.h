#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "Book.h"

class Textbook : public Book {
protected:
    std::string subject;
    std::string gradeLevel;

public:
    Textbook(const std::string& title, int pages, const std::string& publisher, int year,
            const std::string& author, const std::string& genre,
            const std::string& subject, const std::string& gradeLevel);
    virtual ~Textbook();

    void show() const override;
};

#endif // TEXTBOOK_H
