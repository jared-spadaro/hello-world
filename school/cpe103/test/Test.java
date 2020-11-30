public class Test {

  public static void Method1() {
    int x = 2;
    int y = 1;
    int i;
    for(i=0;i<10;i++) {
      System.out.println(i);
      x = x + y;
      if(x>30) {
        break;
      }
    }
  }
  public static void main (String[] args) {
    Method1();
  }
}