class Solution {
    public int[] resultArray(int[] nums) {
        int n = nums.length;
        int[] arr1 = new int[n];
        int[] arr2 = new int[n];

        int size1 = 0, size2 = 0;
        arr1[size1++] = nums[0];
        arr2[size2++] = nums[1];

        for (int i = 2; i < n; i++) {
            if (arr1[size1 - 1] > arr2[size2 - 1]) {
                arr1[size1++] = nums[i];
            } else {
                arr2[size2++] = nums[i];
            }
        }

        int[] result = new int[n];

        for (int i = 0; i < size1; i++) {
            result[i] = arr1[i];
        }

        for (int i = 0; i < size2; i++) {
            result[size1 + i] = arr2[i];
        }

        return result;
    }
}