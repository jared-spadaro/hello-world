import java.util.*;
import java.lang.*;

public class BasicLinkedList<E> implements BasicList<E>, Iterable<E> {

    private int size;
    private Node first;
	private Node last;
	
	private class Node {
	    public E data;
		public Node next;
		public Node previous;
	}
	
	private class MyIterator implements BasicListIterator<E> {
	    
		private Node current;
		
		public MyIterator () {
		    current = null;
		}
		
		public boolean hasNext () {
		    if(current==null) {
			    return first!=null;
			}
			return current.next!=null;	
		}
		
		public E next () {
		    if(!hasNext()) {
		     	throw new NoSuchElementException();
			}
			if(current==null) {
				current = first;
			}
			else {
                current = current.next;
			}
			return current.data;
		}
		
		public void remove () {
		    throw new UnsupportedOperationException();
		}
		
		public boolean hasPrevious () {
			return current!=null;	
			
		}
		
		public E previous () {
		    E element;
	        if(!hasPrevious()) {
			    throw new NoSuchElementException();
			}
			element = current.data;
		    current = current.previous;
			return element;
		}
		
	}

    private boolean isEmpty () {
	    return first == null;
	}

    public BasicLinkedList () {
	    size = 0;
	    first = null;
		last = null;
	}
	
	public void add (E element) {
	    Node newNode = new Node();
		newNode.data = element;
        if(isEmpty()) {
		    first = newNode;
		}
		else {
		    last = newNode;
		    last.next = newNode;
			last.previous = last;
			last = newNode;
		}
		
		
		size++;
	}
	
	public void add (int index, E element) {
	    if(index<0||index>size()) {
		    throw new IndexOutOfBoundsException();
        }
		if(index==size()) {
		    add(element);
			size++;
			return;
		}
		else if(index==0) {
		    Node current = new Node();
			current.data = element;
			current.next = first;
			first.previous = current;
			first = current;
			size++;
			return;
		}
		int i;
		Node current = first;
		for(i=0;i<index-1;i++) {
		    current = current.next;
		}
		Node newNode = new Node();
		newNode.data = element;
        newNode.next = current.next;
		current.next = newNode;
		size++;
    }
	
	public BasicListIterator<E> basicListIterator () {
		return new MyIterator();
	}
	
	public void clear () {
	    first = null;
		size = 0;
	}
	
	public boolean contains (E element) {
	    Node current = first;
		if(element==null) {
		    while(current!=null) {
                if(current.data==null) {
                    return true;
				}
				current = current.next;
			}
		}
		else { 
		    while(current!=null) {
		        if(current.data.equals(element)) {
			        return true;
			    }
			    current = current.next;
		    }
		}
		return false;
	}
	
	public E get (int index) {
	    if(first==null) {
		    throw new IndexOutOfBoundsException();
		}
	    Node current = first;
		int i;
		for(i=0;i<index;i++) {
		    if(current.next==null) {
			    throw new IndexOutOfBoundsException();
			}
		    current = current.next;
		}
	    return current.data;
	}
	
	public int indexOf (E element) {
	    Node current = first;
		int index = 0;
		if(element==null) {
		    while(current!=null) {
			    if(current.data==null) {
				    return index;
				}
				current = current.next;
				index++;
			}
		}
		while(current!=null) {
		    if(current.data.equals(element)) {
			    return index;
            }
			current = current.next;
            index++;
        }
        throw new NoSuchElementException(); //(?)
	}
	
	public Iterator<E> iterator () {
	    return new MyIterator();
	}
	
	public E remove (int index) {
	    if(index<0 || index>size()-1) {
		    throw new IndexOutOfBoundsException();
		}
	    /*if(first==null) {
		    throw new IndexOutOfBoundsException();
		}*/
		if(size()==1) {
		    E element = first.data;
			first = null;
			last = null;
			return element;
		}
		if(size()==2) {
		    if(index==0) {
			    E element = first.data;
				first = first.next;
				first.previous = null;
				size--;
				return element;
			}
			else if(index==1) {
			    E element = last.data;
				last = last.previous;
				last.next = null;
				size--;
				return element;
			}
		}
		if (index==size()-1) {
		    System.out.println(last.data);
			System.out.println(last.previous);
			System.out.println(last.next);
		    E element = last.data;
			last = last.previous;
			last.next = null;
			
			size--;
			return element;
		}
		
	    int i;
		Node current = first;
		for(i=0;i<index;i++) {
		    
		    current = current.next;
			/*if(current==null) {
			    size--;
			    return null;
			}*/
		}
		
		Node two = current.next;
		two.previous = current.previous;
		current.previous.next = two;
		E element = current.data;
		//two = null;
		size--;
		return element;
	}
	
	public E set (int index, E element) {
	    if(index<0||index>size-1) {
		    throw new IndexOutOfBoundsException();
		}
	    Node current = first;
		int i;
		for(i=0;i<index;i++) {
		    current = current.next;
		}
		E oldData = current.data;
		current.data = element;
		return oldData;
	}
	
	public int size () {
	    return size;
	}
	
	
}