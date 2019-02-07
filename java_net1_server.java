import java.net.*;
import java.io.*;

public class java_net1_server extends Thread
{
	private ServerSocket serversocket;
	
	public java_net1_server(int port) throws IOException
	{
		serversocket = new ServerSocket(port);
		serversocket.setSoTimeout(100000);
	}
	
	public void run()
	{
		while(true)
		{
			try
			{
				System.out.println("Hello and welcome to server" + serversocket.getLocalPort() + "waiting ...");
				Socket server_to_client = serversocket.accept();
				
				System.out.println("Hey there" + server_to_client.getRemoteSocketAddress());
				
				DataInputStream in = new DataInputStream(server_to_client.getInputStream());
				System.out.println(in.readUTF());
				
				DataOutputStream out = new DataOutputStream(server_to_client.getOutputStream());
				out.writeUTF("See you later" + server_to_client.getLocalSocketAddress());
				
				server_to_client.close();
			}
			catch(SocketTimeoutException s)
			{
				System.out.println("Socket Time out");
				break;
			}
			
			catch(IOException s)
			{
				s.printStackTrace();
				break;
			}
		}
	}


	
	public static void main(String args[]) throws IOException
	{
		System.out.println("Hello, we are in server-client java program");
		int port = Integer.parseInt(args[0]);
		
		Thread t = new java_net1_server(port);
		t.start();
	}
}
