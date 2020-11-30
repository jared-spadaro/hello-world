import java.util.ArrayList;
import java.util.Collections;

public class PersonList {

    private ArrayList<Person> persons;

    

    public boolean add (Person person) {
        int i;
        boolean unique = true;
        for(i=0;i<persons.size();i++) {
            if(persons.get(i).equals(person)==true) {
                unique = false;
            }
        }
        if(unique==true) {
            persons.add(person);
            return true;
        }
        else {
            return false;
        }
    }

    public void sort () {
        Collections.sort(persons);
    }


    public String toString () {
        String string = " ";
        int i;
        for(i=0;i<persons.size();i++) {
            string+="/n" + "Person: " + persons.get(i);
        }
        return string;
    }
        




}
