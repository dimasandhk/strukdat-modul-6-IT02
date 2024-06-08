#include <bits/stdc++.h>
using namespace std;

enum mark {RED, YELLOW, BLUE, GREEN, PURPLE};

class Activity {
    protected:
        string title;
        string desc;
        mark color;

    public:
        Activity(string inpTitle, string inpDesc, mark inpColor) {
            title = inpTitle;
            desc = inpDesc;
            color = inpColor;
        };

        // Setter
        void setTitle(string inpTitle) {
            title = inpTitle;
        }
        void setDesc(string inpDesc) {
            desc = inpDesc;
        }
        void setColor(mark inpColor) {
            color = inpColor;
        }

        // Getter
        string getTitle() { return title; }
        mark getColor() { return color; }
        string getColorString(mark inpColor) {
            string res;
            switch (inpColor) {
                case RED:
                    res = "Red";
                    break;
                case YELLOW:
                    res = "Yellow";
                    break;
                case BLUE:
                    res = "Blue";
                    break;
                case GREEN:
                    res = "Green";
                    break;
                case PURPLE:
                    res = "Purple";
                    break;
            }
            return res;
        }
        virtual string getDetail() {
            return getDetail(false); // Overload
        }
        virtual string getDetail(bool includeColor) {
            string res = title + ":\n";
            res += desc + "\n";
            if (includeColor) {
                res += "Color: " + getColorString(color) + "\n";
            }
            return title + " " + desc;
        }
};

struct Date {
    int day, month, year;
};

struct Time {
    int hour, minute;
};

struct DateWithWeek {
    int day, month, year, week;
};

class Event : public Activity {
    protected:
        string location;
        Date startDate;
        Date endDate;

    public:
        Event(string inpTitle, string inpDesc, mark inpColor, string inpLocation, Date inpStartDate, Date inpEndDate) 
        : Activity(inpTitle, inpDesc, inpColor) {
            location = inpLocation;
            startDate = inpStartDate;
            endDate = inpEndDate;
        };

        // Additional Method
        DateWithWeek getCurrentTime() {
            auto now = chrono::system_clock::now();
            time_t now_c = chrono::system_clock::to_time_t(now);

            struct tm *parts = localtime(&now_c);

            DateWithWeek res;
            res.year = 1900 + parts->tm_year;
            res.month = 1 + parts->tm_mon;
            res.day = parts->tm_mday;
            res.week = parts->tm_wday;

            return res;
        }

        // Setter
        void setLocation(string inpLocation) {
            location = inpLocation;
        }
        void setStartDate(Date inpStartDate) {
            startDate = inpStartDate;
        }
        void setEndDate(Date inpEndDate) {
            endDate = inpEndDate;
        }

        // Getter
        int getStartDateDay() {
            return startDate.day;
        }
        int getStartDateMonth() {
            return startDate.month;
        }
        int getStartDateYear() {
            return startDate.year;
        }
        int getEndDateDay() {
            return endDate.day;
        }
        int getEndDateMonth() {
            return endDate.month;
        }
        int getEndDateYear() {
            return endDate.year;
        }
        string getLocation() { return location; }
        string getDateString(Date inpDate) {
            string res = to_string(inpDate.day) + "/" + to_string(inpDate.month) + "/" + to_string(inpDate.year);
            return res;
        }
        string getDetail() override {
            return getDetail(false); // Overload
        }
        string getDetail(bool includeColor) override {
            string res = title + " (" + location + ")" ":\n" + "Waktu: ";
            string resStartDate = getDateString(startDate);
            string resEndDate = getDateString(endDate);
            res += resStartDate + " - " + resEndDate + "\nDesc:\n";
            res += desc;

            if (includeColor) {
                res += "\nColor: " + getColorString(color) + "\n";
            }

            return res;
        }
};

struct DateTime {
    Date date;
    Time time;
};

struct DateTimeWithWeek {
    int day, month, year, week;
    int hour, minute;
};

class Task : public Activity {
    protected:
        DateTime deadline;

    public:
        Task(DateTime inpDeadline, string inpTitle, string inpDesc, mark inpColor) 
        : Activity(inpTitle, inpDesc, inpColor) {
            deadline = inpDeadline;
        };

