package esercizio4;

public class Writer implements Runnable {
    private RWext rw;
    private String name;

    public Writer(RWext rw, String name) {
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
