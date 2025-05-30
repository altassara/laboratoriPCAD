package laboratorio4.versione_illimitata;

import java.net.*;
import java.io.*;

public class ClientProducer {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 4242);
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
            pw.println("producer");
            pw.flush();
            String mess = br.readLine();
            System.out.println("Message from the server:" + mess);
            if (mess.equals("okprod")) {
                pw.println("FORZA GENOA");
                pw.flush();
            } else {
                System.out.println("Invalid message");
            }
            pw.close();
            br.close();
            socket.close();
        } catch (Exception e) {
            System.out.println(e);
            e.printStackTrace();
        }
    }
}
