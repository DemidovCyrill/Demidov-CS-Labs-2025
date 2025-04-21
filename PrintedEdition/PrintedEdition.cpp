#include "PrintedEdition.h"

PrintedEdition::PrintedEdition(const std::string& title, int pages, const std::string& publisher, int year)
    : title(title), pages(pages), publisher(publisher), year(year) {
    std::cout << "PrintedEdition()" << std::endl;
}

PrintedEdition::~PrintedEdition() {
    std::cout << "~PrintedEdition()" << std::endl;
}
