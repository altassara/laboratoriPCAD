package laboratorio5.chocolates;

public class PastryChef extends Thread {
    private final ChocolateBox box;

    public PastryChef(ChocolateBox box) {
        this.box = box;
    }

    public void run() {
        try {
            while (true) {
                box.fill();
                Thread.sleep(1000);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
