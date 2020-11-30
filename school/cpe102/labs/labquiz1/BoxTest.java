

public class BoxTest {

    private static void equalsTest () {
        Box b1 = new Box (3,4,5);
        Box b2 = new Box (3,4,5);
        Box b3 = new Box (3.1,4,5);
        Box b4 = new Box ();
        Box b5 = new Box ();
        System.out.println (b1.equals(b2));
        System.out.println (b2.equals(b3));
        System.out.println (b4.equals(b5));
    }

    private static void toStringTest () {
        Box b1 = new Box ();
        Box b2 = new Box (56,87,34);
        Box b3 = new Box (-54,23,-1);
        System.out.println (b1.toString());
        System.out.println (b2.toString());
        System.out.println (b3.toString());
    }

    public static void main (String args[]) {
        equalsTest();
        toStringTest();
    }

    

}
