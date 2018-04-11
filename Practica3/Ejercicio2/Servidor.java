
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;
import java.util.Map;

public class Servidor implements Servidor_I,Replica_I {
	
	private Map<String,Cliente> clientes;
	
	private float subtotal;
	private String replica;
	private String nombre;
	
	Servidor(String nombre,String replica){
		clientes  = new HashMap();
		subtotal=0;
		this.replica=replica;
		this.nombre = nombre;
		
	}
	
	

	@Override
	public int registrar(String idCliente,String passwordCliente) throws RemoteException {
		
		if(this.clienteRegistrado(idCliente)) {
			return 0;
		}else {
			
			Replica_I replica = this.getReplica("localhost", this.replica);
			
			if(replica.clienteRegistrado(idCliente)) {
				return 0;
			}else {
				if(this.numeroClientes() < replica.numeroClientes())
					this.registrarCliente(idCliente, passwordCliente);
				else replica.registrarCliente(idCliente, passwordCliente);
				
				return 1;
			}	
			
		}
	}

	@Override
	public String identificar(String idCliente, String passwordCliente) throws RemoteException {
		
		if(this.clienteRegistrado(idCliente)) {
			if(this.identificarCliente(idCliente, passwordCliente))
				return this.nombre;
		}else {
			Replica_I replica = this.getReplica("localhost", this.replica);
			
			if(replica.clienteRegistrado(idCliente))
				if(replica.identificarCliente(idCliente, passwordCliente))
					return this.replica;
			
		}
		
		
		
		
		
		return "";
	}
	
	@Override
	public double donar(String idCliente,double cantidad) throws RemoteException {
		
		clientes.get(idCliente).addDonacion(cantidad);
		subtotal += cantidad;
		System.out.println("El cliente " + idCliente + "ha donado: " + cantidad);
		
		return clientes.get(idCliente).getDonado();
	}

	@Override
	public double verTotal(String idCliente) throws RemoteException {
		
		if(clientes.get(idCliente).getDonado() != 0) {
			Replica_I replica = this.getReplica("localhost", this.replica); 
			
			double total_donado_replica = replica.donacionesReplica();
			double total_donado = this.donacionesReplica();
			
			return (total_donado + total_donado_replica);
			
			
		}else return -1;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            String nombreServidor = "Server1";
            String nombreReplica = "Server2";
            Servidor_I prueba = new Servidor(nombreServidor,nombreReplica);
            Servidor_I stub =
                (Servidor_I) UnicastRemoteObject.exportObject(prueba, 0);
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind(nombreServidor, stub);
            System.out.println("Server bound");
        } catch (Exception e) {
            System.err.println("Server exception:");
            e.printStackTrace();
        }

	}

	/////////////////Metodos entre servidores//////////////////////////


	@Override
	public int numeroClientes() throws RemoteException {
		return clientes.size();
	}



	@Override
	public void registrarCliente(String idCliente, String passwordCliente) throws RemoteException {
		clientes.put(idCliente, new Cliente(idCliente,passwordCliente));
		System.out.println("Cliente " + idCliente + " registrado en " + this.nombre);
	}



	@Override
	public boolean clienteRegistrado(String idCliente) throws RemoteException {
		return clientes.containsKey(idCliente);
	}



	@Override
	public Replica_I getReplica(String host, String nombreReplica) throws RemoteException {
		// TODO Auto-generated method stub
		
		Replica_I replica = null;
		
		try {
            Registry registry = LocateRegistry.getRegistry(host);
            replica = (Replica_I) registry.lookup(nombreReplica); 
		}catch (Exception e) {
            System.err.println("Servidor exception:");
            e.printStackTrace();
        }
		
		return replica;
	}



	@Override
	public boolean identificarCliente(String idCliente, String passwordCliente) throws RemoteException {
		return clientes.get(idCliente).getPassword().equals(passwordCliente);
	}



	@Override
	public double donacionesReplica() throws RemoteException {
		return subtotal;
	}

}
