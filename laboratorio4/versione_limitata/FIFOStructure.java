package laboratorio4.versione_limitata;

import java.util.ArrayList;

public class FIFOStructure {

    private static final int MAX_SIZE = 3;
    private ArrayList<String> receivedStrings = new ArrayList<>();

    public synchronized String addString(String str) {
        System.out.println("Size " + receivedStrings.size());
        while (receivedStrings.size() >= MAX_SIZE) {
            System.out.println("Queue is full, waiting to add: " + str);
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("Waiting interrupted: " + e);
            }
        }
        if (!receivedStrings.add(str))
            System.out.println("Failed to add string: " + str);

        notifyAll();
        System.out.println("Added string: " + str);

        return str;
    }

    public synchronized String removeString() {
        while (receivedStrings.isEmpty()) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println("Waiting interrupted: " + e);
            }
        }
        String str = receivedStrings.remove(0);
        notifyAll();
        System.out.println("Removed string: " + str);
        return str;
    }

}
