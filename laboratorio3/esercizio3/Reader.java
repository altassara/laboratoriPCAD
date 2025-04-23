package esercizio3;

public class Reader implements Runnable {
    private RW rw;
    private String name;

    public Reader(RW rw, String name) {
        this.rw = rw;
        this.name = name;
    }

    @Override
    public void run() {
        System.out.println("Reader " + name + " is reading...");
        int value = rw.read();
        System.out.println("Reader " + name + " read value: " + value);
    }
}
