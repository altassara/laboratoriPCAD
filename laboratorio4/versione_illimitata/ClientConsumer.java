package laboratorio4.versione_illimitata;

import java.net.*;
import java.io.*;

public class ClientConsumer {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 4242);
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
            pw.println("consumer");
            pw.flush();
            String mess = br.readLine();
            System.out.println("Message from the server:" + mess);
            if (mess.equals("okcons")) {
                pw.println("FORZA GENOA");
                pw.flush();

                mess = br.readLine();
                System.out.println("Message from the server:" + mess);
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
