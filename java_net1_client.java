import java.net.*;
import java.io.*;

public class java_net1_client
{
	public static void main(String args[])
	{
		try
		{
			String servername = args[0];
			int port = Integer.parseInt(args[1]);
			
			Socket client_to_server = new Socket(servername, port);
			
			System.out.println("Hello server " + client_to_server.getRemoteSocketAddress());
			
			DataOutputStream out = new DataOutputStream(client_to_server.getOutputStream());
			out.writeUTF("Hello, this is client: " + client_to_server.getLocalSocketAddress());
			
			DataInputStream in = new DataInputStream(client_to_server.getInputStream());
			
			System.out.println("Server says: " + in.readUTF());
			
			client_to_server.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}
