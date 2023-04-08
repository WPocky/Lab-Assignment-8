#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// swap for heapSort
void swap(int* a, int* b) {
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

// heapify for heapSort
void heapify(int arr[], int n, int i) {
    // largest root
    int big = i;

    // left
    int left = 2 * i + 1;

    // right
    int right = 2 * i + 2;

    if(left < n && arr[left] > arr[big]) {
        big = left;
    }
    if (right < n && arr[right] > arr[big]) {
        big = right;
    }
    if (big != i) {
		// swapping i and biggest root for recursive call correction
        swap(&arr[i], &arr[big]);
        // recursively call heapify
        heapify(arr, n, big);
    }
}


// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
    // max heap
    for(int i = n/2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    // heapsort
    for(int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i ,0);
    }
}

// merge function for mergesort
void merge(int pData[], int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;

	// temp arrays for left and right
	int *L, *R;
	L = (int*)malloc(n1 * sizeof(int));
    R = (int*)malloc(n2 * sizeof(int));

	// filling temp arrays
	for(int i = 0; i < n1; i++) {
		L[i] = pData[l+i];
	}
	for(int i = 0; i < n2; i++) {
		R[i] = pData[m + 1 + i];
	}
	// merging temp arrays back into pData
	int x = 0;
	int y = 0;
	int z = l;
	while(x < n1 && y < n2) {
		if(L[x] <= R[y]) {
			pData[z] = L[x];
			x++;
		}
		else {
			pData[z] = R[y];
			y++;
		}
		z++;
	}

	// copying remaining elements in temp arrays
	while(x < n1) {
		pData[z] = L[x];
		x++;
		z++;
	}
	while(y < n2) {
		pData[z] = R[y];
		y++;
		z++;
	}
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    if(l < r) {
		int m = (l+r) / 2;
		// sorting both halves
		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);
		extraMemoryAllocated++;
		// merging arrays
		merge(pData,l,m,r);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
 		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}