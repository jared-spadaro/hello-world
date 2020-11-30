

public class HashTable {

  private int capacity;
  private LinkedList[] hashTable;
  private int maxBuckets;
  private int numElements;
  private int nonZeroBucketCount;

  public HashTable (int capacity) {
     this.capacity = capacity;
     hashTable = new LinkedList[capacity];
     for (int i=0;i<capacity;i++) {
       hashTable[i] = new LinkedList();
     }
     maxBuckets = 0;
     numElements = 0;
     nonZeroBucketCount = 0;
  }

  public void add (Object element) {
    int code = Math.abs(element.hashCode() % capacity);
    if(hashTable[code]==null) hashTable[code] = new LinkedList();
    if(hashTable[code].isEmpty()) nonZeroBucketCount++;
    hashTable[code].addLast(element);
    numElements++;
    int length = hashTable[code].length();
    if(length>maxBuckets) maxBuckets = length;    
  }

  public boolean contains (Object element) {
    int code = Math.abs(element.hashCode() % capacity);
    if(hashTable[code]==null) hashTable[code] = new LinkedList();
    LinkedList ll = hashTable[code];
    if(ll.contains(element)) return true;
    else return false;
  }

  public int numElements () {
    return numElements;
  }
    
  public int capacity () {
    return capacity;
  }

  public int maxBucketCount () {
    return maxBuckets;
  }

  public int nonZeroBucketCount () {
    return nonZeroBucketCount;
  }

  public float avgNonZeroBucketCount () {
    float avg = 0;
    for(int i=0;i<capacity;i++) {
      if(hashTable[i]!=null) {
        if(!hashTable[i].isEmpty()) {
          avg += hashTable[i].length();
        }
      }
    }
    return avg/nonZeroBucketCount;
  }

  /*public static class Error extends RuntimeException {
    
  }*/

}
