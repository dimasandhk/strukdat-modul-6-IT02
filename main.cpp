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
            res += resStartDate + " - " + resEndDate + "\n";
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
            string res = title + ":\n" + "Deadline: ";
            res += getDateTimeString() + "\n";
            res += desc;

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

int main() {
    Date startDate = {1, 6, 2024};
    Date endDate = {2, 6, 2024};
    Date startDatelg = {1, 6, 2024};
    Date endDate2 = {2, 6, 2024};
    Event event1("Event 1", "Deskripsi Event 1", RED, "Jakarta", startDate, endDate);
    Event event2("Event 2", "Deskripsi Event 2", BLUE, "Bandung", startDate, endDate);
    Event event3("Event 3", "Deskripsi Event 3", GREEN, "Surabaya", startDatelg, endDate2);

    EventList eventList;
    eventList.addEvent(event1);
    eventList.addEvent(event2);
    eventList.addEvent(event3);

    // Print all events
    eventList.printEventList(MONTH);

    // Remove the first event
    eventList.removeEvent(0);

    cout << endl << "-------------------------" << endl;
    // Print all events again to verify the first event was removed
    eventList.printEventList();

    return 0;
}