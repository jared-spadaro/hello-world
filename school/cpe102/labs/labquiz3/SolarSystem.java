import java.util.*;
import java.io.*;

public class SolarSystem {

    private ArrayList<Planet> planets;

    public SolarSystem () {
        planets = new ArrayList<Planet>();
    }

    public int numPlanets () {
        return planets.size();
    }

    public void add (Planet p) {
        int i;
        for(i=0;i<numPlanets();i++) {
            if(planets.get(i).getName().equals(p)) {
                return;
            }
        }
        planets.add(p);
    }

    public Planet find (String name) {
        int i;
        for(i=0;i<numPlanets();i++) {
            if(planets.get(i).getName().equals(name)) {
                 return planets.get(i);
            }
        }
        return null;
    }

    public void remove (String name) {
        int i;
        for(i=0;i<numPlanets();i++) {
            if(planets.get(i).getName().equals(name)) {
                 planets.remove(i);
            }
        }
    }

    public void writeToFile (String filename) {
        FileOutputStream output;
        PrintStream ps;
        int i;
        try {
            output = new FileOutputStream (filename);
            ps = new PrintStream (output);
            for(i=0;i<numPlanets();i++) {
                planets.get(i).writeToFile(ps);
            } 
        }
        catch (FileNotFoundException e) { }
        
    }

    public void readFromFile (String filename) {
        FileInputStream input;
        Scanner lineReader;
        Scanner parser;
        int i;
        try {
            input = new FileInputStream (filename);
            lineReader = new Scanner (input);
            while(lineReader.hasNextLine()) {
                parser = new Scanner (lineReader.nextLine());
                Planet p = new Planet();
                p.readFromFile(parser);
                planets.add(p);
            }
        }
        catch(FileNotFoundException e) { }
    }

    public String toString () {
        int i;
        String system = "";
        for(i=0;i<numPlanets();i++) {
            system+=planets.get(i).toString();
        }
        return system;
    }

    public void sortByName () {
    
    }

    public void sortByMass () {

    }


}
