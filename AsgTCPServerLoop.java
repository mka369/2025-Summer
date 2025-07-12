import java.io.*;
import java.net.*;

public class AsgTCPServerLoop {
    public static void main(String[] args) {
        while (true) {
            try {
                // Create a server socket
                ServerSocket server = new ServerSocket(53333);
                
                // Wait for incoming connection requests
                Socket client = server.accept();

                // Create input and output streams
                PrintWriter out = new PrintWriter(client.getOutputStream(), true);
                BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));

                // Read data
                for (int i = 0; i < 1000; i++) {
                    String data = in.readLine();
                }
                // Send response
                out.println("back at you TCP");

                // Close the streams and socket
                in.close();
                out.close();
                client.close();
            }

            catch (IOException e) {
            e.printStackTrace();
            }
        }
    }
}