

public class Exceptions {
   
    public String nullException () {
        String bad = null;
        return bad;
    }

    public void classException () {
        Object x = new Integer (2);
        System.out.print((String)x);
    }

    public void indexException () {
        int i;
        int a[] = new int[10];
        for(i=0;i<11;i++) {
            a[i] = 2;
        }
    }

    
    private void NullExceptionTest () {
            Exceptions e = new Exceptions();
            e.nullException();
        }

}
