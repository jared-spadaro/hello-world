class bubbleSort {
    private static int[] sort(int[] a) {
        if (a.length == 0 || a.length == 1) return a;
        //bubble sort
        for (int i = 0; i < a.length - 1; i++) {
            for (int j = 0; j < a.length - i - 1; j++) {
            if (a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
            }
        }
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i] + " ");
        }
        System.out.print("\n");
          //get number of duplicates
        int count = 0;
        for (int i = 0; i < a.length-1; i++) {
            if (a[i] == a[i+1]) count++;
        }
        System.out.println("Number of duplicates = " + count);
        if (count == 0) return a;
        int ret[] = new int[a.length - count];
        for (int i = 0, j = 0; i < a.length; i++) {
            while (i < a.length-1 && a[i] == a[i+1]) i++;
            ret[j++] = a[i];
        }
        for (int i = 0; i < ret.length; i++) {
            System.out.print(ret[i] + " ");
        }
        System.out.print("\n");
        return a;
    }

    public static void main(String[] args) {
        sort(new int[]{ 6,4,7,3,9,9,9,9,9,9,1,10,2 });
    }
}