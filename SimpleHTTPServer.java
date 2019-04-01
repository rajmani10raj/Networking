import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

/**
 * Java program to create a simple HTTP Server to demonstrate how to use
 * ServerSocket and Socket class.
 * 
 * @author Javin Paul
 */
public class SimpleHTTPServer {

    public static void main(String args[]) throws IOException {

        ServerSocket server = new ServerSocket(8082);
        System.out.println("Listening for connection on port 8080 ....");
        while (true) {
            try (Socket socket = server.accept()) {

                String res = "From server.";
                
                String httpResponse = "HTTP/1.1 200 OK\r\n\r\n" + res;
                socket.getOutputStream().write(httpResponse.getBytes("UTF-8"));
            }
        }
    }

}