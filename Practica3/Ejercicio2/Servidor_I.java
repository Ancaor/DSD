import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Servidor_I extends Remote{
	
	public int registrar (String idCliente, String passwordCliente) throws RemoteException;
	
	public String identificar (String idCliente, String passwordCliente) throws RemoteException;
	
	public double donar(String idCliente, double cantidad) throws RemoteException;
	
	public double verTotal(String idCliente) throws RemoteException;
	
}
