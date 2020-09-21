class activity:
    def __init__(self, start, end):
        self.start = start
        self.end = end

    def __repr__(self):
        return f"({self.start}, {self.end})"


activities_count = int(input())
activities = []
for _ in range(activities_count):
    start, end = map(int, input().split())
    activities.append(activity(start, end))

activities = sorted(activities,  key=lambda activity: activity.end)

solutions = [activities[0]]
for activity in activities:
    if solutions[-1].end <= activity.start:
        solutions.append(activity)

print(solutions)
