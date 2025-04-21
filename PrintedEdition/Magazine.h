#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "PrintedEdition.h"

class Magazine : public PrintedEdition {
protected:
    int issueNumber;
    std::string issueDate;

public:
    Magazine(const std::string& title, int pages, const std::string& publisher, int year,
             int issueNumber, const std::string& issueDate);
    virtual ~Magazine();

    void show() const override;
};

#endif // MAGAZINE_H
