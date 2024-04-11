#include <iostream>
#include <vector>
#include <string>

template<typename T>
class Tab {
public:
    std::string url;
    std::string name;
    T memory;
    Tab* next;
    Tab* prev;
public:
    Tab(const std::string& url, const std::string& name, const T& memory)
        : url(url), name(name), memory(memory), next(nullptr), prev(nullptr) {}
};

template<typename T>
class Browser {
private:
    Tab<T>* head;
    Tab<T>* tail;
    std::vector<std::pair<std::string, std::string>> bookmarks;
public:
    Browser() : head(nullptr), tail(nullptr) {}

    void addNewTab(const std::string& url, const std::string& name, const T& memory) {
        Tab<T>* newTab = new Tab<T>(url, name, memory);
        if (!head) {
            head = tail = newTab;
        } else {
            tail->next = newTab;
            newTab->prev = tail;
            tail = newTab;
        }
    }

    void switchToPrevTab() {
        if (!head) {
            std::cout << "No previous tab." << std::endl;
            return;
        }
        if (head == tail) {
            std::cout << "No previous tab." << std::endl;
            return;
        }
        Tab<T>* current = tail->prev;
        std::cout << "The URL: " << current->url << std::endl;
        std::cout << "Website Name: " << current->name << std::endl;
        std::cout << "Memory: " << current->memory << std::endl;
        display();
    }

    void switchToNextTab() {
        if (!head) {
            std::cout << "No next tab." << std::endl;
            return;
        }
        if (tail->next == nullptr) {
            std::cout << "No next tab." << std::endl;
            return;
        }
        Tab<T>* current = tail->next;
        std::cout << "Switch to next tab = " << std::endl;
        std::cout << "The URL: " << current->url << std::endl;
        std::cout << "Website Name: " << current->name << std::endl;
        std::cout << "Memory: " << current->memory << std::endl;
        display();
    }

    void closeCurrentTab() {
        if (!head) {
            std::cout << "No tabs to close." << std::endl;
            return;
        }
        Tab<T>* current = tail;
        if (current == head && current == tail) {
            delete current;
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
            delete current;
        }
        std::cout << "Now the current tab is = " << tail->name << std::endl;
    }

    void bookmarkCurrent() {
        if (!head) {
            std::cout << "No current tab to bookmark." << std::endl;
            return;
        }
        for (const auto& bookmark : bookmarks) {
            if (bookmark.first == tail->name) {
                std::cout << "The bookmark is already added!!" << std::endl;
                return;
            }
        }
        bookmarks.push_back(std::make_pair(tail->name, tail->url));
    }

    void showBookmarkTab() {
        std::cout << "Bookmarks: " << std::endl;
        for (const auto& bookmark : bookmarks) {
            std::cout << bookmark.first << "(" << bookmark.second << ")" << std::endl;
        }
    }

    void moveCurrentToFirst() {
        if (!head) {
            std::cout << "No current tab to move." << std::endl;
            return;
        }
        if (tail == head) {
            std::cout << "Current tab already at the first position." << std::endl;
            return;
        }
        Tab<T>* current = tail;
        tail->prev->next = nullptr;
        tail = tail->prev;
        current->next = head;
        head->prev = current;
        head = current;
        current->prev = nullptr;
    }

    T total_memory() {
        T totalMemory = 0;
        Tab<T>* current = head;
        while (current) {
            totalMemory += current->memory;
            current = current->next;
        }
        return totalMemory;
    }

    void deleteTab() {
    if (!head) {
        std::cout << "No tabs to delete." << std::endl;
        return;
    }

    Tab<T>* maxMemoryTab = head;
    Tab<T>* current = head->next;
    while (current) {
        if (current->memory > maxMemoryTab->memory) {
            maxMemoryTab = current;
        }
        current = current->next;
    }

    if (maxMemoryTab == head && maxMemoryTab == tail) {
        std::cout << "Deleted element = " << maxMemoryTab->name << " with memory size = " << maxMemoryTab->memory << "MB." << std::endl;
        delete maxMemoryTab;
        head = tail = nullptr;
        return;
    }

    if (maxMemoryTab == head) {
        head = head->next;
        head->prev = nullptr;
    } else if (maxMemoryTab == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        maxMemoryTab->prev->next = maxMemoryTab->next;
        maxMemoryTab->next->prev = maxMemoryTab->prev;
    }

    std::cout << "Deleted element = " << maxMemoryTab->name << " with memory size = " << maxMemoryTab->memory << "MB." << std::endl;
    delete maxMemoryTab;
}

    void display() {
        auto curr = head;
        std::cout << "Browser tab list = " << std::endl;
        while (curr) {
            std::cout << "| " << curr->name << "  x|-->";
            curr = curr->next;
        }
        std::cout << std::endl << std::endl;
    }
};

int main(){
Browser<double> b1;
b1.addNewTab("https://www.google.com","Google",23.45);
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to Next tab = "<<std::endl;
b1.switchToNextTab();
b1.addNewTab("https://www.youtube.com","YouTube",56);
b1.bookmarkCurrent();
b1.display();
b1.addNewTab("https://www.geeksforgeeks.com","GeeksForGeeks",45.78);
b1.bookmarkCurrent();
b1.addNewTab("https://chat.openai.com","ChatGPT",129);
b1.addNewTab("https://linkedin.com","LinkedIn",410);
b1.bookmarkCurrent();
b1.addNewTab("https://github.com","Github",110);
b1.addNewTab("https://kaggle.com","Kaggle",310);
b1.bookmarkCurrent();
b1.display();
std::cout<<"Total memory consumption = "<<b1.total_memory()<<"MB"<<std::endl;
b1.showBookmarkTab();
b1.moveCurrentToFirst();
b1.display();
b1.deleteTab();
b1.display();
std::cout<<"Switch to next tab = "<<std::endl;
b1.switchToNextTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.closeCurrentTab();
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.closeCurrentTab();
b1.display();
}
