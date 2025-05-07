package laboratorio4.versione_illimitata;

import java.net.*;
import java.io.*;

public class ServerThread implements Runnable {
    public Socket socket;
    public FIFOStructure fifo;

    public ServerThread(Socket s, FIFOStructure fifo) {
        this.socket = s;
        this.fifo = fifo;
    }

    public void run() {
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
            String mess = br.readLine();
            System.out.println("Message from the client:" + mess);

            if (mess.equals("producer")) {
                pw.println("okprod");
                pw.flush();
                mess = br.readLine();

                fifo.addString(mess);
            } else if (mess.equals("consumer")) {
                pw.println("okcons");
                pw.flush();
                mess = br.readLine();

                String recieved = fifo.removeString();
                pw.println("String removed:" + recieved);
                pw.flush();

            } else {
                System.out.println("Invalid message");
            }

            Thread.sleep(10000);
            br.close();
            pw.close();
            socket.close();
        } catch (Exception e) {
            System.out.println(e);
            e.printStackTrace();
        }
    }
}
