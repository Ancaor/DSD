
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class ProgCliente {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String host = "";
		String idCliente = "";
		String passwordCliente = "";
		String accion = "";
		String hostName = "localhost";   // localhost
		String servidor = ""; 
		
		String menu_no_identificado = 
				"\n--------Menu----------\n"
					+"R : Registrarse\n"
					+"I : Identificarse\n"
					+"S : Salir\n"
				;
		String menu_identificado = 
				"\n--------Menu----------\n"
					+"D : Donar\n"
					+"T : Consultar total donado\n"
					+"B : Consultar subtotal donado en el servidor\n"
					+"S : Salir\n"
				;
		
		boolean exit = false;
		boolean identificado = false;
		Scanner entrada = new Scanner (System.in);
		
		if(System.getSecurityManager() == null) {
			System.setSecurityManager(new SecurityManager());
		}
		
		try {
            Registry registry = LocateRegistry.getRegistry(hostName);
            Servidor_I instancia_local = (Servidor_I) registry.lookup("Server1"); // asignacion predeterminada de Server1
            System.out.println("Invocando el objeto remoto");
            
            while(!exit) {
            	
            	if(!identificado) {
	            	
	            	System.out.println(menu_no_identificado);
	            	
	            	accion = entrada.nextLine();
	            	accion = accion.toUpperCase();
	            
	            	switch(accion) {
	            	case "R":
	            		System.out.println("Introduce el nombre de usuario:");
	            		idCliente = entrada.nextLine();
	            		System.out.println("Introduce la contrasena:");
	            		passwordCliente = entrada.nextLine();
	            		
	            		int resultadoRegistro = instancia_local.registrar(idCliente,passwordCliente);
	            		System.out.println(String.valueOf(resultadoRegistro));
	            		break;
	            	case "I":
	            		System.out.println("Introduce el nombre de usuario:");
	            		idCliente = entrada.nextLine();
	            		System.out.println("Introduce la contrasena:");
	            		passwordCliente = entrada.nextLine();
	            		
	            		servidor = instancia_local.identificar(idCliente, passwordCliente);
	            		
	            		if(!servidor.equals("")) {
	            			identificado = true;
	            			instancia_local = (Servidor_I) registry.lookup(servidor); // servidor asignado
	            			System.out.println("Bienvenido "+ idCliente);
	            		}else {
	            			identificado = false;
	            			System.out.println("No existe una cuenta con ese nombre de usuario.");
	            		}
	            		
	            		
	            		break;
	            	case "S":
	            		System.exit(0);
	            		break;
	            	}
	            	
            	}else {
            		
            		System.out.println(menu_identificado);
	            	
	            	accion = entrada.nextLine();
	            	accion = accion.toUpperCase();
	            	
	            	switch(accion) {
	            	case "D":
	            		System.out.println("Introduce la cantidad:");
	            		//idCliente = entrada.nextLine();
	            		double donado = instancia_local.donar(idCliente,Double.parseDouble(entrada.nextLine()));
	            		//int resultadoRegistro = instancia_local.registrar(idCliente,passwordCliente);
	            		System.out.println(String.valueOf(donado));
	            		break;
	            	case "I":
	            		
	            		break;
	            	case "S":
	            		System.exit(0);
	            		break;
	            	}
            		
            		
            		
            		
            	}
            	
            	
            
            
            }
            
            
            
            
            
            
            
            
        } catch (Exception e) {
            System.err.println("Ejemplo_I exception:");
            e.printStackTrace();
        }

	}

}
