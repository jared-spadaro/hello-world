public class Lab5B
{
   private static int[] data = {5,2,1,8,4,3,7,10,0,6,11,12,9};
   private static boolean[] answer = 
      {true,true,false,true,true,false,true,true,true,true,true,false,true};
   private static int failures = 0;

   public static void main(String[] args)
   {
      int i;
      if (data.length != answer.length)
         throw new RuntimeException("Initialization error in driver.");

      System.out.println("Begin creating tree A");
      MyBST t = new MyBST();
      for(i=0;i<data.length;++i)
      {
         t.insert(new Integer(data[i]));
         reportTest("A"+i,t.isBalanced()==answer[i]);
      }

      System.out.println("Begin creating tree B");
      t = new MyBST();
      reportTest("B",t.isBalanced());
      for(i=0;i<=2;++i)
      {
         t.insert(new Integer(i));
         t.insert(new Integer(-i));
         reportTest("B"+i,t.isBalanced());
      }
      for(i=3;i<=5;++i)
      {
         t.insert(new Integer(i));
         t.insert(new Integer(-i));
         reportTest("B"+i,!t.isBalanced());
      }
      System.out.println();
      if (failures == 0)
         System.out.println("All test cases were passed.");
      else
         System.out.println("Failed " + failures + " test cases.");
   }

   private static void reportTest(String ID,boolean passed)
   {
      if (passed)
         System.out.println("Passed test " + ID);
      else
      {
         ++failures;
         System.out.println("FAILED test " + ID);
      }
   }
}
