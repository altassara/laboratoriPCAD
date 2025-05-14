package laboratorio5.swimmingPool;

import java.util.concurrent.Semaphore;

public class SmartSwimmers implements Runnable {
    private int id;
    private Semaphore lockers;
    private Semaphore changingRooms;

    public SmartSwimmers(int id, Semaphore lockers, Semaphore changingRooms) {
        this.id = id;
        this.lockers = lockers;
        this.changingRooms = changingRooms;
    }

    public void run() {
        try {

            System.out.println("Swimmer " + id + " is waiting for a locker.");
            lockers.acquire();
            System.out.println("Swimmer " + id + " has acquired a locker.");

            System.out.println("Swimmer " + id + " is waiting for a changing room.");
            changingRooms.acquire();
            System.out.println("Swimmer " + id + " has entered the changing room.");

            // Simulate time spent in the changing room
            Thread.sleep((long) (Math.random() * 1000));

            System.out.println("Swimmer " + id + " has left the changing room.");

            // Simulate time spent putting clothes in the locker
            Thread.sleep((long) (Math.random() * 1000));

            System.out.println("Swimmer " + id + " is giving back changing room keys");
            changingRooms.release();

            // Simulate time spent in the pool
            Thread.sleep((long) (Math.random() * 5000));

            System.out.println("Swimmer " + id + " is waiting for a changing room.");
            changingRooms.acquire();

            // Simulate time spent in the changing room
            Thread.sleep((long) (Math.random() * 1000));

            System.out.println("Swimmer " + id + " has left the changing room.");
            changingRooms.release();

            System.out.println("Swimmer " + id + " is leaving the locker.");
            lockers.release();

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}
