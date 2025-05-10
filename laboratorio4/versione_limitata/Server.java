package laboratorio4.versione_limitata;

import java.net.*;

public class Server {
    public static void main(String[] args) {
        try {
            FIFOStructure fifo = new FIFOStructure();
            ServerSocket server = new ServerSocket(4242);
            while (true) {
                Socket socket = server.accept();
                ServerThread serv = new ServerThread(socket, fifo);
                Thread t = new Thread(serv);
                t.start();
            }
        } catch (Exception e) {
            System.out.println(e);
            e.printStackTrace();
        }
    }
}
