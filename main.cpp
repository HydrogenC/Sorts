#include "main.h"

using namespace std;

//Main Functions Begin
typedef void (*FuncType)(llong array[], llong n);

//Make switch() compatible with string
constexpr int getASC(char *p) {
    //To prevent conflicts
    return (int(p[0]) * 2) + (int(p[1]) * 3) + (int(p[2]) * 4);
}

llong inputElements(llong array[]) {
    cout << "Please input the length of the array: ";
    llong n;
    cin >> n;
    cout << "Please input the elements: " << endl;
    for (llong i = 0; i < n; i += 1) {
        cin >> array[i];
    }
    return n;
}
void inputElements(llong array[],llong n) {
    cout << "Please input the elements: " << endl;
    for (llong i = 0; i < n; i += 1) {
        cin >> array[i];
    }
}

llong getTime(llong array[], llong n, FuncType function) {
    clock_t begin, end;
    begin = clock();
    function(array, n);
    end = clock();
    return end - begin;
}

const string algorithmNames[9] = {
        "Bubble Sort",
        "Selection Sort",
        "Insertion Sort",
        "Merge Sort",
        "Quick Sort",
        "Heap Sort",
        "Radix Sort"
};

int checkIndex(char *arg) {
    switch (getASC(arg)) {
        case getASC((char *) "bubble"):
            return 1;
            break;
        case getASC((char *) "select"):
            return 2;
            break;
        case getASC((char *) "insert"):
            return 3;
            break;
        case getASC((char *) "merge"):
            return 4;
            break;
        case getASC((char *) "quick"):
            return 5;
            break;
        case getASC((char *) "heap"):
            return 6;
            break;
        case getASC((char *) "radix"):
            return 7;
            break;
        case getASC((char *) "all"):
            return 8;
            break;
        case getASC((char *) "help"):
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
            cout << "csort [bubble, select, insert, merge, quick, heap, radix, all] [elements]" << endl;
            system("pause>nul");
            exit(0);
        default:
            cout << "'csort help' for help! " << endl;
            return 1;
    }
}

void output(llong array[], llong n, FuncType sort, int index) {
    llong temp[65536];
    memcpy(temp, array, 65536);
    clock_t begin, end;
    begin = clock();
    sort(temp, n);
    end = clock();
    cout << "Algorithm name: " << algorithmNames[index] << endl;
    cout << "Sorted array: ";
    for (llong i = 0; i < n; i += 1) {
        if (i == n - 1) {
            cout << temp[i];
        } else {
            cout << temp[i] << " ";
        }
    }
    cout << endl << "Time used: " << end - begin << endl << endl;
}
//Main Functions End

