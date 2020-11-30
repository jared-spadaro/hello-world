import mycs1.*;

public class Lab0
{
   public static void main(String[] args)
   {
      boolean negative = false;
      while(true) {
      System.out.print("Value: ");
      int v = Keyboard.readInt();
      if(v<0) {
        negative = true;
        v = (-1) * v;
      }
      System.out.print("Base: ");
      int b = Keyboard.readInt();
      if(b<2 || b>16) {
        throw new RuntimeException();
      }
      String newValue = changeBase(v,b);
      System.out.println("\nValue: " + v);
      System.out.println("Base: " + b);
      if(negative==false) {
        System.out.println("New Value: " + newValue); 
      }
      else {
        System.out.println("New Value: " + "-" + newValue);
      }  
      System.out.print("\nType STOP if you want to stop. Type anything else to continue.\n");
      String stop = Keyboard.readString();
      if(stop.equals("STOP")) break;
}
   }

   private static final char[] digits = {'0','1','2','3','4','5','6','7','8',
                                         '9','A','B','C','D','E','F'};

   // value must be >= 0 and base must be in 2..16

   private static String changeBase(long value,int base)
   {
      if (value < base)
         return "" + digits[(int)value];
      else
         return changeBase(value/base,base) + digits[(int)(value%base)];
   }
}
