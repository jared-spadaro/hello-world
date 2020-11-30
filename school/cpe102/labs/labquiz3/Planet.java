import java.util.*;
import java.io.*;

public class Planet implements Comparable<Planet> {

    private String name;
    private double mass;
    private double diameter;
    private double day;
    private int moons;

    public Planet () {

    }

    public Planet (String name, double mass, double diameter, double day, int moons) {
        this.name = name;
        this.mass = mass;
        this.diameter = diameter;
        this.day = day;
        this.moons = moons;
    }

    public String getName () {
        return name;
    }

    public double getMass () {
        return mass;
    }

    public void writeToFile (PrintStream ps) {
        ps.println (name + " " + mass + " " + diameter + " " + day
        + " " + moons);
    }

    public void readFromFile (Scanner s) {
        name = s.next();
        mass = s.nextDouble();
        diameter = s.nextDouble();
        day = s.nextDouble();
        moons = s.nextInt();
    }

    public String toString () {
        String s = "Name: " + name + ", Mass: " + mass + ", Diameter: " + diameter + ", Day: "
        + day + ", Moons: " + moons + "\n" + "";
        //s.trim();
        s = s.replace("\n","");
        return s;
    }

    public int compareTo (Planet p) {
        return name.compareTo(p.name);
    }

}
