

public class Person implements Comparable<Person> {

    private String name;
    private int id;
    private String address;

    public Person (String name, int id, String address) {
        this.name = name;
        this.id = id;
        this.address = address;
    }

    public boolean equals (Object obj) {
        if(getClass()!=obj.getClass()) {
            return false;
        }
        if(obj==null) {
            return false;
        }
        Person p = (Person)obj;
        return id==p.id;
    }

    public String toString () {
        return "name: " + name + "/nid: " + id + "/naddress: " + address;
    }

    public int compareTo (Person other) {
        if(id>other.id) {
            return 1;
        }
        else if (id<other.id) {
            return -1;
        }
        else {
            return 0;
        }
    }
   




}
