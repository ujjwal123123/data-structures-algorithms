#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

class Activity {
  public:
    int start;
    int end;

    Activity(int start, int end) {
        this->start = start;
        this->end = end;
    }

    bool static CompareAges(const Activity &left,
                            const Activity &right) {
        return left.end < right.end;
    }

    void print() {
        cout << "[" << this->start << ", " << this->end << ")"
             << endl;
    }
};

vector<Activity> activity_selection(vector<Activity> activities) {
    vector<Activity> solutions;

    int last_end = 0;
    for (Activity activity : activities) {
        if (last_end <= activity.start) {
            solutions.push_back(activity);
            last_end = activity.end;
        }
    }
    return solutions;
}

vector<Activity> get_activities() {
    int activities_count;
    cin >> activities_count;

    vector<Activity> activities;
    for (int i = 0; i < activities_count; i++) {
        int start, end;
        cin >> start;
        cin >> end;

        activities.push_back(Activity(start, end));
    }

    sort(activities.begin(), activities.end(), Activity::CompareAges);

    return activities;
}

int main() {
    vector<Activity> activities = get_activities();

    cout << "Activities:" << endl;
    for (Activity activity : activities) {
        activity.print();
    }

    vector<Activity> solutions = activity_selection(activities);

    cout << "Solutions:" << endl;
    for (Activity solution : solutions) {
        solution.print();
    }

    return 0;
}
