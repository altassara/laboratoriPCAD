package laboratorio5.swimmingPool;

import java.util.concurrent.Semaphore;

public class SwimmingPools {
    private static final int NUM_LOCKERS = 5;
    private static final int NUM_CHANGING_ROOMS = 10;
    private static final int NUM_SWIMMERS = 20;

    private static Semaphore lockers;
    private static Semaphore changingRooms;

    public static void main(String[] args) {
        lockers = new Semaphore(NUM_LOCKERS);
        changingRooms = new Semaphore(NUM_CHANGING_ROOMS);

        for (int i = 0; i < NUM_SWIMMERS; i++) {
            new Thread(new SmartSwimmers(i, lockers, changingRooms)).start();
        }
    }

}
