import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Replica_I extends Remote{

	public int numeroClientes () throws RemoteException;
	public boolean clienteRegistrado (String idCliente) throws RemoteException;
	public void registrarCliente(String idCliente, String passwordCliente) throws RemoteException;
	public boolean identificarCliente(String idCliente, String passwordCliente) throws RemoteException;
	public Replica_I getReplica (String host,String nombreReplica)throws RemoteException;
}
