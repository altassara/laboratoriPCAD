package esercizio2;

public class Reader implements Runnable {
    private RWexclusive rw;
    private String name;

    public Reader(RWexclusive rw, String name) {
        this.rw = rw;
        this.name = name;
    }

    @Override
    public void run() {
        int value = rw.read();
        System.out.println("Reader " + name + " read value: " + value);
    }
}
