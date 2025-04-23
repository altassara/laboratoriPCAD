package esercizio2;

public class RWexclusive extends RWbasic {

    @Override
    public synchronized int read() {
        return super.read();
    }

    @Override
    public synchronized void write() {
        super.write();
    }
}
