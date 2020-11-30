import java.util.Random;

public class Test {

    private static void RandomTest () {
	    Random random = new Random(0);
		int i;
		for(i=0;i<15;i++) {
		    System.out.println(random.nextInt(4));
		}
	}
	
	
	
	public static void main (String args[]) {
	    RandomTest();
	}
	
}