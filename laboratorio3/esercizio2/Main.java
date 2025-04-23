package esercizio2;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        RWexclusive sharedData = new RWexclusive();

        List<Thread> threads = new ArrayList<>();

        for (int i = 0; i < 50; i++) {
            Thread readerThread = new Thread(new Reader(sharedData, "R" + i));
            threads.add(readerThread);
        }

        for (int i = 0; i < 50; i++) {
            Thread writerThread = new Thread(new Writer(sharedData, "W" + i));
            threads.add(writerThread);
        }

        for (Thread t : threads) {
            t.start();
        }

        for (Thread t : threads) {
            t.join();
        }

        System.out.println("Final value of data: " + sharedData.read());
    }
}
