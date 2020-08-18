package Server;

import java.net.*;

import Interface.ServerInterface;
import utilities.*;

public class Server{
	ServerSocket ss;

	public Server(int serverPort){
		try {
			this.ss = new ServerSocket(serverPort);
		} catch (Exception e){System.out.println(e.getMessage());}
	}

	public static void main(String[] args) throws Exception{
		try{
			Server server = new Server(9888);
			ServerOperations operator = new ServerOperations(server.ss);

			while(true){
				Socket s = server.ss.accept();
				ServerThread thread = new ServerThread(s, server.ss, operator);
				thread.start();
			}

		} catch (Exception e){e.printStackTrace();}

	}
}
