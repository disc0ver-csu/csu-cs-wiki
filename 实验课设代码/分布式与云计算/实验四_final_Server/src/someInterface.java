import java.rmi.Remote;
import java.rmi.RemoteException;

public interface someInterface extends Remote {

    String sayHello(String name) throws RemoteException;

}