        // Additional Method
        DateWithWeek getCurrentTime() {
            auto now = chrono::system_clock::now();
            time_t now_c = chrono::system_clock::to_time_t(now);

            struct tm *parts = localtime(&now_c);

            DateWithWeek res;
            res.year = 1900 + parts->tm_year;
            res.month = 1 + parts->tm_mon;
            res.day = parts->tm_mday;
            res.week = parts->tm_wday;

            return res;
        }

        // Setter
        void setDeadline(DateTime inpDeadline) {
            deadline = inpDeadline;
        }

        // Getter
        DateTimeWithWeek getDeadline() {
            DateTimeWithWeek res;
            res.day = deadline.date.day;
            res.month = deadline.date.month;
            res.year = deadline.date.year;
            res.week = 0;
            res.hour = deadline.time.hour;
            res.minute = deadline.time.minute;
            return res;
        }
        string getDateTimeString() {
            string resDate = to_string(deadline.date.day) + "/" + to_string(deadline.date.month) + "/" + to_string(deadline.date.year) + " ";
            string resTime = to_string(deadline.time.hour) + ":" + to_string(deadline.time.minute);
            return resDate + " " + resTime;
        }
        string getDetail() override {
            return getDetail(false); // Overload
        }
        string getDetail(bool includeColor) override {
            string res = title + " | " + "Deadline: ";
            res += getDateTimeString() + "\nDesc: \n";
            res += desc + "\n";

            if (includeColor) {
                res += "Color: " + getColorString(color) + "\n";
            }

            return res;
        }
};

enum ViewType {MONTH, WEEK, DAY, YEAR};

class EventList {
    private:
        vector<Event> eventList;

    public:
        // vector manipulation
        void addEvent(Event inpEvent) {
            eventList.push_back(inpEvent);
        }

        void updateTitle(string oldTitle, string newTitle) {
            for (int i = 0; i < eventList.size(); i++) {
                if (eventList[i].getTitle() == oldTitle) {
                    eventList[i].setTitle(newTitle);
                    return;
                }
            }
        }

        void updateDesc(string title, string newDesc) {
            for (int i = 0; i < eventList.size(); i++) {
                if (eventList[i].getTitle() == title) {
                    eventList[i].setDesc(newDesc);
                    return;
                }
            }
        }

        void removeEventByTitle(string title) {
            for (int i = 0; i < eventList.size(); i++) {
                if (eventList[i].getTitle() == title) {
                    eventList.erase(eventList.begin() + i);
                    return;
                }
            }
        }

        void removeEvent(int idx) {
            eventList.erase(eventList.begin() + idx);
        }

        // show event list
        void searchByTitle(string title) {
            cout << "Events with title " << title << ": " << endl;
            for (int i = 0; i < eventList.size(); i++) {
                if (eventList[i].getTitle() == title) {
                    cout << eventList[i].getDetail(true) << endl;
                }
            }
        }

        void printBasedOnLocation(string location) {
            cout << "Events in " << location << ": " << endl;
            for (int i = 0; i < eventList.size(); i++) {
                if (eventList[i].getLocation() == location) {
                    cout << eventList[i].getDetail(true) << endl;
                }
            }
        }

        void printBasedOnColor(mark color) {
            cout << "Events with color " << color << ": " << endl;
            for (int i = 0; i < eventList.size(); i++) {
                if (eventList[i].getColor() == color) {
                    cout << eventList[i].getDetail(true) << endl;
                }
            }
        }

        void printNearestEvent() {
            cout << "Nearest Event (this week): " << endl;
            for (int i = 0; i < eventList.size(); i++) {
                DateWithWeek currentTime = eventList[i].getCurrentTime();
                int currentYear = currentTime.year;
                int currentMonth = currentTime.month;
                int currentDay = currentTime.day;
                int currentWeek = currentTime.week;

                // Check if the event is this week
                if (eventList[i].getStartDateYear() == currentYear && eventList[i].getStartDateMonth() == currentMonth && eventList[i].getStartDateDay() >= currentDay && eventList[i].getStartDateDay() <= currentDay + 7) {
                    cout << eventList[i].getDetail(true) << endl;
                    return;
                }
            }
        }

        void printEventList() {
            cout << "All events:" << endl;
            for (int i = 0; i < eventList.size(); i++) {
                cout << eventList[i].getDetail(true) << endl;
            }
        }

