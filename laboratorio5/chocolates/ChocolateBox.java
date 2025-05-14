package laboratorio5.chocolates;

public class ChocolateBox {
    private final int capacity = 5;
    private int chocolates = 0;

    public synchronized void fill() throws InterruptedException {
        while (chocolates > 0) {
            wait();
        }
        chocolates = capacity;
        System.out.println("👨‍🍳 PastryChef filled the box with " + capacity + " chocolates.");
        notifyAll();
    }

    public synchronized void take(int id) throws InterruptedException {
        while (chocolates == 0) {
            wait();
        }
        chocolates--;
        System.out.println("🍫 Eater " + id + " took a chocolate. Left: " + chocolates);
        if (chocolates == 0) {
            notifyAll();
        }
    }
}
