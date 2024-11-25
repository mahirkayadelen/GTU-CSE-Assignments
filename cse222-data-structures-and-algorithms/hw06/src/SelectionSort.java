public class SelectionSort extends SortAlgorithm {

	public SelectionSort(int input_array[]) {
		super(input_array);
	}

    @Override
    public void sort() {
        int totalElements = arr.length; // Total number of elements in the array
    
        // Iterate over each element except the last
        for (int current = 0; current < totalElements - 1; current++) {
            int minIndex = current; // Assume the current position holds the minimum value
    
            // Find the smallest element in the remaining unsorted part of the array
            for (int next = current + 1; next < totalElements; next++) {
                comparison_counter++;
                if (arr[next] < arr[minIndex]) {
                    minIndex = next; // Update minIndex to the position of the new minimum
                }
            }
    
            // Swap the found minimum element with the current element
            swap(minIndex, current);
        }
    }

    @Override
    public void print() {
    	System.out.print("Selection Sort\t=>\t");
    	super.print();
    }
}
