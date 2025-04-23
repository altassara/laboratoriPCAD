package esercizio1;

public class Reader implements Runnable {
    private RWbasic rw;
    private String name;

    public Reader(RWbasic rw, String name) {
        this.rw = rw;
        this.name = name;
    }

    @Override
    public void run() {
        int value = rw.read();
        System.out.println("Reader " + name + " read value: " + value);
    }
}
