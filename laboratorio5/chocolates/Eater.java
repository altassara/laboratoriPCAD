package laboratorio5.chocolates;

public class Eater extends Thread {
    private final int id;
    private final ChocolateBox box;

    public Eater(int id, ChocolateBox box) {
        this.id = id;
        this.box = box;
    }

    public void run() {
        try {
            while (true) {
                box.take(id);
                Thread.sleep((long) (Math.random() * 1500));
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
