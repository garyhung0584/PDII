#include <stdio.h>
#include <stdlib.h>

// Struct to hold classroom information
typedef struct {
    int id;
    int capacity;
    int original_index; // To keep track for scheduling
} Classroom;

// Struct to hold course information
typedef struct {
    int id;
    int students;
    int start;
    int end;
    int duration;
} Course;

// Struct to hold the final assignment of a course to a classroom
typedef struct {
    int course_id;
    int classroom_id;
} Assignment;

// Comparison function for qsort to sort classrooms.
// Primary sort key: capacity (ascending).
// Secondary sort key: id (ascending).
int compare_classrooms(const void* a, const void* b) {
    Classroom* r1 = (Classroom*)a;
    Classroom* r2 = (Classroom*)b;
    if (r1->capacity != r2->capacity) {
        return r1->capacity - r2->capacity;
    }
    return r1->id - r2->id;
}

// Comparison function for qsort to sort courses.
// Primary sort key: duration (descending).
// Secondary sort key: id (descending).
int compare_courses(const void* a, const void* b) {
    Course* c1 = (Course*)a;
    Course* c2 = (Course*)b;
    if (c1->duration != c2->duration) {
        return c2->duration - c1->duration; // Descending
    }
    return c2->id - c1->id; // Descending
}

// Comparison function for qsort to sort the final assignments for output.
// Sort key: course_id (ascending).
int compare_assignments(const void* a, const void* b) {
    Assignment* as1 = (Assignment*)a;
    Assignment* as2 = (Assignment*)b;
    return as1->course_id - as2->course_id;
}

int main() {
    // 1. Read Input
    int M, N;
    scanf("%d %d", &M, &N);

    Classroom classrooms[M];
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &classrooms[i].id, &classrooms[i].capacity);
        classrooms[i].original_index = i;
    }

    Course courses[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &courses[i].id, &courses[i].students, &courses[i].start, &courses[i].end);
        courses[i].duration = courses[i].end - courses[i].start;
    }

    int b;
    scanf("%d", &b);

    // 2. Sort classrooms and courses based on the greedy strategy
    qsort(classrooms, M, sizeof(Classroom), compare_classrooms);
    qsort(courses, N, sizeof(Course), compare_courses);

    // 3. Initialize scheduling data structures
    // We use a simple array of pointers to store scheduled courses for each classroom.
    // The size N is the max possible courses for any room.
    Course* schedule[M][N];
    int scheduled_count[M];
    for(int i=0; i<M; ++i) {
        scheduled_count[i] = 0;
    }

    Assignment assignments[N];
    int assignment_count = 0;
    long long total_hours = 0;

    // 4. Greedy Scheduling Algorithm
    // Iterate through the high-priority courses first
    for (int i = 0; i < N; i++) {
        Course* current_course = &courses[i];

        // For each course, find the best-fit classroom (tightest capacity)
        for (int j = 0; j < M; j++) {
            Classroom* current_classroom = &classrooms[j];

            // a. Capacity Check (if required)
            if (b > 0 && current_course->students > current_classroom->capacity) {
                continue; // Try the next bigger classroom
            }

            // b. Time Conflict Check
            int has_conflict = 0;
            // The classroom's schedule is identified by its original index
            int classroom_schedule_idx = current_classroom->original_index;
            for (int k = 0; k < scheduled_count[classroom_schedule_idx]; k++) {
                Course* scheduled_course = schedule[classroom_schedule_idx][k];
                // A conflict exists if the time intervals overlap.
                // (StartA < EndB) and (EndA > StartB)
                if (current_course->start < scheduled_course->end && current_course->end > scheduled_course->start) {
                    has_conflict = 1;
                    break;
                }
            }

            // c. Schedule if no conflict
            if (!has_conflict) {
                // Add course to this classroom's schedule
                schedule[classroom_schedule_idx][scheduled_count[classroom_schedule_idx]] = current_course;
                scheduled_count[classroom_schedule_idx]++;

                // Record the assignment for final output
                assignments[assignment_count].course_id = current_course->id;
                assignments[assignment_count].classroom_id = current_classroom->id;

                // Update totals
                assignment_count++;
                total_hours += current_course->duration;

                // Course has been scheduled, move to the next course
                break;
            }
        }
    }

    // 5. Print Results
    printf("max hours %lld\n", total_hours);
    printf("max courses %d\n", assignment_count);

    if (b == 2) {
        // Sort the assignments by course ID for the final output
        qsort(assignments, assignment_count, sizeof(Assignment), compare_assignments);
        for (int i = 0; i < assignment_count; i++) {
            printf("%d %d\n", assignments[i].course_id, assignments[i].classroom_id);
        }
    }

    return 0;
}
