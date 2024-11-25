public class QuickSort extends SortAlgorithm {

	public QuickSort(int input_array[]) {
		super(input_array);
	}
	
    private int partition(int startIndex, int endIndex) {
        // Pivot element taken from the end of the array
        int pivot = arr[endIndex];  
        int smallerElementIndex = (startIndex - 1);  // Tracks the last position of smaller element
    
        for (int current = startIndex; current < endIndex; current++) {
            // If current element is smaller than or equal to pivot
            if (arr[current] <= pivot) {
                smallerElementIndex++;  // Move to next position
    
                // Swap elements at smallerElementIndex and current index
                swap(smallerElementIndex, current);
            }
            comparison_counter++;
        }
    
        // Place pivot in the correct position by swapping
        swap(smallerElementIndex + 1, endIndex);
    
        return smallerElementIndex + 1;  // Return the pivot's final position
    }
    
    private void sort(int startIndex, int endIndex) {
        if (startIndex < endIndex) {
            // Partition the array and get the index of the placed pivot
            int pivotIndex = partition(startIndex, endIndex);
    
            // Recursively sort the array before and after the pivot
            sort(startIndex, pivotIndex - 1);
            sort(pivotIndex + 1, endIndex);
        }
    }

    @Override
    public void sort() {
    	sort(0, arr.length -1);
    }

    @Override
    public void print() {
    	System.out.print("Quick Sort\t=>\t");
    	super.print();
    }
}
