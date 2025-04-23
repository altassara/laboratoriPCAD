package esercizio3;

public class RW extends RWbasic {
    int readers = 0;
    boolean isWriting = false;

    @Override
    public int read() {
        synchronized (this) {
            while (isWriting) {
                try {
                    wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            readers++;
        }

        int value = super.read();

        synchronized (this) {
            readers--;
            if (readers == 0) {
                notifyAll();
            }
        }

        return value;
    }

    @Override
    public synchronized void write() {
        while (readers > 0 || isWriting) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        isWriting = true;
        super.write();
        isWriting = false;
        notifyAll();
    }

}
