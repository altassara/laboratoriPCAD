package laboratorio5.chocolates;

public class Main {
    public static void main(String[] args) {
        ChocolateBox box = new ChocolateBox();

        PastryChef chef = new PastryChef(box);
        chef.start();

        for (int i = 1; i <= 3; i++) {
            new Eater(i, box).start();
        }
    }
}
