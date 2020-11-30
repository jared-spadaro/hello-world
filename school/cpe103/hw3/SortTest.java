import java.util.Random;
import java.util.Arrays;

public class SortTest {
  public void Sort() {
    SortDriver s = new SortDriver();
    int[] array = s.Array();
    System.out.println(Arrays.toString(array));
    s.doQuickSort(array);
    System.out.println(Arrays.toString(array));
    
  }

   

  public static void main (String[] args) {
    SortTest s = new SortTest();
    s.Sort();  
     
  }

}