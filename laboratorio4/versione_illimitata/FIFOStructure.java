package laboratorio4.versione_illimitata;

import java.util.ArrayList;

public class FIFOStructure {

    private ArrayList<String> receivedStrings = new ArrayList<>();

    public synchronized void addString(String str) {
        receivedStrings.add(str);
        notifyAll();
        System.out.println("Added string: " + str);
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
        System.out.println("Removed string: " + str);
        return str;
    }

}