        void printEventList(ViewType viewType) {
            if (viewType == MONTH) {
                cout << "Viewing events in month view: " << endl;
            } else if (viewType == WEEK) {
                cout << "Viewing events in week view: " << endl;
            } else if (viewType == DAY) {
                cout << "Viewing events in day view: " << endl;
            } else if (viewType == YEAR) {
                cout << "Viewing events in year view: " << endl;
            }

            for (int i = 0; i < eventList.size(); i++) {
                DateWithWeek currentTime = eventList[i].getCurrentTime();
                int currentYear = currentTime.year;
                int currentMonth = currentTime.month;
                int currentDay = currentTime.day;
                int currentWeek = currentTime.week;

                if (viewType == MONTH) {
                    if (eventList[i].getStartDateMonth() == currentMonth) {
                        cout << eventList[i].getDetail(true) << endl;
                    }
                } else if (viewType == WEEK) {
                    if (eventList[i].getStartDateMonth() == currentMonth && eventList[i].getStartDateDay() >= currentDay && eventList[i].getStartDateDay() <= currentDay + 7) {
                        cout << eventList[i].getDetail(true) << endl;
                    }
                } else if (viewType == DAY) {
                    if (eventList[i].getStartDateMonth() == currentMonth && eventList[i].getStartDateDay() == currentDay) {
                        cout << eventList[i].getDetail(true) << endl;
                    }
                } else if (viewType == YEAR) {
                    if (eventList[i].getStartDateYear() == currentYear) {
                        cout << eventList[i].getDetail(true) << endl;
                    }
                }
            }
        }
};

class TaskList {
    private:
        vector<Task> taskList;

    public:
        // vector manipulation
        void addTask(Task inpTask) {
            taskList.push_back(inpTask);
        }

        void updateTitle(string oldTitle, string newTitle) {
            for (int i = 0; i < taskList.size(); i++) {
                if (taskList[i].getTitle() == oldTitle) {
                    taskList[i].setTitle(newTitle);
                    return;
                }
            }
        }

        void updateDesc(string title, string newDesc) {
            for (int i = 0; i < taskList.size(); i++) {
                if (taskList[i].getTitle() == title) {
                    taskList[i].setDesc(newDesc);
                    return;
                }
            }
        }

        void removeTaskByTitle(string title) {
            for (int i = 0; i < taskList.size(); i++) {
                if (taskList[i].getTitle() == title) {
                    taskList.erase(taskList.begin() + i);
                    return;
                }
            }
        }

        void removeTask(int idx) {
            taskList.erase(taskList.begin() + idx);
        }

        // show task list
        void searchByTitle(string title) {
            cout << "Tasks with title " << title << ": " << endl;
            for (int i = 0; i < taskList.size(); i++) {
                if (taskList[i].getTitle() == title) {
                    cout << taskList[i].getDetail(true) << endl;
                }
            }
        }

        void printBasedOnColor(mark color) {
            cout << "Tasks with color " << color << ": " << endl;
            for (int i = 0; i < taskList.size(); i++) {
                if (taskList[i].getColor() == color) {
                    cout << taskList[i].getDetail(true) << endl;
                }
            }
        }

        void printTaskList() {
            cout << "All tasks:" << endl;
            for (int i = 0; i < taskList.size(); i++) {
                cout << taskList[i].getDetail(true) << endl;
            }
        }

        void printNearestTask() {
            cout << "Nearest Task (this week): " << endl;
            for (int i = 0; i < taskList.size(); i++) {
                DateWithWeek currentTime = taskList[i].getCurrentTime();
                int currentYear = currentTime.year;
                int currentMonth = currentTime.month;
                int currentDay = currentTime.day;
                int currentWeek = currentTime.week;

                // Check if the task is this week
                if (taskList[i].getDeadline().year == currentYear && taskList[i].getDeadline().month == currentMonth && taskList[i].getDeadline().day >= currentDay && taskList[i].getDeadline().day <= currentDay + 7) {
                    cout << taskList[i].getDetail(true) << endl;
                    return;
                }
            }
        }

