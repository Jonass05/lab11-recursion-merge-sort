/*
 * Course: COEN 2220 - Programming 2
 * Name: [John P. Badillo Lamourt]
 * Lab: Lab 11 - Recursion and Merge Sort
 * Description: Practice - sort a temporary view without changing original tasks
 * Due date: [3 november 2026]
 */

#include <iostream>
#include <string>
using namespace std;

struct RepairTask
{
    string taskId;     // Preserve the identity of the original task.
    int daysUntilDue;  // Smaller values must appear first in the report.
    int minutesNeeded; // Break equal-deadline ties with smaller durations first.
};

bool comesBeforeOrEqual(const RepairTask *left, const RepairTask *right);
void mergeTaskView(RepairTask *view[], RepairTask *temporary[],
                   int first, int middle, int last);
void mergeSortView(RepairTask *view[], RepairTask *temporary[], int first, int last);
void displayOriginal(const RepairTask tasks[], int count);
void displayView(RepairTask *view[], int count);

int main()
{
    const int TASK_COUNT = 8;
    RepairTask tasks[TASK_COUNT] =
    {
        {"RT-101", 3, 30}, {"RT-102", 1, 20},
        {"RT-103", 2, 15}, {"RT-104", 1, 10},
        {"RT-105", 2, 15}, {"RT-106", 3, 10},
        {"RT-107", 1, 20}, {"RT-108", 2, 5}
    };
    RepairTask *view[TASK_COUNT];      // Borrow addresses of existing tasks.
    RepairTask *temporary[TASK_COUNT]; // Hold addresses while merging the view.
    for (int index = 0; index < TASK_COUNT; index++)
    {
        view[index] = &tasks[index]; // Preserve arrival order in the initial view.
    }

    cout << boolalpha;
    cout << "Original arrival order:" << endl;
    displayOriginal(tasks, TASK_COUNT);

    // ===== Resolve these TODOs now (Part C) =====
    // TODO (Part C): Activate the C test block after completing the comparator.
    
    cout << "Earlier deadline first: "
         << comesBeforeOrEqual(&tasks[1], &tasks[0]) << endl;
    cout << "Shorter duration within same deadline: "
         << comesBeforeOrEqual(&tasks[3], &tasks[1]) << endl;
    cout << "Exact tie keeps left: "
         << comesBeforeOrEqual(&tasks[2], &tasks[4]) << endl;
    cout << "Later deadline first: "
         << comesBeforeOrEqual(&tasks[0], &tasks[1]) << endl;
    

    // ===== Resolve these TODOs later (Part D) =====
    // TODO (Part D): Call mergeSortView for the complete logical range.
    
    mergeSortView(view, temporary, 0, TASK_COUNT - 1);

    // TODO (Part D): Display the sorted view with a descriptive heading.
    
    cout << "Sorted by deadline and duration:" << endl;
    displayView(view, TASK_COUNT);

    // TODO (Part D): Display tasks again to prove that arrival order did not change.
    
    cout << "Original arrival order (unchanged):" << endl;
    displayOriginal(tasks, TASK_COUNT);

    return 0;
}

bool comesBeforeOrEqual(const RepairTask *left, const RepairTask *right)
{
    // ===== Resolve this TODO now (Part C) =====
    // TODO (Part C): Implement the specified two-field order, including exact ties.
    if (left->daysUntilDue < right->daysUntilDue)
    {
        return true; // Left has an earlier deadline.
    }
    else if (left->daysUntilDue > right->daysUntilDue)
    {
        return false; // Right has an earlier deadline.
    }
    else
    {
        // Deadlines are equal, compare minutesNeeded
        if (left->minutesNeeded < right->minutesNeeded)
        {
            return true; // Left has a shorter duration.
        }
        else if (left->minutesNeeded > right->minutesNeeded)
        {
            return false; // Right has a shorter duration.
        }
        else
        {
            return true; // Exact tie, preserve left's position.
        }
    }

    return false; // Temporary placeholder; replace this line in Part C.
}

