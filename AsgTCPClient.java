import java.io.*;
import java.net.*;

public class AsgTCPClient {
    public static void main(String[] args) {
        try {
            // Establish a connection
            Socket socket = new Socket("localhost", 53333);

            // Create input and output streams
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            // Send data
            String data = "hello TCP";
            long startTime = System.nanoTime();
            out.println(data);
            String response = in.readLine();
            long endTime = System.nanoTime();

            // Calculate the round-trip time
            long rtt = endTime - startTime;
            System.out.println("Round-trip time: " + rtt + " ns");

            // Close the streams and socket
            in.close();
            out.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}