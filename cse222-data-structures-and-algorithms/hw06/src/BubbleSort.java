public class BubbleSort extends SortAlgorithm {

	public BubbleSort(int input_array[]) {
		super(input_array);
	}
	
    @Override
    public void sort() {
        int arrayLength = arr.length; // Total number of elements in the array
        for (int iteration = 0; iteration < arrayLength - 1; iteration++) {
            boolean hasSwapped = false; // Flag to check if a swap occurred
    
            // Loop through the array up to the sorted portion
            for (int current = 0; current < arrayLength - iteration - 1; current++) {
                comparison_counter++;
                // Compare adjacent elements and swap if they are in the wrong order
                if (arr[current] > arr[current + 1]) {
                    swap(current, current + 1);
                    hasSwapped = true; // Set flag to true indicating a swap occurred
                }
            }
    
            // If no elements were swapped, the array is already sorted
            if (!hasSwapped)
                break;
        }
    }
    
    @Override
    public void print() {
    	System.out.print("Bubble Sort\t=>\t");
    	super.print();
    }
}
