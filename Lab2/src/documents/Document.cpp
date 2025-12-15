#include "documents/Document.h"

using namespace std;

Document::Document()
    : id(0),
    createdDate(),
    author(nullptr),
    status("draft"),
    version(1) {
}

Document::Document(int id, const Date& createdDate, Employee* author)
    : id(id),
    createdDate(createdDate),
    author(author),
    status("draft"),
    version(1) {
}

int Document::getId() const { return id; }
const Date& Document::getCreatedDate() const { return createdDate; }
Employee* Document::getAuthor() const { return author; }
const string& Document::getStatus() const { return status; }
int Document::getVersion() const { return version; }

void Document::setAuthor(Employee* value) { author = value; }
void Document::setStatus(const string& value) { status = value; }

void Document::incrementVersion() {
    ++version;
}

void Document::save() {
    if (status == "draft")
        status = "active";
}

void Document::markArchived() {
    status = "archived";
}
