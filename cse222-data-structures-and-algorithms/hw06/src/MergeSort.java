public class MergeSort extends SortAlgorithm {
	
	public MergeSort(int input_array[]) {
		super(input_array);
	}
	
	private void merge(int leftIndex, int middleIndex, int rightIndex) {
        // Sizes of the subarrays to be merged
        int sizeLeft = middleIndex - leftIndex + 1;
        int sizeRight = rightIndex - middleIndex;
    
        // Temporary arrays for the subarrays
        int[] leftArray = new int[sizeLeft];
        int[] rightArray = new int[sizeRight];
    
        // Copy elements to temporary arrays
        for (int i = 0; i < sizeLeft; i++) {
            leftArray[i] = arr[leftIndex + i];
        }
        for (int j = 0; j < sizeRight; j++) {
            rightArray[j] = arr[middleIndex + 1 + j];
        }
    
        // Merge the temporary arrays back into the main array
        int i = 0, j = 0, k = leftIndex;
        while (i < sizeLeft && j < sizeRight) {
            comparison_counter++;
            if (leftArray[i] <= rightArray[j]) {
                arr[k] = leftArray[i++];
            } else {
                arr[k] = rightArray[j++];
            }
            k++;
        }
    
        // Copy any remaining elements from leftArray
        while (i < sizeLeft) {
            arr[k++] = leftArray[i++];
        }
    
        // Copy any remaining elements from rightArray
        while (j < sizeRight) {
            arr[k++] = rightArray[j++];
        }
    }
    
    private void sort(int leftIndex, int rightIndex) {
        if (leftIndex < rightIndex) {
            // Calculate middle index
            int middleIndex = (leftIndex + rightIndex) / 2;
    
            // Recursively sort the first and second halves
            sort(leftIndex, middleIndex);
            sort(middleIndex + 1, rightIndex);
    
            // Merge the sorted halves
            merge(leftIndex, middleIndex, rightIndex);
        }
    }
    
    
    @Override
    public void sort() {
    	sort(0,arr.length - 1);
    }
    
    @Override
    public void print() {
    	System.out.print("Merge Sort\t=>\t");
    	super.print();
    }
}
