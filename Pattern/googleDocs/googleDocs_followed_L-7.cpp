// Google Docs foolled (SRP,OCP)

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Abstraction for document elements
class DocumentElement {
public:
    virtual string render() = 0;
    virtual ~DocumentElement() = default;
};

// Concrete implementation for text elements
class TextElement : public DocumentElement {
private:
    string text;

public:
    TextElement(string text) {
        this->text = text;
    }

    string render() override {
        return text;
    }
};

// Concrete implementation for image elements
class ImageElement : public DocumentElement {
private:
    string imagePath;

public:
    ImageElement(string imagePath) {
        this->imagePath = imagePath;
    }

    string render() override {
        return "[Image:" + imagePath + "]";
    }
};

// NewLineElement represents a line break
class NewLineElement : public DocumentElement {
public:
    string render() override {
        return "\n";
    }
};

// TabSpaceElement represents a tab space
class TabSpaceElement : public DocumentElement {
public:
    string render() override {
        return "\t";
    }
};

// Document class responsible for holding elements
class Document {
private:
    vector<DocumentElement*> documentElements;

public:
    void addElement(DocumentElement* element) {
        documentElements.push_back(element);
    }

    string render() {
        string result;

        for (auto element : documentElements) {
            result += element->render();
        }

        return result;
    }

    ~Document() {
        for (auto element : documentElements) {
            delete element;
        }
    }
};

// Persistence interface
class Persistence {
public:
    virtual void save(string data) = 0;
    virtual ~Persistence() = default;
};

// File storage implementation
class FileStorage : public Persistence {
public:
    void save(string data) override {
        ofstream file("document.txt");

        if (file.is_open()) {
            file << data;
            file.close();

            cout << "Document saved to document.txt" << endl;
        } else {
            cout << "Error: Unable to open file for writing" << endl;
        }
    }
};

// Placeholder DB storage implementation
class DBStorage : public Persistence {
public:
    void save(string data) override {
        cout << "Saving document to database..." << endl;
    }
};

// Document editor class
class DocumentEditor {
private:
    Document* document;
    Persistence* storage;
    string renderedDocument;

public:
    DocumentEditor(Document* document, Persistence* storage) {
        this->document = document;
        this->storage = storage;
    }

    void addText(string text) {
        document->addElement(new TextElement(text));
        renderedDocument.clear();
    }

    void addImage(string imagePath) {
        document->addElement(new ImageElement(imagePath));
        renderedDocument.clear();
    }

    void addNewLine() {
        document->addElement(new NewLineElement());
        renderedDocument.clear();
    }

    void addTabSpace() {
        document->addElement(new TabSpaceElement());
        renderedDocument.clear();
    }

    string renderDocument() {
        if (renderedDocument.empty()) {
            renderedDocument = document->render();
        }

        return renderedDocument;
    }

    void saveDocument() {
        storage->save(renderDocument());
    }
};

// Client code
int main() {
    Document* document = new Document();
    Persistence* persistence = new FileStorage();

    DocumentEditor* editor =
        new DocumentEditor(document, persistence);

    editor->addText("Hello World");
    editor->addNewLine();

    editor->addText(
        "This is a real world document editor example.");
    editor->addNewLine();

    editor->addTabSpace();
    editor->addText(
        "Indented text after a tab space.");
    editor->addNewLine();

    editor->addImage("picture.jpg");

    cout << editor->renderDocument() << endl;

    editor->saveDocument();

    delete editor;
    delete persistence;
    delete document;

    return 0;
}