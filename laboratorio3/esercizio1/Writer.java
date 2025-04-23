package esercizio1;

public class Writer implements Runnable {
    private RWbasic rw;
    private String name;

    public Writer(RWbasic rw, String name) {
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
