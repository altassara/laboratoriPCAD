package esercizio2;

public class Writer implements Runnable {
    private RWexclusive rw;
    private String name;

    public Writer(RWexclusive rw, String name) {
        this.rw = rw;
        this.name = name;
    }

    @Override
    public void run() {
        System.out.println("Writer " + name + " is writing...");
        rw.write();
        System.out.println("Writer " + name + " finished writing.");
    }
}
