class activity:
    # [start, end)
    # start is included in the interval, but end is not
    def __init__(self, start, end):
        self.start = start
        self.end = end

    def __repr__(self):
        return f"({self.start}, {self.end})"


def activity_selection(activities):
    activities = sorted(activities, key=lambda activity: activity.end)

    solutions = []
    last_end = 0
    for activity in activities:
        if last_end <= activity.start:
            solutions.append(activity)
            last_end = activity.end

    return solutions


def get_activities():
    activities_count = int(input())
    activities = []
    for _ in range(activities_count):
        start, end = map(int, input().split())
        activities.append(activity(start, end))

    return activities


activities = get_activities()
print(activity_selection(activities))
