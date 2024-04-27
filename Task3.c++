#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

ofstream dataFile("sort_results.csv");

int heapifying(int arr[], int n, int i)
{
    int number_of_comparisons = 0;
    int minimumValue = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n)
    {
        number_of_comparisons++;
        if (arr[left] < arr[minimumValue])
        {
            minimumValue = left;
        }
    }
    if (right < n)
    {
        number_of_comparisons++;
        if (arr[right
] < arr[minimumValue])
        {
            minimumValue = right
    ;
        }
    }
    if (minimumValue != i)
    {
        swap(arr[i], arr[minimumValue]);
        number_of_comparisons += heapifying(arr, n, minimumValue);
    }
    return number_of_comparisons;
}

int heap_sort_count(int arr[], int n)
{
    int number_of_comparisons = 0;
    for (int i = (n - 2) / 2; i >= 0; i--)
    {
        number_of_comparisons += heapifying(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        number_of_comparisons += heapifying(arr, i, 0);
    }
    return number_of_comparisons;
}

int bubble_sort_count(int arr[], int n)
{
    int number_of_comparisons = 0;
    bool swap_occurs;
    for (int i = 0; i < n - 1; i++)
    {
        swap_occurs = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                swap_occurs = true;
            }
            number_of_comparisons++;
        }
        if (!swap_occurs)
        {
            break;
        }
    }
    return number_of_comparisons;
}

int selection_sort_count(int arr[], int n)
{
    int number_of_comparisons = 0;
    int min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
            number_of_comparisons++;
        }
        swap(arr[i], arr[min]);
    }
    return number_of_comparisons;
}

int insertion_sort_count(int arr[], int n)
{
    int number_of_comparisons = 0;
    int key = 0;
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        for (int j = i - 1; j > -1; j--)
        {
            number_of_comparisons++;
            if (key < arr[j])
            {
                swap(arr[j], arr[j+1]);
            }
            else
            {
                break;
            }
        }
    }
    return number_of_comparisons;
}

void reshuffle(int temp[], int arr[], int n)
{
    for (int x = 0; x < n; x++)
    {
        temp[x] = arr[x];
    }
}

void printTable(int n, string arr_type, string sort_type, int sort, double exec_time)
{
    cout << n << "  " << arr_type  << "  " << sort_type << "  " << sort << "  " << exec_time << "\n";
}

void exec_sorts(int temp[], int arr[], int n, string arr_type, string sort_alg)
{
    reshuffle(temp, arr, n);
    auto start = chrono::high_resolution_clock::now();
    int sort;
    if (sort_alg == "Heap")
    {
        sort = heap_sort_count(temp, n);
    }
    else if (sort_alg == "Bubble")
    {
        sort = bubble_sort_count(temp, n);
    }
    else if (sort_alg == "Selection")
    {
        sort = selection_sort_count(temp, n);
    }
    else
    {
        sort = insertion_sort_count(temp, n);
    }
    auto end = chrono::high_resolution_clock::now();
    double exec_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-9;
    dataFile << n << "," << arr_type << "," << sort_alg << "," << sort << "," << exec_time << "\n";
    printTable(n, arr_type, sort_alg, sort, exec_time);
}

void run_sorts(int arr[], string arr_type, int n)
{
    int* temp = new int[n];
    exec_sorts(temp, arr, n, arr_type, "Heap");
    exec_sorts(temp, arr, n, arr_type, "Bubble");
    exec_sorts(temp, arr, n, arr_type, "Selection");
    exec_sorts(temp, arr, n, arr_type, "Insertion");
}

void Comparison_Time_Complexity()
{
    srand(time(0));

    dataFile << "Size of Array , Type of Array , Sorting Algorithm , Number of Comparisons, Execution Time\n";
    cout << "Size of Array" << "  Type of Array"
    << "  Sorting Algorithm" << "  Number of Comparisons"
    "  Execution Time" << "\n";

    for (int s = 1; s < 31; s++)
    {
        int* random_array = new int[s];
        int* sorted_array = new int[s];
        int* inverse_array = new int[s];
        int num1 = 0;
        int num2 = 0;
        for (int i = 0; i < s; i++)
        {
            random_array[i] = rand() % (s * 20);
            num1 += rand() % (s * 20);
            sorted_array[i] = num1;
            num2 += rand() % (s * 20);
            inverse_array[s-i-1] = num2;
        }
        run_sorts(random_array, "Random", s);
        run_sorts(sorted_array, "Sorted", s);
        run_sorts(inverse_array, "Inversely-sorted", s);
        delete[] random_array;
        delete[] sorted_array;
        delete[] inverse_array;
    }
}

int main()
{
    Comparison_Time_Complexity();
    dataFile.close();
    return 0;
}