package 实验四.实验四_RMI_v1;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IHello extends Remote {

    String say(HelloTask task) throws RemoteException;

}