        void printTaskList(ViewType viewType) {
            if (viewType == MONTH) {
                cout << "Viewing tasks in month view: " << endl;
            } else if (viewType == WEEK) {
                cout << "Viewing tasks in week view: " << endl;
            } else if (viewType == DAY) {
                cout << "Viewing tasks in day view: " << endl;
            } else if (viewType == YEAR) {
                cout << "Viewing tasks in year view: " << endl;
            }

            for (int i = 0; i < taskList.size(); i++) {
                DateWithWeek currentTime = taskList[i].getCurrentTime();
                int currentYear = currentTime.year;
                int currentMonth = currentTime.month;
                int currentDay = currentTime.day;
                int currentWeek = currentTime.week;

                if (viewType == MONTH) {
                    if (taskList[i].getDeadline().month == currentMonth) {
                        cout << taskList[i].getDetail(true) << endl;
                    }
                } else if (viewType == WEEK) {
                    if (taskList[i].getDeadline().month == currentMonth && taskList[i].getDeadline().day >= currentDay && taskList[i].getDeadline().day <= currentDay + 7) {
                        cout << taskList[i].getDetail(true) << endl;
                    }
                } else if (viewType == DAY) {
                    if (taskList[i].getDeadline().month == currentMonth && taskList[i].getDeadline().day == currentDay) {
                        cout << taskList[i].getDetail(true) << endl;
                    }
                } else if (viewType == YEAR) {
                    if (taskList[i].getDeadline().year == currentYear) {
                        cout << taskList[i].getDetail(true) << endl;
                    }
                }
            }
        }
};

void handleEventMenu();
void handleTaskMenu();

EventList eventList;
TaskList taskList;

