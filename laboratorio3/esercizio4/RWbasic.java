package esercizio4;

public class RWbasic {
    private int data = 0;

    public int read() {
        return data;
    }

    public void write() {
        int tmp = data;
        try {
            Thread.sleep(3);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        tmp++;
        data = tmp;
    }
}
