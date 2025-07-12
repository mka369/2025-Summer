import java.io.*;
import java.net.*;

public class AsgTCPServer {
    public static void main(String[] args) {
        try {
            // Create a server socket
            ServerSocket server = new ServerSocket(53333);

            while (true) {
                // Wait for incoming connection requests
                Socket client = server.accept();

                // Create input and output streams
                PrintWriter out = new PrintWriter(client.getOutputStream(), true);
                BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));

                // Read data
                if (in.readLine().equals("hello TCP")) {
                    out.println("back at you TCP");
                }

                // Close the streams and socket
                in.close();
                out.close();
                client.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}