int main() {
    /* 
        IT 02 Strukdat Final Project:
        - Dimas Andhika Diputra
        - Ryan Adya Purwanto
        - Nafi Firdaus
    */

    cout << "-----------------------------------------------------------" << endl;
    cout << "------------ Event & Task Management System ---------------" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "------- Google Calendar System implemented with OOP -------" << endl;
    cout << "-----------------------------------------------------------" << endl;

    string choice;
    do {
        cout << "-----------------------------------------------------------" << endl;
        cout << "Menu: " << endl;
        cout << "1. Event Menu" << endl;
        cout << "2. Task Menu" << endl;
        cout << "Q. Quit" << endl;
        
        cout << "-----------------------------------------------------------" << endl;
        cout << "Choice: ";
        cin >> choice;
        
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

        if (choice == "1") {
            handleEventMenu();
        } else if (choice == "2") {
            handleTaskMenu();
        } else if (choice == "Q") {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != "q" || choice != "Q");

    return 0;
}

void handleEventMenu() {
    cout << "-----------------------------------------------------------" << endl;
    cout << "Event Menu: " << endl;
    cout << "1. Add Event" << endl;
    cout << "2. Update Event Title" << endl;
    cout << "3. Update Event Description" << endl;
    cout << "4. Remove Event" << endl;
    cout << "5. Search Event by Title" << endl;
    cout << "6. Print Event List" << endl;
    cout << "7. Print Event List based on Location" << endl;
    cout << "8. Print Event List based on Color" << endl;
    cout << "9. Print Nearest Event" << endl;
    cout << "10. Print Event List based on View Type" << endl;
    cout << "-----------------------------------------------------------" << endl;

    string choice;
    cin >> choice;
    if (choice == "1") {
        string title, desc, location;
        int color;
        Date startDate, endDate;

        cout << "--- Add Event ---" << endl;
        cout << "Title: ";
        cin >> title;
        cout << "Description: ";
        cin >> desc;
        cout << "Location: ";
        cin >> location;
        cout << "Color (0: Red, 1: Yellow, 2: Blue, 3: Green, 4: Purple): ";
        cin >> color;
        cout << "Start Date (dd mm yyyy): ";
        cin >> startDate.day >> startDate.month >> startDate.year;
        cout << "End Date (dd mm yyyy): ";
        cin >> endDate.day >> endDate.month >> endDate.year;

        Event newEvent(title, desc, (mark)color, location, startDate, endDate);
        eventList.addEvent(newEvent);
    } else if (choice == "2") {
        cout << "--- Update Event Title ---" << endl;
        string oldTitle, newTitle;
        cout << "Old Title: ";
        cin >> oldTitle;
        cout << "New Title: ";
        cin >> newTitle;
        eventList.updateTitle(oldTitle, newTitle);
        cout << "--- Event Title Updated ---" << endl;
        eventList.searchByTitle(newTitle);
    } else if (choice == "3") {
        string title, newDesc;
        cout << "Title: ";
        cin >> title;
        cout << "New Description: ";
        cin >> newDesc;
        eventList.updateDesc(title, newDesc);
        cout << "--- Event Description Updated ---" << endl;
        eventList.searchByTitle(title);
    } else if (choice == "4") {
        string title;
        cout << "Title: ";
        cin >> title;
        eventList.removeEventByTitle(title);
    } else if (choice == "5") {
        string title;
        cout << "Title: ";
        cin >> title;
        eventList.searchByTitle(title);
    } else if (choice == "6") {
        eventList.printEventList();
    } else if (choice == "7") {
        string location;
        cout << "Location: ";
        cin >> location;
        eventList.printBasedOnLocation(location);
    } else if (choice == "8") {
        int color;
        cout << "Color (0: Red, 1: Yellow, 2: Blue, 3: Green, 4: Purple): ";
        cin >> color;
        eventList.printBasedOnColor((mark)color);
    } else if (choice == "9") {
        eventList.printNearestEvent();
    } else if (choice == "10") {
        int viewType;
        cout << "View Type (0: Month, 1: Week, 2: Day, 3: Year): ";
        cin >> viewType;
        eventList.printEventList((ViewType)viewType);
    }
}

void handleTaskMenu() {
    cout << "-----------------------------------------------------------" << endl;
    cout << "Task Menu: " << endl;
    cout << "1. Add Task" << endl;
    cout << "2. Update Task Title" << endl;
    cout << "3. Update Task Description" << endl;
    cout << "4. Remove Task" << endl;
    cout << "5. Search Task by Title" << endl;
    cout << "6. Print Task List" << endl;
    cout << "7. Print Task List based on Color" << endl;
    cout << "8. Print Nearest Task" << endl;
    cout << "9. Print Task List based on View Type" << endl;
    cout << "-----------------------------------------------------------" << endl;

    string choice;
    cout << "Choose menu: ";
    cin >> choice;
    cin.ignore();
    cout << "-----------------------------------------------------------" << endl;

    if (choice == "1") {
        string title, desc;
        int color;
        DateTime deadline;

        cout << "--- Add Task ---" << endl;
        cout << "Title: ";
        getline(cin, title);
        cout << "Description: ";
        getline(cin, desc);
        cout << "Color (0: Red, 1: Yellow, 2: Blue, 3: Green, 4: Purple): ";
        cin >> color;
        cout << "Deadline Date (dd mm yyyy): ";
        cin >> deadline.date.day >> deadline.date.month >> deadline.date.year;
        cout << "Deadline Time (hh mm): ";
        cin >> deadline.time.hour >> deadline.time.minute;

        Task newTask(deadline, title, desc, (mark)color);
        taskList.addTask(newTask);
    } else if (choice == "2") {
        cout << "--- Update Task Title ---" << endl;
        string oldTitle, newTitle;
        cout << "Old Title: ";
        getline(cin, oldTitle);
        cout << "New Title: ";
        getline(cin, newTitle);
        taskList.updateTitle(oldTitle, newTitle);
        cout << "--- Task Title Updated ---" << endl;
        taskList.searchByTitle(newTitle);
    } else if (choice == "3") {
        string title, newDesc;
        cout << "--- Update Task Description ---" << endl;
        cout << "Title: ";
        getline(cin, title);
        cout << "New Description: ";
        getline(cin, newDesc);
        taskList.updateDesc(title, newDesc);
        cout << "--- Task Description Updated ---" << endl;
        taskList.searchByTitle(title);
    } else if (choice == "4") {
        cout << "--- Remove Task ---" << endl;
        string title;
        cout << "Title: ";
        getline(cin, title);
        taskList.removeTaskByTitle(title);
    } else if (choice == "5") {
        string title;
        cout << "--- Search Task by Title ---" << endl;
        cout << "Title: ";
        getline(cin, title);
        cout << endl;
        taskList.searchByTitle(title);
    } else if (choice == "6") {
        cout << endl;
        cout << "--- Print Task List ---" << endl;
        taskList.printTaskList();
    } else if (choice == "7") {
        int color;
        cout << "--- Print Task List based on Color ---" << endl;
        cout << "Color (0: Red, 1: Yellow, 2: Blue, 3: Green, 4: Purple): ";
        cin >> color;
        cout << endl;
        taskList.printBasedOnColor((mark)color);
    } else if (choice == "8") {
        taskList.printNearestTask();
    } else if (choice == "9") {
        int viewType;
        cout << "--- Print Task List based on View Type ---" << endl;
        cout << "View Type (0: Month, 1: Week, 2: Day, 3: Year): ";
        cin >> viewType;
        cout << endl;
        taskList.printTaskList((ViewType)viewType);
    }
}