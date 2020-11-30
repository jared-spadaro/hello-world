import java.util.Iterator;

public interface BasicListIterator<E> extends Iterator<E> {

    public boolean hasPrevious ();
	
	public E previous ();


}