//Bubble Sort Begins
void bubbleSort(llong array[], llong n) {
    for (llong i = 0; i < n - 1; i += 1) {
        for (llong j = 0; j < n - 1 - i; j += 1) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}
//Bubble Sort Ends

//Insertion Sort Begins
void insertSort(llong array[], llong n) {
    llong temp, j;
    for (llong i = 1; i < n; i += 1) {
        temp = array[i];
        for (j = i; (j > 0) && (array[j - 1] > temp); j -= 1) {
            array[j] = array[j - 1];
        }
        array[j] = temp;
    }
}
//Insertion Sort Ends

//Selection Sort Begins
void selectSort(llong array[], llong n) {
    llong min;
    for (llong i = 0; i < n - 1; i++) {
        min = i;
        for (llong j = i + 1; j < n; j++) {
            if (array[min] > array[j]) {
                min = j;
            }
        }
        if (min != i) {
            swap(array[min], array[i]);
        }
    }
}
//Selection Sort Ends

//Merge Sort Begins
void Merge(llong sourceArr[], llong tempArr[], llong startIndex, llong midIndex, llong endIndex) {
    llong i = startIndex;
    llong j = midIndex + 1;
    llong k = startIndex;
    while (i != midIndex + 1 && j != endIndex + 1) {
        if (sourceArr[i] >= sourceArr[j]) {
            tempArr[k++] = sourceArr[j++];
        } else {
            tempArr[k++] = sourceArr[i++];
        }
    }
    while (i != midIndex + 1) {
        tempArr[k++] = sourceArr[i++];
    }
    while (j != endIndex + 1) {
        tempArr[k++] = sourceArr[j++];
    }
    for (i = startIndex; i <= endIndex; i += 1) {
        sourceArr[i] = tempArr[i];
    }
}

void MSort(llong sourceArr[], llong tempArr[], llong startIndex, llong endIndex) {
    llong midIndex;
    if (startIndex < endIndex) {
        midIndex = (startIndex + endIndex) / 2;
        MSort(sourceArr, tempArr, startIndex, midIndex);
        MSort(sourceArr, tempArr, midIndex + 1, endIndex);
        Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
    }
}

void mergeSort(llong array[], llong n) {
    llong b[n];
    MSort(array, b, 0, n - 1);
}
//Merge Sort Ends

//Quick Sort Begins
void QSort(llong a[], llong low, llong high) {
    if (low >= high) {
        return;
    }
    llong first = low;
    llong last = high;
    llong key = a[first];

    while (first < last) {
        while (first < last && a[last] >= key) {
            --last;
        }

        a[first] = a[last];

        while (first < last && a[first] <= key) {
            ++first;
        }

        a[last] = a[first];
    }
    a[first] = key;
    QSort(a, low, first - 1);
    QSort(a, first + 1, high);
}

void quickSort(llong array[], llong n) {
    QSort(array, 0, n - 1);
}
//Quick Sort Ends

//Heap Sort Begins
void HeapAdjust(llong array[], llong i, llong length) {
    llong nChild;
    llong nTemp;
    for (; 2 * i + 1 < length; i = nChild) {
        nChild = 2 * i + 1;
        if (nChild < length - 1 && array[nChild + 1] > array[nChild]) {
            ++nChild;
        }
        if (array[i] < array[nChild]) {
            nTemp = array[i];
            array[i] = array[nChild];
            array[nChild] = nTemp;
        } else {
            break;
        }
    }
}

void heapSort(llong array[], llong n) {
    llong i;
    for (i = n / 2 - 1; i >= 0; --i) {
        HeapAdjust(array, i, n);
    }
    for (i = n - 1; i > 0; --i) {
        array[i] = array[0] ^ array[i];
        array[0] = array[0] ^ array[i];
        array[i] = array[0] ^ array[i];
        HeapAdjust(array, 0, i);
    }
}
//Heap Sort Ends

//Radix Sort Begins
llong maxBit(llong array[], llong n) {
    llong d = 1;
    llong p = 10;
    for (llong i = 0; i < n; ++i) {
        while (array[i] >= p) {
            p *= 10;
            ++d;
        }
    }
    return d;
}

void radixSort(llong array[], llong n) {
    llong d = maxBit(array, n);
    llong tmp[n];
    llong count[10];
    llong i, j, k;
    llong radix = 1;
    for (i = 1; i <= d; i += 1) {
        for (j = 0; j < 10; j += 1) {
            count[j] = 0;
        }
        for (j = 0; j < n; j += 1) {
            k = (array[j] / radix) % 10;
            count[k]++;
        }
        for (j = 1; j < 10; j += 1) {
            count[j] = count[j - 1] + count[j];
        }
        for (j = n - 1; j >= 0; j -= 1) {
            k = (array[j] / radix) % 10;
            tmp[count[k] - 1] = array[j];
            count[k]--;
        }
        for (j = 0; j < n; j++) {
            array[j] = tmp[j];
        }
        radix = radix * 10;
    }
}
//Radix Sort Ends

int main(int argc, char *argv[]) {
    llong length = 0;
    llong time = 0;
    llong arr[65536];
    llong index = 0;
    switch (argc) {
        case 0:
        case 1:
            length = inputElements(arr);
            cout << "1. Bubble Sort" << endl;
            cout << "2. Selection Sort" << endl;
            cout << "3. Insertion Sort" << endl;
            cout << "4. Merge Sort" << endl;
            cout << "5. Quick Sort" << endl;
            cout << "6. Heap Sort" << endl;
            cout << "7. Radix Sort" << endl;
            cout << "8. All" << endl;
            cin >> index;
            break;
        case 2:
            index = checkIndex(argv[1]);
            length = inputElements(arr);
            break;
        case 3:
            index=checkIndex(argv[1]);
            length=atoll(argv[2]);
            inputElements(arr,length);
            break;
        default:
            index = checkIndex(argv[1]);
            if (argc > 3) {
                length = argc - 2;
                for (llong i = 0; i < length; i += 1) {
                    arr[i] = atoll(argv[i + 2]);
                }
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                cout << "Unknown error! " << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
                return -1;
            }
            break;
    }
    cout << endl;
    switch (index) {
        case 1:
            time = getTime(arr, length, bubbleSort);
            break;
        case 2:
            time = getTime(arr, length, selectSort);
            break;
        case 3:
            time = getTime(arr, length, insertSort);
            break;
        case 4:
            time = getTime(arr, length, mergeSort);
            break;
        case 5:
            time = getTime(arr, length, quickSort);
            break;
        case 6:
            time = getTime(arr, length, heapSort);
            break;
        case 7:
            time = getTime(arr, length, radixSort);
            break;
        case 8:
            output(arr, length, bubbleSort, 0);
            output(arr, length, selectSort, 1);
            output(arr, length, insertSort, 2);
            output(arr, length, mergeSort, 3);
            output(arr, length, quickSort, 4);
            output(arr, length, heapSort, 5);
            output(arr, length, radixSort, 6);
            system("pause>nul");
            return 0;
        default:
            cout << "Incorrect input! " << endl;
            return -1;
    }
    cout << "Algorithm name: " << algorithmNames[index - 1] << endl;
    cout << "Sorted array: ";
    for (llong i = 0; i < length; i += 1) {
        if (i == length - 1) {
            cout << arr[i];
        } else {
            cout << arr[i] << " ";
        }
    }
    cout << endl << "Time used: " << time << endl;
    system("pause>nul");
    return 0;
}