// ===== Resolve these TODOs later (Part D) =====
void mergeSortView(RepairTask *view[], RepairTask *temporary[], int first, int last)
{
    // TODO (Part D): Implement recursive merge sort using inclusive indices.
    if (first < last)
    {
        int middle = first + (last - first) / 2; // Avoid potential overflow.
        mergeSortView(view, temporary, first, middle); // Sort left half.
        mergeSortView(view, temporary, middle + 1, last); // Sort right half.
        mergeTaskView(view, temporary, first, middle, last); // Merge sorted halves.
    }
}

void mergeTaskView(RepairTask *view[], RepairTask *temporary[],
                   int first, int middle, int last)
{
    // TODO (Part D): Merge two sorted segments using comesBeforeOrEqual.
    int leftIndex = first;
    int rightIndex = middle + 1;
    int tempIndex = first;

    while (leftIndex <= middle && rightIndex <= last)
    {
        if (comesBeforeOrEqual(view[leftIndex], view[rightIndex]))
        {
            temporary[tempIndex] = view[leftIndex];
            leftIndex++;
        }
        else
        {
            temporary[tempIndex] = view[rightIndex];
            rightIndex++;
        }
        tempIndex++;
    }

    // TODO (Part D): Preserve pending pointers and copy the merged segment back.
    while (leftIndex <= middle)
    {
        temporary[tempIndex] = view[leftIndex];
        leftIndex++;
        tempIndex++;
    }

    while (rightIndex <= last)
    {
        temporary[tempIndex] = view[rightIndex];
        rightIndex++;
        tempIndex++;
    }

    for (int i = first; i <= last; i++)
    {
        view[i] = temporary[i];
    }
}

void displayOriginal(const RepairTask tasks[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Task: " << tasks[index].taskId
             << " | Days until due: " << tasks[index].daysUntilDue
             << " | Minutes: " << tasks[index].minutesNeeded << endl;
    }
}

void displayView(RepairTask *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Task: " << view[index]->taskId
             << " | Days until due: " << view[index]->daysUntilDue
             << " | Minutes: " << view[index]->minutesNeeded << endl;
    }
}

/*
 * Analysis Answers
 *
 * C5 - Two-field decision
 * Explain the result for RT-103 compared with RT-108. Which field decides it?
 * Answer:
 * RT-103 and RT-108 have the same daysUntilDue, so the minutesNeeded field decides the order.
 * 
 * D1 - Recursive ranges
 * Show first, last, middle, and the base-case evaluations along the first branch
 * starting at 0..7. Identify where execution resumes after the call for 0..0.
 * Answer:
 * mergeSortView(0, 7) middle = 3, Splits into left 0..3 and right 4..7
 * mergeSortView(0, 3) middle = 1. Splits into left 0..1 and right 2..3. mergeSortView(0, 1) middle = 0. Splits into left 0..0 and right 1..1.
 * mergeSortView(0, 0) first >= last (0 >= 0), hitting the base case and returning immediately.
 * Execution resumes back inside the pending call for 0..1 to proceed to its right half 1..1.
 * 
 * D2 - Stable ties
 * Identify both pairs of tasks that tie in the two sort fields. Explain how the
 * comparator and the merge preserve their arrival order.
 * Answer:
 * The pairs of tasks that tie in both fields are RT-103 and RT-105 (both have daysUntilDue = 2 and minutesNeeded = 15),
 * and RT-102 and RT-107 (both have daysUntilDue = 1 and minutesNeeded = 20). The comparator returns true for the left task
 * in case of an exact tie, which preserves the arrival order during the merge process. Thus, 
 * RT-103 will appear before RT-105, and RT-102 will appear before RT-107 in the sorted view.
 * 
 * D3 - Time, space, and original data
 * Give the sorting time and auxiliary-space order of this pointer-array version.
 * Compare with the linked-list sort in Part B and explain why the original task
 * storage order is preserved here but the node order changes in Part B.
 * Answer:
 * The time complexity of the pointer-array version is O(n log n), where n is the number of tasks, due to the recursive merge sort algorithm.
 * The auxiliary space complexity is O(n) for the temporary array used during merging. In contrast,
 * the linked-list sort in Part B also has a time complexity of O(n log n) but uses O(log n) auxiliary space due to the recursive call stack.
 * The original task storage order is preserved in this pointer-array version because we are sorting pointers to existing tasks rather than
 * modifying the tasks themselves. In Part B, the node order changes because we are rearranging the actual nodes in the linked list, which alters their order in memory.
 * 
 */