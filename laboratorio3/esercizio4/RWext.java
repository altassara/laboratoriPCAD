package esercizio4;

public class RWext extends RWbasic {
    private int readers = 0;
    private boolean isWriting = false;
    private boolean hasRead = true;

    @Override
    public int read() {
        synchronized (this) {
            while (isWriting) {
                try {
                    System.out.println("ciao1");
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
            hasRead = true;
            if (readers == 0) {
                notifyAll();
            }
        }

        return value;
    }

    @Override
    public synchronized void write() {
        while (readers > 0 || isWriting || !hasRead) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        hasRead = false;
        isWriting = true;
        super.write();
        isWriting = false;
        notifyAll();
    }

}
